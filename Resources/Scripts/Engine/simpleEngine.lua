--
-- Created by IntelliJ IDEA.
-- User: Nikita
-- Date: 26.03.2021
-- Time: 23:21
-- To change this template use File | Settings | File Templates.
--

local scene; -- Scene*
local window; -- Window*

function Init()
    Debug.Log("Initialize engine editor GUI...");

    Script.this:ImportLib("Math");
    Script.this:ImportLib("Engine");
    Script.this:ImportLib("Editor");
    Script.this:ImportLib("Graphics");
    Script.this:ImportLib("GUI");

    scene   = Scene.Get();
    window  = Window.Get();

    collectgarbage() -- collect memory
end;

function Start()
    Debug.Log("Starting main engine script...");

    --window:Resize(1600, 900);

    window:CentralizeWindow();

    --window:SetFullScreen(false);


    collectgarbage() -- collect memory
end;

function FixedUpdate()

end;

function Update()

end;

function Close()
    Debug.Log("Close main engine script...");

    if (not (scene == nil)) then
        scene:Destroy();
        scene:Free();
    end;

    collectgarbage() -- collect memory
end;