import assert from 'node:assert/strict';
import http from 'node:http';
import { createReadStream, writeFileSync, writeSync } from 'node:fs';
import { access, mkdir, writeFile } from 'node:fs/promises';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { chromium } from 'playwright';

const directory = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(process.env.SR_BROWSER_BIN || path.join(directory, '../../Platform/Emscripten/Bin'));
const output = path.resolve(process.env.SR_BROWSER_REPORT || path.join(directory, 'report'));
const errors = [];
const logs = [];
const log = (message, isError = false) => {
    const line = `${new Date().toISOString()} ${message}`;
    logs.push(line);
    writeSync(isError ? 2 : 1, line + '\n');
};
const watchdog = setTimeout(() => {
    const message = 'Browser smoke test exceeded the 8 minute limit (including cleanup).';
    log(message, true);
    try { writeFileSync(path.join(output, 'console.log'), logs.concat(errors, message).join('\n')); }
    catch (error) { log(String(error.stack || error), true); }
    process.exit(1);
}, 8 * 60 * 1000);
watchdog.unref();
await mkdir(output, { recursive: true });
const types = { '.html': 'text/html', '.js': 'text/javascript', '.wasm': 'application/wasm', '.data': 'application/octet-stream' };
const server = http.createServer(async (request, response) => {
    try {
        const relative = decodeURIComponent(new URL(request.url, 'http://localhost').pathname).replace(/^\/+/, '');
        if (relative === '__webgpu_probe') {
            response.writeHead(200, { 'Content-Type': 'text/html' }).end('<!doctype html><title>WebGPU probe</title>');
            return;
        }
        const file = path.resolve(root, relative || 'SREngine.html');
        if (!file.startsWith(root + path.sep)) {
            log(`HTTP 403: ${request.url}`, true);
            response.writeHead(403).end(); return;
        }
        await access(file);
        response.writeHead(200, { 'Content-Type': types[path.extname(file)] || 'application/octet-stream', 'Cache-Control': 'no-store' });
        createReadStream(file).on('error', error => {
            log(`HTTP stream error: ${request.url}: ${error.stack || error}`, true);
            response.destroy();
        }).pipe(response);
    } catch (error) {
        log(`HTTP 404: ${request.url}: ${error.stack || error}`, true);
        response.writeHead(404).end();
    }
});
await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
const url = `http://127.0.0.1:${server.address().port}/SREngine.html`;
const defaultArgs = [
    '--enable-unsafe-webgpu',
    '--use-webgpu-adapter=swiftshader',
    // Windows WebGPU initialization queries a D3D11 device from ANGLE.
    process.platform === 'win32' ? '--use-angle=d3d11-warp' : '--use-angle=swiftshader',
    '--enable-unsafe-swiftshader'
];
const launchArgs = process.env.SR_WEBGPU_ARGS ? JSON.parse(process.env.SR_WEBGPU_ARGS) : defaultArgs;
log(`Chromium channel: chromium; host platform: ${process.platform}`);
log(`Chromium arguments: ${JSON.stringify(launchArgs)}`);
const browser = await chromium.launch({ channel: 'chromium', headless: true, args: launchArgs })
    .catch(async error => { await new Promise(resolve => server.close(resolve)); throw error; });
const context = await browser.newContext({ viewport: { width: 960, height: 640 }, deviceScaleFactor: 2 });
context.setDefaultTimeout(30000);
context.setDefaultNavigationTimeout(120000);
context.on('page', page => {
    page.on('pageerror', error => {
        const text = String(error.stack || error);
        errors.push(text);
        log(`[browser pageerror] ${text}`, true);
    });
    page.on('console', message => {
        const text = message.text();
        const location = message.location();
        log(`[browser ${message.type()}] ${text} (${location.url}:${location.lineNumber}:${location.columnNumber})`, message.type() === 'error');
        if (/UncapturedErrorCallback|WGSL shader compilation failed|WebGPU.*\[Validation\]/i.test(text)) errors.push(text);
    });
    page.on('requestfailed', request => log(`[browser requestfailed] ${request.method()} ${request.url()}: ${request.failure()?.errorText}`, true));
    page.on('response', response => {
        if (response.status() >= 400) log(`[browser HTTP ${response.status()}] ${response.url()}`, true);
    });
    page.on('crash', () => {
        const message = `[browser crash] ${page.url()}`;
        errors.push(message);
        log(message, true);
    });
});
browser.on('disconnected', () => log('Chromium disconnected.'));
const page = await context.newPage();
try {
    log('Checking WebGPU adapter and device before engine startup...');
    log(`Chromium version: ${browser.version()}`);
    await page.goto(new URL('/__webgpu_probe', url).href);
    const gpu = await page.evaluate(() => Promise.race([
        (async () => {
            if (!navigator.gpu) throw new Error('WebGPU API is unavailable in this runner');
            const adapter = await navigator.gpu.requestAdapter();
            if (!adapter) throw new Error('WebGPU requestAdapter returned null in this runner');
            const info = adapter.info || await adapter.requestAdapterInfo?.() || {};
            const device = await adapter.requestDevice();
            try {
                const encoder = device.createCommandEncoder();
                device.queue.submit([encoder.finish()]);
                await device.queue.onSubmittedWorkDone();
                return { vendor: info.vendor, architecture: info.architecture,
                    device: info.device, description: info.description, features: [...adapter.features] };
            } finally { device.destroy(); }
        })(),
        new Promise((_, reject) => setTimeout(() => reject(new Error('WebGPU adapter/device probe timed out after 30 seconds')), 30000))
    ]));
    log(`WebGPU probe passed: ${JSON.stringify(gpu)}`);
    log('Checking startup failure without WebGPU...');
    // Failure must be visible, with no endless startup wait.
    await page.addInitScript(() => Object.defineProperty(navigator, 'gpu', { value: undefined, configurable: true }));
    await page.goto(url);
    await page.waitForFunction(() => !!globalThis.srEngineFatalError);
    assert.match(await page.locator('#sr-status').textContent(), /WebGPU/);
    await page.close();
    log('Checking WebGPU rendering...');
    const running = await context.newPage();
    await running.goto(url);
    await running.waitForFunction(() => !!globalThis.srEngineFatalError || globalThis.srEngineModule?.srSubmittedFrames >= 5, null, { timeout: 120000 });
    assert.equal(await running.evaluate(() => globalThis.srEngineFatalError || ''), '');
    const sizes = await running.locator('#srengine-canvas').evaluate(canvas => ({ width: canvas.width, css: canvas.clientWidth }));
    assert.ok(sizes.width > sizes.css, 'High-DPI backing store must exceed logical size');
    await running.setViewportSize({ width: 800, height: 600 });
    log('Checking canvas resize...');
    await running.waitForFunction(() => document.querySelector('#srengine-canvas').width === 1600);
    log('Checking persistent storage write and sync...');
    await running.evaluate(async () => {
        const fs = globalThis.srEngineModule.FS;
        fs.writeFile('/Persistent/Data/browser-smoke.txt', 'persists-after-reload');
        await new Promise((resolve, reject) => fs.syncfs(false, error => error ? reject(error) : resolve()));
    });
    log('Checking persistence after reload...');
    await running.reload();
    await running.waitForFunction(() => !!globalThis.srEngineFatalError || globalThis.srEngineModule?.srSubmittedFrames >= 5, null, { timeout: 120000 });
    assert.equal(await running.evaluate(() => globalThis.srEngineFatalError || ''), '');
    assert.equal(await running.evaluate(() => globalThis.srEngineModule.FS.readFile('/Persistent/Data/browser-smoke.txt', { encoding: 'utf8' })), 'persists-after-reload');
    await running.screenshot({ path: path.join(output, 'frame.png') });
    assert.deepEqual(errors, []);
    log('Browser smoke checks passed.');
} catch (error) {
    log(String(error.stack || error), true);
    errors.push(String(error.stack || error));
    throw error;
} finally {
    try {
        log('Closing Chromium...');
        await browser.close();
    } finally {
        try {
            log('Closing HTTP server...');
            server.closeAllConnections();
            await new Promise(resolve => server.close(resolve));
            log('Browser smoke cleanup finished.');
        } finally {
            await writeFile(path.join(output, 'console.log'), logs.concat(errors).join('\n'));
        }
    }
}
clearTimeout(watchdog);
