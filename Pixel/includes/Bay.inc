; Bay.inc — W11 LAUNCH BAY, Milestone B: slots are populated from the
; active workspace folder (@Resources\Workspaces\WS<N>\*.url) via the
; FileView children in logic\workspace.inc; a tap runs the shortcut.
; The whole group hides in editor mode (WS4) and an EDITOR frame of
; IDENTICAL geometry swaps in (constraint 3: both panes 230px).
; NOTE: FileView is a third-party plugin — bundle it in the .rmskin.

[BayFrame]
Meter=Shape
Group=Bay
Shape=Rectangle 50,414,894,230,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=#PaneIsEditor#
DynamicVariables=1

[BayCap]
Meter=String
MeterStyle=sCap
X=62
Y=407
DynamicVariables=1
Group=Bay
Hidden=#PaneIsEditor#
Text=LAUNCH BAY

; editor-mode frame (the Editor child skin renders inside it)
[EdFrame]
Meter=Shape
Shape=Rectangle 50,414,894,230,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=(#PaneIsEditor#=0)
DynamicVariables=1

[EdCap]
Meter=String
MeterStyle=sCap
X=62
Y=407
DynamicVariables=1
Hidden=(#PaneIsEditor#=0)
Text=EDITOR

[Bay1Box]
Meter=Shape
Group=Bay
Shape=Rectangle 63,431,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=#PaneIsEditor#
DynamicVariables=1
LeftMouseUpAction=["[&mBayGo1]"]

[Bay1Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=79
Y=443
Group=Bay
DynamicVariables=1
Hidden=#PaneIsEditor#
Text=01

[Bay1App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=12.75
X=79
Y=461
Group=Bay
DynamicVariables=1
StringStyle=BOLD
W=251
H=24
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayName1]

[Bay1Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=8.25
X=79
Y=495
Group=Bay
DynamicVariables=1
W=251
H=16
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayFile1]

[Bay2Box]
Meter=Shape
Group=Bay
Shape=Rectangle 356,431,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=#PaneIsEditor#
DynamicVariables=1
LeftMouseUpAction=["[&mBayGo2]"]

[Bay2Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=372
Y=443
Group=Bay
DynamicVariables=1
Hidden=#PaneIsEditor#
Text=02

[Bay2App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=12.75
X=372
Y=461
Group=Bay
DynamicVariables=1
StringStyle=BOLD
W=251
H=24
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayName2]

[Bay2Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=8.25
X=372
Y=495
Group=Bay
DynamicVariables=1
W=251
H=16
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayFile2]

[Bay3Box]
Meter=Shape
Group=Bay
Shape=Rectangle 648,431,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=#PaneIsEditor#
DynamicVariables=1
LeftMouseUpAction=["[&mBayGo3]"]

[Bay3Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=664
Y=443
Group=Bay
DynamicVariables=1
Hidden=#PaneIsEditor#
Text=03

[Bay3App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=12.75
X=664
Y=461
Group=Bay
DynamicVariables=1
StringStyle=BOLD
W=251
H=24
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayName3]

[Bay3Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=8.25
X=664
Y=495
Group=Bay
DynamicVariables=1
W=251
H=16
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayFile3]

[Bay4Box]
Meter=Shape
Group=Bay
Shape=Rectangle 63,537,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=#PaneIsEditor#
DynamicVariables=1
LeftMouseUpAction=["[&mBayGo4]"]

[Bay4Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=79
Y=549
Group=Bay
DynamicVariables=1
Hidden=#PaneIsEditor#
Text=04

[Bay4App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=12.75
X=79
Y=567
Group=Bay
DynamicVariables=1
StringStyle=BOLD
W=251
H=24
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayName4]

[Bay4Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=8.25
X=79
Y=601
Group=Bay
DynamicVariables=1
W=251
H=16
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayFile4]

[Bay5Box]
Meter=Shape
Group=Bay
Shape=Rectangle 356,537,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=#PaneIsEditor#
DynamicVariables=1
LeftMouseUpAction=["[&mBayGo5]"]

[Bay5Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=372
Y=549
Group=Bay
DynamicVariables=1
Hidden=#PaneIsEditor#
Text=05

[Bay5App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=12.75
X=372
Y=567
Group=Bay
DynamicVariables=1
StringStyle=BOLD
W=251
H=24
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayName5]

[Bay5Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=8.25
X=372
Y=601
Group=Bay
DynamicVariables=1
W=251
H=16
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayFile5]

[Bay6Box]
Meter=Shape
Group=Bay
Shape=Rectangle 648,537,283,96,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=#PaneIsEditor#
DynamicVariables=1
LeftMouseUpAction=["[&mBayGo6]"]

[Bay6Num]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
X=664
Y=549
Group=Bay
DynamicVariables=1
Hidden=#PaneIsEditor#
Text=06

[Bay6App]
Meter=String
MeterStyle=sBody
FontColor=#Str#
FontSize=12.75
X=664
Y=567
Group=Bay
DynamicVariables=1
StringStyle=BOLD
W=251
H=24
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayName6]

[Bay6Exe]
Meter=String
MeterStyle=sBody
FontColor=#Path#
FontSize=8.25
X=664
Y=601
Group=Bay
DynamicVariables=1
W=251
H=16
ClipString=1
Hidden=#PaneIsEditor#
Text=[mBayFile6]
