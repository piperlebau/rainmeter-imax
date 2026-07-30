# pipOS component vocabulary

Each entry gives the intent, the Pixel construction, and the TUI construction.
Reuse before inventing.

---

## Caption-break box
The signature frame. A hairline rectangle whose label sits **on** the top border, with the
border interrupted behind it.

- **Pixel:** `Meter=Shape` rectangle, `StrokeWidth 1`, `frame` colour. Label is a separate
  String meter in `kw`, painted over the border with `SolidColor` = `bg` and ~6px padding.
- **TUI:** `┌─┤ LABEL ├────┐` — the tee glyphs make the interruption explicit.

Never use a filled box, a rounded corner, or a drop shadow.

---

## Inverse-video field
A filled bar with dark ink. Used for the status strip and any active selection.

- **Pixel:** filled `Shape` rectangle in the severity colour + String meter in `inkOnFill`.
- **TUI:** run of cells with the severity colour as background.

**The fill colour carries the meaning** (law 2). A status field is green at nominal, amber at
warning, red at critical — readable before the words.

---

## Segmented bar
Discrete cells, never a smooth gradient. 14 cells is the reference at narrow widths, 26 at wide.

- **Pixel:** N small rectangles, gap 2px, lit ones in the threshold colour, unlit in `faint`.
- **TUI:** `█` for lit, `░` for unlit.

**Threshold colouring is mandatory:** `ok` below 60%, `warn` below 85%, `err` at or above 85%.
A hot subsystem must be visible without reading the number.

---

## Checkbox toggle
- **Pixel:** 12–14px stroked square; filled inner square when on.
- **TUI:** `[■]` on, `[ ]` off. Add explicit `ON` / `OFF` text at the right when width allows —
  the redundancy is deliberate (law 2).

Rows may be 16px in dense stacks. That is under the touch minimum and is an accepted trade for
visual fidelity; do not enlarge them.

---

## LED indicator
- **Pixel:** filled circle with a soft outer glow ring.
- **TUI:** `●` on, `○` off.

In the Pixel variant this is the **only** place green appears. Used for the workspace rail
and the bezel.

---

## Chip
Secondary action. `[LABEL]` with brackets in `faint` and the label in `key` (or `ok` for the
primary action in a group). Minimum 26px tall. Active state is inverse-filled.

---

## key=value pair
The console idiom for any labelled field.

```
host=FLOW-Z13     model=GZ302EA     profile=DEV / ODYSSEY
```
Key in `key`, `=` in `dim`, value in `str` (or `num` for numeric, `path` for files).
Prefer this over a two-column label table in the TUI variant.

---

## Log line
```
log[04:52:26] ERR   toggle poller stopped — states will go stale in 30s        #47
```
`log[` `]` in `faint` · timestamp in `num` · level colour-coded (`INFO`→`key`, `OK`→`ok`,
`WARN`→`warn`, `ERR`→`err`) · message in `dim` · sequence right-aligned in `faint`.

**Log every state change** the user causes, plus automatic events. **Log threshold crossings
once** — on change, not every update, or a hot CPU floods the buffer.

Needs a ring buffer. In Rainmeter that means Lua (`Measure=Script`) — there are no arrays and
variables are single-line.

---

## Tab rail
Bottom-anchored, full width, one cell per workspace. Active tab inverse-filled; inactive tabs
bracketed `┤ ├` in the TUI. Shows an item count or mode per tab. An LED row sits directly above.

---

## Fragility mark `△`
Placed at the right edge of any row whose mechanism is unofficial — undocumented registry keys,
hotkey-driven controls, experimental APIs. Rendered in `warn`.

When such a control fires, the log entry is `WARN` and names the risk. This is how the UI stays
honest about what it can and cannot actually guarantee.

---

## Readout block
A labelled group of 2–4 numeric fields, divided by hairlines.

- Label bar: inverse-video, `kw` or `key`.
- Values in `num`, sub-labels in `dim` beneath.
- Negative power draw uses `err` — a discharging battery reads as a fault-adjacent state.

---

## Empty and absent states

| Situation | Render |
|---|---|
| Empty launcher slot | dashed border, `— EMPTY —` in `faint`, non-interactive |
| Sensor unavailable | `—` in `dim`. **Never `0`** |
| Value stale | keep the value but surface the age; a heartbeat counter beside it |
| Commanded, not read back | show as last commanded; never imply confirmation |
