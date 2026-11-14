//
// Created by Codex on 14.11.2026.
//

class DapDebugData
{
    int score = 7;
}

class DapDebugProbe : ScriptBehaviour
{
    int ticks = 0;
    string label = "Привет, DAP";
    DapDebugData@ data = DapDebugData();
    FVector2 position;
    Vector<int> numbers;
    Map<string,int> counters;

    void Update(float dt)
    {
        int before = ticks;
        position.x = 12.5f;
        position.y = -3.25f;
        numbers.clear();
        numbers.pushBack(7);
        numbers.pushBack(-4);
        counters.insert("score", 11);
        ticks += 1; // DAP_BREAKPOINT
        StepProbe(before);
    }

    void StepProbe(int previous)
    {
        data.score = previous + 7;
    }
}
