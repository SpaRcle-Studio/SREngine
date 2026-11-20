//
// Created by Codex on 20.11.2026.
//

class ReflectionProbeNode
{
    int score = 7;
    String label = "node";
    FVector3 position;
    ReflectionProbeNode@ next;
    Vector<ReflectionProbeNode@> links;
}

class ReflectionValueProbe : ScriptBehaviour
{
    bool passed = false;
    FVector3 position;
    String label = "initial";
    Vector<int> numbers;
    Vector<FVector3> positions;
    Vector<String> labels;
    Vector<ReflectionProbeNode> nodes;
    Vector<ReflectionProbeNode@> links;
    ReflectionProbeNode@ root;

    void Awake()
    {
        passed = RunProbe();
    }

    bool RunProbe()
    {
        FVector3 original;
        original.x = 12.5f;
        FVector3 copy = original;
        copy.x = -3.25f;
        if (original.x < 12.49f || original.x > 12.51f)
            return false;

        FSize size;
        size.value = 25.0f;
        size.metric = SizeMetric::Percent;
        FSize sizeCopy = size;
        sizeCopy.metric = SizeMetric::Px;
        if (size.metric != SizeMetric::Percent || sizeCopy.metric != SizeMetric::Px)
            return false;

        String text = "alpha";
        String textCopy = text;
        textCopy = "beta";
        if (text != "alpha" || textCopy != "beta" || text.substring(1, 3) != "lph")
            return false;

        numbers.resize(2);
        numbers[0] = 7;
        Vector<int> copiedNumbers = numbers;
        copiedNumbers[0] = 11;
        if (numbers[0] != 7 || copiedNumbers[0] != 11)
            return false;

        positions.pushBack(original);
        positions[0].x = 21.0f;
        if (positions[0].x < 20.99f || positions[0].x > 21.01f)
            return false;

        labels.pushBack(text);
        labels[0] = "changed";
        if (labels[0] != "changed" || text != "alpha")
            return false;

        nodes.resize(1);
        nodes[0].score = 15;
        Vector<ReflectionProbeNode> copiedNodes = nodes;
        copiedNodes[0].score = 25;
        if (nodes[0].score != 15 || copiedNodes[0].score != 25)
            return false;

        @root = ReflectionProbeNode();
        @root.next = root;
        root.links.pushBack(root);
        links.resize(1);
        if (links[0] !is null)
            return false;
        links.pushBack(root);
        links[1].score = 42;
        if (root.score != 42 || root.next !is root || root.links[0] !is root)
            return false;

        Vector<ReflectionProbeNode@> copiedLinks = links;
        if (copiedLinks[0] !is null || copiedLinks[1] !is root)
            return false;
        @links[0] = root;
        position = original;
        label = "saved";
        return true;
    }

    bool CheckRestoredGraph() const
    {
        return passed && label == "saved" && root !is null && root.score == 42 &&
            root.links.size() == 1 && links.size() == 2 &&
            root.next is root && root.links[0] is root && links[0] is root && links[1] is root;
    }
}
