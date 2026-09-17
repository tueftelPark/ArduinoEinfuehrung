/* Befehle:
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN, OUTPUT gibt Strom und INPUT misst den Strom am PIN, PIN mit einer Zahl ersetzen
analogRead(PIN); <- liest den Wert eines analogen Pins, PIN mit einer Zahl ersetzen, gibt einen Wert zwischen 0 und 1023 zurück
tone(PIN, FREQUENZ); <- erzeugt einen Ton mit einer bestimmten Frequenz am PIN, PIN mit einer Zahl und FREQUENZ mit einer Zahl in Hertz ersetzen
noTone(PIN); <- stoppt den Ton am PIN, PIN mit einer Zahl ersetzen
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden

map(WERT, VON_MIN, VON_MAX, NACH_MIN, NACH_MAX); <- ändert den Bereich eines Wertes von einem Bereich auf einen anderen 
-> WERT ist der zu ändernde Wert, VON_MIN und VON_MAX sind der alte Bereich, NACH_MIN und NACH_MAX sind der neue Bereich
*/


  //TODO: Ersetze XX mit einer Zahl (ohne D) -> Die Zahl wird jetzt unter der Variable Buzzer abgespeichert.
  int Buzzer = 5;
  //TODO: Ersetze X mit einer Zahl (inklusive A -> z.B. A7)
  int Poti = A0;


void setup() // Hier beginnt das Setup
{ 
  //TODO: Der Buzzer wird als Ausgang definiert. 
   pinMode(Buzzer, OUTPUT);

  //TODO: Der Pin für den Potentiometer wird als Eingang definiert. 
  pinMode(Poti, INPUT);
} 

void loop() // Hier beginnt das Hauptprogramm
{ 
  //TODO: Definiere die Variable sensorWert und diese liest den Wert vom Potentiometer. Ersetze XX mit der Variable für den Buzzer
  int sensorWert = analogRead(Poti); 

  //Mappe den Sensorwert (0-1023) auf eine Frequenz (100-2000 Hz) -> Die Frequenz ergibt die Tonhöhe
  int frequenz = map(sensorWert, 0, 1023, 100, 2000);

  //TODO: Erzeuge einen Ton für 1 Sekunde. Ersetze XX mit der entsprechenden Zahl.
  tone(Buzzer, frequenz);
  delay(1000);
  //TODO: stoppe den Ton beim Buzzer (nutze die Variable und nicht die Zahl!)
  noTone(Buzzer);

  //TODO: Warte 3 Sekunden, bevor das Programm neu startet
  delay(3000);
} 
