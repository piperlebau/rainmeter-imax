; ============================================================
;  logic\workspace.inc — active workspace + mode. SHARED.
;  Persistence per §8.1: !SetVariable (live) + !WriteKeyValue
;  (survives restart). Both variants bind their rail meters to
;  the same bang string below.
; ============================================================

[mWorkspace]
Measure=String
String=#Workspace#
DynamicVariables=1

; Mode drives which pane shows (§8.2). Pixel swaps meter groups;
; TUI composes a different box. Same variable either way.
[mMode]
Measure=String
String=#WSMode#
IfMatch=editor
IfMatchAction=[!SetVariable PaneIsEditor "1"]
IfNotMatchAction=[!SetVariable PaneIsEditor "0"]
DynamicVariables=1

; Bay path follows the active workspace (§7).
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
