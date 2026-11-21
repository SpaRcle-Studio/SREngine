//
// Created by Monika on 10.11.2026.
//

class AngelScriptAllocationTest : ScriptBehaviour
{
    float posX = 0.f;

    void Update(float dt)
    {
        posX += gameObject.transform.GetGlobalTranslation().x;
    }
}
