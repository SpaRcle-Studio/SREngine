
function Inspector()

end;

function Hierarchy()

end;

function Initialize()
    Debug.Log("Initialize engine editor GUI...");

    Script.this:ImportLib("Math",     LuaState.L);
    Script.this:ImportLib("Engine",   LuaState.L);
    Script.this:ImportLib("Graphics", LuaState.L);
    Script.this:ImportLib("GUI",      LuaState.L);

    collectgarbage() -- collect memory
end;

function Close()
    Debug.Log("Close engine editor GUI...");
end;
