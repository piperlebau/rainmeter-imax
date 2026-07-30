; Bay.inc — W11 LAUNCH BAY (swaps with W18 editor; both 230px). DEV workspace, static (A1).
; Group=Bay so B can hide/show it against WSMode.

[BayFrame]
Meter=Shape
Shape=Rectangle 50,414,894,230,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1

[BayCap]
Meter=String
MeterStyle=sCap
X=(50+12)
Y=(414-7)
Text=LAUNCH BAY

[Bay1Box]
Meter=Shape
Group=Bay
Shape=Rectangle 63,431,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
LeftMouseUpAction=[!Log "launch 01 VS CODE"]

[Bay1Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=79
Y=443
Group=Bay
Text=01

[Bay1App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=17
X=79
Y=461
Group=Bay
StringStyle=BOLD
Text=VS CODE

[Bay1Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=11
X=79
Y=495
Group=Bay
Text=Code.exe

[Bay2Box]
Meter=Shape
Group=Bay
Shape=Rectangle 356,431,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
LeftMouseUpAction=[!Log "launch 02 TERMINAL"]

[Bay2Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=372
Y=443
Group=Bay
Text=02

[Bay2App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=17
X=372
Y=461
Group=Bay
StringStyle=BOLD
Text=TERMINAL

[Bay2Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=11
X=372
Y=495
Group=Bay
Text=wt.exe

[Bay3Box]
Meter=Shape
Group=Bay
Shape=Rectangle 648,431,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
LeftMouseUpAction=[!Log "launch 03 GITHUB DESKTOP"]

[Bay3Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=664
Y=443
Group=Bay
Text=03

[Bay3App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=17
X=664
Y=461
Group=Bay
StringStyle=BOLD
Text=GITHUB DESKTOP

[Bay3Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=11
X=664
Y=495
Group=Bay
Text=GitHubDesktop.exe

[Bay4Box]
Meter=Shape
Group=Bay
Shape=Rectangle 63,537,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
LeftMouseUpAction=[!Log "launch 04 DOCKER"]

[Bay4Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=79
Y=549
Group=Bay
Text=04

[Bay4App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=17
X=79
Y=567
Group=Bay
StringStyle=BOLD
Text=DOCKER

[Bay4Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=11
X=79
Y=601
Group=Bay
Text=Docker Desktop.exe

[Bay5Box]
Meter=Shape
Group=Bay
Shape=Rectangle 356,537,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
LeftMouseUpAction=[!Log "launch 05 POSTMAN"]

[Bay5Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=372
Y=549
Group=Bay
Text=05

[Bay5App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=17
X=372
Y=567
Group=Bay
StringStyle=BOLD
Text=POSTMAN

[Bay5Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=11
X=372
Y=601
Group=Bay
Text=Postman.exe

[Bay6Box]
Meter=Shape
Group=Bay
Shape=Rectangle 648,537,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
LeftMouseUpAction=[!Log "launch 06 FIREFOX DEV"]

[Bay6Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=664
Y=549
Group=Bay
Text=06

[Bay6App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=17
X=664
Y=567
Group=Bay
StringStyle=BOLD
Text=FIREFOX DEV

[Bay6Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=11
X=664
Y=601
Group=Bay
Text=firefox.exe -P dev
