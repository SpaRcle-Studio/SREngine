#!/usr/bin/env python3
# Created by Codex on 14.11.2026.
"""Exercise a running SREngine DAP server; never builds or launches the engine."""

import argparse
import json
from pathlib import Path
import socket
import os
import queue
import subprocess
import sys
import threading
import time


class BridgeSocket:
    def __init__(self, port, timeout):
        self.process = subprocess.Popen([str(Client.bridge_engine), "--angelscript-dap-bridge", "--port", str(port)],
                                        stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                        creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0)
        self.chunks = queue.Queue()
        self.timeout = timeout

        def read():
            while chunk := os.read(self.process.stdout.fileno(), 8192):
                self.chunks.put(chunk)
            self.chunks.put(b"")

        threading.Thread(target=read, daemon=True).start()

    def sendall(self, data):
        self.process.stdin.write(data)
        self.process.stdin.flush()

    def recv(self, size):
        try:
            return self.chunks.get(timeout=self.timeout)
        except queue.Empty as error:
            raise TimeoutError("No DAP message received through stdio bridge") from error

    def settimeout(self, timeout):
        self.timeout = timeout

    def close(self):
        if self.process.poll() is None:
            self.process.terminate()
            self.process.wait(timeout=5)


class Client:
    use_bridge = False
    bridge_engine = None

    def __init__(self, port, timeout):
        self.socket = BridgeSocket(port, timeout) if self.use_bridge else socket.create_connection(("127.0.0.1", port), timeout)
        self.socket.settimeout(timeout)
        self.buffer = b""
        self.sequence = 0
        self.events = []
        self.last_server_sequence = 0

    def close(self):
        self.socket.close()

    def send(self, command, arguments=None, fragmented=False):
        self.sequence += 1
        payload = json.dumps({
            "seq": self.sequence, "type": "request", "command": command,
            "arguments": arguments or {},
        }, ensure_ascii=False).encode("utf-8")
        packet = f"Content-Length: {len(payload)}\r\n\r\n".encode("ascii") + payload
        if fragmented:
            for offset in range(0, len(packet), 7):
                self.socket.sendall(packet[offset:offset + 7])
        else:
            self.socket.sendall(packet)
        return self.sequence

    def receive(self):
        while b"\r\n\r\n" not in self.buffer:
            self.read()
        header, body = self.buffer.split(b"\r\n\r\n", 1)
        fields = dict(line.split(b":", 1) for line in header.split(b"\r\n"))
        length = int(fields[b"Content-Length"].strip())
        while len(body) < length:
            self.read()
            body = self.buffer.split(b"\r\n\r\n", 1)[1]
        self.buffer = body[length:]
        result = json.loads(body[:length])
        assert result["seq"] > self.last_server_sequence, result
        self.last_server_sequence = result["seq"]
        return result

    def read(self):
        chunk = self.socket.recv(8192)
        if not chunk:
            raise AssertionError("DAP connection closed unexpectedly")
        self.buffer += chunk

    def response(self, sequence, command, success=True):
        while True:
            result = self.receive()
            if result["type"] == "event":
                self.events.append(result)
                continue
            assert result["request_seq"] == sequence, result
            assert result["command"] == command, result
            assert result["success"] is success, result
            return result.get("body", {})

    def request(self, command, arguments=None, success=True, fragmented=False):
        sequence = self.send(command, arguments, fragmented)
        return self.response(sequence, command, success)

    def event(self, name):
        for index, event in enumerate(self.events):
            if event["event"] == name:
                return self.events.pop(index).get("body", {})
        while True:
            result = self.receive()
            assert result["type"] == "event", result
            if result["event"] == name:
                return result.get("body", {})
            self.events.append(result)

    def attach(self, stop=False, zero_based=False):
        capabilities = self.request("initialize", {
            "adapterID": "srengine-angelscript", "clientID": "dap-smoke",
            "pathFormat": "path", "linesStartAt1": not zero_based,
            "columnsStartAt1": not zero_based,
        }, fragmented=True)
        assert capabilities["supportsConfigurationDoneRequest"]
        self.request("attach", {"stopOnEntry": stop})
        self.event("initialized")
        self.request("setExceptionBreakpoints", {"filters": []})
        self.request("configurationDone")

    def detach(self):
        self.request("disconnect", {"terminateDebuggee": False})
        self.event("terminated")
        self.close()


def protocol_checks(port, timeout):
    client = Client(port, timeout)
    try:
        client.request("threads", success=False)
        client.attach()
        # A DAP connection must survive the underlying socket's one-second timeout.
        time.sleep(2.1)
        assert client.request("threads")["threads"][0]["id"] == 1
        client.request("launch", success=False)
        client.request("неподдерживаемая-команда", success=False)
        client.request("stackTrace", {"threadId": 1}, success=False)
        # Two requests in flight exercise coalesced packets and response sequencing.
        first = client.send("threads")
        second = client.send("threads")
        client.response(first, "threads")
        client.response(second, "threads")
        client.detach()
    finally:
        client.close()


def execution_checks(port, timeout):
    client = Client(port, timeout)
    try:
        client.attach(stop=True)
        client.event("stopped")
        frames = client.request("stackTrace", {"threadId": 1})["stackFrames"]
        frame = frames[0]
        source = frame["source"]["path"]
        assert Path(source).name == "DapDebugProbe.as", (
            "Run a scene with DapDebugProbe as the only active AngelScript behaviour", frame
        )
        lines = Path(source).read_text(encoding="utf-8").splitlines()
        line = next(index + 1 for index, text in enumerate(lines) if "// DAP_BREAKPOINT" in text)
        breakpoint = client.request("setBreakpoints", {
            "source": {"path": source}, "breakpoints": [{"line": line}],
        })["breakpoints"][0]
        assert breakpoint["verified"] and breakpoint["line"] == line, breakpoint
        client.request("continue", {"threadId": 1})
        stopped = client.event("stopped")
        assert stopped["reason"] == "breakpoint", stopped
        assert breakpoint["id"] in stopped["hitBreakpointIds"]
        frame = client.request("stackTrace", {"threadId": 1})["stackFrames"][0]
        scopes = client.request("scopes", {"frameId": frame["id"]})["scopes"]
        locals_reference = scopes[0]["variablesReference"]
        locals_ = client.request("variables", {"variablesReference": locals_reference})["variables"]
        assert {"this", "before"} <= {value["name"] for value in locals_}, locals_
        for expression in ("before", "this.ticks", "label", "this.data.score"):
            value = client.request("evaluate", {"expression": expression, "frameId": frame["id"]})
            assert "result" in value, value
        label = client.request("evaluate", {"expression": "this.label"})["result"]
        assert "Привет" in label, label
        position = client.request("evaluate", {"expression": "this.position"})
        assert position["variablesReference"] > 0, position
        coordinates = client.request("variables", {"variablesReference": position["variablesReference"]})["variables"]
        coordinates = {item["name"]: item["value"] for item in coordinates}
        assert float(coordinates["x"]) == 12.5 and float(coordinates["y"]) == -3.25, coordinates
        assert float(client.request("evaluate", {"expression": "this.position.x"})["result"]) == 12.5
        numbers = client.request("evaluate", {"expression": "this.numbers"})
        elements = client.request("variables", {"variablesReference": numbers["variablesReference"]})["variables"]
        elements = {item["name"]: item["value"] for item in elements}
        assert elements == {"size": "2", "[0]": "7", "[1]": "-4"}, elements
        counters = client.request("evaluate", {"expression": "this.counters"})
        entries = client.request("variables", {"variablesReference": counters["variablesReference"]})["variables"]
        entry = next(item for item in entries if item["name"] == "[0]")
        pair = client.request("variables", {"variablesReference": entry["variablesReference"]})["variables"]
        pair = {item["name"]: item["value"] for item in pair}
        assert pair == {"first": '"score"', "second": "11"}, pair
        native = client.request("evaluate", {"expression": "this.gameObject"})
        assert native["variablesReference"] > 0, native
        properties = client.request("variables", {"variablesReference": native["variablesReference"]})["variables"]
        assert properties, properties
        client.request("evaluate", {"expression": "DangerousCall()"}, success=False)
        client.request("setBreakpoints", {"source": {"path": source}, "breakpoints": []})
        for command in ("stepIn", "next", "stepOut"):
            client.request(command, {"threadId": 1})
            assert client.event("stopped")["reason"] == "step"
        client.request("scopes", {"frameId": frame["id"]}, success=False)
        client.request("variables", {"variablesReference": locals_reference}, success=False)
        client.request("variables", {"variablesReference": position["variablesReference"]}, success=False)
        client.request("continue", {"threadId": 1})
        client.request("pause", {"threadId": 1})
        assert client.event("stopped")["reason"] == "pause"
        # Simulate a crashed IDE while stopped. Reconnection must resume execution.
        client.close()
    finally:
        client.close()

    reconnect = Client(port, timeout)
    try:
        reconnect.attach(stop=True, zero_based=True)
        reconnect.event("stopped")
        frame = reconnect.request("stackTrace", {"threadId": 1})["stackFrames"][0]
        assert frame["id"] > 0 and frame["line"] >= 0
        zero_line = line - 1
        breakpoint = reconnect.request("setBreakpoints", {
            "source": {"path": source}, "breakpoints": [{"line": zero_line}],
        })["breakpoints"][0]
        assert breakpoint["verified"] and breakpoint["line"] == zero_line
        reconnect.detach()
    finally:
        reconnect.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--port", type=int, default=4711)
    parser.add_argument("--timeout", type=float, default=15)
    parser.add_argument("--execute", action="store_true", help="also stop/step DapDebugProbe in a running scene")
    parser.add_argument("--bridge", action="store_true", help="use the stdio bridge configured for CLion")
    parser.add_argument("--engine", type=Path, help="SREngine executable for --bridge")
    args = parser.parse_args()
    Client.use_bridge = args.bridge
    if args.bridge and args.engine is None:
        parser.error("--bridge requires --engine")
    Client.bridge_engine = args.engine.resolve() if args.engine else None
    protocol_checks(args.port, args.timeout)
    if args.execute:
        execution_checks(args.port, args.timeout)
    print("AngelScript DAP smoke checks passed")


if __name__ == "__main__":
    main()
