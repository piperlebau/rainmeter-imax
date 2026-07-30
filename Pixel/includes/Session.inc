; Session.inc — W2 SESSION INFORMATION, W3 STATUS strip, W4 UPTIME strip (v21)

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
Text=DEV / ODYSSEY

[StatusFill]
Meter=Shape
Shape=Rectangle 50,346,894,24 | FillColor #Ok# | StrokeWidth 0

[StatusTxt]
Meter=String
MeterStyle=sInk
X=64
Y=350
Text=STATUS: AUTO MODE      ALL PRESETS NOMINAL

[UptimeBox]
Meter=Shape
Shape=Rectangle 50,379,894,26,2 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[UptimeTxt]
Meter=String
MeterStyle=sBody
FontColor=#Fg#
X=64
Y=384
Text=UPTIME 0004:12 (HH:MM)      DATE 07/30/26      TIME 04:14:44
