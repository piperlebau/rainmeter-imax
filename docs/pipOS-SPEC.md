# pipOS — Rainmeter Suite Implementation Spec

**Target:** ASUS ROG Flow Z13 (2025, GZ302EA) · Ryzen AI Max+ 395 · Radeon 8060S · 2560×1600 touchscreen · Windows 11
**Reference designs:** `pipOS-wireframe-v21.html` (Pixel variant) and `pipOS-console-live.html` (TUI variant) — both in this folder. Treat them as the authority for layout, colour, and geometry.
**Aesthetic:** 1990s IMAX film-projector control console. Amber phosphor on near-black, monospace all-caps, hairline boxes with caption-break labels, inverse-video status fields, green LED rail on the bezel edge.

---

## 0. Start here

1. Read §1 (constraints) and §3 (tokens) before writing any `.ini`. **Both visual variants ship (§17)** — build Pixel first, then TUI over the same shared logic layer (§17.6).
2. Build **Milestone A0 then A1** (§13) before anything from B or C. A0 proves the architecture; do not skip it.
3. The first thing to build is the **HWiNFO index discovery helper** (§5.2). Nothing else can be wired without it.

**Estimated effort:** Milestone A0 ≈ ½ day, A1 ≈ 1 day. B ≈ 2–3 days. C ≈ open-ended (depends on InputTextX behaviour).

---

## 1. Hard constraints

These are not preferences. Violating any of them breaks something that was already fixed.

| # | Constraint | Why |
|---|---|---|
| 1 | Shell renders in a **1280×800 logical** area | 2560×1600 at 200% Windows scaling |
| 2 | **The lowest widget in each column must satisfy Y+H ≤ 607px** (measured from the top of the `.main` region). | Rainmeter has no auto-flow; positions are explicit. In the reference the columns are bottom-anchored, so any widget that overshoots rides *upward* into the header. Enforce per-widget, not as a flow property. |
| 3 | **W11 and W18 must be exactly the same height (230px)** | They swap via group show/hide. Any difference shifts every widget below them |
| 4 | `Draggable=0` on all skins | Prevents touch-drag displacing the console |
| 5 | `LeftMouseUpAction` for every tap. Never `LeftMouseDownAction` | Down-press disables dragging and is not the tap event |
| 6 | **No `MouseOverAction`-dependent UI** | Touch has no hover state; hidden-until-hover controls are unreachable |
| 7 | **No animation.** Nothing blinks, pulses, or fades | Explicit design decision |
| 8 | **Three target tiers:** primary controls (W5 transport, W7/FUNCTIONS actions, launch slots, workspace rail, perf mode) ≥44px · secondary chips (console/notes/editor toolbars, header FUNCTIONS/ALERTS buttons) ≥26px · W8 toggle rows 16px (deliberate). | Matches the reference measurements. Do **not** enlarge chips or toggles to hit 44px — it breaks the column budget (constraint 2). See §9.1. |
| 9 | `ClipString=1` with fixed `W`/`H`. **Never `ClipString=2`** in W17/W18 | `ClipString=2` grows the meter, which breaks constraint 3 |

### 1.2 Skin architecture — hybrid

The reference renders as **one** 1280×800 console, and that single coordinate space is *why* the layout is provably correct: the 607px budget (constraint 2) and the W11/W18 parity (constraint 3) are only enforceable when everything shares one origin. Eleven independent skins cannot see each other, so those guarantees would degrade to hope and the overlap bug this project already fixed would return at the skin level.

Therefore:

*(This section describes the **Pixel** variant. The TUI variant is monolithic — see §17.1a.)*

- **One main skin — `Pixel\pipOS.ini`** — owns the bezel, the screen frame, and every *light* widget: W1, W2, W3, W4, W5, W6, W8, W9/10, W11, W12a, W12b, W13, W14, W16. All of these live in one coordinate system where §14's checks are real.
- **Child skins for the heavy, frequently-refreshed text panes**, each occupying a reserved rectangle the main skin leaves empty:
  - `Notes.ini` → W17
  - `Editor.ini` → W18 (loaded only on editor-mode workspaces; the main skin leaves W11's rectangle empty in that mode)

Child skins refresh independently, so editing a note or opening a file does **not** reload telemetry. Their rectangles are defined by shared variables (`NotesX/Y/W/H`, `EditorX/Y/W/H`) in `Variables.inc`, so the main skin and the child agree on the hole without either measuring the other.

**Rule:** a widget goes in a child skin only if it refreshes on its own cadence (text edit, model response). Everything driven by the shared telemetry/workspace cycle stays in the main skin. Do not split further — every split trades an enforceable boundary for an unverifiable one.

The `§4` folder layout still holds for `@Resources`; the per-widget subfolders become organisational homes for that widget's `.inc` include, pulled into `pipOS.ini` via `@Include`, rather than eleven separate configs.

### 1.1 DPI strategy

**Default: let Rainmeter scale with Windows.** Design in logical pixels; the 2× scale helps touch targets. Accept mild text softening.

Only if amber text is unacceptably soft: set `Rainmeter.exe` → Properties → Compatibility → high-DPI override and redesign at native 2560×1600. Downsides: launched apps may inherit the override and render tiny, and `#SCREENAREAWIDTH#`/`#SCREENAREAHEIGHT#` change meaning.

Position relative to screen edges using `#SCREENAREAWIDTH#` / `#SCREENAREAHEIGHT#` in formulas, never hard pixels.

---

## 2. Dependencies

| Component | Required | Notes |
|---|---|---|
| Rainmeter | 4.5.x+ | `UsageMonitor`, `FileView`, `RunCommand`, `InputText`, `Quote` ship with it |
| HWiNFO64 | v7.02+ | Sensors-only mode is fine. **Do not enable Shared Memory** (§5.1) |
| InputTextX | Milestone C only | Third-party. Required for multiline editing — stock `InputText` cannot do it (§10.2) |
| nircmd | Milestone B | Mute toggle, media keys, brightness |
| Lua (built into Rainmeter) | Milestone B | Log ring buffer for W19 / ALERTS (§6.1a). No install needed |
| AutoHotkey | Milestone B | Only way to drive G-Helper performance modes (§11) |
| G-Helper | Milestone B | Must be tray-resident. Prefer over Armoury Crate (§5.4) |
| Windows PowerShell 5.1 | Milestone B | **Not pwsh 7** — WinRT radio calls fail there (§9.2) |

---

## 3. Design tokens

Put these in `@Resources\Variables.inc`. Every colour and dimension must come from here — no literals in skin files.

```ini
[Variables]
; ---- amber phosphor palette
AmberBright=255,176,0
AmberMid=204,140,0
AmberDim=127,88,0
AmberFaint=74,51,0
AmberGlow=255,176,0,77
ScreenBG=10,7,0
BezelBG=16,14,10
LEDOn=59,255,106
LEDOff=14,42,20
Warn=255,94,43
InkOnAmber=13,9,0

; ---- geometry (see constraint 2 & 3)
PaneHeight=230        ; outer height of W11 and W18 — FIXED, never flows (constraint 3)
EdBodyH=129           ; W18 text clip region — fixed; lines flow inside, clipped past ~8 (§10.4)
ColRightW=292
ScreenPad=13
GapL=9
GapR=7
HdrH=42
RailH=79

; ---- type
FontMain=IBM Plex Mono
FontSizeBody=12
FontSizeLabel=10
FontSizeReadout=17
```

**Font:** bundle an OFL-licensed monospace in `@Resources\Fonts`. Rainmeter auto-loads fonts from there on skin load — no system install, and it packages into the `.rmskin` automatically. Reference by *family* name, not filename.

Suggested: **IBM Plex Mono** (matches the reference design). Alternatives if a more period feel is wanted: JetBrains Mono, Space Mono, VT323. **DSEG** is worth considering for numeric readouts only (W9/10, W14).

### 3.1 Visual techniques

**Glow on text** — stack blurred shadows:
```ini
InlineSetting=Shadow | 0 | 0 | 6 | #AmberGlow#
InlineSetting2=Shadow | 0 | 0 | 12 | 255,176,0,20
```

**Boxes** — `Meter=Shape` with `StrokeWidth 1`. The caption-break label is a separate String meter with `SolidColor=#ScreenBG#` painted over the top border.

**Inverse-video fields** (W3, `.rlabel`) — filled `Shape` rectangle with a String meter in `#InkOnAmber#` on top.

**Scanlines** — tile a 4px-tall PNG via `Meter=Image` + `Tile=1`, in a **separate always-on-top skin with `ClickThrough=1`** so it doesn't block taps. Rainmeter has **no blend modes**; bake the effect into the PNG's alpha.

**No native blur or drop shadow on shapes.** Fake glow with concentric semi-transparent strokes or a pre-rendered PNG.

---

## 4. Structure

**Superseded by §17.6** once the TUI variant is in scope — see that section for the full two-variant tree. In the Pixel variant alone, the **activated** configs are `Pixel\pipOS.ini` plus the child skins `Notes\Notes.ini` and `Editor\Editor.ini`; everything in `includes\` is an `@Include` section, not a separately loaded skin. Shared measures live in `@Resources\logic\` (§17.6) and are included by both variants.

```
Skins\pipOS\
  @Resources\
    Variables.inc          ; tokens + persisted state (§8)
    Fonts\                 ; bundled OFL monospace
    Images\scanline.png
    Scripts\
      sensors.ps1          ; toggle-state poller (§9.4)
      radio.ps1            ; wifi/bluetooth toggle — PS 5.1 (§9.2)
      dialog.ps1           ; native file open/save dialogs (§10.3)
      perfmode.ahk         ; G-Helper hotkey sender (§11)
    Workspaces\
      WS1\ … WS5\          ; one folder of shortcuts per workspace (§7)
      notes\ws1-dev.md …   ; per-workspace notes files
  pipOS.ini                    ; MAIN skin — frame + all light widgets (§1.2)
  includes\                    ; per-widget .inc files pulled in via @Include
    header.inc W1 · session.inc W2/W3/W4 · bay.inc W11+W18-rect
    banner.inc W6 · telemetry.inc W8/W13/W9-10/W14/W16
    transport.inc W5 · rail.inc W12a · bezel.inc W12b
  Notes\Notes.ini              ; CHILD skin — W17
  Editor\Editor.ini            ; CHILD skin — W18 (editor workspaces only)
  Overlay\Scanlines.ini        ; ClickThrough overlay
  Tools\Discover.ini           ; HWiNFO index discovery helper (§5.2)
```

`@Resources` at the config root is shared by all skins beneath it; reference with `#@#`. Save a **Layout** once positioned so the whole suite loads together, and include it in the `.rmskin` (Manage → Create .rmskin package).

---

## 5. Sensor data

### 5.1 Use the registry (VSB) method

**Do not use the HWiNFO Rainmeter plugin.** It is unmaintained and depends on Shared Memory, which in free HWiNFO is time-limited to 12 hours and silently deactivates.

The registry method is free, unlimited, and needs no plugin. Setup for the user:

1. Install HWiNFO 7.02+, run it. Leave Shared Memory Support **off**.
2. Tray → Sensors → **Configure Sensors** → **HWiNFO Gadget** tab.
3. Check **Enable reporting to Gadget**.
4. For each wanted sensor, check **Report value in Gadget** and note its **Index**.

HWiNFO writes four values per index N under `HKEY_CURRENT_USER\SOFTWARE\HWiNFO64\VSB`:
`SensorN` (device name) · `LabelN` (element name) · `ValueN` (formatted, e.g. `61 °C`) · `ValueRawN` (raw number, e.g. `61`).

```ini
[MeasureCPUTemp]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=ValueRaw#IdxCPUTemp#
MinValue=0
MaxValue=100
DynamicVariables=1
```

Use `ValueRawN` for anything driving a bar or Calc; `ValueN` for direct display; `LabelN` to verify you're reading what you think.

Note: the `VSB` key only exists while HWiNFO is running. If HWiNFO runs elevated or under another account, read `HKEY_LOCAL_MACHINE` instead.

### 5.2 Build the discovery helper first

Index numbers are **fragile**: they shift when the user changes which sensors are exported, and — critically — **if a sensor is inactive at HWiNFO start (an idle fan), HWiNFO omits it and every later index shifts down.**

`Tools\Discover.ini` must:
1. Run `reg query HKEY_CURRENT_USER\SOFTWARE\HWiNFO64\VSB` via RunCommand.
2. Display every index with its `SensorN` / `LabelN` / `ValueN`.
3. Let the user write the chosen index into `Variables.inc` via `!WriteKeyValue`.

Store every index as a named variable (`IdxCPUTemp`, `IdxGPULoad`, …), never inline. Additionally, read `Label#IdxX#` alongside each value and show a warning flag if it doesn't match the expected string — that turns silent drift into a visible fault.

### 5.3 Sensor sourcing rule

**UsageMonitor for anything it can read; HWiNFO only for what it cannot.** This confines index-drift risk (§5.2) to the sensors that genuinely require HWiNFO.

- **UsageMonitor** (no dependency, no drift): CPU total + per-core, RAM, DISK activity, network.
- **HWiNFO** (unavoidable): all temperatures, all power/wattage, GPU load, VRAM, battery charge/discharge rate and time remaining.

### 5.3.1 Sensors to map


| Widget field | HWiNFO sensor (verify exact label on device) |
|---|---|
| W9/10 CPU TCTL | `CPU (Tctl/Tdie)` |
| W9/10 IGPU | `GPU Temperature` |
| W9/10 PACKAGE | `CPU Package Power` |
| W9/10 BATTERY | `Charge Rate` / `Discharge Rate` |
| W13 CPU | **UsageMonitor** `Alias=CPU` (not HWiNFO) |
| W13 IGPU | HWiNFO **`GPU Core Load`** — not `GPU D3D Usage` |
| W13 RAM | **UsageMonitor** `Alias=RAM` (not HWiNFO) |
| W13 VRAM | HWiNFO `GPU D3D Memory Dedicated` + `Dynamic` |
| W13 DISK | **UsageMonitor** `Alias=DISK` (not HWiNFO) |
| W14 LEFT / CHARGE | HWiNFO `Estimated Remaining Time` / `Charge Level` |

**Strix Halo quirks:**
- Use `GPU Core Load` (from the GPU directly) rather than the D3D counter, which only reflects D3D workloads.
- `GPU ASIC Power` on this platform reports **whole-APU** power, not iGPU-only.
- Unified LPDDR5X appears as `GPU D3D Memory Dedicated` (the BIOS carve-out via AMD Variable Graphics Memory — up to 24 GB on a 32 GB GZ302EA) plus `Dynamic` (shared pool). AMD does not expose exact iGPU memory usage as precisely as NVIDIA.

### 5.4 EC contention — expect this

The embedded controller is a shared resource. **Armoury Crate locks the SMBus/EC and is known to hang HWiNFO at "analyzing memory" or leave fan values frozen/grey.**

Spec the user guidance: run **G-Helper, not Armoury Crate**; only one EC-polling app at a time. If fan or thermal values freeze, disable HWiNFO's ASUS EC sensor or close the conflicting app.

### 5.5 UsageMonitor is primary for CPU/RAM/DISK, and the HWiNFO fallback

Per §5.3 `UsageMonitor` is the **primary** source for CPU, RAM, and disk — not a fallback. It also stands in for the HWiNFO-only fields when HWiNFO is absent (degrading as noted below). It covers CPU, per-core, RAM, disk, network:
```ini
[MeasureCPU]
Measure=Plugin
Plugin=UsageMonitor
Alias=CPU
```
`Index=0` sums all instances, `-1` averages, `N` returns the Nth-highest.

**UsageMonitor cannot report temperatures, fan speed, clocks, voltages, or power**, and its GPU counters are not trustworthy for total iGPU load. Degrade gracefully: show `—` in W9/10 and hide the IGPU/VRAM bars rather than displaying zeros.

---

## 6. Widget catalogue

Nineteen widgets. IDs match the `ANNOTATE WIDGETS` overlay in the wireframe. (W15, the AI console, was removed; its ID is retired and not reused. W19, the log line, was added in its place — see §6.1a.)

| ID | Name | Column | Interactive | Data source |
|---|---|---|---|---|
| W1 | Header — brand, mode line, FUNCTIONS, ALERTS | top | yes | `Workspace` var |
| W2 | Session information | left | no | static + `Workspace` |
| W3 | Status strip (inverse video) | left | no | derived (§6.1) |
| W19 | Log line | left | no | Lua ring buffer (§6.1a) |
| W4 | Uptime / date / time | left | no | `Measure=Time`, `UsageMonitor` |
| W5 | RUN / JOG / STOP transport | right | yes | nircmd media keys |
| W6 | Workspace banner (static) | left | no | `Workspace` |
| W8 | Toggles — 5 checkbox rows | right | **yes** | poller file (§9.4) |
| W9/10 | Thermal / power quad | right | no | HWiNFO |
| W11 | Launch bay — 6 slots, 3×2 | left | yes | FileView (§7) |
| W12a | Workspace rail — 5 buttons, bottom | bottom | yes | `Workspace` |
| W12b | Bezel LED rail — 5 LEDs | bezel | no | `Workspace` |
| W13 | Subsystem load — 5 segmented bars | right | no | HWiNFO |
| W14 | Battery / energy tri-field + RST | right | RST only | HWiNFO + Calc |
| W16 | Performance mode — 3-state | right | yes | AHK → G-Helper (§11) |
| W17 | Notes | left | yes | Quote + InputTextX |
| W18 | Editor (replaces W11 on editor workspaces) | left | yes | Quote + InputTextX |

### 6.1 W3 status strip

Not decorative. Derive from real conditions, in priority order. **Only one may display** — Rainmeter `IfCondition`s all evaluate independently, so do not use four separate conditions. Instead compute a single priority integer in one Calc measure and drive the string from that one value.

| Priority | Condition | Message | Severity |
|---|---|---|---|
| 3 | Any HWiNFO label mismatch | `CRIT  SENSOR MAP DRIFT — HWiNFO label mismatch, indices must be re-discovered` | error |
| 2 | Poller file stale >30s | `WARN  TOGGLE POLLER DOWN — switch states are stale, values not trustworthy` | warning |
| 1 | CPU load ≥85% (or temp >90°C) | `WARN  THERMAL LIMIT — package throttling expected` | warning |
| 0 | none of the above | `OK    AUTO MODE — ALL PRESETS NOMINAL — sensors ready, poller alive` | ok |

Use multiplicative guards so exactly one term is non-zero:

```ini
[mStatusCode]
Measure=Calc
Formula=(mLabelDrift>0)*3 + (mLabelDrift=0)*(mPollerStale>0)*2 + (mLabelDrift=0)*(mPollerStale=0)*(mCPULoad>=85)*1
DynamicVariables=1
IfCondition=(mStatusCode=3)
IfTrueAction=[!SetOption W3Text Text "CRIT  SENSOR MAP DRIFT…"][!SetOption W3Fill SolidColor #Err#]
; …one IfCondition per code, each also setting the strip fill colour
```

**The strip's background colour is part of the signal**, not decoration: green at code 0, amber at 1–2, red at 3. An operator should read state from colour before reading the words.

**Poller heartbeat.** Right-align a live `poll +Ns` counter inside the strip, where N is seconds since the poller last wrote. This makes the difference between "everything nominal" and "nothing has updated in five minutes" visible at a glance — without it, a dead poller looks identical to a healthy idle system.

**This logic is validated** in `pipOS-console-live.html`: injecting all three faults simultaneously displays only `SENSOR MAP DRIFT`, and the strip degrades correctly through each level as faults clear.

### 6.1a W19 Log line

A single-line rolling log beneath the status strip. Format:

```
log[04:52:26] ERR   toggle poller stopped — switch states will go stale in 30s        #47
```

`log[` and `]` dim · timestamp in the number colour · level colour-coded (`INFO` key, `OK` green, `WARN` amber, `ERR` red) · message dim · sequence number faint, right-aligned.

**What must be logged:** every user action that changes state (toggle, workspace switch, perf mode, wrap, energy reset, transport), plus automatic events — threshold crossings, poller up/down, sensor drift detected/cleared.

**Log threshold crossings once, not every update.** Use `IfConditionMode=1` so the condition fires on change rather than continuously; otherwise a hot CPU floods the log every second.

**Two rules that make the log honest:**
- Toggling an item marked `△` (unofficial API) logs `WARN`, noting it may fail silently.
- Toggling while the poller is down logs that the resulting state is unconfirmed.

**Implementation — this one needs Lua.** Rainmeter has no arrays and variables are single-line, so a ring buffer is not expressible in pure INI. Use `Measure=Script` with a small Lua module holding the buffer and exposing the most recent entry (and the last N for the `ALERTS` panel, §6.2). Lua ships with Rainmeter, so this adds no third-party dependency. The alternative — N shift-register variables (`Log1…Log8`) shuffled with chained `!SetVariable` — works but fires a large number of bangs per event and is harder to maintain; prefer Lua.

### 6.2 W1 FUNCTIONS / ALERTS

`FUNCTIONS` opens a context menu (or toggles a hidden panel group) containing the four actions displaced from the old bottom rail: **AUTO LOAD · ROTATE DISPLAY · RELOAD SHELL · LOCK SESSION**.

`ALERTS` shows the last N entries from the same Lua ring buffer that feeds W19 (§6.1a) — sensor drift, failed toggles, EC conflict, threshold crossings. One buffer, two views: W19 shows the newest entry inline, `ALERTS` expands the history.

Both header buttons are 29px tall — **secondary controls** under the tiered rule (constraint 8), which is correct for menu-openers. Do not raise them to 44px: the header budget is a fixed 42px and there is no room. If they feel too small in use, widen them horizontally rather than taller.

### 6.3 W6 banner — flagged as redundant

The active workspace already appears in W1's mode line, W2's profile row, W12a, and W12b. W6 is a fifth repetition. It is retained because it's load-bearing *aesthetically* (it's the `✳✳ REMOTE MODE ✳✳` element from the source photo). Do not add a sixth workspace indicator. If a better use emerges, candidates are now-playing (pairs with W5) or the most recent alert.

---

## 7. Launcher data model

Rainmeter has **no loops**. Standard workaround: a fixed maximum number of meters, dynamically populated.

Six slots. Data-driven from a folder of shortcuts per workspace, so the user edits `@Resources\Workspaces\WS3\` in Explorer and never touches skin code.

```ini
[mBayPath]
Measure=Plugin
Plugin=FileView
Path=#@#Workspaces\WS#Workspace#
ShowDotDot=0
ShowFolder=0
HideExtensions=1
Count=6
FinishAction=[!UpdateMeasureGroup Bay][!UpdateMeterGroup Bay][!Redraw]
DynamicVariables=1

[mBay1Name]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FileName
Index=1
Group=Bay
IfMatch=^$
IfMatchAction=[!SetOption Slot1 MeterStyle sSlotEmpty][!SetOption Slot1Name Text "— EMPTY —"]
DynamicVariables=1

[mBay1Path]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FilePath
Index=1
Group=Bay
```

Repeat for indices 1–6. Each slot meter shows: index (`01`), name (16px), and launch target (9px dim). Empty slots switch to a dashed-border style and become non-interactive.

Slot tap: `LeftMouseUpAction=["[mBay1Path]"]` with `DynamicVariables=1`.

Alternatives if FileView proves awkward: `Quote` plugin reading a manifest file, `WebParser` with `Url=file://...`, or Lua via `Measure=Script`. FileView is the least-code option for the folder-of-shortcuts model.

### 7.1 Launching

```ini
; plain exe
LeftMouseUpAction=["C:\Program Files\App\app.exe"]
; with arguments
LeftMouseUpAction=["C:\path\app.exe" "-P" "dev"]
; UWP / Store app — find IDs via: explorer shell:AppsFolder
LeftMouseUpAction=["shell:AppsFolder\<PackageFamilyName>!App"]
; elevated (no native Rainmeter flag)
LeftMouseUpAction=["powershell" "Start-Process 'app.exe' -Verb RunAs"]
```

For anything needing a working directory or output capture, use the **RunCommand** plugin rather than `!Execute`.

---

## 8. Workspace state machine

Five workspaces. Each has an **id**, **code**, **title**, **mode** (`apps` | `editor`), a shortcuts folder, and a notes file.

Reference config: WS1 DEV, WS2 MEDIA, WS3 GAME, **WS4 WRITE (mode=editor)**, WS5 DIAG.

### 8.1 Persistence + instant switch

Combine two mechanisms — this is the only approach that survives a Rainmeter restart *and* switches without a refresh:

```ini
LeftMouseUpAction=[
  !SetVariable Workspace "3"
  ][!WriteKeyValue Variables Workspace "3" "#@#Variables.inc"
  ][!HideMeterGroup WSAll][!ShowMeterGroup WS3
  ][!UpdateMeasure mBayPath][!UpdateMeter *][!Redraw]
```

- `!SetVariable` — live, takes effect next update cycle. Consumers need `DynamicVariables=1`.
- `!WriteKeyValue` — persists to disk; alone it would require a refresh, which is why both are used.
- Group show/hide — instant, no refresh.

On skin load, restore from the persisted variable with an `IfEqualValue` measure that fires the matching `!ShowMeterGroup`.

### 8.2 Mode switching — critical

`Mode` decides whether **W11** or **W18** is visible. Per constraint 3 they are **both exactly 230px**. Verify this with a measurement, not by eye — if they differ, every widget below them moves when switching workspace.

```ini
[mMode]
Measure=String
String=#WSMode#
IfMatch=editor
IfMatchAction=[!HideMeter BayFrame][!HideMeterGroup Bay][!ShowMeterGroup Editor]
IfNotMatchAction=[!HideMeterGroup Editor][!ShowMeter BayFrame][!ShowMeterGroup Bay]
DynamicVariables=1
```

W12a shows `EDITOR` instead of an app count for editor-mode workspaces.

---

## 9. Toggles (W8)

Five rows, tight checkbox styling: 12px checkbox, 5px gaps, 11px label, no dividers. Filled checkbox = on. A `△` glyph in `#Warn#` marks mechanisms that rely on unofficial APIs.

| Row | Mechanism | Admin | Fragile |
|---|---|---|---|
| WI-FI | WinRT `Windows.Devices.Radios` | no | no |
| BLUETOOTH | WinRT `Windows.Devices.Radios` | no | no |
| MUTE | `nircmd mutesysvolume 2` | no | no |
| NIGHT LIGHT | CloudStore registry blob | no | **△** |
| ROTATION LOCK | `AutoRotation\Enable` registry | no | **△** |

### 9.1 Accepted tradeoff

At 16px the toggle rows are the smallest targets in the suite and fall well below the 40–48px Windows touch guideline. **This is deliberate** — chosen for visual fidelity to the source panel. Do not enlarge them. Everything else in the suite is ≥26px.

### 9.2 Radios — the correct mechanism

Use the WinRT `Windows.Devices.Radios` namespace, which is what the Action Center toggles use. Two things that will otherwise waste hours:

- **Run under Windows PowerShell 5.1, not pwsh 7.** The WinRT interop calls fail in pwsh; community scripts ship a separate module specifically because of this.
- **The obvious approaches are wrong on Windows 11.** `Disable-NetAdapter` needs admin and disables the adapter at hardware level (the WLAN button disappears) rather than toggling the radio. The `radioEnable` / `SoftwareRadioOff` registry keywords were **removed in Windows 11**. `netsh interface set interface` requires elevation.

### 9.3 Night light and rotation lock

Both are registry manipulations with no supported API. Night light lives in a `CloudStore` binary blob (`bluelightreductionstate`) requiring byte-level edits; it can break with Windows updates. Implement, mark `△`, and fail visibly rather than silently.

### 9.4 State polling — do not skip this

A toggle that misreports its state is worse than a read-only indicator.

**Do not poll by spawning PowerShell per row per update.** One background script (`sensors.ps1`) runs on a timer, queries all five states, and writes a single small file:

```
wifi=1
bluetooth=0
mute=0
nightlight=1
rotationlock=0
ts=1753564125
```

Rainmeter reads it with cheap measures. Include the timestamp so W3 can report `TOGGLE POLLER DOWN` when it goes stale (§6.1). **Interval: 5s.** W3 flags stale at >30s (6 missed cycles). §14's "within one poll interval" therefore means within 5s.

---

## 10. Text widgets

### 10.1 W17 Notes and W18 Editor are the same machinery

Same read path, same write path, same dialogs — different size and different file. **Build one implementation and instantiate it twice.** W17 is per-workspace (`notes\ws{N}-{code}.md`); W18 opens arbitrary files.

### 10.2 Read vs write are separate components

- **Display:** `Quote` plugin (`PathName=`, `Separator=`) or Lua reads the file; content renders into String meters.
- **Edit:** InputTextX overlays a real input box.

Stock `InputText` **cannot do multiline** — a limitation open since 2016, rooted in the fact that Rainmeter variable values must occupy a single line. Community workarounds stack multiple single-line inputs and break selection and copy-paste. **InputTextX** adds multiline with vertical scroll and can load fonts from `@Resources\Fonts`, so its text can match the theme.

Consequences:
- `SAVE` must write the file **and** trigger a re-read, since display and edit are different components.
- **Dirty state must be tracked manually** — Rainmeter has no document model. Set a variable on edit, clear on save. Show `● UNSAVED` in `#Warn#` vs `SAVED` in `#AmberDim#`.
- **Unverified:** whether InputTextX's box wraps identically to the display meters. If widths or fonts differ, text will reflow when entering or leaving edit mode. **Test this early** — it determines whether W18 is viable.
- If InputTextX is unavailable, degrade to append-only single-line entry via stock `InputText`. Do not silently drop the widget.

### 10.3 File dialogs

Rainmeter has no file dialog. `OPEN…` and `SAVE AS…` shell out to PowerShell:

```powershell
Add-Type -AssemblyName System.Windows.Forms
$d = New-Object System.Windows.Forms.OpenFileDialog
$d.Filter = "Text/Markdown|*.md;*.txt|All files|*.*"
if ($d.ShowDialog() -eq 'OK') { $d.FileName }
```

Capture stdout via RunCommand, then `!SetVariable` + `!WriteKeyValue` the returned path.

### 10.4 Wrapping

```ini
[EdLine3]
Meter=String
MeasureName=mQuoteLine3
X=31
Y=2R
W=#EdTextW#
H=#EdLineH#
ClipString=1
DynamicVariables=1
```

- **`ClipString=1`, fixed `W` and `H`.** `ClipString=2` grows the meter and breaks the 230px constraint.
- Wrapping occurs **only on word boundaries**; a single word longer than `W` clips that line rather than breaking. Long paths and URLs will truncate — expected, not a bug.
- `DynamicVariables=1` is **required** on meters bound to Quote/WebParser measures, whose initial value is empty.
- The `WRAP` chip toggles `ClipString` between `1` and `0` via `!SetOption`.
- **The container is a fixed clip region, not a flowing box.** The editor body is pinned to `#EdBodyH#` (129px). Individual line meters flow *inside* it via relative positioning (`Y=2R`), but the region's own height never changes — this is how the fixed `PaneHeight` (constraint 3) and per-line flow coexist. Lines past the ~8 that fit at 12px/1.2 line-height are clipped at the boundary; a scroll-offset variable re-renders which slice of the file is shown. Rainmeter has no scrollbar. **Verify the last visible line is never half-clipped** — pick `EdBodyH` as an exact multiple of the line pitch.

---

## 11. W16 Performance mode

Three-state selector (SILENT / BALANCED / TURBO), active state inverse-filled — mirroring how `STOP` reads as active in the source photograph.

**There is no CLI for this.** Armoury Crate has none, and G-Helper's author has stated command-line mode switching is impossible by design because the app must stay resident to react to system events. The documented automation path is **hotkeys**: `Ctrl+Shift+F5` cycles performance modes forward.

So: W16 taps run an AutoHotkey script that sends `^+F5`. Rainmeter cannot send keystrokes itself.

Implications to surface in the UI:
- G-Helper must be tray-resident or the button silently does nothing.
- Cycling is **forward-only**, so reaching a specific mode may need multiple sends. Track the assumed state in a variable and send the right number of presses.
- The displayed state is inferred, not read back. If it can drift, prefer showing the last commanded mode over a confident wrong reading.

---

## 12. W5 Transport

`RUN` / `JOG` / `STOP` mapped to media transport via nircmd `sendkeypress`: play/pause, next track, stop.

State indication follows the source photo: `RUN` fills while playing, `STOP` fills when halted. Track state in a variable — media state is not reliably readable without an audio plugin.

---

## 13. Build order

### Milestone A0 — architecture & one proven slice (≈1 day)

Do not build breadth until the pattern is proven once.

1. **Decide the DPI strategy (§1.1)** on the actual panel — it fixes the coordinate system everything else uses. This gates all positions, so it is step one, not a later discovery.
2. `Variables.inc` with all tokens from §3, including the child-skin rectangle vars (§1.2).
3. `Tools\Discover.ini` — HWiNFO index discovery (§5.2).
4. **Prove the hybrid split (§1.2):** the main `pipOS.ini` frame with W1 + one telemetry widget (W9/10) reading one real HWiNFO value, plus `Notes.ini` as a child skin landing in its reserved rectangle. Confirm the child sits exactly in the hole and refreshing it does not reload the main skin.
5. Verify the pixel budget (§14) on this slice.

### Milestone A1 — full static shell (≈1 day)

6. Remaining light widgets into `pipOS.ini` via `@Include`: W2, W3, W4, W6, W11 (6 fixed slots), W12a, W12b, plus placeholders for W5/W8/W13/W14/W16.
7. Re-verify the full pixel budget (§14). Do not proceed until it passes.
8. Workspace switching with persistence (§8.1) — LED rail and rail buttons responding; mode switch swapping W11/W18 rectangles.

### Milestone B — live data and control (≈2–3 days)

9. HWiNFO wiring for W9/10, W13, W14 with label-verification warnings.
10. `sensors.ps1` poller + W8 toggles (§9).
11. W16 via AHK (§11); W5 via nircmd (§12).
12. FileView launcher data model (§7).
13. W3 derived status conditions **with severity fill colour** (§6.1); W19 log ring buffer in Lua (§6.1a); W1 FUNCTIONS + ALERTS reading that same buffer (§6.2).

### Milestone C — text widgets (open-ended)

14. **Spike InputTextX first** — verify multiline and wrap parity (§10.2) before building anything on it.
15. W17 Notes, then W18 Editor from the same implementation.
16. File dialogs (§10.3).
18. Scanline overlay; `.rmskin` packaging with Layout.

---

### Milestone D — TUI variant (after A–C are green)

Only start once the Pixel variant is complete and the shared logic layer is proven.

16. **Factor the logic out first (§17.6).** Move every `Measure=` out of the Pixel skin into `@Resources\logic\*.inc`; re-include them; confirm Pixel still passes §14 unchanged. This step must not change behaviour — if it does, the boundary is wrong.
17. `TUI\pipOS-tui.ini` — the 132×40 grid, one meter per row with **explicit cell positioning** (§17.3), including the same `logic\` files.
18. Port widgets to grid composition; verify uniform row width (§14 TUI checks).
19. Theme token files in `@Resources\Themes\` (§17.5); confirm both variants read them.

## 14. Verification checklist

Run before declaring any milestone done.

- [ ] In each column the lowest widget satisfies Y+H ≤ 607px (constraint 2)
- [ ] Child skins (Notes/Editor) land exactly in their reserved rectangles; refreshing one does not reload the main skin
- [ ] Nothing extends above the header or below the workspace rail
- [ ] W11 height == W18 height, measured, exactly 230px
- [ ] Switching to the editor workspace moves **nothing** except that one box
- [ ] Header content fits 42px (watch the `®` superscript — it overflowed its line box in an earlier revision)
- [ ] `WRAP` on/off does not change the editor's outer height
- [ ] No skin draggable; every tap uses `LeftMouseUpAction`
- [ ] All five toggles reflect real state within 5s (one poll interval)
- [ ] Killing the poller surfaces a visible fault in W3, not stale values
- [ ] With sensor drift, poller-stale, and thermal all true at once, W3 shows **only** SENSOR MAP DRIFT, and degrades correctly as each clears
- [ ] W3's fill colour changes with severity (green / amber / red), not just its text
- [ ] The poller heartbeat counter in W3 visibly increments and resets
- [ ] A sustained hot CPU logs the threshold crossing **once**, not every update
- [ ] Toggling a `△` item logs a WARN about the unofficial mechanism
- [ ] Killing HWiNFO shows `—`, not zeros
- [ ] W3 shows exactly one status string (single Calc-driven priority, never two conditions firing)
- [ ] Editor: bottom visible line is fully shown, never half-clipped (EdBodyH is a whole multiple of line pitch)
- [ ] Every colour and dimension traces to `Variables.inc`
- [ ] *(TUI variant only)* every row renders at identical pixel width — measure in the rendered grid, not a detached element (§17.3)
- [ ] *(TUI variant only)* a given column index sits at the same x on every row

---

## 15. Known dead ends

Do not spend time on these.

1. **HWiNFO Rainmeter plugin** — unmaintained; Shared Memory is 12-hour limited in the free build.
2. **`ClipString=2` in W17/W18** — grows the meter, breaks fixed geometry.
3. **Stock `InputText` for multiline** — structurally impossible; variables are single-line.
4. **`Disable-NetAdapter` / `netsh` / `radioEnable` registry for Wi-Fi** — admin-required, wrong semantics, or removed in Windows 11.
5. **pwsh 7 for WinRT radio calls** — fails; use PowerShell 5.1.
6. **G-Helper or Armoury Crate CLI mode switching** — does not exist.
7. **Rainmeter sending keystrokes** — not supported; shell out to AHK.
8. **Embedding a live terminal or editor window in a skin** — Rainmeter is not a window host. Docking Windows Terminal into a box fails on letter-spacing (no such setting), Win11 rounded corners, drop shadow, and z-order. If an interactive terminal is wanted, summon it as a **full-screen or large overlay**, never inset in a framed rectangle.
9. **Rainmeter blend modes / native blur** — do not exist; bake into PNG alpha.
10. **Loops in Rainmeter** — none. Fixed meter count, dynamically populated.
11. **Trusting a monospace font to hold a character grid** — box-drawing and block glyphs are commonly substituted from a fallback font with different advance widths, drifting rows by multiple cells. Position cells explicitly (§17.3).
12. **Splitting the layout into many independent skins** — they can't see each other, so the 607px budget and W11/W18 parity become unverifiable and the overlap bug returns. One main skin holds the frame; only the self-refreshing text panes are children (§1.2).

---

## 16. Requires on-device discovery

These cannot be specified in advance and must be resolved on the actual machine:

1. **Every HWiNFO index number** (§5.2) — and the exact sensor label strings on this GZ302EA. Fan labels, the dedicated/dynamic VRAM split, and battery label wording are inferred from Strix Halo generally, not confirmed on this unit. No published full sensor dump exists for this model.
2. **Whether HWiNFO exposes ASUS EC fan data** here, and whether G-Helper contends with it (§5.4).
3. **InputTextX wrap parity** (§10.2) — gates W18.
4. **Whether 200% scaling softens the amber text unacceptably** (§1.1) — resolve at **Milestone A0 step 1**, before any coordinates are fixed.
5. **UWP identifiers** for any Store apps placed in the launch bay (`explorer shell:AppsFolder`).

---

## 17. Visual variants — pixel and TUI

**Both variants ship.** They are two front-ends over one back-end: same nineteen widgets, same workspace state machine, same sensor plumbing, same persisted state. Only the meter definitions differ. The user switches by unloading one and loading the other; because all state lives in `@Resources`, the active workspace, toggle states, notes, and discovered sensor indices carry across unchanged.

This is only affordable because the logic is factored out **once** (§17.6). If the two variants end up with duplicated measures, the build has gone wrong — a sensor index or a workspace bang would then need fixing in two places.

### 17.1 The two variants

| | **Pixel** (IMAX) | **TUI** (console) |
|---|---|---|
| Reference | `pipOS-wireframe-v21.html` | `pipOS-console-live.html` |
| Frames | `Meter=Shape` rectangles | box-drawing characters on a char grid |
| Bars | Shape rectangles | `█`/`░` cells |
| Grid | free pixel positioning, 1280×800 | fixed 132×40 character cells |
| Skin architecture | **hybrid** — main skin + Notes/Editor child skins (§1.2) | **monolithic** — one skin, see 17.1a |
| Colour | amber phosphor, brightness tiers | semantic roles (§17.4) |
| Risk | low — proven | font metrics, see 17.3 |

Build **Pixel first**. It is the safe default, everything in §1–§16 targets it, and it proves the shared logic layer works before the TUI's extra constraints are added on top.

### 17.1a Why the TUI is monolithic

The pixel variant uses child skins for Notes and Editor so a save doesn't reload telemetry (§1.2). **The TUI cannot do this.** A child skin is a separate window with its own coordinate space; landing it inside a character grid would require its cell origin and cell size to match the parent's exactly, and any drift breaks the grid the whole aesthetic depends on. The TUI therefore renders as one skin and redraws the whole grid on update — which is what the prototype does and is cheap enough in practice.

Consequence: `Notes.ini` and `Editor.ini` are **pixel-variant only**. In the TUI their content is composed inline.

### 17.2 TUI geometry

132 columns × 40 rows. At 1248 logical px of usable width that is a **9.45px cell**, ~15.8px font, 18.6px line height — filling 99.8% of the screen width. Layout: notes full width (rows 2–10), session (11–13), status (14), log (15), bay-or-editor left / telemetry right (16–29), banner (31), battery+perf (32–35), transport (36), LED + workspace tabs (37–38).

### 17.3 The TUI's one hard rule

**Do not rely on the font to hold the grid.** Box-drawing (`─│┌┐├┤`) and block (`█░`) glyphs are frequently absent from a chosen monospace font and get substituted from a fallback with *different advance widths*. Measured in the prototype: rows dense in box-drawing rendered **21px wider** than plain-ASCII rows — more than two full cells of drift, enough to break every vertical border.

Two mitigations, in order of preference:

1. **Position every cell explicitly.** One String meter per row with fixed `W`, or per-cell positioning. Glyph metrics then cannot affect layout. This is what the prototype does (fixed-width cells), and it reduced 40 rows spanning 738–759px to a single uniform 757.22px.
2. **Bundle a font verified to contain every glyph used**, and test all of them on-device before building on it. Weaker, because a future font change silently reintroduces the bug.

A naive check is not enough: measuring glyph widths in a detached element gives false confidence because it may not inherit the real font stack. Measure inside the actual rendered grid.

### 17.4 Semantic colour (TUI)

The TUI variant colours by *meaning*, not decoration. This is the main reason it reads as a console rather than a styled panel.

| Role | Applies to |
|---|---|
| `key` | field names — `host=`, `perf=`, `cpu`, `[F1]` |
| `str` | values, app names, workspace codes |
| `num` | all numbers — temps, watts, percentages, timestamps |
| `path` | file paths and executables |
| `kw` | box captions, banner |
| `ok` / `warn` / `err` | state and severity, everywhere |
| `dim` / `faint` | punctuation, frames, line numbers |

Two consequences worth enforcing: **load bars colour by threshold** (green <60%, amber <85%, red ≥85%) so a hot subsystem is visible without reading numbers; and **notes/editor get markdown highlighting** — `#` headings, `` `code` ``, `>` quotes, `!` alerts, and auto-detected filenames.

### 17.5 Theme tokens

Both variants are fully themed from one token set. Adding a theme means defining these and nothing else:

```
bg  bezel  fg  dim  faint  frame        ; structure
key str num path kw                      ; semantic roles
ok  warn  err                            ; severity
sel                                      ; selection
```

In Rainmeter these belong in `@Resources\Variables.inc` (constraint 9 already requires it). A theme switch is then a matter of `@Include`-ing a different token file and refreshing.

**Rate contrast on information-bearing roles only** (`fg`, `key`, `str`, `num`, `ok`, `warn`, `err`) — not on `frame` or `faint`, which are deliberately dim. Rating the frame makes perfectly legible schemes appear to fail.

Prototyped schemes and their measured worst-case WCAG ratio: **MONO WHITE** 11.5 AAA · **HC BLACK / HC GREEN / HC CYAN** 7.1 AAA · **TOKYO NIGHT / CATPPUCCIN** ~7.2 AAA · **HC NAVY** 6.8 · **AMBER HYBRID / GREEN HYBRID** 6.6 · **HC AMBER** 6.3 · **NIGHT RED** 6.1 · **HC WHITE** 5.9.

**AMBER HYBRID** is the recommended default if the IMAX aesthetic matters: it keeps amber phosphor on near-black for structure and text, and introduces green/amber/red *only* for severity — resolving the tension between the source aesthetic and at-a-glance state reading. For maximum robustness against the 200% DPI softening (§16 item 4), **HC AMBER** or **MONO WHITE** are the safest.

### 17.6 Shared logic layer — the rule that makes two variants affordable

**Measures are shared. Meters are not.** Everything that computes state lives in `@Resources\logic\` and is `@Include`d by both variants. Everything that draws lives in the variant's own folder.

```
Skins\pipOS\
  @Resources\
    Variables.inc        ; tokens, geometry for BOTH, persisted state
    Themes\              ; one .inc per colour scheme (§17.5)
      amber-hybrid.inc  hc-amber.inc  tokyo-night.inc  mono-white.inc …
    Scripts\
      sensors.ps1  radio.ps1  dialog.ps1  log.lua
    Workspaces\          ; WS1..WS5 shortcut folders + notes\
    logic\               ; SHARED — measures only, ZERO meters
      sensors.inc        ; HWiNFO registry + UsageMonitor measures (§5)
      workspace.inc      ; active workspace, mode, persistence bangs (§8)
      toggles.inc        ; poller file read, 5 toggle states (§9)
      status.inc         ; W3 priority Calc + W19 log hooks (§6.1, §6.1a)
      power.inc          ; battery, energy accumulator, perf mode (§11)
  Pixel\
    pipOS.ini            ; ACTIVATED — Shape meters, includes ..\@Resources\logic\*
    includes\            ; Session.inc Bay.inc Banner.inc Telemetry.inc …
  TUI\
    pipOS-tui.ini        ; ACTIVATED — String-grid meters, same logic includes
    includes\
  Notes\Notes.ini        ; ACTIVATED (pixel variant only — see 17.1a)
  Editor\Editor.ini      ; ACTIVATED (pixel variant only)
  Overlay\Scanlines.ini
  Tools\Discover.ini
```

**The test for whether this is right:** changing a HWiNFO index, adding a workspace, or fixing the status priority should require editing exactly one file under `logic\`, and both variants should pick it up. If a change has to be made twice, the boundary is in the wrong place.

**What belongs in `logic\`** — anything with `Measure=`: registry reads, UsageMonitor, Calc, Script, the workspace `IfMatch` chain, the poller file parse.
**What belongs in a variant** — anything with `Meter=`, all `X`/`Y`/`W`/`H`, all `MeterStyle`, and the action bangs attached to meters.

**One caveat.** Shared measure *names* become an API: a meter in either variant refers to `[mCPULoad]`, so renaming a measure breaks both. Treat names in `logic\` as fixed once written, and prefix them (`m…`) so a variant's local measures can't collide.

**Geometry stays separate.** `Variables.inc` holds both sets — pixel uses `PaneHeight`, `ColRightW`, `BudgetY`; the TUI uses `GridCols=132`, `GridRows=40`, `CellW`, `CellH`. Do not try to derive one from the other; they are different coordinate systems that happen to describe the same layout.

### 17.7 Switching variants

Both are activated configs. Switching = unload one, load the other; a Rainmeter Layout for each makes it one click. State survives because it lives in `@Resources`: active workspace and mode (`Variables.inc`), toggle states (poller file), notes and manuscripts (`Workspaces\notes\`), discovered sensor indices (`Variables.inc`).

Do **not** attempt to switch variants at runtime inside one skin by hiding meter groups. The two use incompatible coordinate systems and meter types; the result is two full layouts loaded at once, double the measures, and a group-visibility bug surface for no benefit.
