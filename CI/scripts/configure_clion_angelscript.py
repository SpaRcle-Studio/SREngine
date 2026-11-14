#!/usr/bin/env python3
# Created by Codex on 14.11.2026.
"""Install the AngelScript debug profile and .as file association into CLion."""

import argparse
from datetime import datetime
import json
from pathlib import Path
import shutil
import xml.etree.ElementTree as ET


def backup(path):
    if path.exists():
        target = path.with_name(path.name + ".angelscript-" + datetime.now().strftime("%Y%m%d-%H%M%S") + ".bak")
        shutil.copy2(path, target)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config-dir", type=Path, required=True)
    parser.add_argument("--file-type", default="AngelScript")
    parser.add_argument("--engine", type=Path, required=True, help="path to the built SREngine executable")
    parser.add_argument("--port", type=int, default=4711)
    args = parser.parse_args()
    if not 1 <= args.port <= 65535:
        parser.error("--port must be between 1 and 65535")
    profiles_path = args.config_dir / "debug-profiles" / "debug-profiles.json"
    document = json.loads(profiles_path.read_text(encoding="utf-8-sig"))
    profiles = document["debug-profiles"]
    profile = next((item for item in profiles if item.get("name") == "SpaRcle AngelScript"), None)
    if profile is None:
        import uuid
        profile = {"id": str(uuid.uuid4()), "name": "SpaRcle AngelScript", "type": "dap"}
        profiles.append(profile)
    profile.update({
        "debuggerExecutable": str(args.engine.resolve()),
        "debuggerArguments": ["--angelscript-dap-bridge", "--port", str(args.port)],
        "communication": "stdio",
        "launch": {"request": "attach", "stopOnEntry": False},
        "attach": {"stopOnEntry": False},
    })
    backup(profiles_path)
    profiles_path.write_text(json.dumps(document, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

    types_path = args.config_dir / "options" / "filetypes.xml"
    tree = ET.parse(types_path)
    component = tree.find("./component[@name='FileTypeManager']")
    mappings = component.find("extensionMap")
    if mappings is None:
        mappings = ET.SubElement(component, "extensionMap")
    for mapping in list(mappings):
        if mapping.tag in ("mapping", "removed_mapping") and (mapping.get("ext") == "as" or mapping.get("pattern") == "*.as"):
            mappings.remove(mapping)
    ET.SubElement(mappings, "mapping", {"ext": "as", "type": args.file_type})
    backup(types_path)
    ET.indent(tree, space="  ")
    tree.write(types_path, encoding="utf-8", xml_declaration=False)
    print(f"Updated {profiles_path}")
    print(f"Associated .as with {args.file_type} in {types_path}")


if __name__ == "__main__":
    main()
