import assert from 'node:assert/strict';
import http from 'node:http';
import { createReadStream } from 'node:fs';
import { access, mkdir, writeFile } from 'node:fs/promises';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { chromium } from 'playwright';

const directory = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(process.env.SR_BROWSER_BIN || path.join(directory, '../../Platform/Emscripten/Bin'));
const output = path.resolve(process.env.SR_BROWSER_REPORT || path.join(directory, 'report'));
await mkdir(output, { recursive: true });
const types = { '.html': 'text/html', '.js': 'text/javascript', '.wasm': 'application/wasm', '.data': 'application/octet-stream' };
const server = http.createServer(async (request, response) => {
    try {
        const relative = decodeURIComponent(new URL(request.url, 'http://localhost').pathname).replace(/^\/+/, '');
        const file = path.resolve(root, relative || 'SREngine.html');
        if (!file.startsWith(root + path.sep)) { response.writeHead(403).end(); return; }
        await access(file);
        response.writeHead(200, { 'Content-Type': types[path.extname(file)] || 'application/octet-stream', 'Cache-Control': 'no-store' });
        createReadStream(file).on('error', () => response.destroy()).pipe(response);
    } catch { response.writeHead(404).end(); }
});
await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
const url = `http://127.0.0.1:${server.address().port}/SREngine.html`;
const browser = await chromium.launch({ args: JSON.parse(process.env.SR_WEBGPU_ARGS || '["--enable-unsafe-webgpu","--use-angle=swiftshader"]') })
    .catch(async error => { await new Promise(resolve => server.close(resolve)); throw error; });
const context = await browser.newContext({ viewport: { width: 960, height: 640 }, deviceScaleFactor: 2 });
const page = await context.newPage();
const errors = [];
const logs = [];
page.on('pageerror', error => errors.push(String(error)));
page.on('console', message => {
    const text = message.text(); logs.push(`${message.type()}: ${text}`);
    if (/UncapturedErrorCallback|WGSL shader compilation failed|WebGPU.*\[Validation\]/i.test(text)) errors.push(text);
});
try {
    // Failure must be visible, with no endless startup wait.
    await page.addInitScript(() => Object.defineProperty(navigator, 'gpu', { value: undefined, configurable: true }));
    await page.goto(url);
    await page.waitForFunction(() => !!globalThis.srEngineFatalError);
    assert.match(await page.locator('#sr-status').textContent(), /WebGPU/);
    await page.close();
    const running = await context.newPage();
    running.on('pageerror', error => errors.push(String(error)));
    running.on('console', message => {
        const text = message.text(); logs.push(`${message.type()}: ${text}`);
        if (/UncapturedErrorCallback|WGSL shader compilation failed|WebGPU.*\[Validation\]/i.test(text)) errors.push(text);
    });
    await running.goto(url);
    await running.waitForFunction(() => globalThis.srEngineModule?.srSubmittedFrames >= 5, null, { timeout: 120000 });
    assert.equal(await running.evaluate(() => globalThis.srEngineFatalError || ''), '');
    const sizes = await running.locator('#srengine-canvas').evaluate(canvas => ({ width: canvas.width, css: canvas.clientWidth }));
    assert.ok(sizes.width > sizes.css, 'High-DPI backing store must exceed logical size');
    await running.setViewportSize({ width: 800, height: 600 });
    await running.waitForFunction(() => document.querySelector('#srengine-canvas').width === 1600);
    await running.evaluate(async () => {
        const fs = globalThis.srEngineModule.FS;
        fs.writeFile('/Persistent/Data/browser-smoke.txt', 'persists-after-reload');
        await new Promise((resolve, reject) => fs.syncfs(false, error => error ? reject(error) : resolve()));
    });
    await running.reload();
    await running.waitForFunction(() => globalThis.srEngineModule?.srSubmittedFrames >= 5, null, { timeout: 120000 });
    assert.equal(await running.evaluate(() => globalThis.srEngineModule.FS.readFile('/Persistent/Data/browser-smoke.txt', { encoding: 'utf8' })), 'persists-after-reload');
    await running.screenshot({ path: path.join(output, 'frame.png') });
    assert.deepEqual(errors, []);
} finally {
    await writeFile(path.join(output, 'console.log'), logs.concat(errors).join('\n'));
    await browser.close();
    await new Promise(resolve => server.close(resolve));
}
