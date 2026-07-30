[Variables]
; ============================================================
;  pipOS — design tokens + persisted state
;  Every colour and dimension in every skin comes from here.
;  No literals in skin files (CLAUDE.md constraint 9).
; ============================================================

; ---- amber phosphor palette (R,G,B) ----
AmberBright=255,176,0
AmberMid=204,140,0
AmberDim=127,88,0
AmberFaint=74,51,0
AmberGlow=255,176,0,77
; Screen ground is pure black — the shell uses exclusively high-contrast
; black-background themes (all Themes/*.inc set Bg=0,0,0).
ScreenBG=0,0,0
BezelBG=8,8,8
LEDOn=59,255,106
LEDOff=14,42,20
Warn=255,94,43
InkOnAmber=13,9,0

; ---- geometry (logical px @ 1280x800; see CLAUDE.md constraints 2 & 3) ----
ShellW=1280
ShellH=800
BudgetY=607          ; last widget in each column must end at Y+H <= this
PaneHeight=230       ; W11 launch bay AND W18 editor — identical, do not diverge
EdBodyH=129          ; fixed editor/notes text clip region — never grows (ClipString=1)
EdLineH=17           ; per-line meter pitch inside the clip region
; ---- v21 layout origins (measured from docs\pipOS-wireframe-v21.html, 1280x800) ----
MainX=50             ; left edge of the .main content region
MainY=78             ; top of .main (budget is measured from here)
LeftX=50             ; left column x
LeftW=894            ; left column width (v21: console removed, full width)
RightX=957           ; right column x
ColRightW=292        ; right column width
ColGap=13            ; gap between the two columns
ScreenPad=13
BezelRailW=34        ; LED rail gutter
GapL=9               ; left-column vertical gap
GapR=7               ; right-column vertical gap
HdrH=42              ; header height (watch the (R) superscript — keep within this)
RailH=74             ; workspace rail button height (v21)
; NOTE: v21's lowest widgets end ~612px below MainY vs the 607 budget; matched to the
;       wireframe authority. Reconcile to 607 if the geometry gate is enforced on render.

; ---- TUI variant geometry (§17.2) — a SEPARATE coordinate system.
;      Do not derive these from the pixel values; they describe the
;      same layout in different units.
GridCols=132
GridRows=40
CellW=9.45
CellH=18.6
TuiFontSize=15.8
TuiOriginX=16
TuiOriginY=14

; ---- type ----
FontMain=IBM Plex Mono
FontSizeBody=12
FontSizeLabel=10
FontSizeCaption=10
FontSizeReadout=17
FontSizeBanner=22
FontSizeBrand=23

; ---- child-skin hole positions (derived; keep in sync with pipOS.ini frames) ----
; Notes (W17) and Editor (W18) panes are separate skins that land inside
; frames drawn by the main skin. These X/Y are where the child skins position
; themselves. If you move the frame in pipOS.ini, move these too.
; v21: Notes (W17) is the full-width top pane, always visible.
; Editor (W18) swaps into the Launch Bay (W11) slot in WRITE mode — both 230px (constraint 3).
NotesX=50
NotesY=119
NotesW=894
NotesH=159
EditorX=50
EditorY=414
EditorW=894
EditorH=230

; ============================================================
;  PERSISTED STATE  (written at runtime via !WriteKeyValue)
; ============================================================
; ---- runtime state written by logic\ (§17.6) ----
StatusMsg=OK    AUTO MODE — ALL PRESETS NOMINAL
StatusSev=ok         ; ok | warn | err  — drives the W3 fill colour
DriftFlag=0          ; set by logic\sensors.inc label check
LogLast=             ; newest log line, set by Scripts\log.lua
LogSeq=0
PerfMode=1           ; 0 silent 1 balanced 2 turbo (commanded, not read back)

Workspace=1          ; active workspace id 1..5
WSMode=apps          ; apps | editor  (WS4 = editor)
WrapEditor=0         ; editor WRAP toggle: 0=clip 1=wrap

; ============================================================
;  HWiNFO VSB INDICES  — STUBS
;  All 0 = undiscovered. Resolve on the actual GZ302EA with
;  Tools\Discover.ini, then !WriteKeyValue the real indices here.
;  Do NOT invent values (CLAUDE.md "when blocked").
; ============================================================
IdxCPUTemp=0         ; TODO: discover on device — CPU (Tctl/Tdie)
IdxIGPUTemp=0        ; TODO: discover on device — GPU Temperature
IdxPkgPower=0        ; TODO: discover on device — CPU Package Power
IdxBattRate=0        ; TODO: discover on device — Charge/Discharge Rate
IdxIGPULoad=0        ; TODO: discover on device — GPU Core Load (NOT D3D Usage)
IdxVRAMDed=0         ; TODO: discover on device — GPU D3D Memory Dedicated
IdxVRAMDyn=0         ; TODO: discover on device — GPU D3D Memory Dynamic
IdxBattLeft=0        ; TODO: discover on device — Estimated Remaining Time
IdxBattPct=0         ; TODO: discover on device — Charge Level
IdxFanCPU=0          ; TODO: discover on device — may be absent (EC contention, §5.4)
IdxFanGPU=0          ; TODO: discover on device — may be absent

; Expected label strings, for the drift check in W3 (§6.1). If Label#Idx#
; doesn't match these at runtime, W3 shows SENSOR MAP DRIFT.
LblCPUTemp=CPU (Tctl/Tdie)
LblIGPULoad=GPU Core Load
LblBattRate=Charge Rate
