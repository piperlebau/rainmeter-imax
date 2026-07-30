# CLAUDE.md — pipOS build conventions

This file is read automatically. It is the short, load-bearing version of `pipOS-SPEC.md`.
Read the full spec for detail; obey this file always.

## What this is

An amber-phosphor Rainmeter shell for the ASUS ROG Flow Z13 (2025, GZ302EA) touchscreen.
Eighteen widgets, five workspaces, IMAX-projector-console aesthetic. The visual authority is
`docs/pipOS-wireframe-v21.html` — when in doubt about layout, colour, or size, measure it there.

## Non-negotiable constraints

1. **Measures are shared; meters are not.** Everything with `Measure=` lives in
   `@Resources/logic/*.inc` and is included by BOTH variants. Everything with `Meter=` lives
   in `Pixel/` or `TUI/`. If a change has to be made twice, the boundary is wrong.
   `logic/` must contain ZERO meters — the A1 test enforces this.
2. **Layout is one coordinate space per variant.** Pixel: `Pixel/pipOS.ini` holds every light
   widget; only `Notes.ini`, `Editor.ini`, `Overlay/Scanlines.ini`, `Tools/Discover.ini` are
   separate configs. TUI: monolithic — a child skin cannot land inside a character grid.
   Do not split either main skin into more windows.
2. **Column budget:** the lowest widget in each column must satisfy `Y + H ≤ 607`, measured from
   the top of the main content region. Positions are explicit; there is no auto-flow. Run
   `tests/check_geometry.py` after any layout change.
3. **W11 (launch bay) and W18 (editor) are both exactly 230px tall.** They swap by group
   show/hide. If they differ, every widget below shifts. This is checked by the geometry test.
4. `Draggable=0` on every skin. Every tap uses `LeftMouseUpAction`, never `LeftMouseDownAction`.
5. No `MouseOverAction`-dependent UI — touch has no hover.
6. No animation. Nothing blinks, pulses, or fades.
7. Touch tiers: primary controls ≥44px, secondary chips ≥26px, W8 toggle rows 16px (deliberate —
   do not "fix" upward, it breaks the budget).
8. `ClipString=1` with fixed `W`/`H` in text widgets. **Never `ClipString=2`** — it grows the
   meter and breaks constraint 3.
9. Every colour and dimension comes from `@Resources/Variables.inc` or a theme file in
   `@Resources/Themes/`. No literals in skin files.
10. **TUI only:** never trust a font to hold the grid. Box-drawing and block glyphs get
   substituted from fallback fonts with different advance widths — measured drift was 21px
   per row. Give every row meter the same explicit fixed `W`.

## When you are blocked

- **Unknown HWiNFO index?** Stub it: set the index variable to `0`, add `; TODO: discover on device`,
  and keep going. Do NOT invent a plausible index or halt. The user resolves these with
  `Tools/Discover.ini` on the actual machine.
- **Unknown sensor label string?** Same — stub and TODO. Labels are device-specific.
- **InputTextX not present?** Degrade the editor to read-only display + append-only single-line
  entry. Do not drop the widget silently.
- **A design choice the spec doesn't cover?** Prefer the option that keeps the column budget and
  the 230px pane constraint intact, then leave a `; NOTE:` explaining the choice.

## Sensor sourcing rule

UsageMonitor for anything it can read (CPU load, per-core, RAM, disk, network).
HWiNFO **only** for what UsageMonitor cannot (temps, power, GPU load, VRAM, battery rate, fan RPM).
This confines HWiNFO index-drift risk to the sensors that truly need it.

## Dead ends — do not attempt

1. The HWiNFO Rainmeter plugin (unmaintained; Shared Memory is 12h-limited in free HWiNFO).
   Use the Registry/VSB method — see `Tools/Discover.ini`.
2. `ClipString=2` anywhere in Notes/Editor.
3. Stock `InputText` for multiline — structurally impossible. Use InputTextX.
4. `Disable-NetAdapter` / `netsh` / `radioEnable` registry for Wi-Fi (admin-required, wrong
   semantics, or removed in Win11). Use WinRT `Windows.Devices.Radios` under **PowerShell 5.1**,
   not pwsh 7.
5. G-Helper / Armoury Crate CLI mode switching — does not exist. Drive it via AutoHotkey hotkeys.
6. Rainmeter sending keystrokes — not supported; shell out to AHK.
7. Embedding a live terminal/editor window inside a skin — Rainmeter is not a window host.
8. Loops in Rainmeter — none exist. Fixed meter count, dynamically populated.
9. Blend modes / native blur — none. Bake into PNG alpha.

## Build order

Milestone A0 (architecture spike) → A1 (static shell) → B (live data + control) →
C (text widgets) → **D (TUI variant)**. Do A0 first and prove the hybrid split before
building on it. D starts only when A-C are green; its first step is factoring every
`Measure=` out into `logic/` WITHOUT changing behaviour.
Each milestone has an exit test in `tests/` — do not advance until it passes.

## Verifying your work

```
python tests/check_geometry.py        # column budget + W11/W18 parity, both modes
python tests/check_milestone.py A0     # or A1 — per-milestone exit criteria
```

Both exit non-zero on failure and print what failed. Run them before claiming a milestone done.
