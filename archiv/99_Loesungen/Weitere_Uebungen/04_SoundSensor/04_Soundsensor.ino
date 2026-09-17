/* Befehle:
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN (ohne D), OUTPUT gibt Strom und INPUT misst den Strom am PIN
ZAHL = analogRead(PIN); <- Wert zwischen 0 und 1023 wird am PIN gemessen. Dieser Wert wird unter der Variable "ZAHL" gespeichert.
delay(ZEIT); <- macht eine Pause mit der ZEIT in millisekunden
tone(PIN, FREQUENZ); <- erzeugt einen Ton mit einer bestimmten Frequenz am PIN, PIN mit einer Zahl und FREQUENZ mit einer Zahl in Hertz ersetzen
noTone(PIN); <- stoppt den Ton am PIN, PIN mit einer Zahl ersetzen
*/


//TODO: Welche PIN Nummer hat der Buzzer -> schaue dazu auf dem Sensor-Kit und ersetze unten das X mit der Nummer (ohne das D)
int BUZZER = 5; //Hier speichern wir eine Zahl (der PIN von unserem Buzzer) auf das Wort Buzzer


void setup() { //Das Setup wird nur einmal ausgeführt -> Beim Start des Arduinos
Serial.begin(9600); //Starte die Kommunikation mit dem Serial Monitor
pinMode(BUZZER, OUTPUT);  //Definiert den Buzzer (PIN X) als OUTPUT (OUTPUT = Arduino gibt Strom an LED) 

}
 
void loop() { //Der Loop-Bereich wird immer wiederholt solange das Arduino läuft
  //TODO: Welche PIN Nummer hat der Geräuschsensor -> schaue dazu auf dem Sensor-Kit und ersetze unten das X mit der Nummer (inklusive das A)
  int sound = analogRead(A2); // lese die Werte aus dem Geräuschsensor und speichere diese auf der Variable (Wort) Licht ab.
 
 //TODO: Du kannst jetzt oben dein Arduino auswählen und mit dem Pfeil-Symbol (upload) den Code auf das Arduino hochladen (Du musst hier nichts schreiben)

  Serial.println(sound); //print the value of sound sensor
 
 //TODO: Öffne den Serial Monitor (oben rechts die Lupe) und schaue welche Werte der Sound hat - Versuche jetzt den Code unten anzupassen, damit deine LED leuchtet wenn es dunkel wird.
 if (sound > 150) { //wenn der Sound-Wert grösser ist als 3000, dann mache....

 //TEST:Ändere die Zahl hinter BUZZER und schaue was passiert
  tone(BUZZER, 250); //Buzzer einschalten und Ton abspielen
  delay(1000);//Ton abspielen für 1000 Milisekunden

 }
 else { //falls das if nicht zutrifft, dann mache...
  noTone(BUZZER); //Buzzer auschalten - kein Ton
 }
  
}