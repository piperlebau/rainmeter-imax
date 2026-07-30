# pipOS — runnable skeleton

This is a seed, not a finished theme. It gives you a valid Rainmeter config tree with the
architecture, tokens, and the on-device discovery tool already working, so you extend a running
thing instead of building from a blank folder. Read `CLAUDE.md` first — it is the rules.
Read `pipOS-SPEC.md` (one level up) for full detail. The visual authority is
`pipOS-wireframe-v20.html`.

## What already works

- **`@Resources/Variables.inc`** — every design token and geometry constant. HWiNFO indices are
  stubbed at `0` with `TODO` comments; resolve them on the device (below).
- **`@Resources/logic/*.inc`** — the shared layer: all sensor, workspace, toggle, status and
  power **measures**. Included by both variants. Contains zero meters, by rule.
- **`@Resources/Themes/*.inc`** — colour token sets (amber-hybrid, hc-amber, mono-white,
  tokyo-night). Swap the `@IncludeTheme` line in a skin to change scheme.
- **`@Resources/Scripts/log.lua`** — ring buffer for the log line / ALERTS. Lua because
  Rainmeter has no arrays.
- **`Pixel/pipOS.ini`** — the IMAX variant: bezel, frame, header (W1), LED rail, reserved holes.
- **`TUI/pipOS-tui.ini`** — the console variant: 132x40 grid, one fixed-width meter per row.
- **`Notes/`, `Editor/`** — child-skin stubs that render a placeholder line each,
  positioned from the shared geometry vars so they sit inside the main skin's frames.
- **`Tools/Discover.ini`** — **functional.** Lists every HWiNFO VSB registry index. This is how
  you turn the `Idx*` stubs in `Variables.inc` into real numbers.
- **`includes/*.inc`** — six stub sections (`Session`, `Bay`, `Banner`, `Telemetry`, `Transport`,
  `Rail`) to be filled in during A1 and `@Include`d into `pipOS.ini`.
- **`tests/`** — `check_geometry.py` (layout budget + pane parity) and `check_milestone.py A0|A1`.

## First run on the device

1. Install Rainmeter. Drop this folder into `Documents\Rainmeter\Skins\pipOS`.
2. Load `Tools\Discover.ini`. With HWiNFO running and Gadget reporting enabled, it lists the
   sensor indices. Copy the matching numbers into the `Idx*` variables in `Variables.inc`.
3. Load `Pixel/pipOS.ini`, then load `Notes.ini` and position it (via a saved
   Layout) inside their frames. Confirm they land in the holes — that proves the hybrid
   architecture (Milestone A0).

## Build loop

Work milestone by milestone (see `CLAUDE.md` → build order). After each change:

```
python tests/check_milestone.py A0     # then A1 as you progress
python tests/check_geometry.py         # layout budget + W11/W18 parity
```

Both exit non-zero and name what failed. Don't advance a milestone until its check is green.

## Current state

- Milestone **A0: PASS** (architecture + tokens + reserved holes).
- Milestone **A1: one task remaining** — implement the `includes/*.inc` sections against the
  wireframe and uncomment the `@Include` lines at the bottom of `pipOS.ini`, keeping every
  widget within the 607px column budget.
