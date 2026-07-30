; ============================================================
;  logic\sensors.inc — SHARED MEASURES ONLY. No meters.
;  Included by BOTH Pixel\pipOS.ini and TUI\pipOS-tui.ini.
;  Renaming a measure here breaks both variants (§17.6).
;
;  Sourcing rule (§5.3): UsageMonitor for anything it can read;
;  HWiNFO only for temps/power/GPU/VRAM/battery/fan.
; ============================================================

; ---- UsageMonitor: primary for CPU / RAM / DISK ----
[mCPULoad]
Measure=Plugin
Plugin=UsageMonitor
Alias=CPU
Index=0

[mRAMLoad]
Measure=Plugin
Plugin=UsageMonitor
Alias=RAM

[mDiskLoad]
Measure=Plugin
Plugin=UsageMonitor
Alias=DISK
Index=0

; ---- HWiNFO VSB registry: only what UsageMonitor cannot read ----
; Index variables are stubs until Tools\Discover.ini is run on-device.
[mCPUTemp]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=ValueRaw#IdxCPUTemp#
MinValue=0
MaxValue=110
DynamicVariables=1

[mCPUTempLabel]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=Label#IdxCPUTemp#
DynamicVariables=1

[mIGPULoad]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=ValueRaw#IdxIGPULoad#
MinValue=0
MaxValue=100
DynamicVariables=1

[mPkgPower]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=ValueRaw#IdxPkgPower#
DynamicVariables=1

; ---- label drift detection (feeds W3 priority 3, §6.1) ----
[mLabelDrift]
Measure=String
String=[mCPUTempLabel]
IfMatch=^#LblCPUTemp#$
IfMatchAction=[!SetVariable DriftFlag "0"]
IfNotMatchAction=[!SetVariable DriftFlag "1"]
DynamicVariables=1
