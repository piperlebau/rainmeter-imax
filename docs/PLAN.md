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

## Blocker — need the visual authority files
The skeleton references three files that are NOT in the shared zip and are required to match the
canonical layout (this is why the earlier standalone mockup diverged):

1. **`pipOS-wireframe-v20.html`** — the Pixel layout source of truth; `tests/check_geometry.py`
   measures it, and the `includes/*.inc` sections must be built against it.
2. **`pipOS-console-live.html`** — the TUI reference grid.
3. **`pipOS-SPEC.md`** — full spec (widget list W1–W18, §-references throughout CLAUDE.md).

Please share these; until then, layout work (Milestone A1) can't faithfully match v20.

## Status (skeleton milestones)
- **A0 (architecture + tokens + reserved holes): PASS** (from skeleton).
- **A1 (implement the six `Pixel/includes/*.inc` against the wireframe): blocked** on the files above.
- Theme + font + variant groundwork done in this repo.

## Open questions
1. Confirm Z13 panel = 2560×1600.
2. Want the two derived themes (HC GREEN / HC CYAN) kept, or a different HC hue set?
3. Workspaces: the skeleton ships WS1–WS5 stubs (`@Resources/Workspaces/`) — hand me your real
   app targets, or keep iterating on the stubs?
