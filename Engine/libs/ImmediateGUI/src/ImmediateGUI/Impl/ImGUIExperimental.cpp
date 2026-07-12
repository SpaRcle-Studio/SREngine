//
// ImGUIExperimental: layout helpers implemented as extension (no imgui edits)
//

#include <ImmediateGUI/Impl/ImGUIExperimental.h>

#ifdef SR_USE_IMGUI

namespace SR_GRAPH_GUI_NS::Immediate::Experimental {
    namespace {
        enum class LayoutKind : uint8_t { Horizontal, Vertical };

        struct LayoutState {
            LayoutKind kind = LayoutKind::Horizontal;
            ImGuiID layoutId = 0;
            ImVec2 startScreenPos = ImVec2(0, 0);
            ImVec2 requestedSize = ImVec2(0, 0);
            ImVec2 availAtBegin = ImVec2(0, 0);

            int currentChunkIndex = 0;
            int currentSpringIndex = 0;
            float maxCross = 0.0f;

            // current chunk placement
            ImVec2 currentChunkPos = ImVec2(0, 0);
        };

        struct CachedLayout {
            LayoutKind kind = LayoutKind::Horizontal;
            // chunk sizes from previous frame (main axis + cross axis)
            std::vector<float> chunkMain;
            std::vector<float> chunkCross;
            // spring specs between chunks (size = chunks-1 typically)
            std::vector<float> springWeight;
            std::vector<float> springSpacing;
        };

        thread_local std::vector<LayoutState> g_layoutStack;
        thread_local std::unordered_map<ImGuiID, CachedLayout> g_cachedLayouts;

        static LayoutState* Current() {
            if (g_layoutStack.empty()) {
                return nullptr;
            }
            return &g_layoutStack.back();
        }

        static float ResolveSpacingX(float spacing) {
            return (spacing >= 0.0f) ? spacing : ImGui::GetStyle().ItemSpacing.x;
        }

        static float ResolveSpacingY(float spacing) {
            return (spacing >= 0.0f) ? spacing : ImGui::GetStyle().ItemSpacing.y;
        }

        static CachedLayout& GetCached(ImGuiID id, LayoutKind kind) {
            auto& c = g_cachedLayouts[id];
            c.kind = kind;
            return c;
        }

        static float GetAvailableMain(const LayoutState& st) {
            if (st.kind == LayoutKind::Horizontal) {
                return (st.requestedSize.x > 0.0f) ? st.requestedSize.x : st.availAtBegin.x;
            }
            return (st.requestedSize.y > 0.0f) ? st.requestedSize.y : st.availAtBegin.y;
        }

        static float GetCachedChunkMain(const CachedLayout& c, int idx) {
            if (idx < 0 || idx >= (int)c.chunkMain.size()) {
                return 0.0f;
            }
            return c.chunkMain[idx];
        }

        static float GetCachedSpringWeight(const CachedLayout& c, int idx) {
            if (idx < 0 || idx >= (int)c.springWeight.size()) {
                return 0.0f;
            }
            return c.springWeight[idx];
        }

        static float GetCachedSpringSpacing(const CachedLayout& c, int idx) {
            if (idx < 0 || idx >= (int)c.springSpacing.size()) {
                return 0.0f;
            }
            return c.springSpacing[idx];
        }

        static void EnsureSize(std::vector<float>& v, int n) {
            if ((int)v.size() < n) {
                v.resize(n, 0.0f);
            }
        }

        static void BeginChunkAt(const LayoutState& st, const ImVec2& pos) {
            ImGui::SetCursorScreenPos(pos);
            ImGui::BeginGroup();
        }

        static void EndChunkAndStore(LayoutState& st, CachedLayout& cache) {
            ImGui::EndGroup();
            const ImVec2 size = ImGui::GetItemRectSize();
            const float main = (st.kind == LayoutKind::Horizontal) ? size.x : size.y;
            const float cross = (st.kind == LayoutKind::Horizontal) ? size.y : size.x;

            EnsureSize(cache.chunkMain, st.currentChunkIndex + 1);
            EnsureSize(cache.chunkCross, st.currentChunkIndex + 1);
            cache.chunkMain[st.currentChunkIndex] = main;
            cache.chunkCross[st.currentChunkIndex] = cross;
            st.maxCross = ImMax(st.maxCross, cross);
        }

        // Compute spring extra sizes using cached chunk/spring data.
        // We only need the prefix sum up to a given spring index to place next chunk.
        static float ComputePrefixOffsetMain(const LayoutState& st, const CachedLayout& cache, int nextChunkIndex) {
            const float available = GetAvailableMain(st);

            // Predict total occupied space using cached arrays.
            const int predictedChunks = ImMax(nextChunkIndex + 1, (int)cache.chunkMain.size());
            const int predictedSprings = ImMax(nextChunkIndex, (int)cache.springWeight.size());

            float chunksSum = 0.0f;
            for (int i = 0; i < predictedChunks; ++i) {
                chunksSum += GetCachedChunkMain(cache, i);
            }

            float spacingSum = 0.0f;
            for (int i = 0; i < predictedSprings; ++i) {
                spacingSum += GetCachedSpringSpacing(cache, i);
            }

            const float occupied = chunksSum + spacingSum;
            const float free = ImMax(available - occupied, 0.0f);

            float totalWeight = 0.0f;
            for (int i = 0; i < predictedSprings; ++i) {
                const float w = GetCachedSpringWeight(cache, i);
                if (w > 0.0f) {
                    totalWeight += w;
                }
            }

            // Prefix sum for offset: chunks[0..nextChunkIndex-1] + springs[0..nextChunkIndex-1] (spacing + extra)
            float offset = 0.0f;
            float weightPrefix = 0.0f;
            float extraPrefix = 0.0f;

            // We mimic imgui-node-editor's distribution: each spring gets floor(free * prefix/total), last spring gets remainder.
            int lastWeighted = -1;
            for (int i = 0; i < predictedSprings; ++i) {
                if (GetCachedSpringWeight(cache, i) > 0.0f) {
                    lastWeighted = i;
                }
            }

            float usedExtra = 0.0f;
            for (int i = 0; i < nextChunkIndex; ++i) {
                offset += GetCachedChunkMain(cache, i);
                offset += GetCachedSpringSpacing(cache, i);

                const float w = GetCachedSpringWeight(cache, i);
                if (w > 0.0f && totalWeight > 0.0f && free > 0.0f) {
                    float extra = 0.0f;
                    if (i == lastWeighted) {
                        extra = ImMax(free - usedExtra, 0.0f);
                    }
                    else {
                        // incremental floor keeps stability
                        const float nextPrefix = weightPrefix + w;
                        const float spanEnd = ImFloor(free * nextPrefix / totalWeight);
                        const float spanStart = ImFloor(free * weightPrefix / totalWeight);
                        extra = spanEnd - spanStart;
                    }
                    usedExtra += extra;
                    extraPrefix += extra;
                    weightPrefix += w;
                }
                else if (w > 0.0f) {
                    weightPrefix += w;
                }

                offset += extraPrefix - (offset - (offset - extraPrefix)); // no-op placeholder
            }

            // Note: we already accumulated extras in extraPrefix, but didn't add to offset per-step.
            // Add total extra for springs before nextChunkIndex.
            offset += extraPrefix;
            return offset;
        }
    }

    void BeginHorizontal(const char* str_id, const ImVec2& size, float /*align*/) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        const ImGuiID id = window->GetID(str_id);

        LayoutState st;
        st.kind = LayoutKind::Horizontal;
        st.layoutId = id;
        st.requestedSize = size;
        st.availAtBegin = ImGui::GetContentRegionAvail();
        st.startScreenPos = ImGui::GetCursorScreenPos();
        st.currentChunkIndex = 0;
        st.currentSpringIndex = 0;
        st.currentChunkPos = st.startScreenPos;
        st.maxCross = 0.0f;

        // Ensure cache exists
        (void)GetCached(id, LayoutKind::Horizontal);

        g_layoutStack.emplace_back(st);
        BeginChunkAt(g_layoutStack.back(), st.currentChunkPos);
    }

    void BeginHorizontal(const void* ptr_id, const ImVec2& /*size*/, float /*align*/) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        const ImGuiID id = window->GetID(ptr_id);

        LayoutState st;
        st.kind = LayoutKind::Horizontal;
        st.layoutId = id;
        st.requestedSize = ImVec2(0, 0);
        st.availAtBegin = ImGui::GetContentRegionAvail();
        st.startScreenPos = ImGui::GetCursorScreenPos();
        st.currentChunkIndex = 0;
        st.currentSpringIndex = 0;
        st.currentChunkPos = st.startScreenPos;
        st.maxCross = 0.0f;

        (void)GetCached(id, LayoutKind::Horizontal);

        g_layoutStack.emplace_back(st);
        BeginChunkAt(g_layoutStack.back(), st.currentChunkPos);
    }

    void EndHorizontal() {
        LayoutState* state = Current();
        if (!state) {
            // Mismatch; keep ImGui state untouched.
            return;
        }

        if (state->kind != LayoutKind::Horizontal) {
            // Wrong end; keep stack intact.
            return;
        }

        auto& cache = GetCached(state->layoutId, LayoutKind::Horizontal);
        EndChunkAndStore(*state, cache);

        // Trim cache to what was used this frame (chunks = springs+1)
        const int usedChunks = state->currentChunkIndex + 1;
        const int usedSprings = state->currentSpringIndex;
        if ((int)cache.chunkMain.size() > usedChunks) cache.chunkMain.resize(usedChunks);
        if ((int)cache.chunkCross.size() > usedChunks) cache.chunkCross.resize(usedChunks);
        if ((int)cache.springWeight.size() > usedSprings) cache.springWeight.resize(usedSprings);
        if ((int)cache.springSpacing.size() > usedSprings) cache.springSpacing.resize(usedSprings);

        // Emit bounding item for the whole layout so parent layout advances correctly.
        const float available = GetAvailableMain(*state);
        const ImVec2 dummySize = ImVec2(available, state->maxCross);
        ImGui::SetCursorScreenPos(state->startScreenPos);
        ImGui::Dummy(dummySize);

        g_layoutStack.pop_back();
        return;
    }

    void BeginVertical(const char* str_id, const ImVec2& /*size*/, float /*align*/) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        const ImGuiID id = window->GetID(str_id);

        LayoutState st;
        st.kind = LayoutKind::Vertical;
        st.layoutId = id;
        st.requestedSize = ImVec2(0, 0);
        st.availAtBegin = ImGui::GetContentRegionAvail();
        st.startScreenPos = ImGui::GetCursorScreenPos();
        st.currentChunkIndex = 0;
        st.currentSpringIndex = 0;
        st.currentChunkPos = st.startScreenPos;
        st.maxCross = 0.0f;

        (void)GetCached(id, LayoutKind::Vertical);

        g_layoutStack.emplace_back(st);
        BeginChunkAt(g_layoutStack.back(), st.currentChunkPos);
    }

    void BeginVertical(const void* ptr_id, const ImVec2& /*size*/, float /*align*/) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        const ImGuiID id = window->GetID(ptr_id);

        LayoutState st;
        st.kind = LayoutKind::Vertical;
        st.layoutId = id;
        st.requestedSize = ImVec2(0, 0);
        st.availAtBegin = ImGui::GetContentRegionAvail();
        st.startScreenPos = ImGui::GetCursorScreenPos();
        st.currentChunkIndex = 0;
        st.currentSpringIndex = 0;
        st.currentChunkPos = st.startScreenPos;
        st.maxCross = 0.0f;

        (void)GetCached(id, LayoutKind::Vertical);

        g_layoutStack.emplace_back(st);
        BeginChunkAt(g_layoutStack.back(), st.currentChunkPos);
    }

    void EndVertical() {
        LayoutState* state = Current();
        if (!state) {
            return;
        }

        if (state->kind != LayoutKind::Vertical) {
            return;
        }

        auto& cache = GetCached(state->layoutId, LayoutKind::Vertical);
        EndChunkAndStore(*state, cache);

        const int usedChunks = state->currentChunkIndex + 1;
        const int usedSprings = state->currentSpringIndex;
        if ((int)cache.chunkMain.size() > usedChunks) cache.chunkMain.resize(usedChunks);
        if ((int)cache.chunkCross.size() > usedChunks) cache.chunkCross.resize(usedChunks);
        if ((int)cache.springWeight.size() > usedSprings) cache.springWeight.resize(usedSprings);
        if ((int)cache.springSpacing.size() > usedSprings) cache.springSpacing.resize(usedSprings);

        // For vertical, keep auto-height (no forced available main). Use accumulated height.
        float totalMain = 0.0f;
        for (int i = 0; i < usedChunks; ++i) totalMain += cache.chunkMain[i];
        for (int i = 0; i < usedSprings; ++i) totalMain += cache.springSpacing[i];
        const ImVec2 dummySize = ImVec2(state->maxCross, totalMain);
        ImGui::SetCursorScreenPos(state->startScreenPos);
        ImGui::Dummy(dummySize);

        g_layoutStack.pop_back();
    }

    void Spring(float weight, float spacing) {
        LayoutState* state = Current();

        // No active layout: treat as a normal spacer.
        if (!state) {
            const float s = ResolveSpacingY(spacing);
            if (s > 0.0f) {
                ImGui::Dummy(ImVec2(0.0f, s));
            }
            return;
        }

        auto& cache = GetCached(state->layoutId, state->kind);

        // Finish current chunk (measure + store).
        EndChunkAndStore(*state, cache);

        // Store spring spec into cache for stability.
        EnsureSize(cache.springWeight, state->currentSpringIndex + 1);
        EnsureSize(cache.springSpacing, state->currentSpringIndex + 1);

        const float resolvedSpacing = (state->kind == LayoutKind::Horizontal) ? ResolveSpacingX(spacing) : ResolveSpacingY(spacing);
        cache.springWeight[state->currentSpringIndex] = (weight < 0.0f) ? 0.0f : weight;
        cache.springSpacing[state->currentSpringIndex] = resolvedSpacing;

        // Advance indices.
        state->currentSpringIndex++;
        state->currentChunkIndex++;

        // Place next chunk based on cached predictions (previous frame + what we have so far).
        const int nextChunkIndex = state->currentChunkIndex;
        float offsetMain = 0.0f;

        // Compute offset from start to next chunk.
        offsetMain = ComputePrefixOffsetMain(*state, cache, nextChunkIndex);

        if (state->kind == LayoutKind::Horizontal) {
            state->currentChunkPos = ImVec2(state->startScreenPos.x + offsetMain, state->startScreenPos.y);
        }
        else {
            state->currentChunkPos = ImVec2(state->startScreenPos.x, state->startScreenPos.y + offsetMain);
        }

        BeginChunkAt(*state, state->currentChunkPos);
    }
}

#endif // SR_USE_IMGUI

