/* Befehle:
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN (ohne D), OUTPUT gibt Strom und INPUT misst den Strom am PIN
ZAHL = analogRead(PIN); <- Wert zwischen 0 und 1023 wird am PIN gemessen. Dieser Wert wird unter der Variable "ZAHL" gespeichert.
digitalWrite (PIN, HIGH oder LOW); <- schaltet etwas EIN (HIGH) oder AUS (LOW) - PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), dann HIGH oder LOW
delay(ZEIT); <- macht eine Pause mit der ZEIT in millisekunden
*/


//TODO: Welche PIN Nummer hat die LED -> schaue dazu auf dem Sensor-Kit und ersetze unten das X mit der Nummer (ohne das D)
int LED = 6; //Hier speichern wir eine Zahl (der PIN von unserer LED) auf das Wort LED (LED ist die Variabel)

void setup() { //Das Setup wird nur einmal ausgeführt -> Beim Start des Arduinos
Serial.begin(9600); //Starte die Kommunikation mit dem Serial Monitor
pinMode(LED,OUTPUT);  //Definiere die LED (PIN X) als OUTPUT (OUTPUT = Arduino gibt Strom an LED) 

}
 
void loop() { //Der Loop-Bereich wird immer wiederholt solange das Arduino läuft
  //TODO: Welche PIN Nummer hat der Lichtsensor -> schaue dazu auf dem Sensor-Kit und ersetze unten das X mit der Nummer (inklusive das A)
  int licht = analogRead(A3); // lese die Werte aus dem Lichtsensor und speichere diese auf der Variable (Wort) Licht ab.
 
 //TODO: Du kannst jetzt oben dein Arduino auswählen und mit dem Pfeil-Symbol den Code auf das Arduino hochladen (Du musst hier nichts schreiben)

  Serial.print("Helligkeit: "); //Schreibe das Wort Helligkeit: in den Serial Monitor (unten oder oben rechts bei der Lupe öffnen)
  Serial.println(licht); // Schreibt den Wert, welchen wir in der Variabel "licht" gespeichert haben
 
 //TODO: Öffne den Serial Monitor (oben rechts die Lupe) und schaue welche Werte die Helligkeit hat - Versuche jetzt den Code unten anzupassen, damit deine LED leuchtet wenn es dunkel wird.
 if (licht < 3) { //wenn der Licht-Wert kleiner ist als 2, dann mache....
 digitalWrite(LED, HIGH); //schaltet die LED ein
 }
 else { //falls das if nicht zutrifft, dann mache...
 digitalWrite(LED, LOW); //schaltet die LED aus
 }

  delay(100); // Pause zwischen den Messungen in Millisekunden
  
}