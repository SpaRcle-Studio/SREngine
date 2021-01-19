local cameraSize;    -- Vector2
local colored_id;    -- int
local final_id;      -- int
local bloom_id;      -- int
local bloomBlur_id;  -- int
local skybox_id;     -- int

local enabled;       -- Bool

function Inspector()

end;

function Hierarchy()
    GUIWindow.Begin("Hierarchy");

    GUIWindow.End();
end;

function Enabled()
    enabled = Stack.PopBool(Script.this);
end;

function SetIndices()
    local camera = Stack.PopCamera(Script.this);

    cameraSize    = camera:GetSize();
    final_id      = camera:GetPostProcessing():GetFinalTextureID();
    colored_id    = camera:GetPostProcessing():GetColoredImage();
    bloom_id      = camera:GetPostProcessing():GetBloomMask();
    bloomBlur_id  = 6;--Stack.PopInt(Script.this);
    skybox_id     = 3;--Stack.PopInt(Script.this);

    enabled = true;
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
    GUIWindow.Begin("Scene");
    GUIWindow.BeginChild("Render");
        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            cameraSize,
            final_id,
            true
        );
    GUIWindow.EndChild();
    GUIWindow.End();

    GUIWindow.Begin("Bloom Mask");
    GUIWindow.BeginChild("Render");
        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            cameraSize,
            bloom_id,
            true
        );
    GUIWindow.EndChild();
    GUIWindow.End();

    GUIWindow.Begin("Skybox");
    GUIWindow.BeginChild("Render");
        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            cameraSize,
            skybox_id,
            true
        );
    GUIWindow.EndChild();
    GUIWindow.End();

    GUIWindow.Begin("Blur Bloom Mask");
    GUIWindow.BeginChild("Render");
        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            cameraSize,
            bloomBlur_id,
            true
        );
    GUIWindow.EndChild();
    GUIWindow.End();

    GUIWindow.Begin("Colored");
    GUIWindow.BeginChild("Render");
        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            cameraSize,
            colored_id,
            true
        );
    GUIWindow.EndChild();
    GUIWindow.End();
end;

function Draw()
    if (enabled == true) then
        DockSpace.Begin();
        Hierarchy();
        Windows();
    end;

    collectgarbage() -- collect memory
end;

function Close()
    Debug.Log("Close engine editor GUI...");
end;
