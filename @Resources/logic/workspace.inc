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

; ---- bay slot children (shared API: mBayFileN / mBayNameN / mBayGoN) ----
; FileName feeds the label (ordering prefix "N_" stripped, empty slot
; becomes the — EMPTY — state per the component vocabulary); FilePath is
; what a tap executes. All in Group=Bay so mBayPath's FinishAction
; refreshes them on workspace change.

[mBayFile1]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FileName
Index=1
Group=Bay
DynamicVariables=1

[mBayGo1]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FilePath
Index=1
Group=Bay
DynamicVariables=1

[mBayName1]
Measure=String
String=[mBayFile1]
RegExpSubstitute=1
Substitute="^\d+_":"","^$":"— EMPTY —"
Group=Bay
DynamicVariables=1

[mBayFile2]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FileName
Index=2
Group=Bay
DynamicVariables=1

[mBayGo2]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FilePath
Index=2
Group=Bay
DynamicVariables=1

[mBayName2]
Measure=String
String=[mBayFile2]
RegExpSubstitute=1
Substitute="^\d+_":"","^$":"— EMPTY —"
Group=Bay
DynamicVariables=1

[mBayFile3]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FileName
Index=3
Group=Bay
DynamicVariables=1

[mBayGo3]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FilePath
Index=3
Group=Bay
DynamicVariables=1

[mBayName3]
Measure=String
String=[mBayFile3]
RegExpSubstitute=1
Substitute="^\d+_":"","^$":"— EMPTY —"
Group=Bay
DynamicVariables=1

[mBayFile4]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FileName
Index=4
Group=Bay
DynamicVariables=1

[mBayGo4]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FilePath
Index=4
Group=Bay
DynamicVariables=1

[mBayName4]
Measure=String
String=[mBayFile4]
RegExpSubstitute=1
Substitute="^\d+_":"","^$":"— EMPTY —"
Group=Bay
DynamicVariables=1

[mBayFile5]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FileName
Index=5
Group=Bay
DynamicVariables=1

[mBayGo5]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FilePath
Index=5
Group=Bay
DynamicVariables=1

[mBayName5]
Measure=String
String=[mBayFile5]
RegExpSubstitute=1
Substitute="^\d+_":"","^$":"— EMPTY —"
Group=Bay
DynamicVariables=1

[mBayFile6]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FileName
Index=6
Group=Bay
DynamicVariables=1

[mBayGo6]
Measure=Plugin
Plugin=FileView
Path=[mBayPath]
Type=FilePath
Index=6
Group=Bay
DynamicVariables=1

[mBayName6]
Measure=String
String=[mBayFile6]
RegExpSubstitute=1
Substitute="^\d+_":"","^$":"— EMPTY —"
Group=Bay
DynamicVariables=1
