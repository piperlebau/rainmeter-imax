# pipOS architecture

How the pieces fit, so a new widget lands in the right place.

---

## Measures are shared; meters are not

The single rule that lets two visual variants coexist without doubling the work.

```
@Resources/logic/*.inc     ← every Measure=.  Included by BOTH variants. ZERO meters.
Pixel/…                    ← every Meter=, all X/Y/W/H, all MeterStyle, action bangs
TUI/…                      ← same, different rendering
```

**The test:** changing a sensor index, adding a workspace, or fixing the status priority
should mean editing exactly one file under `logic/`, and both variants pick it up. If a change
has to be made twice, the boundary is in the wrong place.

Measure names in `logic/` are a **public API** — a meter in either variant refers to
`[mCPULoad]`. Renaming breaks both. Prefix shared measures `m…` so variant-local measures
can't collide.

---

## Where a new widget goes

1. **Does it compute state?** That part goes in `logic/` as measures. No exceptions.
2. **Does it draw?** That part goes in the variant folder as meters.
3. **Does it need a new token?** Add it to every palette, not just the one you're testing.
4. **Does it need persistence?** `!SetVariable` for live effect **and** `!WriteKeyValue` to
   `Variables.inc` to survive a restart. One without the other is a bug.

---

## Geometry contracts

**Pixel.** 1280×800 logical. Columns bottom-anchored: the lowest widget in each must satisfy
`Y + H ≤ 607`, measured from the top of the main region. Rainmeter has no auto-flow, so this
is arithmetic you do yourself — there is no layout engine to catch an overflow. Because the
columns are bottom-anchored, overflow rides **upward** and collides with the header, which is
a confusing symptom for an obvious cause.

**TUI.** 132 columns × 40 rows, cell 9.45×18.6px. Every row meter gets the **same explicit
fixed width**. This is not a style choice — see the font-metrics anti-pattern below.

**Swapped panes.** Any two widgets that occupy the same slot must be byte-identical in height.
The reference pair is the launch bay and the editor, both exactly 230px. A one-pixel difference
shifts everything below them when the user switches workspace.

---

## The variants differ in skin shape

**Pixel is hybrid.** One main skin holds the frame and all light widgets; the text panes
(Notes, Editor) are child skins occupying reserved rectangles the main skin leaves empty. This
exists so saving a note doesn't reload the telemetry. Child positions derive from the same
geometry variables as the holes, so they can't drift.

**TUI is monolithic.** A child skin is a separate window with its own coordinate space;
landing it inside a character grid would require its cell origin *and* cell size to match the
parent exactly, and any drift breaks the grid the whole aesthetic depends on. The TUI redraws
the whole grid instead — cheap enough in practice.

Consequence: Notes and Editor exist as separate skins **only** in the Pixel variant.

---

## Data sourcing

Use the cheapest source that can answer, and confine fragile sources to what only they can do.

- **UsageMonitor** for CPU load, per-core, RAM, disk, network. No dependency, no drift.
- **HWiNFO (registry/VSB method)** only for what UsageMonitor cannot read: temperatures,
  power, GPU load, VRAM, battery rate, fan RPM.
- **A background writer** for anything requiring a shell call — radio states, night light.
  It writes one small state file on a timer; the UI only reads. Never spawn a process per row
  per update.

HWiNFO index numbers are **fragile**: they shift when the exported sensor set changes, and a
sensor that is inactive at HWiNFO start is omitted entirely, shifting every later index down.
Always store indices as named variables, and read the *label* alongside the value to detect
drift. Silent drift is worse than a missing sensor.

---

## State that must survive

| State | Lives in |
|---|---|
| Active workspace + mode | `Variables.inc` (written with `!WriteKeyValue`) |
| Toggle states | the background writer's state file |
| Notes / manuscripts | `@Resources/Workspaces/notes/` |
| Discovered sensor indices | `Variables.inc` |
| Theme choice | the `@IncludeTheme` line |

Because all of it is in `@Resources`, switching variants preserves everything. Switching means
unloading one skin and loading the other — never runtime-swapping meter groups inside a single
skin, which would load two full layouts at once for no benefit.

---

## Anti-patterns, with the evidence

**Trusting a font to hold a character grid.** Box-drawing (`─│┌┐├┤`) and block (`█░`) glyphs
are frequently absent from a chosen monospace font and get substituted from a fallback with
different advance widths. Measured: rows dense in box-drawing rendered **21px wider** than
plain-ASCII rows — over two cells of drift, enough to break every vertical border. Fix by
giving every row an explicit fixed width; that collapsed a 738–759px spread to a uniform
757.22px. Corollary: measure inside the *rendered* grid. Testing glyph widths in a detached
element inherits the wrong font stack and reports everything as uniform when it isn't.

**Content overrunning a border.** Most "alignment bugs" are one label a character too long.
Compose every field at a fixed width and clamp it.

**A growing text meter inside fixed geometry.** In Rainmeter, `ClipString=2` grows the meter
to fit its content, which breaks any pane with a fixed height. Use `ClipString=1` with fixed
`W`/`H` and let it clip.

**Two conditions rendering at once.** Rainmeter `IfCondition`s all evaluate independently.
Compute a single priority integer with multiplicative guards so exactly one term is non-zero,
then branch on that value.

**Rating contrast on decorative colours.** `frame` and `faint` are deliberately dim. Including
them makes perfectly legible schemes appear to fail. Rate `fg key str num ok warn err`.

**Polling per row.** One writer, one file, cheap reads. Anything else thrashes.

---

## Things that do not exist in Rainmeter

Do not spend time looking for them: loops, arrays, blend modes, native blur, a file dialog,
a scrollbar, keystroke sending, multiline text input (stock), or a way to host another
application's window inside a skin. Each has a documented workaround in the main spec;
none has a native solution.
