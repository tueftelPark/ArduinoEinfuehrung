/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Mit dem Buzzer kannst du Töne abspielen. 
Jetzt möchten wir einen Alarm bauen. Jedes Mal wenn es im Klassenzimmer zu laut wird, dann ertönt der Buzzer-Alarm.
Nutze dazu das Mikrofon - es ist auf dem Sensor-Kit mit A2 Sound angeschrieben und noch den Buzzer.

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang)
digitalWrite (PIN, pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang)
ZAHL = analogRead(PIN); <- Zahlenwert wird am PIN gemessen. Dieser Wert wird unter der Variable "ZAHL" gespeichert.
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
tone(PIN, FREQUENZ); <- erzeugt einen Ton mit einer bestimmten Frequenz am PIN, PIN mit einer Zahl und FREQUENZ mit einer Zahl in Hertz ersetzen
noTone(PIN); <- stoppt den Ton am PIN, PIN mit einer Zahl ersetzen
*/


//TODO: Welche PIN Nummer hat der Buzzer -> schaue dazu auf dem Sensor-Kit und ersetze unten das ? mit der Nummer (ohne das D)
int Buzzer = ?; //Hier speichern wir eine Zahl (der PIN von unserem Buzzer) auf das Wort Buzzer

void setup() { //Das Setup wird nur einmal ausgeführt -> Beim Start des Arduinos
Serial.begin(9600); //Starte die Kommunikation mit dem Serial Monitor

//TODO: Definiere den PIN für den Buzzer. Nutze hier die Variabel! Ist es INPUT oder OUTPUT?


}
 
void loop() { //Der Loop-Bereich wird immer wiederholt solange das Arduino läuft

  //TODO: Welche PIN Nummer hat der Geräuschsensor -> schaue dazu auf dem Sensor-Kit und ersetze unten das ? mit der Nummer (inklusive das A)
  int Sound = analogRead(A?); // lese die Werte aus dem Geräuschsensor und speichere diese auf der Variable (Wort) Sound ab.
 
 //TODO: Du kannst jetzt oben dein Arduino auswählen und mit dem Pfeil-Symbol (upload) den Code auf das Arduino hochladen (Du musst hier nichts schreiben)

  Serial.println(Sound); //print the value of Sound sensor
 
 //TODO: Öffne den Serial Monitor (oben rechts die Lupe) und schaue welche Werte der Sound hat 
 //TODO: -> Versuche jetzt den Code unten anzupassen, damit der Buzzer abgeht wenns laut ist.
 if (Sound > 3000) { //wenn der Sound-Wert grösser ist als 3000, dann mache....

 //TEST:Ändere die Zahl hinter Buzzer und schaue was passiert
  tone(Buzzer, 250); //Buzzer einschalten und Ton abspielen
  delay(1000);//Ton abspielen für 1000 Milisekunden

 }
 else { //falls das if nicht zutrifft, dann mache...
  noTone(Buzzer); //Buzzer auschalten - kein Ton
 }
  
}
