// Linked with --pre-js so filesystem and audio integration also works in an embedded host.
(() => {
    const listeners = [];
    const listen = (target, event, callback, options) => {
        target.addEventListener(event, callback, options);
        listeners.push(() => target.removeEventListener(event, callback, options));
    };
    const emit = (name, detail) => globalThis.dispatchEvent(new CustomEvent(name, { detail }));
    let flushing = false;
    let flushAgain = false;
    let storageReady = false;
    let dirty = false;
    let importId = 0;
    const downloads = new Set();
    const clipboard = { text: '' };
    const gameText = [];
    const guiText = [];
    const textInput = document.createElement('textarea');
    textInput.dataset.srEngineInput = '1';
    textInput.setAttribute('aria-label', 'Engine text input');
    textInput.autocomplete = 'off';
    textInput.style.cssText = 'position:fixed;left:0;bottom:0;width:1px;height:1px;opacity:0;pointer-events:none;font-size:16px';
    document.body.appendChild(textInput);
    let wantsText = false;
    let compositionCommit = null;
    const enqueueText = text => {
        if (!text) return;
        // Bound queued input when the game is paused or the GUI is disabled.
        for (const queue of [gameText, guiText]) {
            queue.push(text);
            if (queue.length > 64) queue.shift();
        }
    };
    listen(textInput, 'input', event => {
        if (!event.isComposing) {
            if (textInput.value !== compositionCommit) enqueueText(textInput.value);
            compositionCommit = null;
            textInput.value = '';
        }
    });
    listen(textInput, 'compositionstart', () => { Module['srComposing'] = true; });
    listen(textInput, 'compositionend', event => {
        Module['srComposing'] = false;
        compositionCommit = typeof event.data === 'string' ? event.data : textInput.value;
        enqueueText(compositionCommit);
        textInput.value = '';
        setTimeout(() => { compositionCommit = null; }, 0);
    });
    listen(document, 'keydown', event => {
        if (!wantsText && event.key.length === 1 && !event.ctrlKey && !event.metaKey && !event.altKey
            && document.activeElement === canvas) {
            gameText.push(event.key);
            if (gameText.length > 64) gameText.shift();
        }
    });
    Module['srSetTextInput'] = enabled => {
        wantsText = !!enabled;
        Module['srTextInputActive'] = wantsText;
        if (!wantsText && document.activeElement === textInput) {
            textInput.blur(); document.querySelector('#srengine-canvas')?.focus({preventScroll: true});
        }
        if (wantsText && (document.activeElement === document.querySelector('#srengine-canvas') || document.activeElement === document.body)) {
            textInput.focus({preventScroll: true});
        }
    };
    Module['srShowKeyboard'] = () => textInput.focus({preventScroll: true});
    Module['srPollText'] = (pointer, capacity, gui) => {
        const queue = gui ? guiText : gameText;
        if (!queue.length) return 0;
        // Split only at Unicode code point boundaries.
        const characters = Array.from(queue[0]);
        let text = '';
        while (characters.length && lengthBytesUTF8(text + characters[0]) < capacity) text += characters.shift();
        if (characters.length) queue[0] = characters.join(''); else queue.shift();
        stringToUTF8(text, pointer, capacity);
        return lengthBytesUTF8(text);
    };
    const canvas = document.querySelector('#srengine-canvas');
    if (canvas) {
        const touches = new Map();
        listen(globalThis, 'blur', () => { touches.clear(); Module['srTouches'] = []; });
        const forwardTouch = event => {
            if (event.pointerType !== 'touch' && event.pointerType !== 'pen') return;
            const isEnd = event.type === 'pointerup' || event.type === 'pointercancel';
            if (isEnd) touches.delete(event.pointerId);
            else touches.set(event.pointerId, {id: event.pointerId, x: event.clientX, y: event.clientY, pressure: event.pressure});
            Module['srTouches'] = Array.from(touches.values());
            if (!event.isPrimary) return;
            if (event.type === 'pointerdown') canvas.setPointerCapture(event.pointerId);
            const type = event.type === 'pointerdown' ? 'mousedown' : isEnd ? 'mouseup' : 'mousemove';
            canvas.dispatchEvent(new MouseEvent(type, {bubbles: true, cancelable: true,
                clientX: event.clientX, clientY: event.clientY, button: 0, buttons: isEnd ? 0 : 1}));
            if (event.type === 'pointerdown' && wantsText) textInput.focus({preventScroll: true});
            event.preventDefault();
        };
        for (const event of ['pointerdown', 'pointermove', 'pointerup', 'pointercancel']) listen(canvas, event, forwardTouch, {passive: false});
    }

    Module['srFlushStorage'] = () => {
        if (!storageReady || !dirty) return;
        if (flushing) { flushAgain = true; return; }
        flushing = true;
        dirty = false;
        FS.syncfs(false, error => {
            flushing = false;
            if (error) {
                dirty = true;
                emit('srengine-warning', 'Could not save browser data: ' + error);
            }
            if (flushAgain) { flushAgain = false; Module['srFlushStorage'](); }
        });
    };
    Module['srDownloadFile'] = path => {
        try {
            const bytes = FS.readFile(path);
            const url = URL.createObjectURL(new Blob([bytes]));
            const anchor = document.createElement('a');
            anchor.href = url;
            anchor.download = path.split('/').pop() || 'download';
            document.body.appendChild(anchor);
            anchor.click();
            anchor.remove();
            setTimeout(() => URL.revokeObjectURL(url), 1000);
            return true;
        } catch (error) { emit('srengine-warning', String(error)); return false; }
    };
    Module['srChooseFile'] = (directory, accept) => new Promise(resolve => {
        // An explicit DOM button keeps file selection within a user activation.
        const panel = document.createElement('dialog');
        const label = document.createElement('p');
        label.textContent = directory ? 'Import a folder into browser storage' : 'Import a file into browser storage';
        const input = document.createElement('input');
        input.type = 'file';
        input.accept = accept || '';
        if (directory) { input.webkitdirectory = true; input.multiple = true; }
        const cancel = document.createElement('button');
        cancel.textContent = 'Cancel';
        let done = false;
        const finish = value => {
            if (done) return;
            done = true;
            panel.remove();
            resolve(value);
        };
        cancel.onclick = () => finish('');
        panel.oncancel = event => { event.preventDefault(); finish(''); };
        input.onchange = async () => {
            input.disabled = true;
            try {
                if (!input.files.length) { finish(''); return; }
                const root = '/Persistent/Imports/' + Date.now() + '-' + (++importId);
                FS.mkdirTree(root);
                let firstPath = '';
                for (const file of input.files) {
                    const relative = directory ? file.webkitRelativePath : file.name;
                    const segments = relative.split('/');
                    if (segments.some(part => !part || part === '.' || part === '..' || part.includes('\\'))) {
                        throw new Error('Invalid imported path');
                    }
                    const path = root + '/' + relative;
                    FS.mkdirTree(path.slice(0, path.lastIndexOf('/')));
                    FS.writeFile(path, new Uint8Array(await file.arrayBuffer()));
                    if (!firstPath) firstPath = directory ? root + '/' + segments[0] : path;
                }
                Module['srFlushStorage']();
                finish(firstPath);
            } catch (error) { emit('srengine-warning', String(error)); finish(''); }
        };
        panel.append(label, input, cancel);
        document.body.appendChild(panel);
        panel.showModal();
    });
    Module['srSavePath'] = defaultPath => {
        const initial = (defaultPath || 'export').split('/').pop();
        const name = globalThis.prompt('Download filename', initial);
        if (!name) return '';
        if (name === '.' || name === '..' || /[\\/\x00-\x1f]/.test(name)) {
            emit('srengine-warning', 'Invalid filename'); return '';
        }
        const path = '/Downloads/' + name;
        downloads.add(path);
        return path;
    };
    Module['srWriteClipboard'] = text => {
        clipboard.text = text;
        navigator.clipboard?.writeText(text).catch(error => emit('srengine-warning', 'Clipboard: ' + error));
    };
    Module['srReadClipboard'] = () => clipboard.text;
    const resumeAudio = () => {
        if (typeof AL === 'undefined') return;
        for (const context of Object.values(AL.contexts)) {
            const audio = context.audioCtx;
            if (audio && (audio.state === 'suspended' || audio.state === 'interrupted')) {
                audio.resume().catch(error => emit('srengine-warning', 'Audio: ' + error));
            }
        }
    };
    Module['srDisposeBrowser'] = () => {
        Module['srFlushStorage']();
        listeners.splice(0).forEach(remove => remove());
        clearInterval(saveTimer);
        textInput.remove();
    };
    const saveTimer = setInterval(() => Module['srFlushStorage'](), 2000);
    listen(document, 'pointerdown', resumeAudio, true);
    listen(document, 'keydown', resumeAudio, true);
    listen(document, 'visibilitychange', () => {
        if (document.hidden) Module['srFlushStorage']();
        else resumeAudio();
    });
    listen(globalThis, 'pagehide', () => Module['srFlushStorage']());
    listen(document, 'paste', event => { clipboard.text = event.clipboardData?.getData('text/plain') || ''; });
    listen(document, 'copy', event => {
        const active = document.activeElement;
        if (active?.matches('input,textarea,[contenteditable="true"]')) return;
        if (clipboard.text) { event.clipboardData?.setData('text/plain', clipboard.text); event.preventDefault(); }
    });
    const originalPreRun = Module['preRun'];
    Module['preRun'] = Array.isArray(originalPreRun) ? originalPreRun : originalPreRun ? [originalPreRun] : [];
    Module['preRun'].push(() => {
        addRunDependency('sr-persistent-storage');
        FS.mkdirTree('/Persistent');
        FS.mkdirTree('/Downloads');
        try {
            FS.mount(IDBFS, {}, '/Persistent');
            FS.syncfs(true, error => {
                for (const path of ['Cache', 'Data', 'Logs', 'Imports']) FS.mkdirTree('/Persistent/' + path);
                storageReady = !error;
                if (error) emit('srengine-warning', 'Persistent storage unavailable: ' + error);
                installTracking();
                removeRunDependency('sr-persistent-storage');
            });
        } catch (error) {
            for (const path of ['Cache', 'Data', 'Logs', 'Imports']) FS.mkdirTree('/Persistent/' + path);
            emit('srengine-warning', 'Persistent storage unavailable: ' + error);
            installTracking();
            removeRunDependency('sr-persistent-storage');
        }
    });
    function installTracking() {
        const markDirty = path => { if (path.startsWith('/Persistent/')) dirty = true; };
        FS.trackingDelegate['onWriteToFile'] = markDirty;
        FS.trackingDelegate['onMakeDirectory'] = markDirty;
        FS.trackingDelegate['onDeletePath'] = markDirty;
        FS.trackingDelegate['onMovePath'] = (oldPath, newPath) => { markDirty(oldPath); markDirty(newPath); };
        FS.trackingDelegate['onCloseFile'] = path => {
            if (!downloads.delete(path)) return;
            // Only the first close after a selected SaveDialog triggers a download.
            setTimeout(() => Module['srDownloadFile'](path), 0);
        };
    }
})();
