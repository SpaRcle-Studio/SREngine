local sceneCamera;      -- Camera*
local postProcessing;   -- PostProcessing*
--local finallyTexture; -- unsigned int
local enabled;          -- Bool

function Inspector()

end;

function Hierarchy()
    GUIWindow.Begin("Hierarchy");

    GUIWindow.End();
end;

function Enabled()
    enabled = Stack.PopBool(Script.this);
end;

function SetCamera()
    sceneCamera = Stack.PopCamera(Script.this);

    if (not (sceneCamera == nil)) then
        postProcessing = sceneCamera:GetPostProcessing();
    end;

    collectgarbage() -- collect memory
end;

function Init()
    Debug.Log("Initialize engine editor GUI...");

    Script.this:ImportLib("Math");
    Script.this:ImportLib("Engine");
    Script.this:ImportLib("Graphics");
    Script.this:ImportLib("GUI");

    enabled = true;

    collectgarbage() -- collect memory
end;

function Windows()
    DockSpace.Begin();

    if (not (sceneCamera == nil)) then
        GUIWindow.Begin("Scene");

        GUIWindow.BeginChild("Render");

        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            sceneCamera:GetSize(),
            postProcessing:GetFinalTextureID(),
            true
        );

        GUIWindow.EndChild();

        GUIWindow.End();
    end;

    if (not (sceneCamera == nil)) then
        GUIWindow.Begin("Bloom Mask");

        GUIWindow.BeginChild("Render");

        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            sceneCamera:GetSize(),
            postProcessing:GetBloomMask(),
            true
        );

        GUIWindow.EndChild();

        GUIWindow.End();
    end;

    if (not (sceneCamera == nil)) then
        GUIWindow.Begin("Skybox");

        GUIWindow.BeginChild("Render");

        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            sceneCamera:GetSize(),
            3,
            true
        );

        GUIWindow.EndChild();

        GUIWindow.End();
    end;

    if (not (sceneCamera == nil)) then
        GUIWindow.Begin("Blur Bloom Mask");

        GUIWindow.BeginChild("Render");

        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            sceneCamera:GetSize(),
            6,
            true
        );

        GUIWindow.EndChild();

        GUIWindow.End();
    end;

    if (not (sceneCamera == nil)) then
        GUIWindow.Begin("Colored");

        GUIWindow.BeginChild("Render");

        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            sceneCamera:GetSize(),
            postProcessing:GetColoredImage(),
            true
        );

        GUIWindow.EndChild();

        GUIWindow.End();
    end;
end;

function Draw()
    if (enabled) then
        Windows();
        if (not (sceneCamera == nil)) then
            Hierarchy();
        end;
    end;

    collectgarbage() -- collect memory
end;

function Close()
    Debug.Log("Close engine editor GUI...");
end;
