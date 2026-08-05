; Telemetry.inc — right column, Milestone B (live).
;  W8 TOGGLES (static until the B2 poller exists), W13 SUBSYSTEM LOAD
;  (live bars, threshold colours from logic\), W9/10 THERMAL/POWER,
;  W14 BATTERY/ENERGY, W16 PERFORMANCE MODE (commanded, not read back).
;  Every HWiNFO-backed value is gated on its Idx* stub: 0 -> — (law 5).

[TogFrame]
Meter=Shape
Shape=Rectangle 957,129,292,122,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[TogCap]
Meter=String
MeterStyle=sCap
X=(957+12)
Y=(129-7)
Text=TOGGLES

; TODO(B2): bind squares/status to mTog* and add tap actions once the
; state poller (sensors.ps1) exists. Static placeholders until then.

[Tog1Sq]
Meter=Shape
Shape=Rectangle 972,148,12,12 | StrokeWidth 1 | Stroke Color #Frame# | FillColor #Fg#

[Tog1Lbl]
Meter=String
MeterStyle=sBody
FontColor=#Fg#
FontSize=8.25
X=992
Y=147
Text=WI-FI

[Tog1State]
Meter=String
MeterStyle=sSub
FontColor=#Ok#
FontSize=7.5
X=1200
Y=147
Text=ON

[Tog2Sq]
Meter=Shape
Shape=Rectangle 972,166,12,12 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[Tog2Lbl]
Meter=String
MeterStyle=sBody
FontColor=#Dim#
FontSize=8.25
X=992
Y=165
Text=BLUETOOTH

[Tog2State]
Meter=String
MeterStyle=sSub
FontColor=#Faint#
FontSize=7.5
X=1200
Y=165
Text=OFF

[Tog3Sq]
Meter=Shape
Shape=Rectangle 972,184,12,12 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[Tog3Lbl]
Meter=String
MeterStyle=sBody
FontColor=#Dim#
FontSize=8.25
X=992
Y=183
Text=MUTE

[Tog3State]
Meter=String
MeterStyle=sSub
FontColor=#Faint#
FontSize=7.5
X=1200
Y=183
Text=OFF

[Tog4Sq]
Meter=Shape
Shape=Rectangle 972,202,12,12 | StrokeWidth 1 | Stroke Color #Frame# | FillColor #Fg#

[Tog4Lbl]
Meter=String
MeterStyle=sBody
FontColor=#Fg#
FontSize=8.25
X=992
Y=201
Text=NIGHT LIGHT

[Tog4State]
Meter=String
MeterStyle=sSub
FontColor=#Ok#
FontSize=7.5
X=1200
Y=201
Text=ON

[Tog4Frag]
Meter=String
MeterStyle=sBody
FontColor=#Warn#
FontSize=8.25
X=1237
Y=201
Text=△

[Tog5Sq]
Meter=Shape
Shape=Rectangle 972,220,12,12 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[Tog5Lbl]
Meter=String
MeterStyle=sBody
FontColor=#Dim#
FontSize=8.25
X=992
Y=219
Text=ROTATION LOCK

[Tog5State]
Meter=String
MeterStyle=sSub
FontColor=#Faint#
FontSize=7.5
X=1200
Y=219
Text=OFF

[Tog5Frag]
Meter=String
MeterStyle=sBody
FontColor=#Warn#
FontSize=8.25
X=1237
Y=219
Text=△

[SubFrame]
Meter=Shape
Shape=Rectangle 957,258,292,100,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[SubCap]
Meter=String
MeterStyle=sCap
X=(957+12)
Y=(258-7)
Text=SUBSYSTEM LOAD

[Sub1Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=275
Text=CPU

[Sub1Track]
Meter=Shape
Shape=Rectangle 1015,278,178,11 | FillColor #Faint# | StrokeWidth 0

[Sub1Bar]
Meter=Bar
MeasureName=mCPULoad
BarOrientation=Horizontal
X=1015
Y=278
W=178
H=11
BarColor=#BarColCPU#
SolidColor=0,0,0,1
DynamicVariables=1

[Sub1Sep]
Meter=Shape
Shape=Rectangle 1025.86,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape2=Rectangle 1038.72,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape3=Rectangle 1051.58,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape4=Rectangle 1064.44,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape5=Rectangle 1077.3,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape6=Rectangle 1090.16,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape7=Rectangle 1103.02,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape8=Rectangle 1115.88,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape9=Rectangle 1128.74,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape10=Rectangle 1141.6,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape11=Rectangle 1154.46,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape12=Rectangle 1167.32,278,2,11 | FillColor #Bg# | StrokeWidth 0
Shape13=Rectangle 1180.18,278,2,11 | FillColor #Bg# | StrokeWidth 0

[Sub1Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=275
DynamicVariables=1
Text=[mCPULoad:0]%

[Sub2Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=291
Text=IGPU

[Sub2Track]
Meter=Shape
Shape=Rectangle 1015,294,178,11 | FillColor #Faint# | StrokeWidth 0

[Sub2Bar]
Meter=Bar
MeasureName=mIGPULoad
BarOrientation=Horizontal
X=1015
Y=294
W=178
H=11
BarColor=#BarColIGPU#
SolidColor=0,0,0,1
DynamicVariables=1
Hidden=(#IdxIGPULoad#=0)

[Sub2Sep]
Meter=Shape
Shape=Rectangle 1025.86,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape2=Rectangle 1038.72,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape3=Rectangle 1051.58,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape4=Rectangle 1064.44,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape5=Rectangle 1077.3,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape6=Rectangle 1090.16,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape7=Rectangle 1103.02,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape8=Rectangle 1115.88,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape9=Rectangle 1128.74,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape10=Rectangle 1141.6,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape11=Rectangle 1154.46,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape12=Rectangle 1167.32,294,2,11 | FillColor #Bg# | StrokeWidth 0
Shape13=Rectangle 1180.18,294,2,11 | FillColor #Bg# | StrokeWidth 0

[Sub2Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=291
DynamicVariables=1
Hidden=(#IdxIGPULoad#=0)
Text=[mIGPULoad:0]%

[Sub2Dash]
Meter=String
MeterStyle=sBody
FontColor=#Dim#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=291
DynamicVariables=1
Hidden=(#IdxIGPULoad#<>0)
Text=—

[Sub3Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=307
Text=RAM

[Sub3Track]
Meter=Shape
Shape=Rectangle 1015,310,178,11 | FillColor #Faint# | StrokeWidth 0

[Sub3Bar]
Meter=Bar
MeasureName=mRAMLoad
BarOrientation=Horizontal
X=1015
Y=310
W=178
H=11
BarColor=#BarColRAM#
SolidColor=0,0,0,1
DynamicVariables=1

[Sub3Sep]
Meter=Shape
Shape=Rectangle 1025.86,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape2=Rectangle 1038.72,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape3=Rectangle 1051.58,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape4=Rectangle 1064.44,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape5=Rectangle 1077.3,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape6=Rectangle 1090.16,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape7=Rectangle 1103.02,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape8=Rectangle 1115.88,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape9=Rectangle 1128.74,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape10=Rectangle 1141.6,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape11=Rectangle 1154.46,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape12=Rectangle 1167.32,310,2,11 | FillColor #Bg# | StrokeWidth 0
Shape13=Rectangle 1180.18,310,2,11 | FillColor #Bg# | StrokeWidth 0

[Sub3Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=307
DynamicVariables=1
Text=[mRAMLoad:0]%

[Sub4Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=323
Text=VRAM

[Sub4Track]
Meter=Shape
Shape=Rectangle 1015,326,178,11 | FillColor #Faint# | StrokeWidth 0

[Sub4Bar]
Meter=Bar
MeasureName=mVRAMPct
BarOrientation=Horizontal
X=1015
Y=326
W=178
H=11
BarColor=#BarColVRAM#
SolidColor=0,0,0,1
DynamicVariables=1
Hidden=((#IdxVRAMDed# * #VRAMTotalMB#)=0)

[Sub4Sep]
Meter=Shape
Shape=Rectangle 1025.86,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape2=Rectangle 1038.72,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape3=Rectangle 1051.58,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape4=Rectangle 1064.44,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape5=Rectangle 1077.3,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape6=Rectangle 1090.16,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape7=Rectangle 1103.02,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape8=Rectangle 1115.88,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape9=Rectangle 1128.74,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape10=Rectangle 1141.6,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape11=Rectangle 1154.46,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape12=Rectangle 1167.32,326,2,11 | FillColor #Bg# | StrokeWidth 0
Shape13=Rectangle 1180.18,326,2,11 | FillColor #Bg# | StrokeWidth 0

[Sub4Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=323
DynamicVariables=1
Hidden=((#IdxVRAMDed# * #VRAMTotalMB#)=0)
Text=[mVRAMPct:0]%

[Sub4Dash]
Meter=String
MeterStyle=sBody
FontColor=#Dim#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=323
DynamicVariables=1
Hidden=((#IdxVRAMDed# * #VRAMTotalMB#)<>0)
Text=—

[Sub5Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=339
Text=DISK

[Sub5Track]
Meter=Shape
Shape=Rectangle 1015,342,178,11 | FillColor #Faint# | StrokeWidth 0

[Sub5Bar]
Meter=Bar
MeasureName=mDiskLoad
BarOrientation=Horizontal
X=1015
Y=342
W=178
H=11
BarColor=#BarColDISK#
SolidColor=0,0,0,1
DynamicVariables=1

[Sub5Sep]
Meter=Shape
Shape=Rectangle 1025.86,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape2=Rectangle 1038.72,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape3=Rectangle 1051.58,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape4=Rectangle 1064.44,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape5=Rectangle 1077.3,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape6=Rectangle 1090.16,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape7=Rectangle 1103.02,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape8=Rectangle 1115.88,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape9=Rectangle 1128.74,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape10=Rectangle 1141.6,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape11=Rectangle 1154.46,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape12=Rectangle 1167.32,342,2,11 | FillColor #Bg# | StrokeWidth 0
Shape13=Rectangle 1180.18,342,2,11 | FillColor #Bg# | StrokeWidth 0

[Sub5Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=339
DynamicVariables=1
Text=[mDiskLoad:0]%

[Thm]
Meter=Shape
Shape=Rectangle 957,365,292,104,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[ThmTitle]
Meter=Shape
Shape=Rectangle 958,366,290,20 | FillColor #Key# | StrokeWidth 0

[ThmTitleT]
Meter=String
MeterStyle=sInk
StringAlign=CENTERCENTER
X=1103
Y=376
Text=THERMAL / POWER

[ThmCpuV]
Meter=String
MeterStyle=sValBig
StringAlign=CENTER
X=1030
Y=392
DynamicVariables=1
Hidden=(#IdxCPUTemp#=0)
Text=[mCPUTemp:0]°C

[ThmCpuD]
Meter=String
MeterStyle=sValBig
FontColor=#Dim#
StringAlign=CENTER
X=1030
Y=392
DynamicVariables=1
Hidden=(#IdxCPUTemp#<>0)
Text=—

[ThmCpuS]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1030
Y=419
Text=CPU TCTL

[ThmGpuV]
Meter=String
MeterStyle=sValBig
StringAlign=CENTER
X=1176
Y=392
DynamicVariables=1
Hidden=(#IdxIGPUTemp#=0)
Text=[mIGPUTemp:0]°C

[ThmGpuD]
Meter=String
MeterStyle=sValBig
FontColor=#Dim#
StringAlign=CENTER
X=1176
Y=392
DynamicVariables=1
Hidden=(#IdxIGPUTemp#<>0)
Text=—

[ThmGpuS]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1176
Y=419
Text=IGPU

[ThmPkgV]
Meter=String
MeterStyle=sValBig
StringAlign=CENTER
X=1030
Y=430
DynamicVariables=1
Hidden=(#IdxPkgPower#=0)
Text=[mPkgPower:1] W

[ThmPkgD]
Meter=String
MeterStyle=sValBig
FontColor=#Dim#
StringAlign=CENTER
X=1030
Y=430
DynamicVariables=1
Hidden=(#IdxPkgPower#<>0)
Text=—

[ThmPkgS]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1030
Y=457
Text=PACKAGE

[ThmBatV]
Meter=String
MeterStyle=sValBig
StringAlign=CENTER
X=1176
Y=430
DynamicVariables=1
Hidden=((#IdxBattRate#=0) || ([&mBattRate] < 0))
Text=[mBattRate:1] W

[ThmBatVNeg]
Meter=String
MeterStyle=sValBig
FontColor=#Err#
StringAlign=CENTER
X=1176
Y=430
DynamicVariables=1
Hidden=((#IdxBattRate#=0) || ([&mBattRate] >= 0))
Text=[mBattRate:1] W

[ThmBatD]
Meter=String
MeterStyle=sValBig
FontColor=#Dim#
StringAlign=CENTER
X=1176
Y=430
DynamicVariables=1
Hidden=(#IdxBattRate#<>0)
Text=—

[ThmBatS]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1176
Y=457
Text=BATTERY

; src line per law 3 — show the mechanism

[Bat]
Meter=Shape
Shape=Rectangle 957,476,292,66,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[BatTitle]
Meter=Shape
Shape=Rectangle 958,477,290,20 | FillColor #Key# | StrokeWidth 0

[BatTitleT]
Meter=String
MeterStyle=sInk
StringAlign=CENTERCENTER
X=1085
Y=487
Text=BATTERY / ENERGY

[BatRst]
Meter=Shape
Shape=Rectangle 1210,479,34,16,2 | StrokeWidth 1 | Stroke Color #InkOnFill# | FillColor 0,0,0,1
LeftMouseUpAction=[!SetOption mEnergyWh Formula "0"][!UpdateMeasure mEnergyWh][!SetOption mEnergyWh Formula "mEnergyWh + (abs(mBattRate) / 3600)"][!CommandMeasure mLog "Add('OK','energy counter reset')"]

[BatRstT]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=6.75
StringAlign=CENTER
X=1227
Y=481
Text=RST

[BatLeftV]
Meter=String
MeterStyle=sVal
StringAlign=CENTER
X=1006
Y=502
DynamicVariables=1
Hidden=(#IdxBattLeft#=0)
Text=[mBattLeft:0] MIN

[BatLeftD]
Meter=String
MeterStyle=sVal
FontColor=#Dim#
StringAlign=CENTER
X=1006
Y=502
DynamicVariables=1
Hidden=(#IdxBattLeft#<>0)
Text=—

[BatLeftS]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1006
Y=525
Text=LEFT

[BatChgV]
Meter=String
MeterStyle=sVal
StringAlign=CENTER
X=1103
Y=502
DynamicVariables=1
Hidden=(#IdxBattPct#=0)
Text=[mBattPct:0]%

[BatChgD]
Meter=String
MeterStyle=sVal
FontColor=#Dim#
StringAlign=CENTER
X=1103
Y=502
DynamicVariables=1
Hidden=(#IdxBattPct#<>0)
Text=—

[BatChgS]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1103
Y=525
Text=CHARGE

[BatWhV]
Meter=String
MeterStyle=sVal
StringAlign=CENTER
X=1200
Y=502
DynamicVariables=1
Hidden=(#IdxBattRate#=0)
Text=[mEnergyWh:1]

[BatWhD]
Meter=String
MeterStyle=sVal
FontColor=#Dim#
StringAlign=CENTER
X=1200
Y=502
DynamicVariables=1
Hidden=(#IdxBattRate#<>0)
Text=—

[BatWhS]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1200
Y=525
Text=Wh USED

[Prf]
Meter=Shape
Shape=Rectangle 957,549,292,58,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[PrfTitle]
Meter=Shape
Shape=Rectangle 958,550,290,18 | FillColor #Key# | StrokeWidth 0

[PrfTitleT]
Meter=String
MeterStyle=sInk
StringAlign=CENTERCENTER
X=1103
Y=559
Text=PERFORMANCE MODE

; △ — driven by AHK hotkeys once wired (unofficial mechanism, law 4)

[PrfFrag]
Meter=String
MeterStyle=sBody
FontColor=#InkOnFill#
FontSize=8.25
X=1240
Y=552
Text=△

[Prf1Fill]
Meter=Shape
Shape=Rectangle 959,571,91,32 | FillColor #Key# | StrokeWidth 0
DynamicVariables=1
Hidden=(#PerfMode#<>0)
LeftMouseUpAction=[!SetVariable PerfMode 0][!WriteKeyValue Variables PerfMode 0 "#@#Variables.inc"][!CommandMeasure mLog "Add('WARN','perf mode SILENT commanded — not read back (AHK hookup pending)')"][!UpdateMeter *][!Redraw]

[Prf1Box]
Meter=Shape
Shape=Rectangle 959,571,91,32,2 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
DynamicVariables=1
Hidden=(#PerfMode#=0)
LeftMouseUpAction=[!SetVariable PerfMode 0][!WriteKeyValue Variables PerfMode 0 "#@#Variables.inc"][!CommandMeasure mLog "Add('WARN','perf mode SILENT commanded — not read back (AHK hookup pending)')"][!UpdateMeter *][!Redraw]

[Prf1NameOn]
Meter=String
MeterStyle=sInk
FontSize=9
StringAlign=CENTER
X=1004
Y=576
DynamicVariables=1
Hidden=(#PerfMode#<>0)
Text=SILENT

[Prf1NameOff]
Meter=String
MeterStyle=sBtn
FontColor=#Fg#
FontSize=9
StringAlign=CENTER
X=1004
Y=576
DynamicVariables=1
Hidden=(#PerfMode#=0)
Text=SILENT

[Prf1WOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
StringAlign=CENTER
X=1004
Y=592
DynamicVariables=1
Hidden=(#PerfMode#<>0)
Text=15 W

[Prf1WOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
StringAlign=CENTER
X=1004
Y=592
DynamicVariables=1
Hidden=(#PerfMode#=0)
Text=15 W

[Prf2Fill]
Meter=Shape
Shape=Rectangle 1056,571,91,32 | FillColor #Key# | StrokeWidth 0
DynamicVariables=1
Hidden=(#PerfMode#<>1)
LeftMouseUpAction=[!SetVariable PerfMode 1][!WriteKeyValue Variables PerfMode 1 "#@#Variables.inc"][!CommandMeasure mLog "Add('WARN','perf mode BALANCED commanded — not read back (AHK hookup pending)')"][!UpdateMeter *][!Redraw]

[Prf2Box]
Meter=Shape
Shape=Rectangle 1056,571,91,32,2 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
DynamicVariables=1
Hidden=(#PerfMode#=1)
LeftMouseUpAction=[!SetVariable PerfMode 1][!WriteKeyValue Variables PerfMode 1 "#@#Variables.inc"][!CommandMeasure mLog "Add('WARN','perf mode BALANCED commanded — not read back (AHK hookup pending)')"][!UpdateMeter *][!Redraw]

[Prf2NameOn]
Meter=String
MeterStyle=sInk
FontSize=9
StringAlign=CENTER
X=1101
Y=576
DynamicVariables=1
Hidden=(#PerfMode#<>1)
Text=BALANCED

[Prf2NameOff]
Meter=String
MeterStyle=sBtn
FontColor=#Fg#
FontSize=9
StringAlign=CENTER
X=1101
Y=576
DynamicVariables=1
Hidden=(#PerfMode#=1)
Text=BALANCED

[Prf2WOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
StringAlign=CENTER
X=1101
Y=592
DynamicVariables=1
Hidden=(#PerfMode#<>1)
Text=45 W

[Prf2WOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
StringAlign=CENTER
X=1101
Y=592
DynamicVariables=1
Hidden=(#PerfMode#=1)
Text=45 W

[Prf3Fill]
Meter=Shape
Shape=Rectangle 1153,571,91,32 | FillColor #Key# | StrokeWidth 0
DynamicVariables=1
Hidden=(#PerfMode#<>2)
LeftMouseUpAction=[!SetVariable PerfMode 2][!WriteKeyValue Variables PerfMode 2 "#@#Variables.inc"][!CommandMeasure mLog "Add('WARN','perf mode TURBO commanded — not read back (AHK hookup pending)')"][!UpdateMeter *][!Redraw]

[Prf3Box]
Meter=Shape
Shape=Rectangle 1153,571,91,32,2 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
DynamicVariables=1
Hidden=(#PerfMode#=2)
LeftMouseUpAction=[!SetVariable PerfMode 2][!WriteKeyValue Variables PerfMode 2 "#@#Variables.inc"][!CommandMeasure mLog "Add('WARN','perf mode TURBO commanded — not read back (AHK hookup pending)')"][!UpdateMeter *][!Redraw]

[Prf3NameOn]
Meter=String
MeterStyle=sInk
FontSize=9
StringAlign=CENTER
X=1198
Y=576
DynamicVariables=1
Hidden=(#PerfMode#<>2)
Text=TURBO

[Prf3NameOff]
Meter=String
MeterStyle=sBtn
FontColor=#Fg#
FontSize=9
StringAlign=CENTER
X=1198
Y=576
DynamicVariables=1
Hidden=(#PerfMode#=2)
Text=TURBO

[Prf3WOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
StringAlign=CENTER
X=1198
Y=592
DynamicVariables=1
Hidden=(#PerfMode#<>2)
Text=80 W

[Prf3WOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
StringAlign=CENTER
X=1198
Y=592
DynamicVariables=1
Hidden=(#PerfMode#=2)
Text=80 W
