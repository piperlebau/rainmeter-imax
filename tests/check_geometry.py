#!/usr/bin/env python3
"""
pipOS geometry gate.

Verifies the two constraints that silently break the layout when violated:
  - Column budget: the lowest widget in each column ends at Y+H <= BUDGET.
  - Pane parity:   the launch bay (W11) and editor (W18) are the same height.

This measures the DESIGN AUTHORITY (pipOS-wireframe-v20.html), which is the source of
truth for layout until the actual skins render. When you have rendered skin output you can
adapt MEASURE_URL / the selectors, but the assertions below are the contract either way.

Usage:
    python tests/check_geometry.py [path-or-url-to-wireframe]

Exit code 0 = pass, 1 = fail, 2 = harness error (e.g. Playwright/Chromium missing).
"""

import sys, json, asyncio, pathlib

# ---- contract (keep in sync with Variables.inc / CLAUDE.md) ----
BUDGET = 607          # constraint 2: last widget Y+H must be <= this
PANE_H = 230          # constraint 3: W11 and W18 height
PANE_TOL = 0.6        # px tolerance for the parity check
BUDGET_TOL = 1.0      # px tolerance for the budget check

DEFAULT_WIREFRAME = (pathlib.Path(__file__).resolve().parent.parent.parent
                     / "pipOS-wireframe-v20.html")

MEASURE_JS = r"""
() => {
  const h = e => +e.getBoundingClientRect().height.toFixed(2);
  const q = s => document.querySelector(s);
  const main = q('.main').getBoundingClientRect();

  // lowest widget bottom in each column, relative to top of .main
  function lowest(colSel) {
    const kids = [...q(colSel).children]
      .filter(e => getComputedStyle(e).display !== 'none' && !e.classList.contains('anno'));
    let max = 0, who = '';
    for (const e of kids) {
      const b = e.getBoundingClientRect().bottom - main.top;
      if (b > max) { max = b; who = (typeof e.className === 'string' ? e.className.split(' ')[0] : e.tagName); }
    }
    return { bottom: +max.toFixed(2), widget: who };
  }

  // measure editor height even though it's hidden in apps mode
  const bay = q('#bayBox'), ed = q('#editorBox');
  const prevB = bay.style.display, prevE = ed.style.display;
  bay.style.display = 'none'; ed.style.display = '';
  const editorH = h(ed);
  bay.style.display = prevB; ed.style.display = prevE;

  return {
    left:  lowest('.left'),
    right: lowest('.right'),
    bayH:  h(bay),
    editorH: editorH
  };
}
"""

async def measure(url):
    from playwright.async_api import async_playwright
    async with async_playwright() as p:
        b = await p.chromium.launch()
        pg = await b.new_page(viewport={"width": 1400, "height": 1000})
        await pg.goto(url)
        await pg.wait_for_timeout(700)
        apps = await pg.evaluate(MEASURE_JS)
        # switch to the editor workspace (WS4) and re-measure the left column
        await pg.evaluate("()=>[...document.querySelectorAll('.wsrail .btn')][3].click()")
        await pg.wait_for_timeout(300)
        editor_mode = await pg.evaluate(MEASURE_JS)
        await b.close()
        return apps, editor_mode


def check(apps, editor_mode):
    fails = []

    for label, m in (("apps", apps), ("editor", editor_mode)):
        for col in ("left", "right"):
            b = m[col]["bottom"]
            if b > BUDGET + BUDGET_TOL:
                fails.append(f"[{label}] {col} column overflows: lowest widget "
                             f"'{m[col]['widget']}' ends at {b}px (budget {BUDGET})")

    # parity: bay vs editor
    if abs(apps["bayH"] - apps["editorH"]) > PANE_TOL:
        fails.append(f"W11/W18 height mismatch: bay={apps['bayH']} editor={apps['editorH']} "
                     f"(must match within {PANE_TOL}px)")
    for name, val in (("bay", apps["bayH"]), ("editor", apps["editorH"])):
        if abs(val - PANE_H) > PANE_TOL:
            fails.append(f"{name} height is {val}px, expected {PANE_H}px")

    return fails


def main():
    url = sys.argv[1] if len(sys.argv) > 1 else str(DEFAULT_WIREFRAME)
    if "://" not in url:
        url = "file://" + str(pathlib.Path(url).resolve())

    try:
        apps, editor_mode = asyncio.run(measure(url))
    except Exception as e:
        print(f"HARNESS ERROR: {e}", file=sys.stderr)
        print("Need: pip install playwright && python -m playwright install chromium",
              file=sys.stderr)
        sys.exit(2)

    print("measured:", json.dumps({"apps": apps, "editor": editor_mode}, indent=1))
    fails = check(apps, editor_mode)
    print()
    if fails:
        print("GEOMETRY FAIL")
        for f in fails:
            print("  ✗", f)
        sys.exit(1)
    print(f"GEOMETRY PASS — both columns within {BUDGET}px budget, "
          f"W11==W18=={PANE_H}px in both modes")
    sys.exit(0)


if __name__ == "__main__":
    main()
