; Session.inc — W2 SESSION INFORMATION, W3 STATUS strip (live severity),
;               W4 UPTIME/DATE/TIME strip (live). Milestone B.

[SessFrame]
Meter=Shape
Shape=Rectangle 50,287,894,50,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[SessCap]
Meter=String
MeterStyle=sCap
X=(50+12)
Y=(287-7)
Text=SESSION INFORMATION

[SessHostK]
Meter=String
MeterStyle=sKey
X=64
Y=296
Text=HOST:

[SessHostV]
Meter=String
MeterStyle=sBody
FontColor=#Str#
X=180
Y=296
Text=FLOW-Z13 · GZ302EA

[SessProfK]
Meter=String
MeterStyle=sKey
X=64
Y=316
Text=PROFILE:

[SessProfV]
Meter=String
MeterStyle=sBody
FontColor=#Str#
X=180
Y=316
DynamicVariables=1
Text=[#WSName[#Workspace]] / ODYSSEY

; W3 — fill colour IS the severity (design law 2); logic\status.inc
; owns #SevColor#/#StatusMsg#.

[StatusFill]
Meter=Shape
Shape=Rectangle 50,346,894,24 | FillColor #SevColor# | StrokeWidth 0
DynamicVariables=1

[StatusTxt]
Meter=String
MeterStyle=sInk
X=64
Y=350
DynamicVariables=1
W=870
H=17
Text=#StatusMsg#

[UptimeBox]
Meter=Shape
Shape=Rectangle 50,379,894,26,2 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[UptimeTxt]
Meter=String
MeterStyle=sBody
FontColor=#Fg#
X=64
Y=384
DynamicVariables=1
Text=UPTIME [mUptime] (HH:MM)      DATE [mDate]      TIME [mTime]
