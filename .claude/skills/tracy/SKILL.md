---
name: tracy
description: Analyze a Tracy profiler capture (.tracy, or CSV exported from it) of SREngine for optimization — frame time, hot zones, self time, hitches/spikes, GPU zones, before/after comparison — and map zones to engine code. Use when the user gives a .tracy file or asks to profile/optimize from a Tracy capture.
argument-hint: "<capture.tracy> [--compare <baseline.tracy>] [focus: zone, system, spike]"
---

The user gave a Tracy capture to analyze. Arguments: `$ARGUMENTS`.

Running the exporter through this script is the allowed exception to the "no binaries" rule of CLAUDE.md: it only reads the capture. Do not run other Tracy tools (`tracy-profiler`, `tracy-capture`, ...) and do not run the engine to record a new capture — ask the user for one.

## 1. Export and report

From the repo root, foreground with `timeout: 600000` (in the background for captures over ~1 GB):
```
python .claude/scripts/tracy_analyze.py "<capture.tracy>" [--compare "<baseline.tracy>"] [--top 25] [--filter <zone substring>]
```
- The script runs `Resources/Engine/Utilities/tracy/tracy-csvexport.exe`, caches TSV exports in `%TEMP%\srengine-tracy\<capture>-<hash>\` (`zones.tsv`, `self.tsv`, `frames.tsv`, `gpu.tsv`, `events.tsv`) and prints the report (also saved as `report.txt` there). Repeated runs reuse the cache; `--force` re-exports.
- `--compare`: the baseline is "before", the main capture is "after"; + in deltas = slower.
- Export failure because of a version mismatch: convert the capture with `tracy-update.exe <old> <new>` (path in the error message) into the scratchpad and analyze the converted file.
- If the user gave CSV instead of `.tracy`, read its header and analyze it directly (Grep / short reads, no script).

## 2. Spikes (hitches)

If the frame `p99`/`max` is far above the median, or the user complains about stutters, or a zone is in "Spiky zones":
```
python .claude/scripts/tracy_analyze.py "<capture.tracy>" --spikes "<zone name>" [--spike-count 3]
```
- Zone: the main loop / frame root zone on the main thread from the inclusive table (the largest per-frame zone with ~1 call/frame), or the spiky zone itself.
- Shows the longest instances with the nested zone tree (siblings with the same name are merged), untracked time and what other threads did at that moment. The first run exports every zone event (`events.tsv`, may be hundreds of MB) — warn the user for long captures; `events.tsv` is never read whole, only Grep.

## 3. Interpretation

- Self time = where the time is spent; inclusive = which subsystem it belongs to. ms/frame is a sum over all threads: a worker-thread zone can exceed the frame time and does not necessarily limit FPS — check whether the main/render thread waits for it.
- Waiting zones (Wait, Lock, Fence, Present, Acquire, Submit, Sync, Sleep, Idle ...) are not CPU cost: they mean GPU-bound, vsync or contention. Look at what the other side is doing (GPU zones, the other thread in the spike report).
- Many calls per frame with small mean → per-call overhead, virtual calls, lookups, allocations, string building; Tracy itself costs ~10–30 ns per zone, so at tens of thousands of calls the zone distorts the measurement (suggest removing it or moving it up).
- Big max with small mean → hitch: resource/shader loading, pipeline creation, allocation of large buffers, rebuilding caches, GC-like cleanup, I/O on the main thread, lazy initialization.
- Large "untracked" time in a spike or big self time of a broad zone → missing zones; suggest where to add `SR_TRACY_ZONE` / `SR_TRACY_ZONE_N` (they conflict in one scope — `_N` only in a nested block).
- A Debug capture overstates CPU cost (no inlining, checked iterators, asserts): ask which configuration it was recorded in if unknown and say that only Release numbers are representative.

## 4. Mapping to code

`where` is the zone's source location (`file:line`). Read only the code around the hot zones (the function and its loops), search callers with Grep if the zone is a common helper. Before suggesting changes in a system, read its notes from CLAUDE.md (Render, Terrain, Physics, Shaders, GameProjects). Do not edit code unless the user asked; if asked, follow CLAUDE.md (minimal changes, no STL, no build).

## 5. Answer (in Russian, concise)

1. Frame: mean / median / p99 / max, FPS, who limits it (main thread, render thread, GPU, waiting).
2. 3–7 hot spots ordered by potential gain: zone, ms/frame (or spike size), link to the code `[File.cpp:123](path#L123)`, cause (fact from the capture vs hypothesis — mark which), concrete fix, expected gain.
3. For `--compare`: regressions and improvements with deltas, whether the frame time changed overall.
4. What to measure next: which zones to add, which scenario to capture.
