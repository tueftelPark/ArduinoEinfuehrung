/* 
>> Was soll passieren? <<
Du lässt eine LED blinken: an - aus - an - aus - immer weiter.
Wenn es klappt: Kannst du sie schneller oder langsamer blinken lassen?

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- Sagt dem Arduino: Ist an diesem PIN etwas, das AUSGIBT (OUTPUT, z.B. eine LED) oder etwas, das MISST (INPUT, z.B. ein Sensor)? PIN ist die Zahl auf dem SensorKit, ohne das "D" davor.
digitalWrite(PIN, HIGH oder LOW); <- Schaltet etwas EIN (HIGH) oder AUS (LOW).
delay(ZEIT); <- Macht eine Pause. ZEIT ist die Zeit in Millisekunden (1000 = 1 Sekunde).
*/

void setup()
{ 
//TODO: Definiere den PIN, an dem die LED angeschlossen ist, als Ausgang. Auf deinem SensorKit ist die LED an PIN 6. Ersetze PIN mit dieser Zahl und entscheide: OUTPUT oder INPUT?
//EXPECT: ^6$
//EXPECT: ^OUTPUT$
pinMode(PIN, OUTPUT oder INPUT); 

} 

void loop()
{ 
//TODO: Schalte die LED ein
//EXPECT: ^digitalWrite\s*\(\s*6\s*,\s*HIGH\s*\)\s*;$

//TODO: Warte 1 Sekunde //TEST: Verändere die Zeit - was passiert?
//EXPECT: ^delay\s*\(\s*\d+\s*\)\s*;$

//TODO: Schalte die LED wieder aus
//EXPECT: ^digitalWrite\s*\(\s*6\s*,\s*LOW\s*\)\s*;$

//TODO: Warte 1 Sekunde //TEST: Verändere die Zeit - was passiert?
//EXPECT: ^delay\s*\(\s*\d+\s*\)\s*;$

} 
