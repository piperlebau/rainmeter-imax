# pipOS — project decisions & status

The build rules live in **`/CLAUDE.md`** (load-bearing) and the full **`pipOS-SPEC.md`**.
The visual authority is **`pipOS-wireframe-v20.html`** (Pixel) and **`pipOS-console-live.html`**
(TUI). This file records only the project-specific decisions layered on the skeleton and the
current status — it does not restate the construction rules.

## Target
ASUS ROG Flow Z13 (2025, GZ302EA), 2560×1600 touchscreen, designed at 1280×800 logical
(@200% DPI). Amber-phosphor IMAX-console shell; 18 widgets, 5 workspaces; Pixel + TUI variants.

## Decisions
- **Adopted the official skeleton** as the repo base (was diverging from it earlier). This repo
  *is* the Rainmeter config folder `pipOS`.
- **Themes: exclusively high-contrast, pure-black backgrounds.** Per the user's directive, the
  non-black palettes were removed (`amber-hybrid` bg `10,7,0`; `tokyo-night` bg `12,14,18`).
  `ScreenBG` is forced to `0,0,0` in `Variables.inc`. Active set (all `Bg=0,0,0`):

  | Theme | Notes |
  |---|---|
  | **HC AMBER** *(default)* | The IMAX look at max legibility (design system, WCAG 6.3). |
  | **MONO WHITE** | No hue; highest contrast (11.5); severity via shape/text too. |
  | **NIGHT RED** | Preserves dark adaptation (design system). |
  | **HC GREEN** | Derived from the HC AMBER role structure — confirm on device. |
  | **HC CYAN** | Derived from the HC AMBER role structure — confirm on device. |

  Default `@IncludeTheme` in both skins is now `hc-amber.inc`. More HC hues (NAVY, MAGENTA,
  YELLOW) can be added the same way once their role mappings are confirmed.
- **Fonts bundled**: IBM Plex Mono (Regular/Medium/SemiBold) added to `@Resources/Fonts/`
  (the skeleton had relied on a system install).
- **TUI variant is in scope** and present (`TUI/pipOS-tui.ini`); to be built out in Milestone D.

## Visual authority (received)
The authority files now live in `docs/`: **`pipOS-wireframe-v21.html`** (Pixel — supersedes the
v20 that `CLAUDE.md` named), **`pipOS-console-live.html`** (TUI), **`pipOS-SPEC.md`** (full spec).
Widget geometry was measured from v21 and normalised to the 1280×800 skin space.

## Status (skeleton milestones)
- **A0 (architecture + tokens + reserved holes): PASS.**
- **A1 (implement the six `Pixel/includes/*.inc` against v21): PASS structurally** — all six
  sections implemented to measured coordinates and wired into `pipOS.ini`; `check_milestone.py A1`
  green; `logic/` is meter-free; the shell is fully role-tokenised so the HC themes recolour it.
  *Still needs on-device Rainmeter render to verify, and the browser-based `check_geometry.py`
  to run (the harness needs its Chromium).*
- Reconciled vs. the stale skeleton: left column 616→**894px** (v21), Notes=full-width top pane,
  Editor swaps into the Launch-Bay slot; token names unified to design-system roles.
- **Device feedback round 1** (Z13 screenshots of both variants):
  - *Mojibake everywhere* → Rainmeter reads skin text as ANSI unless UTF-16 LE BOM. All
    `.ini`/`.inc` converted; `.gitattributes` `working-tree-encoding=UTF-16LE-BOM eol=CRLF`
    keeps repo diffs readable; test readers BOM-aware. **Keep new skin files UTF-16 LE BOM.**
  - *Text ~33% oversized* (brand collided with modeline) → Rainmeter `FontSize` is POINTS,
    wireframe is CSS px. All sizes converted ×0.75. **Author sizes in points from now on.**
  - *TUI* — full-grid background added (desktop no longer bleeds through), status row was
    green-on-green → ink-on-fill. Full 40-row build stays Milestone D.
  - *Notes/Editor child skins floated at 0,0* → they now `!Move` into their reserved holes via
    `DpiScale=2` (assumes main skin at screen 0,0). Editor should only be loaded in WRITE mode.
- **Device feedback round 2** — Pixel render verified clean (encoding + sizes correct).
  Fixed: child-skin `!Move` operates in the DPI-scaled space (dropped the ×2), banner `✳`
  had an emoji presentation on Windows → swapped to `✱` (U+2731).
- **Milestone B1 built** (needs on-device verification):
  - `logic/` completed: `mIGPUTemp`, `mVRAMDed`+`mVRAMPct`, `mBattLeft`, `mTime/mDate/mUptime`,
    per-bar threshold-colour mappers (`BarCol*`), `SevColor` from the status machine, FileView
    bay children (`mBayFile/Name/Go 1..6`), broken poller stub fixed.
  - Pixel live: status strip (severity fill + message), uptime/date/clock, subsystem Bar meters
    with threshold colours + cell separators, HWiNFO values gated to `—` while `Idx*=0` (law 5),
    negative battery draw in `err`, perf-mode buttons live on `#PerfMode#` (commanded-not-
    confirmed, logged, `△`), RST resets the energy accumulator.
  - Workspace switching: rail taps set+persist `Workspace`/`WSMode`, active-tab inverse fill,
    LEDs/modeline/banner/profile follow, WS4 (WRITE) hides the bay group and activates the
    Editor child skin at identical 230px geometry.
  - Launch bay is live: slots populate from `@Resources\Workspaces\WS<N>\*.url` and launch on
    tap; empty slots show `— EMPTY —`. **Requires the third-party FileView plugin** — install
    it or the bay stays empty (bundle it in the Phase-4 `.rmskin`).
  - FUNCTIONS now cycles the phosphor theme (hc-amber → hc-green → hc-cyan → mono-white →
    night-red) across all four skins via `NextTheme` chain + `!RefreshApp`.
  - TUI status row severity-coloured from the same `#SevColor#`.
- **B2 (next)**: the toggle poller (`sensors.ps1`, PS 5.1 + WinRT radios), toggle tap actions,
  poller-staleness wiring (`mPollerAge`), AHK hookup for perf mode + transport, battery
  time-left H:MM formatting, HWiNFO index discovery on device (`Tools\Discover.ini`).

## Open questions
1. Confirm Z13 panel = 2560×1600.
2. Want the two derived themes (HC GREEN / HC CYAN) kept, or a different HC hue set?
3. Workspaces: the skeleton ships WS1–WS5 stubs (`@Resources/Workspaces/`) — hand me your real
   app targets, or keep iterating on the stubs?
