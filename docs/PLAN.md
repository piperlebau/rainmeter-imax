# pipOS — Rainmeter theme

A Rainmeter desktop shell that turns an **ASUS ROG Flow Z13 (2025)** into an
**IMAX film-projector control console** — amber phosphor on near-black — that also
works as a real, touch-driven system dashboard and application launcher.

Built to the **pipOS design system** (see the `pipos-design-system` skill: tokens,
components, laws, anti-patterns). This document is the project's own plan; the design
system is the authority on *how things look and are constructed*.

---

## 1. What Rainmeter is (quick primer)

Rainmeter is a free, open-source Windows tool that draws always-on-top "skins" on the
desktop showing live system data and responding to clicks/taps.

| Term | Meaning here |
|---|---|
| **Skin** | One panel, defined by a `.ini` file. |
| **Measure** | A data source (CPU %, RAM, uptime, clock, net bytes…). |
| **Meter** | A drawn element (text, rectangle, image, button), usually fed by a measure. |
| **Plugin** | Add-on for data Rainmeter can't read natively (**UsageMonitor**, **HWiNFO**). |
| **`@Resources`** | Per-config assets: fonts, images, include files. |
| **Include (`.inc`)** | A variables file pulled into the skin — how the theme stays configurable without touching skin code. |
| **`.rmskin`** | One-click installer package (produced at the end). |

**Constraints that shape everything:**
- Rainmeter is **Windows-only**. Authored here on Linux, so **you test on the Z13**;
  the loop is *edit → you refresh → screenshot → fix*.
- **Geometry is 1280×800 logical** = 2560×1600 at Windows' 200% scale. Designing at
  1280×800 fills the Z13 edge-to-edge.
- **Touch = mouse clicks.** Logic is unchanged; buttons must be large (primary ≥44px).
- Rainmeter has **no loops, arrays, blur, or blend modes** — glow/scanlines are baked
  into PNG alpha; repeated elements are written out explicitly.

---

## 2. Identity (from the design system)

A 1990s IMAX projector console, modernised for a tablet. Amber phosphor on near-black,
monospace all-caps labels, hairline **caption-break boxes**, **inverse-video** status
fields, a green LED rail on the bezel. **Nothing animates.** The machine is
*instrumented, not decorated* — it shows model names, `.exe` paths, sensor indices.

**Font:** IBM Plex Mono (bundled — Regular / Medium / SemiBold).

### The laws (each exists because breaking it caused a real defect)
1. No animation. 2. Severity is colour **and** text. 3. Show the mechanism.
4. Mark unofficial mechanisms with `△`. 5. Never fake a value (missing = `—`, never `0`).
6. Swapped panes are byte-identical in size. 7. Fixed regions clip, never grow.
8. Every colour/dimension comes from a token. 9. Touch tiers: primary ≥44px,
   secondary ≥26px, dense rows 16px; tap on release; no hover-only UI.

---

## 3. Two variants, one back-end

| | **Pixel (IMAX)** | **TUI (console)** |
|---|---|---|
| Look | hairline shapes, free pixel layout | box-drawing glyphs on a 132×40 char grid |
| Matches | the reference photo | a text-terminal reading of the same console |

Shared **measures** live in `@Resources/logic/` and feed **both**; **meters** are
per-variant. Changing a sensor index or adding a workspace = edit one `logic/` file,
both variants pick it up. **Pixel is the primary target**; TUI is a stretch variant.

---

## 4. All themes included

Not just amber — the full set of design-system palettes ships, each a token file in
`@Resources/themes/`. The **PHOSPHOR** control cycles them (rewrites `@IncludeTheme`,
refreshes); the choice persists across restarts.

| Theme | Character | WCAG* |
|---|---|---|
| **AMBER HYBRID** *(default)* | IMAX phosphor; severity colours only where state matters | 6.6 AA |
| **HC AMBER** | Same identity, max legibility; safest at 200% DPI | 6.3 AA |
| **MONO WHITE** | No hue; highest contrast; severity via shape/text too | 11.5 AAA |
| **TOKYO NIGHT** | Modern console; strongest token separation | 7.3 AAA |
| **NIGHT RED** | Preserves dark adaptation | 6.1 |

\*Worst case across information-bearing roles only. More palettes from the system
(HC GREEN/CYAN/BLACK, CATPPUCCIN, GRUVBOX, NORD…) can be added as token files once
their 14-role mappings are confirmed.

---

## 5. Anchor panels vs. the variable panel

- **Anchors (identical every workspace):** header + modeline, `SYSNODE` info,
  `STATUS` inverse-video strip, uptime line, and the right-column instruments —
  `LAMP VALUES` (CPU/MEM), `THERMAL` (GPU/CPU °C), `POWER`, `FRAME COUNT` (net RX),
  `INDICATORS`, the bottom **tab rail** + LED row.
- **Variable panel:** the **LAUNCH BAY** only. Each workspace sets its own button
  count and grid; the anchors around it never move (swapped panes stay identical
  height — law 6).

### Field mapping (IMAX → function)
| Panel element | Becomes |
|---|---|
| `SHOW LOCAL – AUTO MODE` | `SYSTEM LOCAL – <MODE> MODE` modeline |
| `SHOW INFORMATION` | `SYSNODE` — host/model/os/user/profile (key=value) |
| `STATUS / PRESETS COMPLETED` | Inverse-video status strip (fill = severity) |
| `SHOW TIME · DATE · TIME` | uptime / date / clock |
| checkboxes | live `INDICATORS` (net/disk/ram, ON/OFF) |
| `LAMP VALUES` | CPU % + MEM %, segmented threshold bars |
| *(new)* `THERMAL` / `POWER` | GPU/CPU °C, battery draw — via HWiNFO, marked `△` |
| `FRAME COUNT` | network received counter |
| `RUN / JOG / STOP` + grid | the per-workspace `LAUNCH BAY` |
| `Change Mode` | cycle workspaces · `PHOSPHOR` | cycle themes · `Exit Show` | unload |

---

## 6. Configuration (no skin edits)

```
pipOS/
├─ pipOS.ini                     ← Pixel skin (generated; you don't edit)
└─ @Resources/
   ├─ Variables.inc              ← active workspace + @IncludeTheme + sensor indices (persisted)
   ├─ fonts/IBMPlexMono-*.ttf
   ├─ images/                    ← baked scanline / glow PNGs
   ├─ logic/                     ← shared MEASURES only (CPU, RAM, thermal, net, status priority)
   ├─ themes/*.inc               ← the palettes (done)
   └─ Workspaces/*.inc           ← YOUR apps per mode (label + command); count & columns per file
```

Each workspace file uses the **same variable names** (`Btn1_Label`, `WS_Cols`, …), so
Change Mode just swaps which file loads and refreshes.

**Data sources:** UsageMonitor for CPU/RAM/disk/net (no dependency); HWiNFO (VSB
method) only for temps/power/GPU, indices stored as named vars and read with their
labels to catch drift (`△`); a background writer for anything needing a shell call.

---

## 7. Roadmap & status

- **Phase 0 — Scope & identity** ✅ locked; realigned to the pipOS design system.
- **Phase 1 — Look** ✅ Pixel mockup at 1280×800 (DEV workspace), live theme switcher
  across all 5 palettes. → `docs/pixel-mockup.html`.
- **Phase 2 — Data (measures)** ⬜ `logic/` measures via UsageMonitor + HWiNFO, with
  `—`/`△` fallbacks and a status priority integer.
- **Phase 3 — Pixel meters** ⬜ translate the mockup to Rainmeter meters; caption-break
  boxes, segmented bars, inverse-video, tab rail; wire launch bay + toggles.
- **Phase 4 — Package & polish** ⬜ `.rmskin`, README, `Scale`/DPI guide, glow/scanline
  bake, TUI variant if wanted.

**Done:** repo reset to pipOS structure; IBM Plex Mono bundled; 5 theme includes;
Pixel mockup + all-themes artifact.

---

## 8. Open questions

1. Confirm Z13 panel is **2560×1600**.
2. **Variants:** Pixel only for now, or build the TUI console variant too?
3. **Workspaces:** keep Gaming / Dev / Productivity / Media, and hand me your real
   app paths, or start from defaults you edit?
4. **Toggle placement:** PHOSPHOR/SCAN/CHANGE MODE on the rail (as mocked) — good?
5. **HWiNFO:** OK as the dependency for temps/power/GPU (with `—` when absent)?
