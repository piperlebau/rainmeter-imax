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
MinValue=0
MaxValue=100

[mRAMLoad]
Measure=Plugin
Plugin=UsageMonitor
Alias=RAM
MinValue=0
MaxValue=100

[mDiskLoad]
Measure=Plugin
Plugin=UsageMonitor
Alias=DISK
Index=0
MinValue=0
MaxValue=100

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

[mIGPUTemp]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=ValueRaw#IdxIGPUTemp#
MinValue=0
MaxValue=110
DynamicVariables=1

[mVRAMDed]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=SOFTWARE\HWiNFO64\VSB
RegValue=ValueRaw#IdxVRAMDed#
MinValue=0
MaxValue=(max(#VRAMTotalMB#,1))
DynamicVariables=1

; ---- native clock / uptime (W4) ----
[mTime]
Measure=Time
Format=%H:%M:%S

[mDate]
Measure=Time
Format=%m/%d/%y

[mUptime]
Measure=UpTime
Format=%H:%M

; ---- segmented-bar threshold colours (§ component: ok<60, warn<85, err>=85) ----
; Each mapper sets a BarCol* variable from the ACTIVE theme's tokens at fire
; time, so bars recolour on theme swap. Variants bind BarColor=#BarCol*#.
[mSevCPU]
Measure=Calc
Formula=(mCPULoad >= 85) * 2 + (mCPULoad >= 60) * (mCPULoad < 85) * 1
IfCondition=(mSevCPU = 0)
IfTrueAction=[!SetVariable BarColCPU "#Ok#"]
IfCondition2=(mSevCPU = 1)
IfTrueAction2=[!SetVariable BarColCPU "#Warn#"]
IfCondition3=(mSevCPU = 2)
IfTrueAction3=[!SetVariable BarColCPU "#Err#"]
DynamicVariables=1

[mSevRAM]
Measure=Calc
Formula=(mRAMLoad >= 85) * 2 + (mRAMLoad >= 60) * (mRAMLoad < 85) * 1
IfCondition=(mSevRAM = 0)
IfTrueAction=[!SetVariable BarColRAM "#Ok#"]
IfCondition2=(mSevRAM = 1)
IfTrueAction2=[!SetVariable BarColRAM "#Warn#"]
IfCondition3=(mSevRAM = 2)
IfTrueAction3=[!SetVariable BarColRAM "#Err#"]
DynamicVariables=1

[mSevDISK]
Measure=Calc
Formula=(mDiskLoad >= 85) * 2 + (mDiskLoad >= 60) * (mDiskLoad < 85) * 1
IfCondition=(mSevDISK = 0)
IfTrueAction=[!SetVariable BarColDISK "#Ok#"]
IfCondition2=(mSevDISK = 1)
IfTrueAction2=[!SetVariable BarColDISK "#Warn#"]
IfCondition3=(mSevDISK = 2)
IfTrueAction3=[!SetVariable BarColDISK "#Err#"]
DynamicVariables=1

[mSevIGPU]
Measure=Calc
Formula=(mIGPULoad >= 85) * 2 + (mIGPULoad >= 60) * (mIGPULoad < 85) * 1
IfCondition=(mSevIGPU = 0)
IfTrueAction=[!SetVariable BarColIGPU "#Ok#"]
IfCondition2=(mSevIGPU = 1)
IfTrueAction2=[!SetVariable BarColIGPU "#Warn#"]
IfCondition3=(mSevIGPU = 2)
IfTrueAction3=[!SetVariable BarColIGPU "#Err#"]
DynamicVariables=1

[mSevVRAM]
Measure=Calc
Formula=((mVRAMDed / max(#VRAMTotalMB#,1)) * 100 >= 85) * 2 + ((mVRAMDed / max(#VRAMTotalMB#,1)) * 100 >= 60) * ((mVRAMDed / max(#VRAMTotalMB#,1)) * 100 < 85) * 1
IfCondition=(mSevVRAM = 0)
IfTrueAction=[!SetVariable BarColVRAM "#Ok#"]
IfCondition2=(mSevVRAM = 1)
IfTrueAction2=[!SetVariable BarColVRAM "#Warn#"]
IfCondition3=(mSevVRAM = 2)
IfTrueAction3=[!SetVariable BarColVRAM "#Err#"]
DynamicVariables=1

[mVRAMPct]
Measure=Calc
Formula=(mVRAMDed / max(#VRAMTotalMB#,1)) * 100
MinValue=0
MaxValue=100
DynamicVariables=1
