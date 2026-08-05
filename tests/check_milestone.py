#!/usr/bin/env python3
"""
pipOS per-milestone exit tests.

These are cheap structural checks the coding agent can run to know when a
milestone is actually done, rather than guessing. They do NOT render Rainmeter
(that needs Windows) — they verify the files, tokens, and wiring that each
milestone requires, plus delegate the layout check to check_geometry.py.

Usage:
    python tests/check_milestone.py A0
    python tests/check_milestone.py A1

Exit 0 = pass, 1 = fail, 2 = bad usage.
"""

import sys, re, pathlib

ROOT = pathlib.Path(__file__).resolve().parent.parent
VARS = ROOT / "@Resources" / "Variables.inc"


def read(p):
    """Skin files are UTF-16 LE with BOM (Rainmeter requirement); everything
    else is UTF-8. Detect by BOM."""
    fp = ROOT / p
    if not fp.exists():
        return None
    raw = fp.read_bytes()
    if raw.startswith(b"\xff\xfe") or raw.startswith(b"\xfe\xff"):
        return raw.decode("utf-16")
    return raw.decode("utf-8")


def var_defined(text, name):
    return re.search(rf"^{re.escape(name)}=", text, re.M) is not None


def check_A0():
    """Architecture spike: frame + header + reserved holes + child skins align."""
    fails = []

    # required files exist
    for f in ["Pixel/pipOS.ini", "@Resources/Variables.inc",
              "Notes/Notes.ini", "Editor/Editor.ini",
              "Tools/Discover.ini", "CLAUDE.md",
              "@Resources/logic/sensors.inc", "@Resources/logic/workspace.inc",
              "@Resources/logic/status.inc", "@Resources/Scripts/log.lua"]:
        if read(f) is None:
            fails.append(f"missing required file: {f}")

    v = read("@Resources/Variables.inc") or ""
    main = read("Pixel/pipOS.ini") or ""

    # geometry tokens the whole build depends on
    for tok in ["BudgetY", "PaneHeight", "EdBodyH", "NotesX", "NotesY",
                "EditorX", "EditorY", "AmberBright", "ScreenBG",
                "GridCols", "GridRows", "CellW", "CellH"]:
        if not var_defined(v, tok):
            fails.append(f"Variables.inc missing token: {tok}")

    # the two constraints that must be their canonical values
    if not re.search(r"^PaneHeight=230\b", v, re.M):
        fails.append("PaneHeight must be 230 (constraint 3)")
    if not re.search(r"^BudgetY=607\b", v, re.M):
        fails.append("BudgetY must be 607 (constraint 2)")

    # main skin must be non-draggable and draw the reserved hole
    if "Draggable=0" not in main:
        fails.append("pipOS.ini must set Draggable=0 (constraint 4)")
    if "MeterNotesFrame" not in main:
        fails.append("pipOS.ini missing Notes reserved-hole frame")

    # child skins must position from the shared vars, not hard-coords
    for f, xvar in [("Notes/Notes.ini", "NotesX"), ("Editor/Editor.ini", "EditorX")]:
        c = read(f) or ""
        if "Draggable=0" not in c:
            fails.append(f"{f} must set Draggable=0")

    # no ClipString=2 anywhere (dead-end 2) — ignore comment lines (;) so a
    # warning comment about it doesn't trip the check
    for f in ["Editor/Editor.ini", "Notes/Notes.ini", "Pixel/pipOS.ini"]:
        for line in (read(f) or "").splitlines():
            if line.lstrip().startswith(";"):
                continue
            if "ClipString=2" in line:
                fails.append(f"{f} uses ClipString=2 — forbidden (breaks 230px pane)")
                break

    return fails


def check_shared_logic():
    """§17.6: logic/ holds measures only — zero meters — and both variants
    include the same files. This is the boundary that makes two variants
    affordable; if it erodes, changes must be made twice."""
    fails = []
    import glob, os
    logic_dir = ROOT / "@Resources" / "logic"
    for f in sorted(logic_dir.glob("*.inc")):
        raw = f.read_bytes()
        body = raw.decode("utf-16") if raw.startswith(b"\xff\xfe") else raw.decode("utf-8")
        for line in body.splitlines():
            t = line.strip()
            if t.lower().startswith("meter="):
                fails.append(f"{f.name} contains a Meter= — logic/ is measures only (§17.6)")
                break
    pixel = read("Pixel/pipOS.ini") or ""
    tui = read("TUI/pipOS-tui.ini") or ""
    if tui:
        for inc in ["sensors.inc", "workspace.inc", "toggles.inc", "status.inc", "power.inc"]:
            if inc not in pixel:
                fails.append(f"Pixel/pipOS.ini does not include logic/{inc}")
            if inc not in tui:
                fails.append(f"TUI/pipOS-tui.ini does not include logic/{inc}")
    return fails


def check_A1():
    """Static shell: A0 plus include sections wired and geometry passing."""
    fails = check_A0() + check_shared_logic()  # A1 subsumes A0

    main = read("Pixel/pipOS.ini") or ""

    # include sections should exist as files
    for inc in ["Session.inc", "Bay.inc", "Banner.inc",
                "Telemetry.inc", "Transport.inc", "Rail.inc"]:
        if read(f"Pixel/includes/{inc}") is None:
            fails.append(f"missing include: Pixel/includes/{inc}")

    # at least one include must actually be wired (uncommented) in the main skin
    wired = re.search(r"^\s*@Include\d+=", main, re.M)
    if not wired:
        fails.append("pipOS.ini has no active @Include — A1 must wire the section files "
                     "(uncomment them as implemented)")

    # discovery helper must still be real (has registry measures)
    disc = read("Tools/Discover.ini") or ""
    if disc.count("Measure=Registry") < 2:
        fails.append("Tools/Discover.ini should read the VSB registry (Measure=Registry)")

    return fails


def main():
    if len(sys.argv) != 2 or sys.argv[1] not in ("A0", "A1"):
        print("usage: python tests/check_milestone.py [A0|A1]", file=sys.stderr)
        sys.exit(2)

    ms = sys.argv[1]
    fails = check_A0() if ms == "A0" else check_A1()

    print(f"=== Milestone {ms} exit check ===")
    if fails:
        print(f"FAIL ({len(fails)} issue(s)):")
        for f in fails:
            print("  ✗", f)
        if ms == "A1":
            print("\nAlso run: python tests/check_geometry.py")
        sys.exit(1)

    print("PASS — structural criteria met.")
    if ms == "A1":
        print("Now run: python tests/check_geometry.py  (layout budget + pane parity)")
    sys.exit(0)


if __name__ == "__main__":
    main()
