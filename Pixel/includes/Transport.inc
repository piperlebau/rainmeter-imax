; Transport.inc — W5 RUN / JOG / STOP primary transport (>=44px).

[Tr1Fill]
Meter=Shape
Shape=Rectangle 957,614,90,76,3 | FillColor #Key# | StrokeWidth 0

[Tr1Name]
Meter=String
MeterStyle=sInk
FontColor=#InkOnFill#
FontSize=18
StringAlign=CENTER
X=1002
Y=636
StringStyle=BOLD
Text=RUN

[Tr1Sub]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
StringAlign=CENTER
X=1002
Y=664
Text=PLAY / PAUSE

; RUN tap

[Tr2Box]
Meter=Shape
Shape=Rectangle 1057,614,90,76,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[Tr2Name]
Meter=String
MeterStyle=sBtn
FontColor=#Fg#
FontSize=18
StringAlign=CENTER
X=1102
Y=636
StringStyle=BOLD
Text=JOG

[Tr2Sub]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
StringAlign=CENTER
X=1102
Y=664
Text=NEXT

; JOG tap

[Tr3Box]
Meter=Shape
Shape=Rectangle 1157,614,90,76,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[Tr3Name]
Meter=String
MeterStyle=sBtn
FontColor=#Fg#
FontSize=18
StringAlign=CENTER
X=1202
Y=636
StringStyle=BOLD
Text=STOP

[Tr3Sub]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
StringAlign=CENTER
X=1202
Y=664
Text=HALT

; STOP tap
