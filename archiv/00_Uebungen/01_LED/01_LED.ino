/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Lasse eine LED blinken - EIN - AUS - EIN - AUS - ...... 
Versuche dies zu programmieren und wenn es funktioniert, 
kannst du es noch schneller oder langsamer blinken lassen?

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang) 
digitalWrite (PIN, HIGH oder LOW); <- schaltet etwas EIN (HIGH) oder AUS (LOW) - PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), dann HIGH oder LOW
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
*/

void setup() // Hier beginnt das Setup
{ 
//TODO: Definiere den PIN (an dem die LED angeschlossen ist) als Ausgang. PIN mit der Zahl für die LED ersetzen (ohne D), OUTPUT oder INPUT entscheiden
pinMode(PIN, OUTPUT oder INPUT); 

} // Hier endet ein Programmabschnitt

void loop() // Hier beginnt das Hauptprogramm
{ 
//TODO: schalte eine LED ein

//TODO: warte 1 Sekunde //TEST: Verändere die Zeit - was passiert?

//TODO: schalte die LED wieder aus

//TODO: warte 1 Sekunde //TEST: Verändere die Zeit - was passiert?

  
} // Hier endet ein Programmabschnitt

