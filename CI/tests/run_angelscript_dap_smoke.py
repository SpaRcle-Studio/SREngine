#!/usr/bin/env python3
# Created by Codex on 14.11.2026.
"""Stage an isolated project and verify DAP against an existing engine build."""

import argparse
import os
from pathlib import Path
import shutil
import socket
import subprocess
import sys
import time
import xml.etree.ElementTree as ET


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--engine", type=Path, required=True)
    args = parser.parse_args()
    try:
        connection = socket.create_connection(("127.0.0.1", 4711), timeout=.2)
    except OSError:
        pass
    else:
        connection.close()
        raise RuntimeError("Port 4711 is already in use; close the existing editor/debug session before running this test.")
    root = Path(__file__).resolve().parents[2]
    project = args.engine.resolve().parents[1] / "DapSmokeProject"
    resources = project / "Resources"
    resources.mkdir(parents=True, exist_ok=True)
    # The engine resource layer also contains sample scripts. Keep the test VM isolated.
    for source in (root / "Resources").rglob("*.as"):
        shadow = resources / source.relative_to(root / "Resources")
        shadow.parent.mkdir(parents=True, exist_ok=True)
        shadow.write_text("// Sample excluded from the isolated DAP test.\n", encoding="utf-8")
    for name in ("DapDebugProbe.as", "DapDebugProbe.scene"):
        shutil.copy2(root / "CI/tests/fixtures" / name, resources / name)
    features = ET.parse(root / "Resources/Engine/Configs/Features.xml")
    for name, value in {"ScriptCompilation": "false", "MainWindow": "false", "ImGUI": "false", "EditorCamera": "false"}.items():
        entry = features.find(f".//{name}")
        if entry is None:
            entry = ET.SubElement(features.find("Common"), name)
        entry.set("Value", value)
    configs = resources / "Engine/Configs"
    configs.mkdir(parents=True, exist_ok=True)
    features.write(configs / "Features.xml", encoding="utf-8")
    project_file = project / ".srproject"
    project_file.write_text(
        "sra format\nuse tabs: true\nuse numeric depth: false\n-r:Root\n"
        "\t-o:asset\n\t\t-v:type\n\t\t\t-s:ProjectSettings\n\t\t-o:ptr\n"
        "\t\t\t-v:projectName\n\t\t\t\t-s:DapSmokeProject\n"
        "\t\t\t-v:enableCppScripts\n\t\t\t\t-b:false\n", encoding="utf-8")
    logs = project / "logs"
    logs.mkdir(exist_ok=True)
    environment = os.environ.copy()
    environment.pop("SR_ANGELSCRIPT_DAP_PORT", None)
    command = [str(args.engine.resolve()), str(project_file), "--headless", "--resources", str(root / "Resources"),
               "--run-scene", str(resources / "DapDebugProbe.scene"), "--log-dir", str(logs)]
    with (logs / "console.log").open("wb") as output:
        process = subprocess.Popen(command, cwd=args.engine.resolve().parent, env=environment,
                                   stdout=output, stderr=subprocess.STDOUT,
                                   creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0)
        try:
            deadline = time.monotonic() + 45
            while time.monotonic() < deadline:
                if process.poll() is not None:
                    raise RuntimeError(f"Engine exited with {process.returncode}; see {logs}")
                try:
                    with socket.create_connection(("127.0.0.1", 4711), timeout=.2):
                        break
                except OSError:
                    time.sleep(.2)
            else:
                raise RuntimeError(f"Editor did not open default port 4711; see {logs}")
            subprocess.run([sys.executable, str(root / "CI/tests/angelscript_dap_smoke.py"), "--execute"], check=True)
            subprocess.run([sys.executable, str(root / "CI/tests/angelscript_dap_smoke.py"), "--execute", "--bridge",
                            "--engine", str(args.engine.resolve())], check=True)
        finally:
            process.terminate()
            try:
                process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                process.kill()
                process.wait()


if __name__ == "__main__":
    main()
