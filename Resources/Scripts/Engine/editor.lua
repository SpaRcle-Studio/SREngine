local cameraSize;    -- Vector2
local colored_id;    -- int
local final_id;      -- int
local bloom_id;      -- int
local bloomBlur_id;  -- int
local skybox_id;     -- int
local depth_id;      -- int
local stencil_id;    -- int

local scene;         -- Scene*
local camera;        -- Camera*
local window;        -- Window*
local render;        -- Render*

local enabled;       -- Bool

local mouseLeftPressed; -- Bool

function Inspector()
    GUIWindow.Begin("Inspector");

    GUIWindow.DrawInspector(scene:GetSelected());

    GUIWindow.End()
end;

function Hierarchy()
    GUIWindow.Begin("Hierarchy");

    GUIWindow.DrawHierarchy(scene);

    GUIWindow.End();
end;

function Enabled()
    enabled = Stack.PopBool(Script.this);
end;

function SetIndices()
    camera        = Stack.PopCamera(Script.this);

    scene         = Stack.PopScene(Script.this);

    cameraSize    = camera:GetSize();
    final_id      = camera:GetPostProcessing():GetFinalTextureID();
    colored_id    = camera:GetPostProcessing():GetColoredImage();
    bloom_id      = camera:GetPostProcessing():GetBloomMask();
    bloomBlur_id  = camera:GetPostProcessing():GetBlurBloomMask();
    depth_id      = camera:GetPostProcessing():GetDepthBuffer();
    skybox_id     = camera:GetPostProcessing():GetSkyboxColor();
    stencil_id    = camera:GetPostProcessing():GetStencilBuffer();

    enabled = true;
end;

function Init()
    Debug.Log("Initialize engine editor GUI...");

    Script.this:ImportLib("Math");
    Script.this:ImportLib("Engine");
    Script.this:ImportLib("Editor");
    Script.this:ImportLib("Graphics");
    Script.this:ImportLib("GUI");

    window = Window.Get();
    render = window:GetRender();

    collectgarbage() -- collect memory
end;

function DrawScene()
    GUIWindow.Begin("Scene");
        GUIWindow.BeginChild("Render");

        GUIWindow.DrawTexture(
            GUIWindow.GetSize(),
            cameraSize,
            final_id,
            true
        );
        local mesh = window:PopAimedMesh();

        GUIWindow.DrawGuizmo(camera, scene:GetSelected(), cameraSize);

        if (mesh ~= nil) then
            if (mesh:Base():GetParent() ~= nil) then
                if (not Input.GetKey(KeyCode.LShift)) then
                    scene:UnselectAll();
                end;
                mesh:Base():GetParent():SetSelect(true);
            end;
        end;

        if (Input.GetKey(KeyCode.MouseLeft)) then
            if (not mouseLeftPressed) then
                mouseLeftPressed = true;
                --window:GetRender():GetManipulationTool():Require(camera, GUIWindow.Get());
                --mousePos = Input.GetMousePos();
                window:RequireAimedMesh(camera, GUIWindow.Get());
            end;

            local select = scene:GetSelected();
        else
            if (mouseLeftPressed == true) then
                mouseLeftPressed = false;
                --window:GetRender():GetManipulationTool():Clear();
                --window:GetRender():GetManipulationTool():DisableAxis();
            end;
        end;

        -----------------------------------------------------------

        GUIWindow.EndChild();
    GUIWindow.End();
end

function Displayes()
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

    GUIWindow.Begin("Depth buffer");
    GUIWindow.BeginChild("Render");
    GUIWindow.DrawTexture(
        GUIWindow.GetSize(),
        cameraSize,
        depth_id,
        true
    );
    GUIWindow.EndChild();
    GUIWindow.End();

    GUIWindow.Begin("Stencil buffer");
    GUIWindow.BeginChild("Render");
    GUIWindow.DrawTexture(
        GUIWindow.GetSize(),
        cameraSize,
        stencil_id,
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

function Windows()
    GUIWindow.Begin("Resources");

    GUIWindow.End();
end;

function ToolBar()
    if (GUIWindow.BeginMainMenuBar()) then
        if (GUIWindow.BeginMenu("File")) then
            if (GUIWindow.MenuItem("New scene")) then

            end;

            if (GUIWindow.MenuItem("Load scene")) then

            end;

            if (GUIWindow.MenuItem("Save scene")) then

            end;

            if (GUIWindow.MenuItem("Exit")) then
                EventManager.Push(Event.Exit);
            end;

            if (GUIWindow.MenuItem("Reload")) then
                Engine.Reload();
            end;

            GUIWindow.EndMenu();
        end;

        if (GUIWindow.BeginMenu("View")) then
            if (GUIWindow.MenuItem("Switch fullscreen")) then
                --window:Resize(1920, 1080);
                local will = not Window.Get():IsFullScreen();
                Window.Get():SetFullScreen(will);
            end;
            GUIWindow.EndMenu();
        end;

        if (GUIWindow.BeginMenu("Config")) then

            GUIWindow.EndMenu();
        end;

        if (GUIWindow.BeginMenu("Edit")) then

            GUIWindow.EndMenu();
        end;

        if (GUIWindow.BeginMenu("GameObject")) then
            if (GUIWindow.MenuItem("Cube")) then
                Editor.InstanceBaseGameObject("Engine/cube.obj", scene, camera);
            end;
            GUIWindow.EndMenu();
        end;

        GUIWindow.EndMainMenuBar();
    end;
end;

function Draw()
    if (enabled == true) then
        DockSpace.Begin();
        Hierarchy();
        Inspector();
        Displayes();
        ToolBar();
        Windows();
        DrawScene();

        if (render ~= nil) then
            render:DrawSettingsPanel();
        end;
    end;

    collectgarbage() -- collect memory
end;

function Close()
    Debug.Log("Close engine editor GUI...");
end;
