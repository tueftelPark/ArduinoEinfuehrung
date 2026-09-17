/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Jetzt machen wir mal ein Sound-Mischpult. 
Wir nutzen den Drehregler (Rotary Potentiometer oder kurz Poti) um den Ton im Buzzer einzustellen.

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang)
analogRead(PIN); <- liest den Wert eines analogen Pins, PIN mit einer Zahl ersetzen, gibt einen Wert zwischen 0 und 1023 zurück
tone(PIN, Frequenz); <- erzeugt einen Ton mit einer bestimmten Frequenz am PIN, PIN mit einer Zahl und Frequenz mit einer Zahl in Hertz ersetzen
noTone(PIN); <- stoppt den Ton am PIN, PIN mit einer Zahl ersetzen
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
*/


  //TODO: Ersetze ? mit einer Zahl (ohne D) -> Die Zahl wird jetzt unter der Variable Buzzer abgespeichert.
  int Buzzer = ?;

  //TODO: Ersetze ? mit einer Zahl (inklusive A -> z.B. A7)
  int Poti = A?;


void setup() // Hier beginnt das Setup
{ 
  //TODO: Der Buzzer wird als Ausgang definiert. 
   

  //TODO: Der Pin für den Potentiometer wird als Eingang definiert. 
  
} 

void loop() // Hier beginnt das Hauptprogramm
{ 
  //TODO: Definiere die Variable Sensorwert und diese liest den Wert vom Potentiometer. Ersetze ? mit der Variable für den Poti
  int Sensorwert = analogRead(?); 

  //Der Sensorwert wird als Tonhöhe für den Buzzer genommen
  int Frequenz = Sensorwert;

 //Hier wird der Ton erzeugt mit der Frequenz
  tone(Buzzer, Frequenz);

  //TODO: Erzeuge einen Ton für 1 Sekunde. Ersetze ? mit der entsprechenden Zahl.
  delay(?);
  //TODO: stoppe den Ton beim Buzzer.
  

  //TODO: Warte 3 Sekunden, bevor das Programm neu startet
  
} 
