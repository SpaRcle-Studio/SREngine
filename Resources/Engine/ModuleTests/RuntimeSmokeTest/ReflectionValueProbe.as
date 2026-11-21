//
// Created by Codex on 20.11.2026.
//

enum ReflectionProbeMode
{
    Dormant,
    Active
}

class ReflectionProbeEmpty
{
}

enum ReflectionProbeWideMode : int64
{
    Far = 1099511627776,
    Before = -1099511627776
}

class ReflectionProbeNode
{
    int score = 7;
    String label = "node";
    FVector3 position;
    ReflectionProbeNode@ next;
    Vector<ReflectionProbeNode@> links;
}

class ReflectionProbeHolder
{
    ReflectionProbeNode@ alias;
    ReflectionProbeNode value;
    private int secret = 14;

    void SetSecret(int value)
    {
        secret = value;
    }

    int GetSecret() const
    {
        return secret;
    }
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
    const ReflectionProbeNode@ constRoot;
    ReflectionProbeHolder holder;
    Vector<ReflectionProbeMode> modes;
    Vector<ReflectionProbeWideMode> wideModes;
    ReflectionProbeEmpty emptyObject;
    Vector<Vector<int>> emptyGroups;
    Set<String> uniqueLabels;
    Set<ReflectionProbeWideMode> uniqueWideModes;
    Map<String, int> scores;
    Map<String, Set<int>> groupedIds;
    Map<String, ReflectionProbeNode> namedNodes;
    Map<String, ReflectionProbeNode@> namedLinks;

    void Awake()
    {
        passed = RunProbe();
        if (!passed) {
            Debug::Instance().Error("Awake() : failed RunProbe!");
        }
        if (!CheckRestoredGraph()) {
            Debug::Instance().Error("Awake() : failed CheckRestoredGraph!");
        }
    }

    bool RunProbe()
    {
        emptyGroups.resize(2);
        emptyGroups[1].pushBack(19);
        wideModes.resize(2);
        wideModes[0] = Far;
        wideModes[1] = Before;
        if (wideModes[0] != 1099511627776 || wideModes[1] != -1099511627776) {
            Debug::Instance().Error("RunProbe() : failed wide mode!");
            return false;
        }

        FVector3 original;
        original.x = 12.5f;
        FVector3 copy = original;
        copy.x = -3.25f;
        if (original.x < 12.49f || original.x > 12.51f) {
            Debug::Instance().Error("RunProbe() : failed FVector3!");
            return false;
        }

        FSize size;
        size.value = 25.0f;
        size.metric = SizeMetric::Percent;
        FSize sizeCopy = size;
        sizeCopy.metric = SizeMetric::Px;
        if (size.metric != SizeMetric::Percent || sizeCopy.metric != SizeMetric::Px) {
            Debug::Instance().Error("RunProbe() : failed FSize!");
            return false;
        }

        String text = "alpha";
        String textCopy = text;
        textCopy = "beta";
        if (text != "alpha" || textCopy != "beta" || text.substring(1, 3) != "lph") {
            Debug::Instance().Error("RunProbe() : failed String!");
            return false;
        }

        numbers.resize(2);
        numbers[0] = 7;
        Vector<int> copiedNumbers = numbers;
        copiedNumbers[0] = 11;
        if (numbers[0] != 7 || copiedNumbers[0] != 11) {
            Debug::Instance().Error("RunProbe() : failed failed numbers Vector!");
            return false;
        }
        Vector<Vector<int>> nestedNumbers;
        nestedNumbers.pushBack(numbers);
        nestedNumbers[0][0] = 19;
        nestedNumbers.reserve(8);
        if (nestedNumbers[0][0] != 19 || numbers[0] != 7) {
            Debug::Instance().Error("RunProbe() : failed nested numbers Vector!");
            return false;
        }

        positions.pushBack(original);
        positions[0].x = 21.0f;
        if (positions[0].x < 20.99f || positions[0].x > 21.01f) {
            Debug::Instance().Error("RunProbe() : failed pushBack!");
            return false;
        }

        labels.pushBack(text);
        labels[0] = "changed";
        if (labels[0] != "changed" || text != "alpha") {
            Debug::Instance().Error("RunProbe() : failed labels!");
            return false;
        }

        Vector<SizeMetric> metrics;
        metrics.resize(1);
        metrics[0] = SizeMetric::Percent;
        Vector<SizeMetric> copiedMetrics = metrics;
        copiedMetrics[0] = SizeMetric::Px;
        if (metrics[0] != SizeMetric::Percent || copiedMetrics[0] != SizeMetric::Px) {
            Debug::Instance().Error("RunProbe() : failed size metric!");
            return false;
        }
        Value packed;
        packed.set(metrics);
        Vector<SizeMetric> restoredMetrics;
        if (!packed.get(restoredMetrics) || restoredMetrics.size() != 1 || restoredMetrics[0] != SizeMetric::Percent) {
            Debug::Instance().Error("RunProbe() : failed packing!");
            return false;
        }

        modes.resize(2);
        modes[0] = Active;
        modes[1] = Dormant;
        Vector<ReflectionProbeMode> copiedModes = modes;
        copiedModes[0] = Dormant;
        if (modes[0] != Active || copiedModes[0] != Dormant) {
            Debug::Instance().Error("RunProbe() : failed copiedModes!");
            return false;
        }

        ReflectionTestComponentData nativeData;
        nativeData.GetWidthReference() = 63;
        nativeData.GetVectorReference().x = 8.5f;
        nativeData.vector.y = 9.5f;
        const ReflectionTestComponentData@ constNativeData = nativeData.GetConstData();
        if (constNativeData.GetConstWidthReference() != 63 || constNativeData.width != 63 ||
            constNativeData.GetConstVectorReference().x < 8.49f || constNativeData.GetConstVectorReference().x > 8.51f ||
            constNativeData.vector.y < 9.49f || constNativeData.vector.y > 9.51f) {
            Debug::Instance().Error("RunProbe() : failed ReflectionTestComponentData!");
            return false;
        }
        ReflectionProbeWide wide = ReflectionProbeWide::High;
        if (nativeData.EchoWide(wide) != 1099511627776) {
            Debug::Instance().Error("RunProbe() : failed EchoWide!");
            return false;
        }
        nativeData.WriteWide(wide);
        if (wide != -1099511627776) {
            Debug::Instance().Error("RunProbe() : failed WriteWide!");
            return false;
        }
        Vector<ReflectionProbeWide> wideValues;
        wideValues.pushBack(ReflectionProbeWide::High);
        Vector<ReflectionProbeWide> copiedWide = constNativeData.EchoWideVector(wideValues);
        copiedWide[0] = ReflectionProbeWide::Negative;
        if (copiedWide[0] != -1099511627776 || wideValues[0] != 1099511627776) {
            Debug::Instance().Error("RunProbe() : failed wideValues!");
            return false;
        }
        nativeData.width = 31;
        nativeData.vector.x = 8.0f;
        if (nativeData.width != 31 || nativeData.vector.x < 7.99f || nativeData.vector.x > 8.01f) {
            Debug::Instance().Error("RunProbe() : failed nativeData!");
            return false;
        }
        Vector<ReflectionTestComponentData> nativeValues;
        nativeValues.pushBack(nativeData);
        nativeValues[0].width = 41;
        Vector<ReflectionTestComponentData> copiedNativeValues = nativeValues;
        copiedNativeValues[0].width = 51;
        copiedNativeValues.reserve(8);
        if (nativeData.width != 31 || nativeValues[0].width != 41 || copiedNativeValues[0].width != 51) {
            Debug::Instance().Error("RunProbe() : failed copiedNativeValues!");
            return false;
        }
        ReflectionTestComponentData@ element = nativeValues[0];
        nativeData.width = 55;
        nativeValues.set(0, nativeData);
        if (element.width != 55 || nativeValues[0] !is element) {
            Debug::Instance().Error("RunProbe() : failed nativeValues!");
            return false;
        }
        packed.set(nativeValues);
        Vector<ReflectionTestComponentData> restoredNativeValues;
        if (!packed.get(restoredNativeValues) || restoredNativeValues.size() != 1 || restoredNativeValues[0].width != 55) {
            Debug::Instance().Error("RunProbe() : failed restoredNativeValues!");
            return false;
        }
        Vector<ReflectionTestComponentData@> nativeHandles;
        nativeHandles.resize(1);
        @nativeHandles[0] = nativeData;
        nativeHandles[0].width = 61;
        ReflectionTestComponentData@ retained = nativeHandles[0];
        nativeHandles.clear();
        retained.width = 71;
        if (nativeData.width != 71) {
            Debug::Instance().Error("RunProbe() : failed retained!");
            return false;
        }

        nodes.resize(1);
        nodes[0].score = 15;
        Vector<ReflectionProbeNode> copiedNodes = nodes;
        copiedNodes[0].score = 25;
        if (nodes[0].score != 15 || copiedNodes[0].score != 25) {
            Debug::Instance().Error("RunProbe() : failed copiedNodes!");
            return false;
        }

        @root = ReflectionProbeNode();
        @root.next = root;
        root.links.pushBack(root);
        links.resize(1);
        if (links[0] !is null) {
            Debug::Instance().Error("RunProbe() : failed links!");
            return false;
        }
        links.pushBack(root);
        links[1].score = 42;
        if (root.score != 42 || root.next !is root || root.links[0] !is root) {
            Debug::Instance().Error("RunProbe() : failed links score!");
            return false;
        }

        Vector<ReflectionProbeNode@> copiedLinks = links;
        if (copiedLinks[0] !is null || copiedLinks[1] !is root) {
            Debug::Instance().Error("RunProbe() : failed copiedLinks!");
            return false;
        }
        @links[0] = root;
        @constRoot = root;
        holder.value.score = 77;
        @holder.alias = holder.value;
        holder.SetSecret(32);
        position = original;
        label = "saved";
        return RunContainerProbe();
    }

    bool CheckConstContainers(const Set<String>&in names, const Map<String, int>&in values) const
    {
        return names.size() == 2 && names.contains("alpha") && names.contains("beta") &&
            values.size() == 2 && values.contains("first") && values.at("first") == 17 && values["second"] == 29;
    }

    bool RunContainerProbe()
    {
        uniqueLabels.clear();
        scores.clear();
        if (uniqueLabels.size() != 0 || uniqueLabels.contains("missing") || uniqueLabels.erase("missing") ||
            scores.size() != 0 || scores.contains("missing") || scores.erase("missing")) {
            Debug::Instance().Error("RunContainerProbe() : failed empty Set/Map!");
            return false;
        }
        if (!uniqueLabels.insert("alpha") || uniqueLabels.insert("alpha") || !uniqueLabels.insert("beta") || uniqueLabels.size() != 2) {
            Debug::Instance().Error("RunContainerProbe() : failed Set insertion!");
            return false;
        }
        Set<String> copiedLabels = uniqueLabels;
        Set<String> assignedLabels;
        assignedLabels.insert("stale");
        assignedLabels = uniqueLabels;
        assignedLabels = assignedLabels;
        if (!copiedLabels.erase("alpha") || copiedLabels.erase("alpha") || !uniqueLabels.contains("alpha") ||
            assignedLabels.size() != 2 || assignedLabels.contains("stale")) {
            Debug::Instance().Error("RunContainerProbe() : failed Set copy/assignment/erase!");
            return false;
        }
        copiedLabels.clear();
        assignedLabels.clear();
        if (copiedLabels.size() != 0 || assignedLabels.size() != 0 || uniqueLabels.size() != 2) {
            Debug::Instance().Error("RunContainerProbe() : failed Set clear independence!");
            return false;
        }

        if (scores["first"] != 0 || scores.size() != 1) {
            Debug::Instance().Error("RunContainerProbe() : failed Map default insertion!");
            return false;
        }
        scores["first"] = 11;
        scores.set("first", 17);
        scores.insert("second", 29);
        if (!CheckConstContainers(uniqueLabels, scores)) {
            Debug::Instance().Error("RunContainerProbe() : failed const Set/Map access or Map overwrite!");
            return false;
        }
        Map<String, int> copiedScores = scores;
        Map<String, int> assignedScores;
        assignedScores["stale"] = -1;
        assignedScores = scores;
        assignedScores = assignedScores;
        copiedScores.at("first") = 41;
        if (!copiedScores.erase("second") || copiedScores.erase("second") || copiedScores.size() != 1 ||
            scores["first"] != 17 || scores["second"] != 29 || assignedScores.size() != 2 ||
            assignedScores.contains("stale") || assignedScores["first"] != 17) {
            Debug::Instance().Error("RunContainerProbe() : failed Map copy/assignment/erase!");
            return false;
        }
        copiedScores.clear();
        assignedScores.clear();
        if (copiedScores.size() != 0 || assignedScores.size() != 0 || scores.size() != 2) {
            Debug::Instance().Error("RunContainerProbe() : failed Map clear independence!");
            return false;
        }

        Set<int> ids;
        Map<int, int> indexed;
        for (int i = 31; i >= 0; --i) {
            ids.insert(i);
            indexed[i] = i * 3;
        }
        for (int i = 0; i < 32; i += 2) {
            if (!ids.erase(i) || !indexed.erase(i)) {
                Debug::Instance().Error("RunContainerProbe() : failed tree erasure!");
                return false;
            }
        }
        for (int i = 0; i < 32; ++i) {
            bool expected = i % 2 != 0;
            if (ids.contains(i) != expected || indexed.contains(i) != expected || (expected && indexed.at(i) != i * 3)) {
                Debug::Instance().Error("RunContainerProbe() : failed tree contents after erasure!");
                return false;
            }
        }
        if (ids.size() != 16 || indexed.size() != 16) {
            Debug::Instance().Error("RunContainerProbe() : failed tree size after erasure!");
            return false;
        }
        groupedIds["odd"] = ids;
        ids.clear();
        Map<String, Set<int>> copiedGroups = groupedIds;
        copiedGroups["odd"].erase(1);
        Vector<Set<int>> sets;
        sets.pushBack(groupedIds["odd"]);
        sets[0].erase(3);
        Vector<Map<String, int>> maps;
        maps.pushBack(scores);
        maps[0]["first"] = 99;
        if (groupedIds["odd"].size() != 16 || !groupedIds["odd"].contains(1) || !groupedIds["odd"].contains(3) ||
            copiedGroups["odd"].contains(1) || sets[0].contains(3) || scores["first"] != 17) {
            Debug::Instance().Error("RunContainerProbe() : failed nested Set/Map copy independence!");
            return false;
        }

        Set<ReflectionProbeMode> modeSet;
        modeSet.insert(Active);
        modeSet.insert(Dormant);
        uniqueWideModes.insert(Far);
        uniqueWideModes.insert(Before);
        Map<ReflectionProbeWideMode, int> wideKeys;
        wideKeys[Far] = 1;
        wideKeys[Before] = 2;
        if (modeSet.size() != 2 || !modeSet.contains(Active) || uniqueWideModes.size() != 2 ||
            !uniqueWideModes.contains(Far) || !uniqueWideModes.contains(Before) || wideKeys[Far] != 1 || wideKeys[Before] != 2) {
            Debug::Instance().Error("RunContainerProbe() : failed enum Set/Map!");
            return false;
        }

        namedNodes["value"].score = 83;
        Map<String, ReflectionProbeNode> copiedNodes = namedNodes;
        copiedNodes["value"].score = 91;
        if (namedLinks["null"] !is null) {
            Debug::Instance().Error("RunContainerProbe() : failed Map default null handle!");
            return false;
        }
        @namedLinks["root"] = root;
        Map<String, ReflectionProbeNode@> copiedLinks = namedLinks;
        namedLinks.erase("root");
        if (namedNodes["value"].score != 83 || copiedNodes["value"].score != 91 ||
            copiedLinks["root"] !is root || copiedLinks["null"] !is null) {
            Debug::Instance().Error("RunContainerProbe() : failed Map object/handle copy!");
            return false;
        }
        @namedLinks["root"] = copiedLinks["root"];

        Value packed;
        packed.set(uniqueLabels);
        Set<String> restoredLabels;
        if (!packed.get(restoredLabels) || restoredLabels.size() != 2 || !restoredLabels.contains("alpha") || !restoredLabels.contains("beta")) {
            Debug::Instance().Error("RunContainerProbe() : failed Set Value round trip!");
            return false;
        }
        packed.set(scores);
        Map<String, int> restoredScores;
        if (!packed.get(restoredScores) || restoredScores.size() != 2 || restoredScores["first"] != 17 || restoredScores["second"] != 29) {
            Debug::Instance().Error("RunContainerProbe() : failed Map Value round trip!");
            return false;
        }
        return true;
    }

    bool CheckRestoredGraph() const
    {
        return passed && label == "saved" && root !is null && root.score == 42 &&
            root.links.size() == 1 && links.size() == 2 &&
            root.next is root && root.links[0] is root && links[0] is root && links[1] is root &&
            constRoot is root && holder.alias is holder.value && holder.value.score == 77 && holder.GetSecret() == 32 &&
            modes.size() == 2 && modes[0] == Active && modes[1] == Dormant &&
            emptyGroups.size() == 2 && emptyGroups[0].size() == 0 &&
            emptyGroups[1].size() == 1 && emptyGroups[1][0] == 19 &&
            wideModes.size() == 2 && wideModes[0] == Far && wideModes[1] == Before &&
            CheckConstContainers(uniqueLabels, scores) && uniqueWideModes.size() == 2 &&
            uniqueWideModes.contains(Far) && uniqueWideModes.contains(Before) &&
            groupedIds.size() == 1 && groupedIds["odd"].size() == 16 &&
            groupedIds["odd"].contains(1) && groupedIds["odd"].contains(31) && !groupedIds["odd"].contains(0) &&
            namedNodes.size() == 1 && namedNodes["value"].score == 83 && namedLinks.size() == 2 &&
            namedLinks["root"] is root && namedLinks.contains("null") && namedLinks["null"] is null;
    }
}
