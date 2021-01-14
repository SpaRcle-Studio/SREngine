
function Inspector()

end;

function Hierarchy()

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

    GUIWindow.Begin("Scene");

    GUIWindow.End();
end;

function Close()
    Debug.Log("Close engine editor GUI...");
end;
