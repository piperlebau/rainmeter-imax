; Rail.inc — W12a workspace tab rail (5 tabs), Milestone B: taps switch
; and persist the workspace; active tab is inverse-filled. WS4 (WRITE)
; swaps the launch bay for the Editor child skin.

[Ws1Fill]
Meter=Shape
Shape=Rectangle 50,700,231,74,3 | FillColor #Key# | StrokeWidth 0
Hidden=(#Workspace#<>1)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 1][!WriteKeyValue Variables Workspace 1 "#@#Variables.inc"][!SetVariable WSMode apps][!WriteKeyValue Variables WSMode apps "#@#Variables.inc"][!DeactivateConfig "#ROOTCONFIG#\Editor"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → DEV')"][!UpdateMeter *][!Redraw]

[Ws1Box]
Meter=Shape
Shape=Rectangle 50,700,231,74,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=(#Workspace#=1)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 1][!WriteKeyValue Variables Workspace 1 "#@#Variables.inc"][!SetVariable WSMode apps][!WriteKeyValue Variables WSMode apps "#@#Variables.inc"][!DeactivateConfig "#ROOTCONFIG#\Editor"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → DEV')"][!UpdateMeter *][!Redraw]

[Ws1NumOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=7.5
X=66
Y=710
DynamicVariables=1
Hidden=(#Workspace#<>1)
Text=01

[Ws1NumOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=7.5
X=66
Y=710
DynamicVariables=1
Hidden=(#Workspace#=1)
Text=01

[Ws1NameOn]
Meter=String
MeterStyle=sBtn
FontColor=#InkOnFill#
FontSize=15
StringAlign=CENTER
X=165
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#<>1)
Text=DEV

[Ws1NameOff]
Meter=String
MeterStyle=sBtn
FontColor=#Str#
FontSize=15
StringAlign=CENTER
X=165
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#=1)
Text=DEV

[Ws1SubOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=6.75
StringAlign=CENTER
X=165
Y=754
DynamicVariables=1
Hidden=(#Workspace#<>1)
Text=6 APPS

[Ws1SubOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=6.75
StringAlign=CENTER
X=165
Y=754
DynamicVariables=1
Hidden=(#Workspace#=1)
Text=6 APPS

[Ws2Fill]
Meter=Shape
Shape=Rectangle 292,700,231,74,3 | FillColor #Key# | StrokeWidth 0
Hidden=(#Workspace#<>2)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 2][!WriteKeyValue Variables Workspace 2 "#@#Variables.inc"][!SetVariable WSMode apps][!WriteKeyValue Variables WSMode apps "#@#Variables.inc"][!DeactivateConfig "#ROOTCONFIG#\Editor"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → MEDIA')"][!UpdateMeter *][!Redraw]

[Ws2Box]
Meter=Shape
Shape=Rectangle 292,700,231,74,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=(#Workspace#=2)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 2][!WriteKeyValue Variables Workspace 2 "#@#Variables.inc"][!SetVariable WSMode apps][!WriteKeyValue Variables WSMode apps "#@#Variables.inc"][!DeactivateConfig "#ROOTCONFIG#\Editor"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → MEDIA')"][!UpdateMeter *][!Redraw]

[Ws2NumOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=7.5
X=308
Y=710
DynamicVariables=1
Hidden=(#Workspace#<>2)
Text=02

[Ws2NumOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=7.5
X=308
Y=710
DynamicVariables=1
Hidden=(#Workspace#=2)
Text=02

[Ws2NameOn]
Meter=String
MeterStyle=sBtn
FontColor=#InkOnFill#
FontSize=15
StringAlign=CENTER
X=407
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#<>2)
Text=MEDIA

[Ws2NameOff]
Meter=String
MeterStyle=sBtn
FontColor=#Str#
FontSize=15
StringAlign=CENTER
X=407
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#=2)
Text=MEDIA

[Ws2SubOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=6.75
StringAlign=CENTER
X=407
Y=754
DynamicVariables=1
Hidden=(#Workspace#<>2)
Text=5 APPS

[Ws2SubOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=6.75
StringAlign=CENTER
X=407
Y=754
DynamicVariables=1
Hidden=(#Workspace#=2)
Text=5 APPS

[Ws3Fill]
Meter=Shape
Shape=Rectangle 534,700,231,74,3 | FillColor #Key# | StrokeWidth 0
Hidden=(#Workspace#<>3)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 3][!WriteKeyValue Variables Workspace 3 "#@#Variables.inc"][!SetVariable WSMode apps][!WriteKeyValue Variables WSMode apps "#@#Variables.inc"][!DeactivateConfig "#ROOTCONFIG#\Editor"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → GAME')"][!UpdateMeter *][!Redraw]

[Ws3Box]
Meter=Shape
Shape=Rectangle 534,700,231,74,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=(#Workspace#=3)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 3][!WriteKeyValue Variables Workspace 3 "#@#Variables.inc"][!SetVariable WSMode apps][!WriteKeyValue Variables WSMode apps "#@#Variables.inc"][!DeactivateConfig "#ROOTCONFIG#\Editor"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → GAME')"][!UpdateMeter *][!Redraw]

[Ws3NumOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=7.5
X=550
Y=710
DynamicVariables=1
Hidden=(#Workspace#<>3)
Text=03

[Ws3NumOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=7.5
X=550
Y=710
DynamicVariables=1
Hidden=(#Workspace#=3)
Text=03

[Ws3NameOn]
Meter=String
MeterStyle=sBtn
FontColor=#InkOnFill#
FontSize=15
StringAlign=CENTER
X=649
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#<>3)
Text=GAME

[Ws3NameOff]
Meter=String
MeterStyle=sBtn
FontColor=#Str#
FontSize=15
StringAlign=CENTER
X=649
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#=3)
Text=GAME

[Ws3SubOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=6.75
StringAlign=CENTER
X=649
Y=754
DynamicVariables=1
Hidden=(#Workspace#<>3)
Text=6 APPS

[Ws3SubOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=6.75
StringAlign=CENTER
X=649
Y=754
DynamicVariables=1
Hidden=(#Workspace#=3)
Text=6 APPS

[Ws4Fill]
Meter=Shape
Shape=Rectangle 776,700,231,74,3 | FillColor #Key# | StrokeWidth 0
Hidden=(#Workspace#<>4)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 4][!WriteKeyValue Variables Workspace 4 "#@#Variables.inc"][!SetVariable WSMode editor][!WriteKeyValue Variables WSMode editor "#@#Variables.inc"][!ActivateConfig "#ROOTCONFIG#\Editor" "Editor.ini"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → WRITE')"][!UpdateMeter *][!Redraw]

[Ws4Box]
Meter=Shape
Shape=Rectangle 776,700,231,74,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=(#Workspace#=4)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 4][!WriteKeyValue Variables Workspace 4 "#@#Variables.inc"][!SetVariable WSMode editor][!WriteKeyValue Variables WSMode editor "#@#Variables.inc"][!ActivateConfig "#ROOTCONFIG#\Editor" "Editor.ini"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → WRITE')"][!UpdateMeter *][!Redraw]

[Ws4NumOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=7.5
X=792
Y=710
DynamicVariables=1
Hidden=(#Workspace#<>4)
Text=04

[Ws4NumOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=7.5
X=792
Y=710
DynamicVariables=1
Hidden=(#Workspace#=4)
Text=04

[Ws4NameOn]
Meter=String
MeterStyle=sBtn
FontColor=#InkOnFill#
FontSize=15
StringAlign=CENTER
X=891
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#<>4)
Text=WRITE

[Ws4NameOff]
Meter=String
MeterStyle=sBtn
FontColor=#Str#
FontSize=15
StringAlign=CENTER
X=891
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#=4)
Text=WRITE

[Ws4SubOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=6.75
StringAlign=CENTER
X=891
Y=754
DynamicVariables=1
Hidden=(#Workspace#<>4)
Text=EDITOR

[Ws4SubOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=6.75
StringAlign=CENTER
X=891
Y=754
DynamicVariables=1
Hidden=(#Workspace#=4)
Text=EDITOR

[Ws5Fill]
Meter=Shape
Shape=Rectangle 1018,700,231,74,3 | FillColor #Key# | StrokeWidth 0
Hidden=(#Workspace#<>5)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 5][!WriteKeyValue Variables Workspace 5 "#@#Variables.inc"][!SetVariable WSMode apps][!WriteKeyValue Variables WSMode apps "#@#Variables.inc"][!DeactivateConfig "#ROOTCONFIG#\Editor"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → DIAG')"][!UpdateMeter *][!Redraw]

[Ws5Box]
Meter=Shape
Shape=Rectangle 1018,700,231,74,3 | StrokeWidth 1 | Stroke Color #Frame# | FillColor 0,0,0,1
Hidden=(#Workspace#=5)
DynamicVariables=1
LeftMouseUpAction=[!SetVariable Workspace 5][!WriteKeyValue Variables Workspace 5 "#@#Variables.inc"][!SetVariable WSMode apps][!WriteKeyValue Variables WSMode apps "#@#Variables.inc"][!DeactivateConfig "#ROOTCONFIG#\Editor"][!UpdateMeasure mMode][!UpdateMeasure mWorkspace][!UpdateMeasure mBayPath][!CommandMeasure mLog "Add('OK','workspace → DIAG')"][!UpdateMeter *][!Redraw]

[Ws5NumOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=7.5
X=1034
Y=710
DynamicVariables=1
Hidden=(#Workspace#<>5)
Text=05

[Ws5NumOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=7.5
X=1034
Y=710
DynamicVariables=1
Hidden=(#Workspace#=5)
Text=05

[Ws5NameOn]
Meter=String
MeterStyle=sBtn
FontColor=#InkOnFill#
FontSize=15
StringAlign=CENTER
X=1133
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#<>5)
Text=DIAG

[Ws5NameOff]
Meter=String
MeterStyle=sBtn
FontColor=#Str#
FontSize=15
StringAlign=CENTER
X=1133
Y=730
DynamicVariables=1
StringStyle=BOLD
Hidden=(#Workspace#=5)
Text=DIAG

[Ws5SubOn]
Meter=String
MeterStyle=sSub
FontColor=#InkOnFill#
FontSize=6.75
StringAlign=CENTER
X=1133
Y=754
DynamicVariables=1
Hidden=(#Workspace#<>5)
Text=6 APPS

[Ws5SubOff]
Meter=String
MeterStyle=sSub
FontColor=#Dim#
FontSize=6.75
StringAlign=CENTER
X=1133
Y=754
DynamicVariables=1
Hidden=(#Workspace#=5)
Text=6 APPS
