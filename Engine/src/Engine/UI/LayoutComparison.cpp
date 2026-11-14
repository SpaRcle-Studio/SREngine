//
// Created by Codex on 15.11.2026.
//

#include <Engine/UI/LayoutComparison.h>

#include <Graphics/UI/Canvas.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/TransformRect.h>
#include <Utils/UI/LayoutGroup.h>
#include <Utils/UI/GridLayoutGroup.h>
#include <Utils/UI/LayoutElement.h>
#include <Utils/UI/LayoutTestMetrics.h>
#include <Utils/UI/ContentSizeFitter.h>
#include <Utils/UI/AspectRatioFitter.h>
#include <Utils/UI/LayoutRebuilder.h>
#include <Utils/Serialization/JsonSerialization.h>
#include <Utils/Serialization/Serialization.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneUpdater.h>
#include <Utils/FileSystem/DirectoryVFSBackend.h>
#include <Utils/FileSystem/VFS.h>

#include <Codegen/LayoutComparison.generated.hpp>

namespace SR_CORE_UI_NS::LayoutComparisonTools {
    SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject> CreateSchedulingFixture(SR_UTILS_NS::GameObject& host) {
        auto pRoot = host.CreateChild("LayoutDirtyFixture");
        pRoot->SetTransform(SR_UTILS_NS::TransformRect::MakeShared<SR_UTILS_NS::TransformRect, SR_UTILS_NS::Transform>());
        auto pGroup = pRoot->AddComponent<SR_UTILS_NS::LayoutGroup>();
        auto pChild = pRoot->CreateChild("LayoutDirtyChild");
        pChild->SetTransform(SR_UTILS_NS::TransformRect::MakeShared<SR_UTILS_NS::TransformRect, SR_UTILS_NS::Transform>());
        auto pElement = pChild->AddComponent<SR_UTILS_NS::LayoutElement>();
        if (!pGroup || !pElement || !pRoot->PostLoad(true)) {
            pRoot->Destroy();
            return nullptr;
        }
        pRoot->Awake(false, true);
        pRoot->CheckActivity(true);
        return pRoot;
    }

    bool ApplyNode(SR_UTILS_NS::JsonDeserializer& input, SR_UTILS_NS::GameObject& object, const bool create) {
        auto&& pRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(&object);
        if (input.BeginObject(SR_UTILS_NS::SerializationId::Create("rect"))) {
            SR_MATH_NS::FVector2 anchorMin;
            SR_MATH_NS::FVector2 anchorMax;
            SR_MATH_NS::FVector2 pivot;
            SR_MATH_NS::FVector2 position;
            SR_MATH_NS::FVector2 size;
            SR_MATH_NS::FVector3 scale;
            SR_UTILS_NS::Serialization::Load(input, anchorMin, SR_UTILS_NS::SerializationId::Create("anchorMin"));
            SR_UTILS_NS::Serialization::Load(input, anchorMax, SR_UTILS_NS::SerializationId::Create("anchorMax"));
            SR_UTILS_NS::Serialization::Load(input, pivot, SR_UTILS_NS::SerializationId::Create("pivot"));
            SR_UTILS_NS::Serialization::Load(input, position, SR_UTILS_NS::SerializationId::Create("position"));
            SR_UTILS_NS::Serialization::Load(input, size, SR_UTILS_NS::SerializationId::Create("size"));
            SR_UTILS_NS::Serialization::Load(input, scale, SR_UTILS_NS::SerializationId::Create("scale"));
            pRect->SetAnchors(SR_UTILS_NS::RectAnchors(anchorMin, anchorMax));
            pRect->SetPivot(pivot);
            pRect->SetSize(size);
            pRect->SetAnchoredPosition(position);
            pRect->SetScale(scale);
            input.EndObject();
        }
        if (input.HasKey(SR_UTILS_NS::SerializationId::Create("active"))) {
            bool active = true;
            input.ReadBool(active, SR_UTILS_NS::SerializationId::Create("active"));
            object.SetEnabled(active);
        }
        const char* names[] = { "group", "grid", "fitter", "aspect", "reflow" };
        for (uint32_t i = 0; i < 5; ++i) {
            if (!input.BeginObject(SR_UTILS_NS::SerializationId::CreateFromString(names[i]))) {
                continue;
            }
            SR_UTILS_NS::Component::Ptr pComponent;
            switch (i) {
                case 0: pComponent = (create ? object.AddComponent<SR_UTILS_NS::LayoutGroup>() : object.GetComponent<SR_UTILS_NS::LayoutGroup>()).StaticCast<SR_UTILS_NS::Component>(); break;
                case 1: pComponent = (create ? object.AddComponent<SR_UTILS_NS::GridLayoutGroup>() : object.GetComponent<SR_UTILS_NS::GridLayoutGroup>()).StaticCast<SR_UTILS_NS::Component>(); break;
                case 2: pComponent = (create ? object.AddComponent<SR_UTILS_NS::ContentSizeFitter>() : object.GetComponent<SR_UTILS_NS::ContentSizeFitter>()).StaticCast<SR_UTILS_NS::Component>(); break;
                case 3: pComponent = (create ? object.AddComponent<SR_UTILS_NS::AspectRatioFitter>() : object.GetComponent<SR_UTILS_NS::AspectRatioFitter>()).StaticCast<SR_UTILS_NS::Component>(); break;
                case 4: pComponent = (create ? object.AddComponent<SR_UTILS_NS::LayoutTestMetrics>() : object.GetComponent<SR_UTILS_NS::LayoutTestMetrics>()).StaticCast<SR_UTILS_NS::Component>(); break;
            }
            if (!pComponent || !pComponent->Load(input)) {
                SR_ERROR("LayoutComparisonTools::ApplyNode() : failed to load fixture component {}.", names[i]);
                input.EndObject();
                return false;
            }
            input.EndObject();
        }
        const auto elements = SR_UTILS_NS::SerializationId::Create("elements");
        if (input.HasKey(elements)) {
            if (!create) {
                SR_ERROR("LayoutComparisonTools::ApplyNode() : dynamic element replacement is unsupported; edit reflow/group or rect instead.");
                return false;
            }
            const uint64_t count = input.BeginArray(elements);
            for (uint64_t i = 0; i < count; ++i) {
                if (!input.BeginItem(elements, static_cast<uint32_t>(i))) {
                    return false;
                }
                auto&& pElement = object.AddComponent<SR_UTILS_NS::LayoutElement>();
                if (!pElement || !pElement->Load(input)) {
                    return false;
                }
                input.EndItem();
            }
            if (count > 0) {
                input.EndArray();
            }
        }
        return true;
    }

    void ExportNode(SR_UTILS_NS::JsonSerializer& output, const SR_UTILS_NS::GameObject& object) {
        auto&& pRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(&object);
        const auto rect = pRect->GetLayoutRect();
        const auto pivot = pRect->GetPivot();
        const auto size = rect.Size();
        const SR_MATH_NS::FVector2 corners[] = {
            rect.Min(), { rect.Min().x, rect.Max().y }, rect.Max(), { rect.Max().x, rect.Min().y }
        };
        const char* cornerNames[] = { "corner0", "corner1", "corner2", "corner3" };
        for (uint32_t i = 0; i < 4; ++i) {
            const auto point = pRect->GetMatrix().TransformPoint({ corners[i].x, corners[i].y, 0.f });
            SR_UTILS_NS::Serialization::Save(output, SR_MATH_NS::FVector2(point.x, point.y), SR_UTILS_NS::SerializationId::CreateFromString(cornerNames[i]));
        }
        SR_UTILS_NS::Serialization::Save(output, SR_MATH_NS::FVector2(-size.x * pivot.x, -size.y * pivot.y), SR_UTILS_NS::SerializationId::Create("rectMin"));
        SR_UTILS_NS::Serialization::Save(output, size, SR_UTILS_NS::SerializationId::Create("rectSize"));
        SR_UTILS_NS::Serialization::Save(output, pRect->GetAnchors().min, SR_UTILS_NS::SerializationId::Create("anchorMin"));
        SR_UTILS_NS::Serialization::Save(output, pRect->GetAnchors().max, SR_UTILS_NS::SerializationId::Create("anchorMax"));
        SR_UTILS_NS::Serialization::Save(output, pivot, SR_UTILS_NS::SerializationId::Create("pivot"));
        SR_UTILS_NS::Serialization::Save(output, pRect->GetAnchoredPosition(), SR_UTILS_NS::SerializationId::Create("position"));
        SR_UTILS_NS::Serialization::Save(output, pRect->GetSizeDelta(), SR_UTILS_NS::SerializationId::Create("sizeDelta"));
        SR_UTILS_NS::Serialization::Save(output, pRect->GetOffsetMin(), SR_UTILS_NS::SerializationId::Create("offsetMin"));
        SR_UTILS_NS::Serialization::Save(output, pRect->GetOffsetMax(), SR_UTILS_NS::SerializationId::Create("offsetMax"));
        SR_UTILS_NS::Serialization::Save(output, pRect->GetScale(), SR_UTILS_NS::SerializationId::Create("scale"));
        const auto x = SR_UTILS_NS::LayoutUtility::GetMetrics(object, true);
        const auto y = SR_UTILS_NS::LayoutUtility::GetMetrics(object, false);
        output.WriteFloat(x.minimum, SR_UTILS_NS::SerializationId::Create("minWidth"));
        output.WriteFloat(x.preferred, SR_UTILS_NS::SerializationId::Create("preferredWidth"));
        output.WriteFloat(x.flexible, SR_UTILS_NS::SerializationId::Create("flexibleWidth"));
        output.WriteFloat(y.minimum, SR_UTILS_NS::SerializationId::Create("minHeight"));
        output.WriteFloat(y.preferred, SR_UTILS_NS::SerializationId::Create("preferredHeight"));
        output.WriteFloat(y.flexible, SR_UTILS_NS::SerializationId::Create("flexibleHeight"));
    }
}

namespace SR_CORE_UI_NS {
    void LayoutComparison::CheckDirtyScheduling() {
        SR_TRACY_ZONE;
        auto&& pHost = GetGameObject();
        if (!pHost || !GetScene() || pHost->GetTransform()->GetMeasurement() != SR_UTILS_NS::Measurement::Space3D) {
            SR_ERROR("LayoutComparison::CheckDirtyScheduling() : use a host with Transform3D in a separate test scene.");
            return;
        }
        auto pFirst = LayoutComparisonTools::CreateSchedulingFixture(*pHost);
        auto pSecond = LayoutComparisonTools::CreateSchedulingFixture(*pHost);
        if (!pFirst || !pSecond) {
            if (pFirst) {
                pFirst->Destroy();
            }
            if (pSecond) {
                pSecond->Destroy();
            }
            SR_ERROR("LayoutComparison::CheckDirtyScheduling() : failed to create fixtures.");
            return;
        }
        auto&& pUpdater = GetScene()->GetSceneUpdater();
        pUpdater->RebuildDirtyLayouts();
        bool passed = true;
        auto expect = [&](const uint64_t before, const uint64_t delta, const char* name) {
            pUpdater->RebuildDirtyLayouts();
            if (pUpdater->GetLayoutRebuildCount() - before != delta) {
                passed = false;
                SR_ERROR("LayoutComparison::CheckDirtyScheduling() : {} expected {} rebuilds, got {}.",
                    name, delta, pUpdater->GetLayoutRebuildCount() - before);
            }
        };
        uint64_t before = pUpdater->GetLayoutRebuildCount();
        expect(before, 0, "idle after layout writes");
        auto pGroup = pFirst->GetComponent<SR_UTILS_NS::LayoutGroup>();
        pGroup->SetSpacing(0.f);
        expect(before, 0, "unchanged property");
        auto pElement = pFirst->GetChildrenRef()[0]->GetComponent<SR_UTILS_NS::LayoutElement>();
        pElement->SetPreferredWidth(125.f);
        pElement->SetPreferredHeight(45.f);
        pGroup->SetSpacing(12.f);
        expect(before, 1, "coalesced metrics and group changes");
        before = pUpdater->GetLayoutRebuildCount();
        expect(before, 0, "idle after dirty pass");
        pFirst->GetChildrenRef()[0]->SetEnabled(false);
        pFirst->CheckActivity(true);
        expect(before, 1, "child disabled");
        before = pUpdater->GetLayoutRebuildCount();
        auto pChild = pFirst->GetChildrenRef()[0];
        pChild->SetEnabled(true);
        pFirst->CheckActivity(true);
        expect(before, 1, "child enabled");
        before = pUpdater->GetLayoutRebuildCount();
        SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(pFirst.Get())->SetSize({ 500.f, 300.f });
        expect(before, 1, "root resized");
        before = pUpdater->GetLayoutRebuildCount();
        pFirst->RemoveChild(pChild);
        if (!pSecond->AddChild(pChild)) {
            passed = false;
            SR_ERROR("LayoutComparison::CheckDirtyScheduling() : reparent failed.");
        }
        pSecond->CheckActivity(true);
        expect(before, 2, "reparent invalidates both roots without duplicate subtree rebuild");
        before = pUpdater->GetLayoutRebuildCount();
        pSecond->RemoveChild(pChild);
        if (!pSecond->AddChild(pChild, 0)) {
            passed = false;
            SR_ERROR("LayoutComparison::CheckDirtyScheduling() : sibling move failed.");
        }
        expect(before, 1, "sibling order changed");
        before = pUpdater->GetLayoutRebuildCount();
        pGroup->SetSpacing(13.f);
        pSecond->GetComponent<SR_UTILS_NS::LayoutGroup>()->SetSpacing(14.f);
        expect(before, 2, "independent UI roots");
        before = pUpdater->GetLayoutRebuildCount();
        pGroup->SetSpacing(15.f);
        pFirst->Destroy();
        expect(before, 0, "destroyed pending root");
        pSecond->Destroy();
        if (passed) {
            SR_LOG("LayoutComparison::CheckDirtyScheduling() : PASS.");
        }
    }

    void LayoutComparison::ExportCases() {
        SR_TRACY_ZONE;
        auto&& pHost = GetGameObject();

        SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::IVFSBackend> pBackend = new SR_UTILS_NS::DirectoryVFSBackend(m_input.GetFolder());
        SR_UTILS_NS::VFS::Instance().Mount(m_input.GetFolder(), pBackend.Get(), 0);
        pBackend.SetDeleter([](SR_UTILS_NS::IVFSBackend* pVFS) {
            SR_UTILS_NS::VFS::Instance().Unmount(pVFS);
            delete pVFS;
        });

        SR_UTILS_NS::JsonDeserializer input;
        if (!pHost || !GetScene() || m_output.empty() || !input.LoadFromFile(m_input)) {
            SR_ERROR("LayoutComparison::ExportCases() : attach to a scene and set input/output paths.");
            return;
        }
        // Fixtures configure existing components and must preserve their registered entity IDs.
        input.AddDontLoadTag("Inspector");
        SR_UTILS_NS::JsonSerializer output;
        output.SetWriteDefaults(true);
        const auto scalersId = SR_UTILS_NS::SerializationId::Create("scalers");
        const uint64_t scalerCount = input.BeginArray(scalersId);
        output.BeginArray(scalerCount, scalersId);
        for (uint64_t i = 0; i < scalerCount; ++i) {
            if (!input.BeginItem(scalersId, static_cast<uint32_t>(i))) {
                return;
            }
            SR_UTILS_NS::String id;
            SR_MATH_NS::FVector2 viewport;
            float_t dpi = 0.f;
            input.ReadString(id, SR_UTILS_NS::SerializationId::Create("id"));
            SR_UTILS_NS::Serialization::Load(input, viewport, SR_UTILS_NS::SerializationId::Create("viewport"));
            input.ReadFloat(dpi, SR_UTILS_NS::SerializationId::Create("dpi"));
            auto pScaler = SR_GRAPH_UI_NS::CanvasScaler::MakeShared<SR_GRAPH_UI_NS::CanvasScaler>();
            if (!input.BeginObject(SR_UTILS_NS::SerializationId::Create("config")) || !pScaler->Load(input)) {
                pScaler.AutoFree();
                SR_ERROR("LayoutComparison::ExportCases() : invalid scaler {}.", id);
                return;
            }
            input.EndObject();
            output.BeginItem(scalersId);
            output.WriteString(id.c_str(), SR_UTILS_NS::SerializationId::Create("id"));
            output.WriteFloat(pScaler->CalculateScaleFactorForViewport(viewport, dpi), SR_UTILS_NS::SerializationId::Create("scaleFactor"));
            output.WriteFloat(pScaler->CalculateReferencePixelsPerUnit(), SR_UTILS_NS::SerializationId::Create("referencePixelsPerUnit"));
            output.EndItem();
            pScaler.AutoFree();
            input.EndItem();
        }
        if (scalerCount > 0) {
            input.EndArray();
        }
        output.EndArray();
        const auto casesId = SR_UTILS_NS::SerializationId::Create("cases");
        const auto nodesId = SR_UTILS_NS::SerializationId::Create("nodes");
        const auto changesId = SR_UTILS_NS::SerializationId::Create("changes");
        const uint64_t cases = input.BeginArray(casesId);
        output.BeginArray(cases, casesId);
        for (uint64_t c = 0; c < cases; ++c) {
            if (!input.BeginItem(casesId, static_cast<uint32_t>(c))) {
                return;
            }
            SR_UTILS_NS::String id;
            input.ReadString(id, SR_UTILS_NS::SerializationId::Create("id"));
            const uint64_t count = input.BeginArray(nodesId);
            SR_UTILS_NS::Vector<SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject>> nodes;
            bool valid = count > 0;
            for (uint64_t n = 0; valid && n < count; ++n) {
                valid = input.BeginItem(nodesId, static_cast<uint32_t>(n));
                int32_t parent = -1;
                input.ReadInt(parent, SR_UTILS_NS::SerializationId::Create("parent"));
                valid &= parent < static_cast<int32_t>(n) && (n == 0 ? parent == -1 : parent >= 0);
                if (!valid) {
                    break;
                }
                auto&& pParent = parent < 0 ? pHost : nodes[parent];
                auto pNode = pParent->CreateChild("LayoutComparisonFixture");
                pNode->SetTransform(SR_UTILS_NS::TransformRect::MakeShared<SR_UTILS_NS::TransformRect, SR_UTILS_NS::Transform>());
                nodes.emplace_back(pNode);
                valid = LayoutComparisonTools::ApplyNode(input, *pNode, true);
                input.EndItem();
            }
            input.EndArray();
            if (!valid) {
                if (!nodes.empty()) {
                    nodes[0]->Destroy();
                }
                SR_ERROR("LayoutComparison::ExportCases() : invalid fixture {}. No result written.", id);
                return;
            }
            if (!nodes[0]->PostLoad(true)) {
                nodes[0]->Destroy();
                SR_ERROR("LayoutComparison::ExportCases() : fixture PostLoad failed.");
                return;
            }
            nodes[0]->Awake(false, true);
            nodes[0]->CheckActivity(true);
            output.BeginItem(casesId);
            output.WriteString(id.c_str(), SR_UTILS_NS::SerializationId::Create("id"));
            const auto statesId = SR_UTILS_NS::SerializationId::Create("states");
            output.BeginArray(3, statesId);
            for (uint32_t phase = 0; phase < 3; ++phase) {
                if (phase == 1 && input.HasKey(changesId)) {
                    const uint64_t changes = input.BeginArray(changesId);
                    for (uint64_t i = 0; i < changes; ++i) {
                        if (!input.BeginItem(changesId, static_cast<uint32_t>(i))) {
                            valid = false;
                            break;
                        }
                        int32_t index = -1;
                        input.ReadInt(index, SR_UTILS_NS::SerializationId::Create("node"));
                        if (index < 0 || index >= static_cast<int32_t>(nodes.size())) {
                            valid = false;
                            break;
                        }
                        if (input.HasKey(SR_UTILS_NS::SerializationId::Create("targetParent"))) {
                            int32_t parent = -1;
                            int32_t sibling = -1;
                            input.ReadInt(parent, SR_UTILS_NS::SerializationId::Create("targetParent"));
                            if (input.HasKey(SR_UTILS_NS::SerializationId::Create("siblingIndex"))) {
                                input.ReadInt(sibling, SR_UTILS_NS::SerializationId::Create("siblingIndex"));
                            }
                            if (index == 0 || parent < 0 || parent >= index) {
                                valid = false;
                                break;
                            }
                            auto pOldParent = nodes[index]->GetParent();
                            pOldParent->RemoveChild(nodes[index].Get());
                            valid &= nodes[parent]->AddChild(nodes[index].Get(), sibling);
                        }
                        valid &= LayoutComparisonTools::ApplyNode(input, *nodes[index], false);
                        input.EndItem();
                    }
                    if (changes > 0) {
                        input.EndArray();
                    }
                    nodes[0]->Awake(false, true);
                    nodes[0]->CheckActivity(true);
                }
                const uint32_t rebuilds = phase == 2 ? 100 : 1;
                for (uint32_t i = 0; i < rebuilds; ++i) {
                    SR_UTILS_NS::LayoutRebuilder::Rebuild(*nodes[0]);
                }
                output.BeginItem(statesId);
                output.BeginArray(nodes.size(), nodesId);
                for (auto&& pNode : nodes) {
                    output.BeginItem(nodesId);
                    LayoutComparisonTools::ExportNode(output, *pNode);
                    output.EndItem();
                }
                output.EndArray();
                output.EndItem();
            }
            output.EndArray();
            output.EndItem();
            nodes[0]->Destroy();
            input.EndItem();
            if (!valid) {
                SR_ERROR("LayoutComparison::ExportCases() : invalid dynamic changes in {}. No result written.", id);
                return;
            }
        }
        output.EndArray();
        if (cases > 0) {
            input.EndArray();
        }
        if (!output.SaveToFile(m_output)) {
            SR_ERROR("LayoutComparison::ExportCases() : failed to write {}.", m_output);
        }
    }
}
