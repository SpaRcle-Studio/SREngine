local scene;  -- Scene*
local window; -- Window*
local camera; -- GameObject*

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
    local direction = Vector3.New();

    if Input.GetKeyDown(KeyCode.W()) then
        direction = Vector3.Sum(direction, camera:GetTransform():Forward());
    end;

    if (Vector3.Empty(direction) == false) then
        Debug.Log(String.FromFloat(direction.x));
        Debug.Log(String.FromFloat(direction.y));
        Debug.Log(String.FromFloat(direction.z));
    end;
end;

function FixedUpdate()
    --Debug.Log(String.FromFloat(Time.DeltaTime()));
end;
