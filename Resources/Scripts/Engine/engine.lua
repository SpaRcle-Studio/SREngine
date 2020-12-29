local scene;
local window;
local camera;

function Start ()
    Debug.Log("Main engine script has been started!");

    scene = Scene.Get();
    window = Window.Get();

    camera = scene:Instance("SceneCamera");

    local cameraComp = Camera.New();
    cameraComp:SetFrameSize(1280, 720);

    camera:AddComponent(cameraComp:Base());

    window:AddCamera(cameraComp);
end;

function Update()
    --Debug.Log(String.FromFloat(Time.DeltaTime()));
end;

function FixedUpdate()

end;
