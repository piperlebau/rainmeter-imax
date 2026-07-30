# pipOS tokens

## Role definitions

Every palette defines the same fourteen roles. A component references a **role**, never a colour.

### Structure
| Role | Meaning |
|---|---|
| `bg` | screen background |
| `bezel` | the frame around the screen |
| `fg` | default foreground text |
| `dim` | secondary text, punctuation, log message bodies |
| `faint` | line numbers, empty-cell fill, rules, disabled |
| `frame` | box-drawing / hairline borders |

### Semantic (TUI variant leans on these; Pixel uses them sparingly)
| Role | Applies to |
|---|---|
| `key` | field names — `host=`, `perf=`, `cpu`, `[F1]` |
| `str` | values, app names, workspace codes |
| `num` | all numbers — temps, watts, percentages, timestamps, RPM |
| `path` | file paths, executables, endpoints |
| `kw` | box captions, banner text |

### Severity — never omit these, and never repurpose them
| Role | Meaning |
|---|---|
| `ok` | nominal, enabled, healthy |
| `warn` | degraded, unconfirmed, unofficial mechanism fired |
| `err` | fault, disabled, negative power draw, critical |

Plus `sel` (selection background) and `inkOnFill` (text drawn on an inverse-video fill).

---

## Palettes

Contrast is the **worst-case WCAG ratio across information-bearing roles only**
(`fg key str num ok warn err`) — decorative `frame`/`faint` are excluded, because
including them makes legible schemes look like failures.

### AMBER HYBRID — default
IMAX phosphor for structure; severity colours introduced only where state matters.
Worst-case **6.6 (AA)**.
```
bg #0A0700   bezel #100E0A  fg #FFB000  dim #7F5800  faint #4A3300  frame #8A5F00
key #CC8C00  str #FFC94D    num #FFE08A path #D9A441 kw #FFD27A
ok #3BFF6A   warn #FF9E2B   err #FF5E2B sel #2A1D00  inkOnFill #0D0900
```

### HC AMBER — maximum legibility, same identity
Safest against 200% DPI softening. Worst-case **6.3 (AA)**.
```
bg #000000   bezel #0B0800  fg #FFC53D  dim #9A6E00  faint #5A4000  frame #B58200
key #FFA500  str #FFDD77    num #FFF0B3 path #FFB733 kw #FFE680
ok #3BFF6A   warn #FF9500   err #FF4A3D sel #2A1D00  inkOnFill #000000
```

### MONO WHITE — no hue; severity by brightness only
Highest measured contrast, **11.5 (AAA)**. Most robust to blur. Use when legibility
outranks character, or for accessibility.
```
bg #000000   bezel #080808  fg #FFFFFF  dim #909090  faint #4A4A4A  frame #B0B0B0
key #E0E0E0  str #FFFFFF    num #F0F0F0 path #D0D0D0 kw #FFFFFF
ok #FFFFFF   warn #C0C0C0   err #FFFFFF sel #222222  inkOnFill #000000
```
Note: with no hue available, severity **must** also change shape or text — brightness
alone is not sufficient signal.

### TOKYO NIGHT — modern console, strongest token separation
Worst-case **7.3 (AAA)**. Best when many token types appear close together.
```
bg #0C0E12   bezel #15181E  fg #C8CDD4  dim #5A6270  faint #333944  frame #3E4A5C
key #7AA2F7  str #9ECE6A    num #FF9E64 path #7DCFFF kw #BB9AF7
ok #9ECE6A   warn #E0AF68   err #F7768E sel #2A3149  inkOnFill #0C0E12
```

### Others prototyped
`HC BLACK` 7.1 AAA · `HC GREEN` 7.1 AAA · `HC CYAN` 7.1 AAA · `CATPPUCCIN` 7.1 AAA ·
`HC NAVY` 6.8 · `GREEN HYBRID` 6.6 · `HC YELLOW` 6.2 · `HC MAGENTA` 6.2 ·
`NIGHT RED` 6.1 (preserves dark adaptation) · `HC WHITE` 5.9 (only light scheme) ·
`DRACULA` 4.5 · `GRUVBOX` 4.3 · `ONE DARK` 4.4 · `MONOKAI` 3.9 · `NORD` 3.1

---

## Type

- **Family:** monospace throughout. IBM Plex Mono is the reference; JetBrains Mono, Cascadia
  Mono, and DejaVu Sans Mono are acceptable. Bundle the font — do not rely on a system install.
- **Case:** labels and captions all-caps. Values and file paths keep their natural case.
- **Sizes (Pixel variant):** brand 23px · modeline 19px · readout 17px · body 13px ·
  caption/label 10px · sub-label 8–9px.
- **TUI variant:** one size only — 15.8px at a 9.45×18.6px cell. Density comes from the grid,
  not from size variation.

## Geometry

**Pixel:** designed at 1280×800 logical (2560×1600 @ 200%). Columns are bottom-anchored;
the lowest widget must end at `Y+H ≤ 607`. Panes that swap are exactly 230px.

**TUI:** 132 columns × 40 rows. Cell 9.45×18.6px, origin (16,14). Fills 99.8% of screen width.
This is a *separate coordinate system* — do not derive it from the pixel values.

## Effects

- **Glow:** stack two blurred shadows (6px at 30% alpha, 12px at 8%). Subtle; it should read
  as phosphor bloom, not neon.
- **Scanlines:** 4px-period horizontal darkening at ~28% via multiply. Tuned for near-black
  backgrounds — reduce or disable on light schemes (`HC WHITE`, `SOLARIZED LIGHT`) where it
  reads as an artifact rather than atmosphere.
- **Vignette:** radial darkening from 55% outward. Optional.
- **No blur, no blend modes** in Rainmeter — bake into PNG alpha.
