#
# Created by Monika on 28.11.2026.
#
# Analyzes a Tracy capture (.tracy) through tracy-csvexport from Resources/Engine/Utilities/tracy.
# Exports are cached as TSV in the output directory (default: %TEMP%/srengine-tracy/<capture>-<hash>),
# the report goes to stdout and to <output directory>/report.txt.
#
# Usage: python .claude/scripts/tracy_analyze.py <capture.tracy> [--compare <baseline.tracy>] [--top N]
#                                               [--filter <zone substring>] [--spikes <zone name>] [--spike-count N]
#                                               [--out <dir>] [--force]
#   --compare  per-frame diff against a baseline capture (baseline = before, capture = after)
#   --spikes   longest instances of the zone with the nested zone tree (exports every zone event, may be large)

import argparse
import hashlib
import os
import subprocess
import sys
import tempfile

ROOT_DIRECTORY = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
TRACY_DIRECTORY = os.path.join(ROOT_DIRECTORY, "Resources", "Engine", "Utilities", "tracy")
EXPORTER = os.path.join(TRACY_DIRECTORY, "tracy-csvexport.exe")
UPDATER = os.path.join(TRACY_DIRECTORY, "tracy-update.exe")

SEPARATOR = "\t"
EXPORT_TIMEOUT = 1800
NAME_WIDTH = 52
PLACE_WIDTH = 60
SPIKE_TREE_DEPTH = 8
SPIKE_TREE_LINES = 60
SPIKE_OTHER_THREADS = 8

BASE_FRAME_SET_NAMES = ("Frame", "???", "")


def Log(message):
    sys.stderr.write(message + "\n")
    sys.stderr.flush()


def ToFloat(value):
    try:
        return float(value)
    except (TypeError, ValueError):
        return 0.0


def ToInt(value):
    try:
        return int(value)
    except (TypeError, ValueError):
        return 0


def FormatTime(nanoseconds):
    if nanoseconds >= 1000000.0:
        return f"{nanoseconds / 1000000.0:.2f}ms"
    if nanoseconds >= 1000.0:
        return f"{nanoseconds / 1000.0:.1f}us"
    return f"{nanoseconds:.0f}ns"


def FormatDelta(nanoseconds):
    sign = "+" if nanoseconds >= 0 else "-"
    return sign + FormatTime(abs(nanoseconds))


def Truncate(text, width):
    if len(text) <= width:
        return text
    return text[:width - 3] + "..."


def ShortPath(path):
    if not path:
        return ""

    normalized = os.path.normpath(path).replace("\\", "/")
    root =ROOT_DIRECTORY.replace("\\", "/").rstrip("/") + "/"
    if normalized.lower().startswith(root.lower()):
        return normalized[len(root):]

    for marker in ("/Engine/", "/Resources/", "/Games/"):
        index = normalized.find(marker)
        if index >= 0:
            return normalized[index + 1:]

    return "/".join(normalized.split("/")[-3:])


def FormatPlace(path, line):
    shortPath = ShortPath(path)
    if not shortPath:
        return ""
    place = f"{shortPath}:{line}" if line and line != "0" else shortPath
    if len(place) <= PLACE_WIDTH:
        return place
    return "..." + place[-(PLACE_WIDTH - 3):]


def FormatTable(columns, rows):
    widths = [len(title) for title, _ in columns]
    for row in rows:
        for index, cell in enumerate(row):
            widths[index] = max(widths[index], len(cell))

    def FormatRow(cells):
        parts = []
        for index, cell in enumerate(cells):
            if columns[index][1] == "<":
                parts.append(cell.ljust(widths[index]))
            else:
                parts.append(cell.rjust(widths[index]))
        return "  ".join(parts).rstrip()

    lines = [FormatRow([title for title, _ in columns])]
    for row in rows:
        lines.append(FormatRow(row))
    return lines


def GetOutputDirectory(tracePath, outDirectory):
    if outDirectory:
        return os.path.abspath(outDirectory)

    absolutePath = os.path.abspath(tracePath)
    digest = hashlib.md5(absolutePath.lower().encode("utf-8")).hexdigest()[:8]
    stem = os.path.splitext(os.path.basename(absolutePath))[0]
    return os.path.join(tempfile.gettempdir(), "srengine-tracy", f"{stem}-{digest}")


def IsCacheValid(outputPath, tracePath):
    return os.path.isfile(outputPath) \
        and os.path.getsize(outputPath) > 0 \
        and os.path.getmtime(outputPath) >= os.path.getmtime(tracePath)


def RunTool(arguments, stdoutFile):
    creationFlags = subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0
    return subprocess.run(arguments, stdout=stdoutFile, stderr=subprocess.PIPE, stdin=subprocess.DEVNULL,
                          timeout=EXPORT_TIMEOUT, creationflags=creationFlags)


def RunExport(tracePath, options, outputPath, force):
    if not force and IsCacheValid(outputPath, tracePath):
        return True, ""

    temporaryPath = outputPath + ".part"
    try:
        with open(temporaryPath, "wb") as outputFile:
            process = RunTool([EXPORTER, *options, tracePath], outputFile)
    except subprocess.TimeoutExpired:
        os.remove(temporaryPath)
        return False, f"timeout ({EXPORT_TIMEOUT}s)"

    if process.returncode != 0:
        os.remove(temporaryPath)
        error = process.stderr.decode("utf-8", "replace").strip()
        return False, error or f"exit code {process.returncode}"

    os.replace(temporaryPath, outputPath)
    return True, ""


def GetExporterVersion():
    try:
        process = subprocess.run([EXPORTER, "-V"], capture_output=True, stdin=subprocess.DEVNULL, timeout=60,
                                 creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0)
        return (process.stdout or process.stderr).decode("utf-8", "replace").strip()
    except Exception as exception:
        return f"unknown ({exception})"


def GetFilterSuffix(filterText):
    if not filterText:
        return ""
    return "-" + hashlib.md5(filterText.encode("utf-8")).hexdigest()[:6]


def ExportCapture(tracePath, outputDirectory, filterText, force):
    os.makedirs(outputDirectory, exist_ok=True)

    filterOptions = ["-f", filterText] if filterText else []
    suffix = GetFilterSuffix(filterText)
    paths = {
        "zones": os.path.join(outputDirectory, f"zones{suffix}.tsv"),
        "self": os.path.join(outputDirectory, f"self{suffix}.tsv"),
        "frames": os.path.join(outputDirectory, "frames.tsv"),
        "gpu": os.path.join(outputDirectory, f"gpu{suffix}.tsv"),
    }
    warnings = []

    Log(f"tracy_analyze.py : exporting zones of {tracePath}")
    success, error = RunExport(tracePath, ["-s", SEPARATOR, "-t", "95", *filterOptions], paths["zones"], force)
    if not success:
        success, error = RunExport(tracePath, ["-s", SEPARATOR, *filterOptions], paths["zones"], force)
    if not success:
        raise RuntimeError(f"zone export failed: {error}")

    Log("tracy_analyze.py : exporting self times")
    success, error = RunExport(tracePath, ["-s", SEPARATOR, "-e", *filterOptions], paths["self"], force)
    if not success:
        warnings.append(f"self time export failed: {error}")

    Log("tracy_analyze.py : exporting frames")
    success, error = RunExport(tracePath, ["-s", SEPARATOR, "-F", "-S"], paths["frames"], force)
    if not success:
        success, error = RunExport(tracePath, ["-s", SEPARATOR, "-F"], paths["frames"], force)
    if not success:
        warnings.append(f"frame export failed (exporter without -F?): {error}")

    Log("tracy_analyze.py : exporting gpu zones")
    success, error = RunExport(tracePath, ["-s", SEPARATOR, "-g", *filterOptions], paths["gpu"], force)
    if not success:
        warnings.append(f"gpu export failed: {error}")

    return paths, warnings


def ReadTable(path):
    rows = []
    if not os.path.isfile(path):
        return rows

    with open(path, "r", encoding="utf-8", errors="replace") as tableFile:
        header = tableFile.readline().rstrip("\r\n").split(SEPARATOR)
        if len(header) < 2:
            return rows

        for line in tableFile:
            parts = line.rstrip("\r\n").split(SEPARATOR)

            # the exporter does not quote fields: a separator inside the name shifts the columns
            if len(parts) > len(header):
                extra = len(parts) - len(header)
                parts = [SEPARATOR.join(parts[:extra + 1])] + parts[extra + 1:]

            if len(parts) != len(header):
                continue

            rows.append(dict(zip(header, parts)))

    return rows


def LoadZones(paths):
    selfTimes = {}
    for row in ReadTable(paths["self"]):
        key = (row["name"], row["src_file"], row["src_line"])
        selfTimes[key] = (ToFloat(row["total_ns"]), ToFloat(row["max_ns"]))

    zones = []
    for row in ReadTable(paths["zones"]):
        key = (row["name"], row["src_file"], row["src_line"])
        total = ToFloat(row["total_ns"])
        selfTotal, selfMax = selfTimes.get(key, (total, ToFloat(row["max_ns"])))
        zones.append({
            "name": row["name"],
            "file": row["src_file"],
            "line": row["src_line"],
            "total": total,
            "perc": ToFloat(row["total_perc"]),
            "count": ToInt(row["counts"]),
            "mean": ToFloat(row["mean_ns"]),
            "min": ToFloat(row["min_ns"]),
            "max": ToFloat(row["max_ns"]),
            "std": ToFloat(row["std_ns"]),
            "p95": ToFloat(row["percentile_ns"]) if "percentile_ns" in row else None,
            "self": selfTotal,
            "selfMax": selfMax,
        })

    return zones


def LoadGpuZones(paths):
    groups = {}
    for row in ReadTable(paths["gpu"]):
        key = (row["name"], row["src_file"])
        duration = ToFloat(row["GPU execution time"])
        group = groups.setdefault(key, {"name": row["name"], "file": row["src_file"], "count": 0, "total": 0.0, "max": 0.0})
        group["count"] += 1
        group["total"] += duration
        group["max"] = max(group["max"], duration)
    return list(groups.values())


def LoadFrames(paths):
    rows = ReadTable(paths["frames"])
    frameSets = [row for row in rows if not row.get("section")]
    sections = [row for row in rows if row.get("section")]
    return frameSets, sections


def GetBaseFrameSet(frameSets):
    # the set with the most frames is the real frame loop: the base "Frame" set may hold only a few marks
    continuous = [row for row in frameSets if row["continuous"] == "1"]
    candidates = continuous or frameSets
    if not candidates:
        return None
    return max(candidates, key=lambda row: (ToInt(row["counts"]), row["frame_set"] in BASE_FRAME_SET_NAMES))


def GetCaptureSpan(baseFrameSet, zones):
    if baseFrameSet and ToFloat(baseFrameSet["span_perc"]) > 0.0:
        return ToFloat(baseFrameSet["total_ns"]) * 100.0 / ToFloat(baseFrameSet["span_perc"])

    for zone in sorted(zones, key=lambda item: item["perc"], reverse=True):
        if zone["perc"] > 0.01:
            return zone["total"] * 100.0 / zone["perc"]

    return 0.0


class Capture:
    def __init__(self, tracePath, outputDirectory, filterText, force):
        self.path = tracePath
        self.outputDirectory = outputDirectory
        self.paths, self.warnings = ExportCapture(tracePath, outputDirectory, filterText, force)
        self.zones = LoadZones(self.paths)
        self.gpuZones = LoadGpuZones(self.paths)
        self.frameSets, self.sections = LoadFrames(self.paths)
        self.baseFrameSet = GetBaseFrameSet(self.frameSets)
        self.span = GetCaptureSpan(self.baseFrameSet, self.zones)

        self.frameCount = ToInt(self.baseFrameSet["counts"]) if self.baseFrameSet else 0
        if self.frameCount > 0:
            self.divisor = float(self.frameCount)
            self.unit = "frame"
        else:
            self.divisor = max(self.span / 1000000000.0, 1e-9)
            self.unit = "s"


def AppendFrames(lines, capture):
    lines.append("")
    lines.append("== Frames ==")
    if not capture.frameSets:
        lines.append("no frame data (no FrameMark in the capture or the exporter has no -F); values below are per second")
        return

    columns = [("frame set", "<"), ("frames", ">"), ("mean", ">"), ("fps", ">"), ("median", ">"), ("p90", ">"),
               ("p99", ">"), ("p99.9", ">"), ("max", ">"), ("cv%", ">")]

    def MakeRow(name, row):
        mean = ToFloat(row["mean_ns"])
        fps = f"{1000000000.0 / mean:.1f}" if mean > 0.0 else "-"
        return [Truncate(name, NAME_WIDTH), row["counts"], FormatTime(mean), fps, FormatTime(ToFloat(row["median_ns"])),
                FormatTime(ToFloat(row["p90_ns"])), FormatTime(ToFloat(row["p99_ns"])), FormatTime(ToFloat(row["p99_9_ns"])),
                FormatTime(ToFloat(row["max_ns"])), f"{ToFloat(row['cv_perc']):.0f}"]

    rows = [MakeRow(row["frame_set"], row) for row in capture.frameSets]
    rows += [MakeRow(f"{row['frame_set']} / section: {row['section']}", row) for row in capture.sections]
    lines.extend(FormatTable(columns, rows))
    lines.append(f"capture span {capture.span / 1000000000.0:.1f}s; per-frame values below are divided by "
                 f"{capture.frameCount} frames of '{capture.baseFrameSet['frame_set']}'")


def AppendZoneTable(lines, title, capture, zones, valueKey):
    lines.append("")
    lines.append(title)
    if not zones:
        lines.append("(none)")
        return

    columns = [("zone", "<"), (f"ms/{capture.unit}", ">"), ("self", ">"), (f"calls/{capture.unit}", ">"),
               ("mean", ">"), ("p95", ">"), ("max", ">"), ("where", "<")]
    rows = []
    for zone in zones:
        rows.append([
            Truncate(zone["name"], NAME_WIDTH),
            f"{zone[valueKey] / capture.divisor / 1000000.0:.3f}",
            f"{zone['self'] / capture.divisor / 1000000.0:.3f}" if valueKey != "self" else f"{zone['total'] / capture.divisor / 1000000.0:.3f}",
            f"{zone['count'] / capture.divisor:.1f}",
            FormatTime(zone["mean"]),
            FormatTime(zone["p95"]) if zone["p95"] is not None else "-",
            FormatTime(zone["max"]),
            FormatPlace(zone["file"], zone["line"]),
        ])

    if valueKey == "self":
        columns[2] = ("incl", ">")

    lines.extend(FormatTable(columns, rows))


def AppendSpikyZones(lines, capture, top):
    medianFrame = ToFloat(capture.baseFrameSet["median_ns"]) if capture.baseFrameSet else 16000000.0
    threshold = max(1000000.0, medianFrame * 0.25)
    candidates = [zone for zone in capture.zones
                  if zone["count"] >= 2 and zone["max"] >= threshold and zone["mean"] > 0.0 and zone["max"] >= zone["mean"] * 4.0]
    candidates.sort(key=lambda zone: zone["max"], reverse=True)

    lines.append("")
    lines.append(f"== Spiky zones (max >= {FormatTime(threshold)} and max >= 4x mean) — hitch candidates ==")
    if not candidates:
        lines.append("(none)")
        return

    columns = [("zone", "<"), ("calls", ">"), ("mean", ">"), ("p95", ">"), ("max", ">"), ("max/mean", ">"), ("self max", ">"), ("where", "<")]
    rows = []
    for zone in candidates[:top]:
        rows.append([
            Truncate(zone["name"], NAME_WIDTH),
            str(zone["count"]),
            FormatTime(zone["mean"]),
            FormatTime(zone["p95"]) if zone["p95"] is not None else "-",
            FormatTime(zone["max"]),
            f"{zone['max'] / zone['mean']:.0f}x",
            FormatTime(zone["selfMax"]),
            FormatPlace(zone["file"], zone["line"]),
        ])
    lines.extend(FormatTable(columns, rows))


def AppendHotZones(lines, capture, top):
    minimumCalls = 200.0 if capture.unit == "frame" else 20000.0
    candidates = [zone for zone in capture.zones if zone["count"] / capture.divisor >= minimumCalls]
    candidates.sort(key=lambda zone: zone["count"], reverse=True)

    lines.append("")
    lines.append(f"== Frequent zones (>= {minimumCalls:.0f} calls/{capture.unit}) — per-call overhead, allocations, Tracy overhead ==")
    if not candidates:
        lines.append("(none)")
        return

    columns = [("zone", "<"), (f"calls/{capture.unit}", ">"), (f"self ms/{capture.unit}", ">"), ("mean", ">"), ("where", "<")]
    rows = []
    for zone in candidates[:top]:
        rows.append([
            Truncate(zone["name"], NAME_WIDTH),
            f"{zone['count'] / capture.divisor:.0f}",
            f"{zone['self'] / capture.divisor / 1000000.0:.3f}",
            FormatTime(zone["mean"]),
            FormatPlace(zone["file"], zone["line"]),
        ])
    lines.extend(FormatTable(columns, rows))


def AppendGpuZones(lines, capture, top):
    lines.append("")
    lines.append("== GPU zones ==")
    if not capture.gpuZones:
        lines.append("(no GPU zones in the capture)")
        return

    gpuZones = sorted(capture.gpuZones, key=lambda zone: zone["total"], reverse=True)
    columns = [("zone", "<"), (f"ms/{capture.unit}", ">"), (f"calls/{capture.unit}", ">"), ("mean", ">"), ("max", ">"), ("where", "<")]
    rows = []
    for zone in gpuZones[:top]:
        rows.append([
            Truncate(zone["name"], NAME_WIDTH),
            f"{zone['total'] / capture.divisor / 1000000.0:.3f}",
            f"{zone['count'] / capture.divisor:.1f}",
            FormatTime(zone["total"] / max(zone["count"], 1)),
            FormatTime(zone["max"]),
            FormatPlace(zone["file"], ""),
        ])
    lines.extend(FormatTable(columns, rows))


def BuildReport(capture, top):
    lines = [f"Capture: {capture.path}", f"Exports: {capture.outputDirectory}"]
    for warning in capture.warnings:
        lines.append(f"WARNING: {warning}")

    AppendFrames(lines, capture)

    bySelf = sorted(capture.zones, key=lambda zone: zone["self"], reverse=True)[:top]
    AppendZoneTable(lines, f"== Top {top} zones by self time (where the time is actually spent; sum over all threads) ==",
                    capture, bySelf, "self")

    byTotal = sorted(capture.zones, key=lambda zone: zone["total"], reverse=True)[:top]
    AppendZoneTable(lines, f"== Top {top} zones by inclusive time ==", capture, byTotal, "total")

    AppendSpikyZones(lines, capture, top)
    AppendHotZones(lines, capture, top)
    AppendGpuZones(lines, capture, top)
    return lines


def GetCompareKey(zone):
    return zone["name"], ShortPath(zone["file"])


def AppendComparison(lines, baseline, capture, top):
    lines.append("")
    lines.append(f"== Comparison: baseline {baseline.path} -> capture {capture.path} ==")

    if baseline.baseFrameSet and capture.baseFrameSet:
        columns = [("frames", "<"), ("baseline", ">"), ("capture", ">"), ("delta", ">")]
        rows = []
        for title, key in (("mean", "mean_ns"), ("median", "median_ns"), ("p90", "p90_ns"), ("p99", "p99_ns"), ("max", "max_ns")):
            before = ToFloat(baseline.baseFrameSet[key])
            after = ToFloat(capture.baseFrameSet[key])
            rows.append([title, FormatTime(before), FormatTime(after), FormatDelta(after - before)])
        lines.extend(FormatTable(columns, rows))
    elif baseline.unit != capture.unit:
        lines.append("WARNING: one capture has no frames, per-unit values are not comparable")

    def Aggregate(source):
        result = {}
        for zone in source.zones:
            entry = result.setdefault(GetCompareKey(zone), {"self": 0.0, "total": 0.0, "count": 0, "file": zone["file"], "line": zone["line"]})
            entry["self"] += zone["self"] / source.divisor
            entry["total"] += zone["total"] / source.divisor
            entry["count"] += zone["count"]
        return result

    before = Aggregate(baseline)
    after = Aggregate(capture)
    keys = set(before) | set(after)
    empty = {"self": 0.0, "total": 0.0, "count": 0, "file": "", "line": ""}

    differences = []
    for key in keys:
        old = before.get(key, empty)
        new = after.get(key, empty)
        differences.append((new["self"] - old["self"], key, old, new))
    differences.sort(key=lambda item: abs(item[0]), reverse=True)

    lines.append("")
    lines.append(f"Top {top} zones by self time change per {capture.unit} (+ = slower in capture)")
    columns = [("zone", "<"), ("baseline", ">"), ("capture", ">"), ("delta", ">"), ("delta%", ">"), ("incl delta", ">"), ("where", "<")]
    rows = []
    for delta, key, old, new in differences[:top]:
        if old["count"] == 0:
            percent = "new"
        elif new["count"] == 0:
            percent = "gone"
        elif old["self"] > 0.0:
            percent = f"{delta * 100.0 / old['self']:+.0f}%"
        else:
            percent = "-"

        place = new if new["count"] else old
        rows.append([
            Truncate(key[0], NAME_WIDTH),
            FormatTime(old["self"]),
            FormatTime(new["self"]),
            FormatDelta(delta),
            percent,
            FormatDelta(new["total"] - old["total"]),
            FormatPlace(place["file"], place["line"]),
        ])
    lines.extend(FormatTable(columns, rows))


def IterateEvents(path):
    with open(path, "r", encoding="utf-8", errors="replace") as eventsFile:
        header = eventsFile.readline().rstrip("\r\n").split(SEPARATOR)
        columnCount = len(header)

        for line in eventsFile:
            parts = line.rstrip("\r\n").split(SEPARATOR)
            if len(parts) > columnCount:
                extra = len(parts) - columnCount
                parts = [SEPARATOR.join(parts[:extra + 1])] + parts[extra + 1:]
            if len(parts) != columnCount:
                continue

            yield parts[0], parts[1], parts[2], ToInt(parts[3]), ToInt(parts[4]), parts[5], parts[6]


class SpikeNode:
    def __init__(self, name, start, duration, value):
        self.name = name
        self.start = start
        self.duration = duration
        self.value = value
        self.children = []

    def End(self):
        return self.start + self.duration


def AppendGroupTree(lines, nodes, depth, threshold, budget):
    groups = {}
    for node in nodes:
        group = groups.setdefault(node.name, {"count": 0, "total": 0, "max": 0, "children": [], "value": node.value})
        group["count"] += 1
        group["total"] += node.duration
        group["max"] = max(group["max"], node.duration)
        group["children"].extend(node.children)

    hiddenCount = 0
    hiddenTime = 0
    for name, group in sorted(groups.items(), key=lambda item: item[1]["total"], reverse=True):
        if group["total"] < threshold or budget[0] <= 0:
            hiddenCount += 1
            hiddenTime += group["total"]
            continue

        childTime = sum(child.duration for child in group["children"])
        text = "  " * depth + f"{Truncate(name, NAME_WIDTH)}  {FormatTime(group['total'])}"
        if group["count"] > 1:
            text += f"  x{group['count']} (max {FormatTime(group['max'])})"
        if group["children"]:
            text += f"  self {FormatTime(group['total'] - childTime)}"
        if group["count"] == 1 and group["value"]:
            text += f"  [{Truncate(group['value'], 60)}]"
        lines.append(text)
        budget[0] -= 1

        if depth < SPIKE_TREE_DEPTH and group["children"]:
            AppendGroupTree(lines, group["children"], depth + 1, threshold, budget)

    if hiddenCount:
        lines.append("  " * depth + f"... {hiddenCount} more zones, {FormatTime(hiddenTime)}")


def AppendSpikes(lines, capture, zoneName, spikeCount, force):
    eventsPath = os.path.join(capture.outputDirectory, "events.tsv")
    Log("tracy_analyze.py : exporting every zone event (may take a while and a lot of disk space)")
    success, error = RunExport(capture.path, ["-s", SEPARATOR, "-u"], eventsPath, force)

    lines.append("")
    lines.append(f"== Spikes of '{zoneName}' ==")
    if not success:
        lines.append(f"event export failed: {error}")
        return

    Log("tracy_analyze.py : searching spikes")
    exact = []
    partial = []
    needle = zoneName.lower()
    for name, _, _, start, duration, thread, value in IterateEvents(eventsPath):
        if name == zoneName:
            exact.append((duration, start, thread, name, value))
        elif needle in name.lower():
            partial.append((duration, start, thread, name, value))

    instances = exact or partial
    if not instances:
        lines.append("zone not found (name is case sensitive for an exact match, substring otherwise)")
        return

    matchedNames = sorted({instance[3] for instance in instances})
    if len(matchedNames) > 1:
        lines.append(f"WARNING: substring matched {len(matchedNames)} zones: {', '.join(Truncate(name, 40) for name in matchedNames[:8])}")

    durations = sorted(instance[0] for instance in instances)
    median = durations[len(durations) // 2]
    p95 = durations[min(len(durations) - 1, int(len(durations) * 0.95))]
    lines.append(f"{len(instances)} instances: median {FormatTime(median)}, p95 {FormatTime(p95)}, max {FormatTime(durations[-1])}")

    spikes = sorted(instances, reverse=True)[:spikeCount]
    roots = [SpikeNode(name, start, duration, value) for duration, start, thread, name, value in spikes]
    sameThread = [[] for _ in spikes]
    otherThreads = [{} for _ in spikes]

    Log("tracy_analyze.py : collecting nested zones of the spikes")
    for name, _, _, start, duration, thread, value in IterateEvents(eventsPath):
        end = start + duration
        for index, (spikeDuration, spikeStart, spikeThread, spikeName, _) in enumerate(spikes):
            spikeEnd = spikeStart + spikeDuration
            if end <= spikeStart or start >= spikeEnd:
                continue

            if thread == spikeThread:
                if start >= spikeStart and end <= spikeEnd and not (start == spikeStart and duration == spikeDuration and name == spikeName):
                    sameThread[index].append(SpikeNode(name, start, duration, value))
                continue

            overlap = min(end, spikeEnd) - max(start, spikeStart)
            if overlap >= spikeDuration * 0.1:
                entry = otherThreads[index].setdefault((name, thread), [0, 0])
                entry[0] += overlap
                entry[1] += 1

    for index, root in enumerate(roots):
        spikeThread = spikes[index][2]
        stack = [root]
        for node in sorted(sameThread[index], key=lambda item: (item.start, -item.duration)):
            while len(stack) > 1 and stack[-1].End() <= node.start:
                stack.pop()
            stack[-1].children.append(node)
            stack.append(node)

        childTime = sum(child.duration for child in root.children)
        lines.append("")
        lines.append(f"-- spike #{index + 1}: {root.name} {FormatTime(root.duration)} ({root.duration / max(median, 1):.1f}x median) "
                     f"at {root.start / 1000000000.0:.3f}s, thread {spikeThread}"
                     + (f" [{Truncate(root.value, 60)}]" if root.value else ""))
        lines.append(f"   untracked time inside (no nested zones): {FormatTime(root.duration - childTime)}")

        threshold = max(root.duration * 0.01, 20000)
        AppendGroupTree(lines, root.children, 1, threshold, [SPIKE_TREE_LINES])

        if otherThreads[index]:
            lines.append("   other threads during the spike (overlap >= 10%, nested zones overlap too):")
            others = sorted(otherThreads[index].items(), key=lambda item: item[1][0], reverse=True)[:SPIKE_OTHER_THREADS]
            for (name, thread), (overlap, count) in others:
                lines.append(f"     thread {thread}: {Truncate(name, NAME_WIDTH)}  {FormatTime(overlap)}" + (f" x{count}" if count > 1 else ""))


def Main():
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    parser = argparse.ArgumentParser(description="Analyze a Tracy capture for SREngine")
    parser.add_argument("capture", help=".tracy capture to analyze (after changes when --compare is used)")
    parser.add_argument("--compare", help="baseline .tracy capture (before changes)")
    parser.add_argument("--top", type=int, default=25, help="rows per table")
    parser.add_argument("--filter", default="", help="keep only zones whose name contains this text (case insensitive)")
    parser.add_argument("--spikes", default="", help="zone name to analyze the longest instances of")
    parser.add_argument("--spike-count", type=int, default=3, help="number of spikes to show")
    parser.add_argument("--out", default="", help="output directory for exports and report.txt")
    parser.add_argument("--force", action="store_true", help="ignore cached exports")
    arguments = parser.parse_args()

    if not os.path.isfile(EXPORTER):
        Log(f"tracy_analyze.py : exporter not found: {EXPORTER}")
        return 1

    for path in (arguments.capture, arguments.compare):
        if path and not os.path.isfile(path):
            Log(f"tracy_analyze.py : capture not found: {path}")
            return 1

    Log(f"tracy_analyze.py : {GetExporterVersion()}")

    try:
        capture = Capture(arguments.capture, GetOutputDirectory(arguments.capture, arguments.out), arguments.filter, arguments.force)
        baseline = None
        if arguments.compare:
            baseline = Capture(arguments.compare, GetOutputDirectory(arguments.compare, ""), arguments.filter, arguments.force)
    except RuntimeError as exception:
        Log(f"tracy_analyze.py : {exception}")
        Log(f"tracy_analyze.py : if the capture was recorded by another Tracy version, convert it first: "
            f"\"{UPDATER}\" <old.tracy> <new.tracy>")
        return 1

    lines = BuildReport(capture, arguments.top)
    if baseline:
        AppendComparison(lines, baseline, capture, arguments.top)
    if arguments.spikes:
        AppendSpikes(lines, capture, arguments.spikes, arguments.spike_count, arguments.force)

    reportPath = os.path.join(capture.outputDirectory, "report.txt")
    with open(reportPath, "w", encoding="utf-8") as reportFile:
        reportFile.write("\n".join(lines) + "\n")

    print("\n".join(lines))
    print(f"\nReport saved: {reportPath}")
    return 0


if __name__ == "__main__":
    sys.exit(Main())
