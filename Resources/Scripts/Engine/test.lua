--
-- Created by IntelliJ IDEA.
-- User: Nikita
-- Date: 11.03.2021
-- Time: 18:14
-- To change this template use File | Settings | File Templates.
--
function SelectOld()
    local mesh = window:PopAimedMesh();
    if (mesh ~= nil) then
        if (mesh:Base():GetParent() ~= nil) then
            if (not Input.GetKey(KeyCode.LShift)) then
                scene:UnselectAll();
            end;
            local gm = mesh:Base():GetParent():SetSelect(true);
        end;
    end;

    if (Input.GetKey(KeyCode.MouseLeft)) then
        if (not mouseLeftPressed) then
            mouseLeftPressed = true;
            window:RequireAimedMesh(camera, GUIWindow.Get());
        end;
    else
        mouseLeftPressed = false;
    end;

    GUIWindow.DrawGuizmo(camera, scene:GetSelected(), cameraSize);
end;

if (Input.GetKey(KeyCode.MouseLeft)) then
    if (not mouseLeftPressed) then
        mouseLeftPressed = true;
        window:GetRender():GetManipulationTool():Require(camera, GUIWindow.Get());

        mousePos = Input.GetMousePos();
        window:RequireAimedMesh(camera, GUIWindow.Get());
    end;

    local select = scene:GetSelected();
    local axis = window:GetRender():GetManipulationTool():GetActiveAxis();
    if (select ~= nil and axis ~= Axis.None) then
        local newPos = Input.GetMousePos();
        local drag = Vector2.Sub(newPos, mousePos);
        mousePos = newPos;

        local op = window:GetRender():GetManipulationTool():GetOperation();

        if (op == Operation.Translate) then
            local dir = select:GetTransform():Direction(Vector3.FromAxis(axis,1), true);

            --local dg = window:GetRender():GetManipulationTool():GetDrag();

            select:GetTransform():Translate(
            --Vector3.FMul(dir, dg / -100.0),
                Vector3.FMul(dir, (-drag.y + drag.x) / -50.0),
                true
            );
        else
            if (op == Operation.Rotate) then
                select:GetTransform():RotateAxis(Vector3.FromAxis(axis,1), (-drag.y + drag.x) / 10.0, true);
            end;
        end;
        --local dr = window:GetRender():GetManipulationTool():GetDrag(Input.GetMousePos());
    end;
else
    if (mouseLeftPressed == true) then
        mouseLeftPressed = false;
        --window:GetRender():GetManipulationTool():Clear();
        window:GetRender():GetManipulationTool():DisableAxis();
    end;
end;

