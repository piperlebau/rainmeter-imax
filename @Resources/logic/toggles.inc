; ============================================================
;  logic\toggles.inc — reads the poller file. SHARED.
;  sensors.ps1 writes all five states + a timestamp every 5s
;  (§9.4). Rainmeter only READS here — never poll per-row.
; ============================================================

[mPollerFile]
Measure=Plugin
Plugin=Quote
PathName=#@#Scripts\state.txt
Separator=|
; file format: wifi=1|bluetooth=0|mute=0|nightlight=1|rotationlock=0|ts=…
UpdateDivider=5
DynamicVariables=1

; One measure per toggle. Names are the shared API (§17.6).
[mTogWifi]
Measure=String
String=[mPollerFile]
RegExpSubstitute=1
Substitute="^.*wifi=(\d).*$":"\1"
DynamicVariables=1

[mTogBluetooth]
Measure=String
String=[mPollerFile]
RegExpSubstitute=1
Substitute="^.*bluetooth=(\d).*$":"\1"
DynamicVariables=1

[mTogMute]
Measure=String
String=[mPollerFile]
RegExpSubstitute=1
Substitute="^.*mute=(\d).*$":"\1"
DynamicVariables=1

[mTogNightLight]
Measure=String
String=[mPollerFile]
RegExpSubstitute=1
Substitute="^.*nightlight=(\d).*$":"\1"
DynamicVariables=1

[mTogRotationLock]
Measure=String
String=[mPollerFile]
RegExpSubstitute=1
Substitute="^.*rotationlock=(\d).*$":"\1"
DynamicVariables=1
