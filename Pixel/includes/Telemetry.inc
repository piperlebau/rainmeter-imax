; Telemetry.inc — right column: W8 TOGGLES, W13 SUBSYSTEM LOAD, W9/10 THERMAL/POWER,
;                  W14 BATTERY/ENERGY, W16 PERFORMANCE MODE. Static values (A1).

[TogFrame]
Meter=Shape
Shape=Rectangle 957,129,292,122,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[TogCap]
Meter=String
MeterStyle=sCap
X=(957+12)
Y=(129-7)
Text=TOGGLES

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

[Sub1Bar]
Meter=Shape
Shape=Rectangle 1015.0,278,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape2=Rectangle 1027.86,278,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape3=Rectangle 1040.72,278,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape4=Rectangle 1053.58,278,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape5=Rectangle 1066.44,278,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape6=Rectangle 1079.3,278,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape7=Rectangle 1092.16,278,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape8=Rectangle 1105.02,278,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape9=Rectangle 1117.88,278,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape10=Rectangle 1130.74,278,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape11=Rectangle 1143.6,278,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape12=Rectangle 1156.46,278,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape13=Rectangle 1169.32,278,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape14=Rectangle 1182.18,278,10.86,11 | FillColor #Faint# | StrokeWidth 0

[Sub1Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=275
Text=36%

[Sub2Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=291
Text=IGPU

[Sub2Bar]
Meter=Shape
Shape=Rectangle 1015.0,294,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape2=Rectangle 1027.86,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape3=Rectangle 1040.72,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape4=Rectangle 1053.58,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape5=Rectangle 1066.44,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape6=Rectangle 1079.3,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape7=Rectangle 1092.16,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape8=Rectangle 1105.02,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape9=Rectangle 1117.88,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape10=Rectangle 1130.74,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape11=Rectangle 1143.6,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape12=Rectangle 1156.46,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape13=Rectangle 1169.32,294,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape14=Rectangle 1182.18,294,10.86,11 | FillColor #Faint# | StrokeWidth 0

[Sub2Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=291
Text=7%

[Sub3Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=307
Text=RAM

[Sub3Bar]
Meter=Shape
Shape=Rectangle 1015.0,310,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape2=Rectangle 1027.86,310,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape3=Rectangle 1040.72,310,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape4=Rectangle 1053.58,310,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape5=Rectangle 1066.44,310,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape6=Rectangle 1079.3,310,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape7=Rectangle 1092.16,310,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape8=Rectangle 1105.02,310,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape9=Rectangle 1117.88,310,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape10=Rectangle 1130.74,310,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape11=Rectangle 1143.6,310,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape12=Rectangle 1156.46,310,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape13=Rectangle 1169.32,310,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape14=Rectangle 1182.18,310,10.86,11 | FillColor #Faint# | StrokeWidth 0

[Sub3Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=307
Text=55%

[Sub4Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=323
Text=VRAM

[Sub4Bar]
Meter=Shape
Shape=Rectangle 1015.0,326,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape2=Rectangle 1027.86,326,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape3=Rectangle 1040.72,326,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape4=Rectangle 1053.58,326,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape5=Rectangle 1066.44,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape6=Rectangle 1079.3,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape7=Rectangle 1092.16,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape8=Rectangle 1105.02,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape9=Rectangle 1117.88,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape10=Rectangle 1130.74,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape11=Rectangle 1143.6,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape12=Rectangle 1156.46,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape13=Rectangle 1169.32,326,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape14=Rectangle 1182.18,326,10.86,11 | FillColor #Faint# | StrokeWidth 0

[Sub4Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=323
Text=28%

[Sub5Lbl]
Meter=String
MeterStyle=sKey
FontSize=7.5
X=970
Y=339
Text=DISK

[Sub5Bar]
Meter=Shape
Shape=Rectangle 1015.0,342,10.86,11 | FillColor #Ok# | StrokeWidth 0
Shape2=Rectangle 1027.86,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape3=Rectangle 1040.72,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape4=Rectangle 1053.58,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape5=Rectangle 1066.44,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape6=Rectangle 1079.3,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape7=Rectangle 1092.16,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape8=Rectangle 1105.02,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape9=Rectangle 1117.88,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape10=Rectangle 1130.74,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape11=Rectangle 1143.6,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape12=Rectangle 1156.46,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape13=Rectangle 1169.32,342,10.86,11 | FillColor #Faint# | StrokeWidth 0
Shape14=Rectangle 1182.18,342,10.86,11 | FillColor #Faint# | StrokeWidth 0

[Sub5Pct]
Meter=String
MeterStyle=sBody
FontColor=#Num#
FontSize=7.5
StringAlign=RIGHT
X=1240
Y=339
Text=9%

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

[Thm0V]
Meter=String
MeterStyle=sValBig
StringAlign=CENTER
X=1030
Y=392
Text=61°C

[Thm0S]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1030
Y=419
Text=CPU TCTL

[Thm1V]
Meter=String
MeterStyle=sValBig
StringAlign=CENTER
X=1176
Y=392
Text=54°C

[Thm1S]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1176
Y=419
Text=IGPU

[Thm2V]
Meter=String
MeterStyle=sValBig
StringAlign=CENTER
X=1030
Y=430
Text=41.0 W

[Thm2S]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1030
Y=457
Text=PACKAGE

[Thm3V]
Meter=String
MeterStyle=sValBig
StringAlign=CENTER
X=1176
Y=430
Text=-18.2 W

[Thm3S]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1176
Y=457
Text=BATTERY

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

[BatRstT]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=6.75
StringAlign=CENTER
X=1227
Y=481
Text=RST

[Bat0V]
Meter=String
MeterStyle=sVal
StringAlign=CENTER
X=1006
Y=502
Text=3:42

[Bat0S]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1006
Y=525
Text=LEFT

[Bat1V]
Meter=String
MeterStyle=sVal
StringAlign=CENTER
X=1103
Y=502
Text=68%

[Bat1S]
Meter=String
MeterStyle=sSub
StringAlign=CENTER
X=1103
Y=525
Text=CHARGE

[Bat2V]
Meter=String
MeterStyle=sVal
StringAlign=CENTER
X=1200
Y=502
Text=14.6

[Bat2S]
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

[Prf1Box]
Meter=Shape
Shape=Rectangle 959,571,91,32,2 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[Prf1Name]
Meter=String
MeterStyle=sBtn
FontColor=#Fg#
FontSize=9
StringAlign=CENTER
X=1004
Y=576
Text=SILENT

[Prf1W]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
StringAlign=CENTER
X=1004
Y=592
Text=15 W

[Prf2Fill]
Meter=Shape
Shape=Rectangle 1056,571,91,32 | FillColor #Key# | StrokeWidth 0

[Prf2Name]
Meter=String
MeterStyle=sInk
FontColor=#InkOnFill#
FontSize=9
StringAlign=CENTER
X=1101
Y=576
Text=BALANCED

[Prf2W]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
StringAlign=CENTER
X=1101
Y=592
Text=45 W

[Prf3Box]
Meter=Shape
Shape=Rectangle 1153,571,91,32,2 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[Prf3Name]
Meter=String
MeterStyle=sBtn
FontColor=#Fg#
FontSize=9
StringAlign=CENTER
X=1198
Y=576
Text=TURBO

[Prf3W]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
StringAlign=CENTER
X=1198
Y=592
Text=80 W
