local scene;           -- Scene*
local window;          -- Window*
local camera;          -- GameObject*
local render;          -- Render*
local skybox;          -- Skybox*
local cameraComp;      -- Camera*
local editorGUIScript; -- Script*

function CreateTreeScene()
    local cube_1      = scene:Instance("cube_1");
    local cube_2      = scene:Instance("cube_2");

    local cube_1_1    = scene:Instance("cube_1_1");
    cube_1:AddChild(cube_1_1);

    local cube_1_2    = scene:Instance("cube_1_2");
    cube_1:AddChild(cube_1_2);

    local cube_1_2_1   = scene:Instance("cube_1_2_1");
    cube_1_2:AddChild(cube_1_2_1);
end;

function GeometryTest()
    local texture = Texture.Load("steel_cube.png", true, TextureType.Diffuse, TextureFilter.LINEAR);
    local cubeMesh = Mesh.Load("cube.obj", 0);
    render:RegisterTexture(texture);

    for a = 0, 50, 1 do
        for b = 0, 50, 1 do
            for g = 0, 0, 1 do
                local cube = scene:Instance("Cube");
                local mesh;

                if (a == 0 and b == 0 and g == 0) then
                    mesh = cubeMesh;
                else
                    mesh = cubeMesh:Copy();
                end;

                render:RegisterMesh(mesh);

                mesh:GetMaterial():SetBloom(true);
                mesh:GetMaterial():SetDiffuse(texture);
                mesh:GetMaterial():SetColor(Vector3.FMul(Material.RandomColor3(), 6.0));

                cube:AddComponent(mesh:Base());
                cube:GetTransform():Translate(
                    Vector3.Sum(
                        Vector3.Sum(
                            Vector3.FMul(cube:GetTransform():Forward(), 8.0 * (a + 1)),
                            Vector3.FMul(cube:GetTransform():Right(), 8.0 * (b + 1))
                        ),
                        Vector3.FMul(cube:GetTransform():Up(), 8.0 * (g + 1))
                    )
                );
            end;
        end;
    end;

    collectgarbage() -- collect memory
end;

local childRotateGM = nil;

function RotationTest()
    local texture = Texture.Load("steel_cube.png", true, TextureType.Diffuse, TextureFilter.LINEAR);
    --local texture = Texture.Load("brickwall.jpg", true, TextureType.Diffuse, TextureFilter.LINEAR);
    local mesh = Mesh.Load("cube.obj", 0);
    --local mesh = Mesh.Load("monkey_low.obj", 0);
    render:RegisterTexture(texture);

    -- first

    local cube_parent = scene:Instance("Cube parent");

    render:RegisterMesh(mesh);
    mesh:GetMaterial():SetDiffuse(texture);
    mesh:GetMaterial():SetColor(Vector3.New(1, 2, 1));

    cube_parent:AddComponent(mesh:Base());

    --cube_parent:GetTransform():Translate(
    --    Vector3.FMul(cube_parent:GetTransform():Forward(), 2.0)
    --);

    -- first

    -- second

    local cube_child = scene:Instance("Cube child");

    mesh = mesh:Copy();

    render:RegisterMesh(mesh);

    mesh:GetMaterial():SetDiffuse(texture);
    mesh:GetMaterial():SetColor(Vector3.New(2, 1, 1));

    cube_child:AddComponent(mesh:Base());
    cube_child:GetTransform():Translate(
        Vector3.FMul(cube_child:GetTransform():Forward(), 4.0), true
    );

    --cube_child:GetTransform():Translate(Vector3.FMul(cube_child:GetTransform():Up(), 2.0));

    cube_parent:AddChild(cube_child);

    childRotateGM = cube_child;

    --cube_parent:GetTransform():SetScale(Vector3.New(0.01, 0.01, 0.01), true);

    -- second
end

function HierarchyTest()
    local texture = Texture.Load("steel_cube.png", true, TextureType.Diffuse, TextureFilter.LINEAR);
    --local texture = Texture.Load("brickwall.jpg", true, TextureType.Diffuse, TextureFilter.LINEAR);
    local mesh = Mesh.Load("engine/cube.obj", 0);
    --local mesh = Mesh.Load("monkey_low.obj", 0);
    render:RegisterTexture(texture);

    -- first

    local cube_parent = scene:Instance("Cube parent");

    render:RegisterMesh(mesh);
    mesh:GetMaterial():SetDiffuse(texture);
    mesh:GetMaterial():SetColor(Vector3.New(1, 2, 1));

    cube_parent:AddComponent(mesh:Base());

    -- first

    -- second

    local cube_child = scene:Instance("Cube child");

    mesh = mesh:Copy();

    render:RegisterMesh(mesh);

    mesh:GetMaterial():SetDiffuse(texture);
    mesh:GetMaterial():SetColor(Vector3.New(2, 1, 1));

    cube_child:AddComponent(mesh:Base());
    cube_child:GetTransform():Translate(
        Vector3.FMul(cube_child:GetTransform():Right(), 2.0), true
    );
    cube_child:GetTransform():Translate(
        Vector3.FMul(cube_child:GetTransform():Forward(), 2.0), true
    );


    cube_parent:AddChild(cube_child);

    -- second

    -- third

    local cube_child2 = scene:Instance("Cube child 2");

    mesh = mesh:Copy();

    render:RegisterMesh(mesh);
    mesh:GetMaterial():SetDiffuse(texture);
    mesh:GetMaterial():SetColor(Vector3.New(1, 1, 2));

    cube_child2:AddComponent(mesh:Base());
    cube_child2:GetTransform():Translate(
        Vector3.FMul(cube_child2:GetTransform():Right(), 2.0), true
    );

    cube_child:AddChild(cube_child2);

    -- third
end

function LoadCamera()
    camera = scene:Instance("SceneCamera");

    cameraComp = Camera.New(4);
   -- local winSize = window:GetWindowSize();
    --cameraComp:SetFrameSize(winSize.x, winSize.y);
    cameraComp:SetFrameSize(1600, 900);

    cameraComp:SetDirectOutput(false);
    window:SetGUIEnabled(true);

    cameraComp:GetPostProcessing():SetBloom(true);
    cameraComp:GetPostProcessing():SetBloomIntensity(2.0);
    cameraComp:GetPostProcessing():SetBloomAmount(5);
    cameraComp:GetPostProcessing():SetGamma(0.8);

    camera:AddComponent(cameraComp:Base());

    window:AddCamera(cameraComp);

    cameraComp:WaitBuffersCalculate();

    collectgarbage() -- collect memory
end;

function Init()
    Debug.Log("Initializing main engine script...");

    Script.this:ImportLib("Math");
    Script.this:ImportLib("Engine");
    Script.this:ImportLib("Graphics");
    Script.this:ImportLib("GUI");

    scene  = Scene.Get();
    window = Window.Get();
    render = Render.Get();

    editorGUIScript = Script.this:LoadScript("editor", true);
    window:SetCanvas(Canvas.Load(editorGUIScript));

    collectgarbage() -- collect memory
end;

function LoadTools()
    local rings = Mesh.LoadAll("Engine/ring 3.0.obj"); -- List<Mesh*>
    local arrows = Mesh.LoadAll("Engine/arrows.obj");  -- List<Mesh*>

    Mesh.Inverse(rings);

    --render:RegisterMeshes(arrows);

    render:GetManipulationTool():SetRings(rings);
    render:GetManipulationTool():SetArrows(arrows);
end;

function Start()
    Debug.Log("Starting main engine script...");

    --window:Resize(3840, 2160);
    --window:Resize(1920, 1080);
    --window:Resize(1920, 1060);
    --window:Resize(1680, 1050);
    window:Resize(1600, 900);

    window:SetFullScreen(false);
    --window:Resize(4086, 900);
    window:CentralizeWindow();

    skybox = Skybox.Load(
        "Sea.jpg", -- images name
        "skybox"   -- shader name
    );
    render:SetSkybox(skybox);

    --------------------------------------

    LoadCamera();
    --CreateTreeScene();
    HierarchyTest();
    --RotationTest();
    --GeometryTest();
    --LoadTools();

    -------------------------------------

    render:SetGridEnabled(true);

    Stack.PushScene(editorGUIScript, scene);
    Stack.PushCamera(editorGUIScript, cameraComp);
    editorGUIScript:Call("SetIndices");

    --cameraComp:SetDirectOutput(true);
    --window:SetGUIEnabled(false);
    --Stack.PushBool(editorGUIScript, false);
    --editorGUIScript:Call("Enabled");

    collectgarbage() -- collect memory
end;

function MouseUpdate()
    local dir = Input.GetMouseDrag();

    local wheel = Input.GetMouseWheel();
    if (wheel ~= 0) then
        local forward = camera:GetTransform():Forward();
        camera:GetTransform():Translate(Vector3.FMul(forward, wheel / -10.0));
    end;

    if (Input.GetKey(KeyCode.MouseRight)) then
        --camera:GetTransform():Rotate(Vector3.New(dir.y / -10.0, dir.x / -10.0, 0.0));
        camera:GetTransform():Rotate(Vector3.New(dir.y / -10.0, dir.x / -10.0, 0.0));
    end;

    if (Input.GetKey(KeyCode.MouseMiddle)) then
        local right = camera:GetTransform():Right();
        local up    = camera:GetTransform():Up();

        camera:GetTransform():Translate(
            Vector3.Sum(
                Vector3.FMul(up,    dir.y /  100.0),
                Vector3.FMul(right, dir.x /  -100.0)
                --Vector3.FMul(right, dir.x / -100.0)
            )
        );
    end;
end;

function FixedUpdate()

end;

function Update()
    if (childRotateGM ~= nil) then
        --childRotateGM:GetTransform():Rotate(Vector3.New(0.001, 0, 0), true);
    end;

    MouseUpdate();

    if (Input.GetKeyDown(KeyCode.W)) then
        --render:GetManipulationTool():SetOperation(Operation.Translate);
        GUIWindow.SetGuizmoTool(1);
    else
        if (Input.GetKeyDown(KeyCode.E)) then
            --render:GetManipulationTool():SetOperation(Operation.Rotate);
            GUIWindow.SetGuizmoTool(2);
        else
            if (Input.GetKeyDown(KeyCode.R)) then
                GUIWindow.SetGuizmoTool(3);
            end
        end
    end

    if (Input.GetKeyDown(KeyCode.P)) then
        local enabled = cameraComp:IsDirectOutput();
        cameraComp:SetDirectOutput(not enabled);
        window:SetGUIEnabled(enabled);
        Stack.PushBool(editorGUIScript, enabled);
        editorGUIScript:Call("Enabled");
    end;

    if (Input.GetKeyDown(KeyCode.B)) then
        local enabled = cameraComp:GetPostProcessing():GetBloomEnabled();
        cameraComp:GetPostProcessing():SetBloom(not enabled);
    end;

    --if (Input.GetKeyDown(KeyCode.F)) then scene:Print(); end;
    --if (Input.GetKeyDown(KeyCode.C)) then Debug.MakeCrash(); end;

    collectgarbage() -- collect memory
end;

function Close()
    Debug.Log("Close main engine script...");

    Stack.PushBool(editorGUIScript, false);
    editorGUIScript:Call("Enabled");

    if (not (skybox == nil)) then
        skybox:AwaitDestroy();
        skybox:Free();
    end;

    if (not (scene == nil)) then
        scene:Destroy();
        scene:Free();
    end;

    collectgarbage() -- collect memory
end;