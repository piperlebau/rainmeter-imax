; ============================================================
;  logic\power.inc — battery, energy accumulator, perf mode.
;  SHARED measures only (§17.6).
; ============================================================

[mBattPct]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=ValueRaw#IdxBattPct#
DynamicVariables=1

[mBattRate]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=ValueRaw#IdxBattRate#
DynamicVariables=1

; Energy used since last RST. Accumulates watt-seconds -> Wh.
[mEnergyWh]
Measure=Calc
Formula=mEnergyWh + (abs(mBattRate) / 3600)
DynamicVariables=1

; Perf mode is COMMANDED, not read back (§11) — G-Helper has no CLI.
; Track the last commanded value; never present it as confirmed.
[mPerfMode]
Measure=String
String=#PerfMode#
DynamicVariables=1
