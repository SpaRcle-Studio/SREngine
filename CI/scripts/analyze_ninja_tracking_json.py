import json
import gzip
from pathlib import Path
import argparse

def load_trace(path):
    try:
        with open(path, "r", encoding="utf8") as f:
            first_line = f.readline() # skip first line
            return json.load(f)
    except Exception:
        pass

    try:
        with gzip.open(path, "rt", encoding="utf8") as f:
            return json.load(f)
    except Exception:
        pass

    raise RuntimeError("Файл не читается как JSON или gzip JSON")

def extract_longest_events(trace, top, nolib=False):
    # если trace — объект с traceEvents
    if isinstance(trace, dict) and "traceEvents" in trace:
        events = trace["traceEvents"]
    # если это просто список
    elif isinstance(trace, list):
        events = trace
    else:
        raise RuntimeError("Формат trace непонятен")

    result = []

    for e in events:
        if not isinstance(e, dict):
            continue

        if e.get("ph") != "X":  # duration event
            continue

        dur = e.get("dur", 0)
        if dur <= 0:
            continue

        name = e.get("name", "<unknown>")

        if nolib:
            modules = ['Utils', 'Physics', 'Audio', 'Scripting', 'Graphics']
            skip = False
            for module in modules:
                if module + "/libs" in name:
                    skip = True
                    break
            if skip:
                continue

        args = e.get("args", {}).get("command", "")

        result.append((dur, name, args))

    result.sort(reverse=True, key=lambda x: x[0])
    return [sum(dur for dur, _, _ in result), result[:top]]

parser = argparse.ArgumentParser()
parser.add_argument('--top', type=int, default=50, help='Number of top longest events to display')
parser.add_argument('--nolib', action='store_true', help='Exclude library commands from the output')

trace = load_trace("trace.json")
arguments = parser.parse_args()
[total_time, longest] = extract_longest_events(trace, top=arguments.top, nolib=arguments.nolib)

total_time_top = sum(dur for dur, _, _ in longest)

for dur, name, cmd in longest:
    print(f"{dur/1e6:8.3f}s  |  {name}")
    if cmd:
        print("   ", cmd)

print(f"\nTotal time of all events: {total_time/1e6:.3f}s")
print(f"\nTotal time of top events: {total_time_top/1e6:.3f}s")