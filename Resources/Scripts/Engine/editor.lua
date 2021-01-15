local sceneCamera;      -- Camera*
local postProcessing;   -- PostProcessing*
--local finallyTexture;   -- unsigned int

function Inspector()

end;

function Hierarchy()

end;

function SetCamera()
    sceneCamera = Stack.PopCamera(Script.this);

    if (not (sceneCamera == nil)) then
        postProcessing = sceneCamera:GetPostProcessing();
    end;

    --finallyTexture = sceneCamera:GetPostProcessing():GetFinallyTexID();
    collectgarbage() -- collect memory
end;

function Init()
    Debug.Log("Initialize engine editor GUI...");

    Script.this:ImportLib("Math");
    Script.this:ImportLib("Engine");
    Script.this:ImportLib("Graphics");
    Script.this:ImportLib("GUI");

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
            postProcessing:GetFinallyTexID(),
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
    Windows();

    collectgarbage() -- collect memory
end;

function Close()
    Debug.Log("Close engine editor GUI...");

    collectgarbage() -- collect memory
end;
