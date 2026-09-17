/* Befehle:
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN, OUTPUT gibt Strom und INPUT misst den Strom am PIN, PIN mit der Zahl auf dem SensorKit ersetzen (ohne D)
digitalWrite (PIN, HIGH oder LOW); <- schaltet etwas EIN (HIGH) oder AUS (LOW) - PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), dann HIGH oder LOW
delay(ZEIT); <- macht eine Pause mit der ZEIT in millisekunden
*/

void setup() // Hier beginnt das Setup
{ 

//TODO: Definiere den PIN (an dem die LED angeschlossen ist) als Ausgang. XX mit der Zahl für die LED ersetzen (ohne D), YY mit OUTPUT oder INPUT ersetzen
pinMode(6, OUTPUT); 

} // Hier endet ein Programmabschnitt

void loop() // Hier beginnt das Hauptprogramm
{ 
//TODO: schalte eine LED ein
digitalWrite(6, HIGH);
//TODO: warte 1 Sekunde //TEST: Verändere die Zeit - was passiert?
delay(1000);
//TODO: schalte die LED wieder aus
digitalWrite(6, LOW);
//TODO: warte 1 Sekunde //TEST: Verändere die Zeit - was passiert?
delay(1000);
  
} // Hier endet ein Programmabschnitt

