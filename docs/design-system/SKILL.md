---
name: pipos-design-system
description: >-
  Use when building any UI in the pipOS visual family — Rainmeter skins, widgets, dashboards,
  HTML mockups, TUI panels, or companion apps that must sit alongside the pipOS shell on the
  ROG Flow Z13. Trigger on mentions of pipOS, the amber-phosphor / IMAX-projector-console
  aesthetic, the 132x40 character-grid console variant, or requests to "match the existing
  theme", "make it look like the rest of the shell", or "add a widget to pipOS". Also trigger
  when extending or restyling the pipOS spec, skeleton, or wireframes. This skill carries the
  design tokens, the component vocabulary, the interaction laws, and — most importantly — the
  anti-patterns that were discovered the expensive way, so a new widget does not re-derive
  them. Do NOT use for unrelated desktop customisation or generic dashboard work with no
  pipOS connection.
---

# pipOS design system

Everything in the pipOS family follows one identity, two rendering variants, and a short list
of laws. Read this before designing; read `reference/` while building.

## The identity in one paragraph

A 1990s IMAX film-projector control console, modernised for a touchscreen tablet. Amber
phosphor on near-black. Monospace, all-caps labels. Hairline boxes whose captions break the
top border. Inverse-video status fields. A green LED rail on the bezel. Nothing animates.
The machine is **instrumented, not decorated** — it shows you its own mechanism.

## Two variants, one back-end

| | **Pixel (IMAX)** | **TUI (console)** |
|---|---|---|
| Frames | `Meter=Shape` hairline rectangles | box-drawing glyphs on a char grid |
| Bars | filled rectangles | `█`/`░` cells |
| Grid | free pixel positioning | fixed 132×40 cells |
| Colour | amber brightness tiers | semantic roles |
| Skin shape | hybrid: main + child text panes | monolithic |

New work should say which variant it targets. If it must work in both, put logic in shared
measures and keep meters per-variant (see `reference/architecture.md`).

## The laws

These are not preferences. Each exists because breaking it caused a real defect.

1. **No animation.** Nothing blinks, pulses, fades, or spins. Status changes are instant.
2. **Severity is colour *and* text.** A fault must be readable from the fill colour before
   the words are read. Never encode state in colour alone, or in text alone.
3. **Show the mechanism.** Display model names, endpoints, latencies, `.exe` paths, sensor
   indices, RPM. The aesthetic *is* the instrumentation. Hiding how it works makes it a
   generic dashboard.
4. **Mark unofficial mechanisms with `△`.** Anything relying on an undocumented registry key,
   a hotkey, or a fragile API gets the mark, and the log says so when it fires.
5. **Never fake a value.** A missing sensor shows `—`, never `0`. A commanded-but-unread
   state (e.g. performance mode) is presented as *last commanded*, not as confirmed.
6. **Swapped panes are identical in size.** If two widgets occupy the same slot, they must
   have byte-identical geometry, or everything below them shifts.
7. **Fixed regions clip; they never grow.** Text overflow is clipped at a fixed boundary and
   handled with a scroll offset.
8. **Every colour and dimension comes from a token.** No literals in component code.
9. **Touch tiers:** primary controls ≥44px, secondary chips ≥26px, dense toggle rows 16px
   (deliberate — do not "fix" upward). Tap on release, never on press. No hover-dependent UI.

## Component vocabulary

Use these before inventing anything. Full construction details in `reference/components.md`.

- **Caption-break box** — the signature frame; label sits *on* the top border
- **Inverse-video field** — filled bar, dark ink; for status and active selections
- **Segmented bar** — discrete cells, threshold-coloured; never a smooth gradient
- **Checkbox toggle** — `[■]` / `[ ]`, with explicit `ON`/`OFF` when width allows
- **LED** — `●` / `○`, the only place green appears in the Pixel variant
- **Chip** — `[LABEL]`, secondary actions
- **key=value pair** — the console idiom for any field
- **Log line** — `log[HH:MM:SS] LEVEL message #seq`
- **Tab rail** — bottom-anchored, active tab inverse-filled
- **Fragility mark** `△` — unofficial mechanism

## Tokens

Full palettes in `reference/tokens.md`; copy-pasteable CSS in `reference/tokens.css`.

Structure roles: `bg bezel fg dim faint frame`
Semantic roles: `key str num path kw`
Severity roles: `ok warn err`

**AMBER HYBRID is the default** — amber phosphor for structure and text, with green/amber/red
introduced *only* for severity. It resolves the tension between the source aesthetic and
at-a-glance state reading. Use **HC AMBER** or **MONO WHITE** when legibility must win.

## Anti-patterns

Each of these cost real debugging time. Do not rediscover them.

- **Never trust a font to hold a character grid.** Box-drawing and block glyphs are frequently
  substituted from a fallback font with different advance widths — measured drift was 21px per
  row, enough to break every border. Give each row an explicit fixed width. And measure inside
  the *rendered* grid: testing glyph widths in a detached element inherits the wrong font stack
  and gives false confidence.
- **Never let content overrun into a border.** Compose fields at a fixed width and clamp them.
  Most "alignment bugs" are a label one character too long.
- **Never rate contrast on decorative colours.** Frame and faint tokens are deliberately dim;
  including them makes perfectly legible schemes appear to fail. Rate `fg key str num ok warn err`.
- **Never use a growing text meter** (`ClipString=2` in Rainmeter) inside fixed geometry.
- **Never poll per-row.** One background writer produces a state file; the UI reads it.
- **Never show a stale value as current.** If the writer dies, say so — a heartbeat counter
  makes the difference between "idle" and "dead" visible.
- **Never let two conditions render at once.** Compute one priority integer; branch on it.

## When adding a widget

1. Name the variant(s) it targets.
2. Reuse a component from the vocabulary; only invent when nothing fits.
3. Place it in the existing column budget — check nothing below it shifts.
4. Decide what it shows when its data source is *absent* (law 5) and when it's *stale* (law 9).
5. If it relies on anything unofficial, add `△` and a log line.
6. Give it a token-only palette; verify contrast on the information-bearing roles.
