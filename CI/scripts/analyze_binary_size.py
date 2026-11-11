"""Read-only PE DLL analysis. No compiler, build or engine processes are started."""

import argparse
from bisect import bisect_right
from collections import defaultdict
import ctypes
from functools import lru_cache
import heapq
import html
import json
import logging
from pathlib import Path
import re
import struct
import sys
from time import perf_counter


LOG = logging.getLogger('binary-size')


class Progress:
    def __init__(self, label, total):
        self.label = label
        self.total = max(total, 1)
        self.started = perf_counter()
        self.last = self.started
        self.terminal = sys.stderr.isatty()
        LOG.info('Start: %s; total=%d', label, total)

    def update(self, done, finish=False):
        now = perf_counter()
        if not finish and now - self.last < (0.25 if self.terminal else 10):
            return
        self.last = now
        ratio = min(done / self.total, 1)
        elapsed = now - self.started
        eta = elapsed * (1 - ratio) / ratio if ratio else 0
        bar = '#' * int(24 * ratio) + '-' * (24 - int(24 * ratio))
        message = f'{self.label}: [{bar}] {ratio:6.1%} {done:,}/{self.total:,} elapsed={elapsed:.1f}s ETA={eta:.1f}s'
        if self.terminal:
            print('\r' + message + '    ', end='\n' if finish else '', file=sys.stderr, flush=True)
        else:
            print(message, file=sys.stderr, flush=True)
        if finish or not self.terminal:
            LOG.info(message)

    def finish(self):
        self.update(self.total, finish=True)


ROOT = Path(__file__).resolve().parents[2]


def discover(root):
    """Find CMake build trees without descending into dependency source trees."""
    found = set()
    pending = [(root, 0)]
    while pending:
        directory, depth = pending.pop()
        if (directory / 'CMakeCache.txt').is_file():
            found.add(directory)
            continue
        if depth >= 3:
            continue
        for child in directory.iterdir():
            if child.is_dir() and not child.is_symlink() and child.name not in {
                '.git', '.venv', 'libs', 'Resources', 'node_modules'
            }:
                pending.append((child, depth + 1))
    return sorted(found)


def choose(root):
    builds = discover(root)
    if not builds:
        raise ValueError('No CMake build directories found. Use --input PATH.')
    for index, build in enumerate(builds, 1):
        print(f'{index}. {build.relative_to(root)}')
    while True:
        answer = input('Select build number (q to quit): ').strip()
        if answer.lower() == 'q':
            raise KeyboardInterrupt
        if answer.isdigit() and 1 <= int(answer) <= len(builds):
            return builds[int(answer) - 1]
        print('Enter one of the listed numbers.')


def demangler():
    if sys.platform != 'win32':
        return lambda name: name
    library = ctypes.WinDLL('dbghelp')
    undecorate = library.UnDecorateSymbolName
    undecorate.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint]
    undecorate.restype = ctypes.c_uint
    buffer = ctypes.create_string_buffer(65536)

    @lru_cache(maxsize=50000)
    def decode(name):
        if not name.startswith('?'):
            return name
        if undecorate(name.encode('ascii', errors='replace'), buffer, len(buffer), 0):
            return buffer.value.decode('utf-8', errors='replace')
        return name
    return decode


def read_pe(path, decode):
    data = path.read_bytes()

    def unpack(fmt, offset):
        return struct.unpack_from('<' + fmt, data, offset)

    if data[:2] != b'MZ':
        raise ValueError('Not a PE binary')
    pe = unpack('I', 0x3c)[0]
    if data[pe:pe + 4] != b'PE\0\0':
        raise ValueError('Invalid PE signature')
    count = unpack('H', pe + 6)[0]
    optional_size = unpack('H', pe + 20)[0]
    optional = pe + 24
    magic = unpack('H', optional)[0]
    if magic not in (0x10b, 0x20b):
        raise ValueError('Unsupported optional header')
    directories = optional + (112 if magic == 0x20b else 96)
    sections = []
    for index in range(count):
        offset = optional + optional_size + index * 40
        virtual_size, rva, raw_size, raw_offset = unpack('IIII', offset + 8)
        sections.append(dict(name=data[offset:offset + 8].rstrip(b'\0').decode('ascii', 'replace'),
                             rva=rva, virtual_size=virtual_size, raw_size=raw_size,
                             raw_offset=raw_offset, characteristics=unpack('I', offset + 36)[0]))

    def file_offset(rva):
        for section in sections:
            delta = rva - section['rva']
            if 0 <= delta < section['raw_size']:
                return section['raw_offset'] + delta
        if 0 <= rva < unpack('I', optional + 60)[0]:
            return rva
        raise ValueError(f'Unmapped RVA: {rva:x}')

    def string_at(rva):
        offset = file_offset(rva)
        end = data.find(b'\0', offset)
        if end < 0:
            raise ValueError('Unterminated PE string')
        return data[offset:end].decode('ascii', errors='replace')

    symbols = []
    export_rva, export_size = unpack('II', directories)
    if export_rva:
        export = file_offset(export_rva)
        functions, names, addresses, name_table, ordinals = unpack('IIIII', export + 20)
        if names > len(data) // 4 or functions > len(data) // 4:
            raise ValueError('Invalid export count')
        names_offset = file_offset(name_table)
        ordinals_offset = file_offset(ordinals)
        addresses_offset = file_offset(addresses)
        for index in range(names):
            name = string_at(unpack('I', names_offset + 4 * index)[0])
            ordinal = unpack('H', ordinals_offset + 2 * index)[0]
            if ordinal >= functions:
                raise ValueError('Invalid export ordinal')
            rva = unpack('I', addresses_offset + 4 * ordinal)[0]
            forwarded = export_rva <= rva < export_rva + export_size
            symbols.append(dict(decorated=name, name=decode(name), rva=rva,
                                forwarded=forwarded, source='export'))
    header_size = unpack('I', optional + 60)[0]
    return dict(path=str(path), file_size=len(data), image_size=unpack('I', optional + 56)[0],
                image_base=unpack('Q' if magic == 0x20b else 'I', optional + (24 if magic == 0x20b else 28))[0],
                header_size=header_size, sections=sections, export_directory_size=export_size,
                non_section_bytes=len(data) - sum(s['raw_size'] for s in sections),
                symbols=symbols)


def read_map(path, decode, module):
    """MSVC MAP public symbols; sizes are bounded address spans, not exact sizes."""
    entries = []
    ranges = defaultdict(list)
    range_pattern = re.compile(r'^\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8,16})\s+([0-9a-fA-F]+)H\s+\S+\s+(?:CODE|DATA)\s*$')
    pattern = re.compile(r'^\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8,16})\s+(\S+)\s+([0-9a-fA-F]{8,16})\s+(.*?)\s*$')
    seen = set()
    progress = Progress('MAP ' + path.name, path.stat().st_size)
    consumed = 0
    sections = sorted(module['sections'], key=lambda s: s['rva'])
    section_starts = [s['rva'] for s in sections]
    with path.open('rb') as stream:
        for line_number, raw_line in enumerate(stream):
            consumed += len(raw_line)
            if line_number % 4096 == 0:
                progress.update(consumed)
            line = raw_line.decode('utf-8', errors='replace')
            contribution = range_pattern.match(line)
            if contribution:
                segment, start, length = contribution.groups()
                start = int(start, 16)
                ranges[segment].append((start, start + int(length, 16)))
                continue
            match = pattern.match(line)
            if not match:
                continue
            segment, offset, name, address, tail = match.groups()
            address = int(address, 16)
            rva = address - module['image_base']
            section_index = bisect_right(section_starts, rva) - 1
            if section_index < 0 or segment == '0000':
                continue
            section = sections[section_index]
            if rva >= section['rva'] + section['raw_size']:
                continue
            owner = sys.intern(re.sub(r'^(?:[fi]\s+)+', '', tail).strip())
            segment = sys.intern(segment)
            key = (address, name, owner)
            if key in seen:
                continue
            seen.add(key)
            entries.append(dict(segment=segment, offset=int(offset, 16), address=address,
                                rva=rva, section=section['name'],
                                section_end=section['rva'] + section['raw_size'],
                                decorated=name, name=decode(name), object=owner,
                                function=bool(re.match(r'f\s', tail)) and bool(section['characteristics'] & 0x20000000),
                                source='map'))
    progress.finish()
    LOG.info('%s: retained %d records; sorting addresses', path.name, len(entries))
    entries.sort(key=lambda entry: (entry['segment'], entry['offset']))
    for values in ranges.values():
        values.sort()
    range_starts = {segment: [start for start, end in values] for segment, values in ranges.items()}
    span_progress = Progress('MAP spans ' + path.name, len(entries))
    next_offsets = {}
    last_offsets = {}
    for index, entry in enumerate(reversed(entries)):
        if index % 4096 == 0:
            span_progress.update(index)
        segment, offset = entry['segment'], entry['offset']
        if last_offsets.get(segment) != offset:
            next_offsets[segment] = last_offsets.get(segment)
            last_offsets[segment] = offset
        following = next_offsets.get(segment)
        range_index = bisect_right(range_starts.get(segment, []), offset) - 1
        range_end = ranges[segment][range_index][1] if range_index >= 0 else offset
        if range_end <= offset:
            range_end = offset
        entry['span_estimate'] = (min(following - offset, entry['section_end'] - entry['rva'], range_end - offset)
                                  if following is not None else None)
    span_progress.finish()
    return entries


def size_summary(module, limit):
    """Attribute each code address once; ambiguous aliases remain a separate bucket."""
    addresses = defaultdict(list)
    for symbol in module['symbols']:
        if symbol.get('source') == 'map' and symbol.get('function') and symbol.get('span_estimate'):
            addresses[symbol['address']].append(symbol)
    objects = defaultdict(lambda: dict(bytes=0, addresses=0))
    libraries = defaultdict(lambda: dict(bytes=0, addresses=0))
    templates = defaultdict(lambda: dict(bytes=0, addresses=0, examples=set()))
    functions = []
    progress = Progress('Code summary ' + Path(module['path']).name, len(addresses))
    for index, aliases in enumerate(addresses.values()):
        if index % 4096 == 0:
            progress.update(index)
        symbol = aliases[0]
        size = min(s['span_estimate'] for s in aliases)
        owners = {s['object'] for s in aliases}
        owner = next(iter(owners)) if len(owners) == 1 else '[shared address: multiple objects]'
        library = owner.split(':', 1)[0] if ':' in owner else '[module objects]'
        for bucket, key in ((objects, owner), (libraries, library)):
            bucket[key]['bytes'] += size
            bucket[key]['addresses'] += 1
        # Choose the innermost owning template-id / function template-id.
        # Count each address once; nested template arguments are not added again.
        families = []
        for alias in aliases:
            families.append(owning_family(alias['name']))
        unique = set(families)
        family = next(iter(unique)) if len(unique) == 1 else '[shared address: multiple families]'
        if family:
            item = templates[family]
            item['bytes'] += size
            item['addresses'] += 1
            if len(item['examples']) < 3:
                item['examples'].add(symbol['name'])
        functions.append(dict(name=symbol['name'], bytes=size, object=owner, aliases=len(aliases)))

    def ranked(bucket):
        return [dict(name=name, **{k: sorted(v) if isinstance(v, set) else v for k, v in item.items()})
                for name, item in sorted(bucket.items(), key=lambda pair: -pair[1]['bytes'])[:limit]]

    progress.finish()
    return dict(estimated_code_bytes=sum(s['bytes'] for s in functions),
                unique_code_addresses=len(addresses), objects=ranked(objects), libraries=ranked(libraries),
                template_code=ranked(templates),
                functions=heapq.nlargest(limit, functions, key=lambda item: item['bytes']))


@lru_cache(maxsize=50000)
def owning_family(name):
    if '<' not in name:
        return None
    depth = 0
    family = None
    for match in re.finditer(r'([\w~]+(?:::[\w~]+)*)\s*<|[<>]', name):
        if match.group(0).endswith('<'):
            if depth == 0 and match.group(1):
                family = match.group(1)
            depth += 1
        else:
            depth = max(0, depth - 1)
    return family


def template_instances(name):
    """Extract balanced template-ids, including nested template arguments."""
    instances = set()
    if '<' not in name:
        return instances
    stack = []
    for match in re.finditer(r'([\w~]+(?:::[\w~]+)*)\s*<|[<>]', name):
        if match.group(0).endswith('<'):
            stack.append((match.group(1), match.start()))
        elif stack:
            family, start = stack.pop()
            if family:
                instances.add((family, name[start:match.end()]))
    return instances


def aggregate(modules):
    families = defaultdict(lambda: dict(specializations=set(), symbol_count=0, module_mask=0))
    repeated = {}
    names = {}
    progress = Progress('Index symbol names', sum(len(m['symbols']) for m in modules))
    processed = 0
    for module_index, module in enumerate(modules):
        bit = 1 << module_index
        for symbol in module['symbols']:
            processed += 1
            if processed % 4096 == 0:
                progress.update(processed)
            if symbol.get('forwarded'):
                continue
            key = symbol['decorated']
            repeated[key] = repeated.get(key, 0) | bit
            names.setdefault(key, symbol['name'])
    progress.finish()
    progress = Progress('Parse unique template names', len(names))
    for index, (key, name) in enumerate(names.items()):
        if index % 4096 == 0:
            progress.update(index)
        touched = set()
        for family, instance in template_instances(name):
            item = families[family]
            item['specializations'].add(instance)
            item['module_mask'] |= repeated[key]
            touched.add(family)
        for family in touched:
            families[family]['symbol_count'] += 1
    progress.finish()

    def module_paths(mask):
        return sorted(m['path'] for index, m in enumerate(modules) if mask & (1 << index))

    return ([dict(family=family, specialization_count=len(item['specializations']),
                  symbol_count=item['symbol_count'], modules=module_paths(item['module_mask']),
                  specializations=sorted(item['specializations']))
             for family, item in sorted(families.items(), key=lambda pair: -len(pair[1]['specializations']))],
            [dict(symbol=name, modules=module_paths(mask)) for name, mask in repeated.items() if mask & (mask - 1)])


NOTES = (
    'Export analysis is a lower bound: private, removed and fully inlined code is invisible. '
    'Template-ids are observed names, not a count of compiler class instantiations; '
    'class templates and function templates can both occur. '
    'Repeated symbols across DLLs are candidates for review, not proof of identical machine code. '
    'MAP spans include possible padding, data and unlisted symbols; they are estimates, '
    'aliases share addresses and must not be summed. PDB type records are not analyzed. '
    'On non-Windows systems MSVC decorated names remain undecoded. '
    'Non-section bytes include headers, alignment, certificates and overlays. '
    'Existing artifacts may be stale; this tool never rebuilds them.'
)


def write_report(report, output, limit, full):
    started = perf_counter()
    LOG.info('Writing JSON report; full symbols=%s', full)
    output.mkdir(parents=True, exist_ok=True)
    compact = dict(report)
    compact['modules'] = [dict(m, symbols=m['symbols'] if full else [], symbol_records=len(m['symbols']))
                          for m in report['modules']]
    compact['templates'] = [dict(f, specializations=f['specializations'] if full else f['specializations'][:10])
                            for f in report['templates'][:None if full else limit]]
    compact['repeated_symbols'] = report['repeated_symbols'][:None if full else limit]
    with (output / 'report.json').open('w', encoding='utf-8') as stream:
        json.dump(compact, stream, ensure_ascii=False, indent=2)
    LOG.info('JSON written: %.2f MiB in %.2fs; rendering HTML',
             (output / 'report.json').stat().st_size / 1048576, perf_counter() - started)

    def table(headers, rows):
        return '<table><thead><tr>' + ''.join(f'<th>{html.escape(str(h))}</th>' for h in headers) + '</tr></thead><tbody>' + ''.join(
            '<tr>' + ''.join(f'<td>{html.escape(str(cell))}</td>' for cell in row) + '</tr>' for row in rows) + '</tbody></table>'

    body = '<h1>Engine DLL size report</h1><p>' + html.escape(NOTES) + '</p>'
    body += '<p>Start with the object/library and template CODE rankings below. Counts alone do not measure size. All code sizes are MAP address-span estimates; each address is counted once. Tables are limited to the largest ' + str(limit) + ' entries. Ambiguous aliases are grouped separately. Template ranking uses a heuristic owning family, not nested argument families.</p>'
    body += table(['DLL', 'File bytes', 'Image bytes', 'Symbols', 'Export directory bytes', 'Non-section bytes'],
                  [(Path(m['path']).name, m['file_size'], m['image_size'], len(m['symbols']),
                    m['export_directory_size'], m['non_section_bytes']) for m in report['modules']])
    for module in report['modules']:
        summary = module['size_summary']
        body += '<h2>' + html.escape(Path(module['path']).name) + ': where code space goes</h2>'
        text_bytes = sum(s['raw_size'] for s in module['sections'] if s['characteristics'] & 0x20000000)
        body += '<p>Executable sections: ' + str(round(text_bytes / 1048576, 2)) + ' MiB; attributed MAP spans: ' + str(round(summary['estimated_code_bytes'] / 1048576, 2)) + ' MiB. Unattributed space includes gaps, padding, unlisted code and last symbols.</p>'
        for title, key in [('Libraries', 'libraries'), ('Object files', 'objects'), ('Template code families', 'template_code')]:
            body += '<h3>' + title + ' (estimated code only)</h3>'
            body += table(['Name', 'KiB', '% of executable sections', 'Unique code addresses'],
                          [(s['name'], round(s['bytes'] / 1024, 1), round(100 * s['bytes'] / text_bytes, 2) if text_bytes else 0,
                            s['addresses']) for s in summary[key]])
        body += '<details><summary>Largest individual function spans</summary>'
        body += table(['Name', 'Estimated bytes', 'Object', 'Aliases'],
                      [(s['name'], s['bytes'], s['object'], s['aliases']) for s in summary['functions']]) + '</details>'
    body += '<h2>Template families (observed names, count ranking)</h2>'
    body += table(['Family', 'Unique specializations', 'Unique symbols', 'DLL count'],
                  [(f['family'], f['specialization_count'], f['symbol_count'], len(f['modules'])) for f in report['templates'][:limit]])
    for family in report['templates'][:limit]:
        body += '<details><summary>' + html.escape(family['family']) + ' (up to 10 examples)</summary><pre>' + html.escape('\n'.join(family['specializations'][:10])) + '</pre></details>'
    body += '<h2>Symbols present in multiple DLLs</h2>'
    body += table(['Symbol', 'DLLs'], [(s['symbol'], ', '.join(Path(p).name for p in s['modules'])) for s in report['repeated_symbols'][:limit]])
    for module in report['modules']:
        body += '<h2>' + html.escape(module['path']) + '</h2>'
        body += table(['Section', 'Disk bytes', 'Virtual bytes'], [(s['name'], s['raw_size'], s['virtual_size']) for s in module['sections']])
    body += '<h2>Warnings</h2><pre>' + html.escape('\n'.join(report['warnings'])) + '</pre>'
    document = '<!doctype html><html lang="en"><meta charset="utf-8"><title>DLL size</title><style>body{font:14px system-ui;margin:24px}table{border-collapse:collapse;width:100%;margin:16px 0}td,th{border:1px solid #ccc;padding:6px;text-align:left;overflow-wrap:anywhere}pre{white-space:pre-wrap}summary{cursor:pointer}</style>' + body + '</html>'
    (output / 'report.html').write_text(document, encoding='utf-8')
    LOG.info('Reports finished in %.2fs', perf_counter() - started)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT, help='Repository to search for builds')
    parser.add_argument('--input', type=Path, help='Build directory, binary directory or single DLL')
    parser.add_argument('--output', type=Path, help='Report directory (default: build/BinarySizeReport)')
    parser.add_argument('--map-dir', type=Path, help='Directory containing matching DLL-stem .map files')
    parser.add_argument('--all-dlls', action='store_true', help='Include dependency DLLs outside Bin')
    parser.add_argument('--top', type=int, default=30, help='Maximum rows per ranking (default: 30)')
    parser.add_argument('--full-symbols', action='store_true', help='Include all raw symbols in JSON; can produce gigabytes')
    parser.add_argument('--log-file', type=Path, help='Log file (default: output/analysis.log)')
    args = parser.parse_args()
    if args.top < 1:
        raise ValueError('--top must be positive')
    selected = (args.input or choose(args.root.resolve())).resolve()
    if not selected.exists():
        raise ValueError(f'Input does not exist: {selected}')
    base = selected.parent if selected.is_file() else selected
    output = (args.output or base / 'BinarySizeReport').resolve()
    output.mkdir(parents=True, exist_ok=True)
    log_path = (args.log_file or output / 'analysis.log').resolve()
    log_path.parent.mkdir(parents=True, exist_ok=True)
    handler = logging.FileHandler(log_path, mode='w', encoding='utf-8')
    handler.setFormatter(logging.Formatter('%(asctime)s %(levelname)s %(message)s'))
    LOG.setLevel(logging.INFO)
    LOG.addHandler(handler)
    started = perf_counter()
    LOG.info('Analysis started: input=%s; Python=%s', selected, sys.version)
    print(f'Log: {log_path}', flush=True)
    search = base / 'Bin' if (base / 'Bin').is_dir() and not args.all_dlls else base
    dlls = [selected] if selected.is_file() else sorted(search.rglob('*.dll'))
    if not dlls:
        raise ValueError(f'No DLLs found in {search}')
    decode = demangler()
    report = dict(input=str(selected), notes=NOTES, modules=[], warnings=[])
    map_index = defaultdict(list)
    LOG.info('Discovering MAP files in %s', args.map_dir or base)
    for map_path in (args.map_dir or base).rglob('*.map'):
        map_index[map_path.stem.casefold()].append(map_path)
    LOG.info('Found %d DLLs and %d MAP candidates', len(dlls), sum(map(len, map_index.values())))
    dll_progress = Progress('DLLs', len(dlls))
    for dll_index, dll in enumerate(dlls):
        module_started = perf_counter()
        print(f'Analyzing [{dll_index + 1}/{len(dlls)}] {dll.name} ...', flush=True)
        LOG.info('Reading PE %s', dll)
        try:
            module = read_pe(dll, decode)
            map_path = (args.map_dir or dll.parent) / (dll.stem + '.map')
            if not map_path.is_file():
                candidates = map_index[dll.stem.casefold()]
                if len(candidates) == 1:
                    map_path = candidates[0]
                elif len(candidates) > 1:
                    report['warnings'].append(f'{dll.name}: multiple matching MAP files; skipped. Use --map-dir.')
            if map_path.is_file():
                mapped = read_map(map_path, decode, module)
                module['map_path'] = str(map_path)
                module['symbols'] += mapped
                report['warnings'].append(f'{dll.name}: MAP identity is not verified; use a MAP from the same link.')
            else:
                report['warnings'].append(f'{dll.name}: exports only; no matching MAP. Function sizes unavailable.')
            module['size_summary'] = size_summary(module, args.top)
            report['modules'].append(module)
            LOG.info('%s completed in %.2fs; %d records', dll.name, perf_counter() - module_started, len(module['symbols']))
        except (ValueError, OSError, struct.error) as error:
            LOG.exception('Failed module %s', dll)
            report['warnings'].append(f'{dll}: {error}')
        dll_progress.update(dll_index + 1)
    dll_progress.finish()
    if not report['modules']:
        raise ValueError('No valid DLLs could be analyzed: ' + '; '.join(report['warnings']))
    report['templates'], report['repeated_symbols'] = aggregate(report['modules'])
    LOG.info('Writing reports to %s', output)
    write_report(report, output, args.top, args.full_symbols)
    for module in report['modules']:
        print(f"{Path(module['path']).name:30} {module['file_size'] / 1048576:9.2f} MiB  {len(module['symbols']):8} symbol records")
        for title, key in [('Objects', 'objects'), ('Template code', 'template_code')]:
            print('  ' + title + ' (estimated code KiB):')
            for item in module['size_summary'][key][:5]:
                print(f"    {item['bytes'] / 1024:10.1f}  {item['name']}")
    print(f"Observed template families: {len(report['templates'])}")
    print(f'Report: {output / "report.html"}')
    for warning in report['warnings']:
        print('Warning:', warning)
        LOG.warning(warning)
    if hasattr(decode, 'cache_info'):
        LOG.info('Demangle cache: %s', decode.cache_info())
    LOG.info('Owning-family cache: %s', owning_family.cache_info())
    LOG.info('Total analysis time: %.2fs', perf_counter() - started)
    print(f'Completed in {perf_counter() - started:.1f}s. Log: {log_path}')


if __name__ == '__main__':
    try:
        main()
    except (ValueError, OSError, EOFError) as error:
        LOG.exception('Analysis failed')
        print(f'Error: {error}', file=sys.stderr)
        sys.exit(1)
    except KeyboardInterrupt:
        LOG.warning('Analysis interrupted by user')
        sys.exit(130)
