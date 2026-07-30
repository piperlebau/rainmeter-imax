; ============================================================
;  logic\status.inc — W3 status priority + W19 log hooks.
;  SHARED. Measures only (§17.6).
;
;  Priority (§6.1): drift(3) > poller stale(2) > thermal(1) > ok(0)
;  Multiplicative guards ensure exactly ONE term is non-zero.
; ============================================================

[mPollerAge]
Measure=Calc
; seconds since sensors.ps1 last wrote its timestamp
Formula=(#CURRENTSECTION#)
; TODO(B): replace with (Time - poller ts) once toggles.inc parses the file
DynamicVariables=1

[mPollerStale]
Measure=Calc
Formula=(mPollerAge > 30) ? 1 : 0
DynamicVariables=1

[mStatusCode]
Measure=Calc
Formula=(#DriftFlag# > 0) * 3 + (#DriftFlag# = 0) * (mPollerStale > 0) * 2 + (#DriftFlag# = 0) * (mPollerStale = 0) * (mCPULoad >= 85) * 1
DynamicVariables=1
; Each variant binds its own meters to these; the codes are the contract.
IfCondition=(mStatusCode = 3)
IfTrueAction=[!SetVariable StatusMsg "CRIT  SENSOR MAP DRIFT — HWiNFO label mismatch, re-run Discover"][!SetVariable StatusSev "err"]
IfCondition2=(mStatusCode = 2)
IfTrueAction2=[!SetVariable StatusMsg "WARN  TOGGLE POLLER DOWN — switch states are stale"][!SetVariable StatusSev "warn"]
IfCondition3=(mStatusCode = 1)
IfTrueAction3=[!SetVariable StatusMsg "WARN  THERMAL LIMIT — package throttling expected"][!SetVariable StatusSev "warn"]
IfCondition4=(mStatusCode = 0)
IfTrueAction4=[!SetVariable StatusMsg "OK    AUTO MODE — ALL PRESETS NOMINAL"][!SetVariable StatusSev "ok"]

; ---- log ring buffer (Lua — Rainmeter has no arrays, §6.1a) ----
[mLog]
Measure=Script
ScriptFile=#@#Scripts\log.lua
UpdateDivider=1

; Threshold crossing: fire ONCE on change, not every update.
[mThermalEdge]
Measure=Calc
Formula=(mCPULoad >= 85) ? 1 : 0
IfCondition=(mThermalEdge = 1)
IfTrueAction=[!CommandMeasure mLog "Add('WARN','CPU crossed 85% thermal threshold')"]
IfCondition2=(mThermalEdge = 0)
IfTrueAction2=[!CommandMeasure mLog "Add('OK','CPU back below threshold')"]
IfConditionMode=1
DynamicVariables=1
