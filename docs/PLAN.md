# IMAX Control Panel — Rainmeter Theme

A Rainmeter desktop theme that reskins a Windows machine as an **IMAX GT projector
control panel** — the amber-phosphor touchscreen from the projection booth — while
functioning as a real, touch-driven system dashboard and app launcher.

Target machine: **ASUS ROG Flow Z13 (2025)**, run **full-screen** on its
**2560×1600, 16:10 touchscreen**. *(Resolution to be confirmed.)*

---

## 1. What is Rainmeter? (quick primer)

**Rainmeter** is a free, open-source Windows desktop-customization tool. It draws
"skins" — small always-on-top panels — directly onto your desktop that can show
live system data and respond to clicks/taps.

Key concepts we'll use:

| Term | What it is |
|---|---|
| **Skin** | A single panel, defined by one `.ini` text file. Ours is `IMAX.ini`. |
| **Config** | The folder holding a skin and its assets (our `IMAX/` folder). |
| **Measure** | A data source — CPU %, free RAM, uptime, clock, network bytes, etc. Measures *get* values. |
| **Meter** | A visible element — text, rectangle, image, button. Meters *draw* things, often fed by a measure. |
| **Plugin** | Add-on for data Rainmeter can't read natively. We need one (**HWiNFO**) only for GPU load & temperatures. |
| **`@Resources`** | Per-config asset folder for fonts, images, and include files. Fonts dropped in `@Resources/Fonts` load automatically. |
| **Include (`.inc`)** | A text file of variables pulled into the skin. This is how we make the theme configurable without editing skin code. |
| **`.rmskin`** | A one-click installer package. We'll produce one at the end so install is drag-and-drop. |

**Important constraints:**
- Rainmeter is **Windows-only**. It's authored here on Linux, so **you test on the
  Z13** and send screenshots; the dev loop is *edit → you refresh → feedback → fix*.
- Skins are drawn in fixed pixels. To fill the Z13 edge-to-edge regardless of
  Windows' display-scaling setting (the Z13 usually ships at 200%), the whole layout
  is driven by one **`Scale`** variable we tune once during setup.
- **Touch** registers as normal mouse clicks, so logic is unchanged — it only means
  buttons must be **large and well-spaced** for fingers.

---

## 2. The vision

Reproduce the look of the reference photo — pure black background, warm amber vector
text and rounded-rectangle boxes, blocky terminal font, checkbox status indicators,
`** REMOTE MODE **` banner — but wire every field to real data and make the buttons
launch real programs. It should read as the IMAX panel at a glance and work as a
control surface up close.

**Aesthetic details:**
- **Font:** VT323 (bundled) — a blocky retro-terminal font matching the panel.
- **Phosphor glow:** a soft bloom around text/lines.
- **CRT scanlines:** a faint horizontal-line overlay (toggleable).
- **Palette:** amber by default, with green and ice/cyan alternates.

---

## 3. Decisions locked so far

| Decision | Choice |
|---|---|
| Purpose | **Functional** system monitor (real data behind IMAX-styled fields) |
| Coverage | **Full-screen** dashboard on the Z13 |
| Metrics tracked | CPU, RAM, Disk, Network, Uptime, Clock/Date, **GPU + temps** (GPU/temps via HWiNFO) |
| Buttons | Launch **real, non-destructive** tools |
| Workspaces | 4 pages: **Gaming · Software Dev · Productivity · Media/Creative** |
| Mode switch | **Change Mode** cycles the workspace pages |
| Phosphor color | **Independent toggle** (amber/green/ice), *not* tied to the mode |
| Launch slots | Configurable **per workspace** (count *and* grid layout can differ) |

---

## 4. Architecture: anchor panels vs. the variable panel

The single most important design idea:

> **Most of the panel is a fixed "anchor" that never changes between workspaces.
> Only the PROGRAMS launch region changes.**

### Anchor panels (identical in every workspace)
These are the IMAX chrome and the performance monitors. They stay put no matter which
mode you're in:

- **Header** — `IMAX®` logo + `SYSTEM LOCAL — <MODE> MODE` title
- **SYSTEM INFO** box — hostname / OS / user *(the old `SHOW INFORMATION` / TRAILER / TITLE box)*
- **STATUS** band — `ONLINE / NOMINAL`, reflecting live CPU state
- **Uptime / Date / Time** line *(the old `SHOW TIME` line)*
- **Performance stack (right column):**
  - `LAMP VALUES` → **CPU % + MEM %**
  - `THERMAL` → **GPU °C + CPU °C** (HWiNFO)
  - `FRAME COUNT` → **network received** counter (odometer feel)
  - **Indicator checkboxes** → live: network link, disk healthy, RAM healthy, power, spare
  - `RESET FRAME COUNT` → reset the network counter
- **`** REMOTE MODE **` banner**
- **Bottom control bar** — Change Mode, workspace tabs, Phosphor/Scan toggles, Exit

### The variable panel (per-workspace)
Only the **PROGRAMS** launch region changes between workspaces. Each workspace defines:
- its **title** (shown in the header),
- how many buttons it has (**count**),
- how they're arranged (**columns** → auto-flow grid),
- and each button's **label + command**.

So Gaming might be 6 buttons in a 3×2 grid, while Dev is 4 large buttons in a 2×2 —
the anchors around them are pixel-for-pixel the same.

---

## 5. How configuration works (easy to edit)

Everything user-tunable lives in plain-text `.inc` files under `IMAX/@Resources/`.
**You never edit the skin code to change your apps.**

```
IMAX/
├─ IMAX.ini                     ← the skin (you don't touch this)
└─ @Resources/
   ├─ Settings.inc              ← active workspace, active color, scanlines on/off
   ├─ Fonts/VT323-Regular.ttf   ← bundled terminal font
   ├─ Images/Scanlines.png      ← CRT overlay
   ├─ Themes/
   │   ├─ Theme-Amber.inc       ← color palettes
   │   ├─ Theme-Green.inc
   │   └─ Theme-Ice.inc
   └─ Workspaces/
       ├─ Gaming.inc            ← YOUR apps + labels per mode
       ├─ Dev.inc
       ├─ Productivity.inc
       └─ Media.inc
```

A workspace file looks like this — add/remove `Btn` lines to change the count, change
`WS_Cols` to change the layout:

```ini
[Variables]
WS_Title=GAMING
WS_Cols=3            ; grid columns
WS_Count=6           ; how many buttons are active

Btn1_Label=STEAM
Btn1_Cmd="C:\Program Files (x86)\Steam\steam.exe"

Btn2_Label=ARMOURY CRATE
Btn2_Cmd="C:\...\ArmouryCrate.exe"

; ...up to a fixed maximum (e.g. 12) of slots

NextWorkspace=Dev    ; wiring for the Change Mode cycle
PrevWorkspace=Media
```

**Why this is robust:** every workspace file uses the *same* variable names
(`Btn1_Label`, `WS_Cols`, …). The skin has a fixed set of button meters that read
those names and lay themselves out. **Change Mode** just rewrites the active workspace
in `Settings.inc` and refreshes — the same button meters repaint from the new file.
No loops, no fragile tricks.

---

## 6. Field mapping (IMAX element → real function)

| Panel element | Becomes |
|---|---|
| `IMAX®` + `SHOW LOCAL – AUTO MODE` | Logo kept · title → `SYSTEM LOCAL – <MODE> MODE` |
| `SHOW INFORMATION` (TRAILER/TITLE) | `SYSTEM INFO` — hostname, OS, user |
| `STATUS: AUTO MODE / PRESETS COMPLETED` | Live status band (`ONLINE / NOMINAL`) |
| `SHOW TIME · DATE · TIME` | Uptime · live date · live clock |
| 5 checkboxes (Spare…SYSTEM READY) | Live indicators: net link, disk, RAM, power, spare |
| `LAMP VALUES 41.0V 154A` | **CPU % + MEM %** |
| `THERMAL` *(new)* | **GPU °C + CPU °C** (HWiNFO) |
| `FRAME COUNT 255315` | **Network received** counter |
| `RESET FRAME COUNT` | Reset the network counter |
| `RUN / JOG / STOP` + grid | **Per-workspace program launchers** (the variable panel) |
| `Functions / Alarms` | Phosphor color toggle · Scanline toggle *(placement TBD)* |
| `Change Mode / MANUAL` | Cycle workspace pages (Gaming→Dev→Prod→Media) |
| `AUTO LOAD` | Open Startup folder |
| `Change Show` | Refresh skin |
| `Exit Show` | Unload skin |

---

## 7. Default app sets (edit freely)

Starting placeholders — swap in your real paths in the workspace files.

| # | Gaming | Software Dev | Productivity | Media / Creative |
|---|---|---|---|---|
| 1 | Steam | VS Code | Outlook | Spotify |
| 2 | Armoury Crate | Windows Terminal | Word | Netflix (browser) |
| 3 | Discord | GitHub Desktop | Excel | OBS Studio |
| 4 | Xbox / Game Bar | Docker Desktop | PowerPoint | Photoshop |
| 5 | OBS Studio | Chrome/Edge | Teams | Premiere / Clipchamp |
| 6 | Spotify | Postman | OneNote | VLC |
| 7 | — | Notion/Obsidian | Calendar | DaVinci Resolve |
| 8 | — | File Explorer | Slack | YouTube (browser) |

---

## 8. Roadmap & status

- **Phase 0 — Scope** ✅ *done* — goals & decisions locked (this doc).
- **Phase 1 — Look** 🔄 *in progress* — static PNG mockups of the layout, amber +
  green shown, full-screen version rendered. Refining proportions back toward the
  original photo, with the anchor/variable split.
- **Phase 2 — Data** ⬜ — wire live measures (CPU, RAM, disk, net, uptime, clock;
  GPU/temps via HWiNFO with graceful `N/A` fallback).
- **Phase 3 — Interactivity** ⬜ — workspace state machine (Change Mode + tabs),
  configurable launch grid, phosphor + scanline toggles, all button actions.
- **Phase 4 — Package & polish** ⬜ — `.rmskin` installer, README, `Scale` tuning
  guide for the Z13, glow/CRT tuning.

**Done so far:** repo scaffolded; VT323 font bundled; three phosphor palettes;
scanline overlay generated; amber/green and full-screen layout mockups in `docs/`.

---

## 9. Open questions to refine

1. **Resolution** — confirm the Z13 panel is 2560×1600.
2. **Layout fidelity** — how close to the original photo's proportions vs. the
   roomier full-screen arrangement? (The anchor/variable split works either way.)
3. **Toggle placement** — do Phosphor/Scan live on the `Functions`/`Alarms` buttons
   (keeps original labels but changes their meaning), or as separate small controls?
4. **Max launch slots** — cap the per-workspace button count at 12? 16?
5. **App lists** — start from the defaults above and you edit, or hand me your exact
   apps + paths to bake in?
6. **GPU/temps** — OK to depend on HWiNFO (free) for those two readouts, with `N/A`
   shown if it isn't running?
