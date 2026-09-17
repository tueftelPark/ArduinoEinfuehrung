/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Hast du schon einmal das Licht gedimmt? Meistens sind das solche Drehknöpfe.
Auf dem Sensor-Kit haben wir auch so einen Drehknopf - du findest ihn als Rotary Potentiometer.
Mit diesem Drehknopf kannst du jetzt die Helligkeit der LED einstellen. Probiere es aus!

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang)
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
analogWrite(PIN, 0 bis 255); <- NEU: neben digitalen gibt es auch analoge Signale. Hier gibt es nicht nur HIGH oder LOW, sondern jede Zahl zwischen 0 und 255 ist möglich.
ZAHL = analogRead(PIN); <- Wert zwischen 0 und 1023 wird am PIN gemessen. Dieser Wert wird unter der Variable "ZAHL" gespeichert.
*/

  int Helligkeit = 0;
  
  int Sensorwert = 0;
  //TODO: Definiere das Potentiometer (Poti) mit der ensprechenden A? Nummer auf dem Sensor Kit. Ersetze ? mit einer Zahl (A inkulsive -> z.B. A7)
  int Poti = A?;

  //TODO: Defiere die Variabeln Rot, Blau und Gruen mit den jeweiligen PIN-Nummern. Erestze ? mit der richtigen Zahl (Du musst die PINs 9, 10 ,11 und GND wählen)
  int Rot = ?;
  //TODO: Wiederhole dies für Blau und Gruen
  


void setup() // Hier beginnt das Setup
{ 
  //TODO: Rot, Blau und Gruen werden als Ausgang definiert. Ersetze ? mit OUTPUT oder INPUT
  pinMode(Rot, ?); 
  //TODO: definiere die weiteren Farben als Ausgang.


  //TODO: definiere das Poti als Eingang.
  
} 

void loop() // Hier beginnt das Hauptprogramm
{ 
  //TODO: Definiert die Variable Sensorwert und liest den Wert vom Potentiometer. Ersetze ? mit der richtigen Variabel.
  Sensorwert = analogRead(?); 

  Helligkeit = Sensorwert/4;       //1023 / 4 = 255 --> analogWrite geht nur bis 255 und Poti bis 1023 

  //TODO: Setze alle Farbkanäle der RGB-LED auf den gleichen Wert, um weißes Licht zu erzeugen
  analogWrite(Rot, Helligkeit); // Rot
  //TODO: Wiederhole dies mit den weiteren zwei Farben


  //TODO: Warte 100 Millisekunden, bevor das Programm neu startet
  
} 
