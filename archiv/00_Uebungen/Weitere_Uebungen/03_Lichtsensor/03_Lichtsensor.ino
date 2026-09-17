/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Siehst du den Lichtsensor auf dem Sensor-Kit? Er ist mit A3 Light beschriftet.
Wenn es dunkel wird, dann soll das Licht angehen. Nutze dazu diesen Lichtsensor und die LED.

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang)
ZAHL = analogRead(PIN); <- Zahlenwert wird am PIN gemessen. Dieser Wert wird unter der Variable "ZAHL" gespeichert.
digitalWrite (PIN, HIGH oder LOW); <- schaltet etwas EIN (HIGH) oder AUS (LOW) - PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), dann HIGH oder LOW
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
*/


//TODO: Welche PIN Nummer hat die LED -> schaue dazu auf dem Sensor-Kit und ersetze unten das ? mit der Nummer (ohne das D)
int LED = ?; //Hier speichern wir eine Zahl (der PIN von unserer LED) auf das Wort LED (LED ist die Variabel)

void setup() { //Das Setup wird nur einmal ausgeführt -> Beim Start des Arduinos
Serial.begin(9600); //Starte die Kommunikation mit dem Serial Monitor

//TODO: Definiere den PIN für die LED. Nutze hier die Variabel! Ist es INPUT oder OUTPUT?


}
 
void loop() { //Der Loop-Bereich wird immer wiederholt solange das Arduino läuft

  //TODO: Welche PIN Nummer hat der Lichtsensor -> schaue dazu auf dem Sensor-Kit und ersetze unten das ? mit der Nummer (inklusive das A)
  int Light = analogRead(A?); // lese die Werte aus dem Lichtsensor und speichere diese auf der Variable (Wort) Light ab.
 
 //TODO: Du kannst jetzt oben dein Arduino auswählen und mit dem Pfeil-Symbol den Code auf das Arduino hochladen (Du musst hier nichts schreiben)

  Serial.print("Helligkeit: "); //Schreibt das Wort Helligkeit: in den Serial Monitor (unten oder oben rechts bei der Lupe öffnen)
  Serial.println(Light); // Schreibt den Wert, welchen wir in der Variabel "Light" gespeichert haben
 
 //TODO: Öffne den Serial Monitor (oben rechts die Lupe) und schaue welche Werte die Helligkeit hat
 //TODO: -> Versuche jetzt den Code unten anzupassen, damit deine LED leuchtet wenn es dunkel wird.

 if (Light < 100) { //wenn der Licht-Wert kleiner ist als 2, dann mache.... 
 digitalWrite(LED, HIGH); //schaltet die LED ein
 }
 else { //falls das if nicht zutrifft, dann mache...
 digitalWrite(LED, LOW); //schaltet die LED aus
 }

  delay(100); // Pause zwischen den Messungen in Millisekunden
  
}
