local sceneCamera;      -- Camera*
local postProcessing;   -- PostProcessing*
--local finallyTexture;   -- unsigned int

function Inspector()

end;

function Hierarchy()

end;

function SetCamera()
    sceneCamera = Stack.PopCamera(Script.this);
    postProcessing = sceneCamera:GetPostProcessing();
    --finallyTexture = sceneCamera:GetPostProcessing():GetFinallyTexID();
end;

function Init()
    Debug.Log("Initialize engine editor GUI...");

    Script.this:ImportLib("Math");
    Script.this:ImportLib("Engine");
    Script.this:ImportLib("Graphics");
    Script.this:ImportLib("GUI");

    collectgarbage() -- collect memory
end;

function Draw()
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

function Close()
    Debug.Log("Close engine editor GUI...");
end;
