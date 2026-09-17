/* Befehle:
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN, OUTPUT gibt Strom und INPUT misst den Strom am PIN
delay(ZEIT); <- macht eine Pause mit der ZEIT in millisekunden
analogWrite(PIN, 0 bis 255); <- NEU: neben digital gibt es auch analoge Signale. Hier gibt es nicht nur HIGH oder LOW, sondern eine Zahl von 0 bis 255.
ZAHL = analogRead(PIN); <- Wert zwischen 0 und 1023 wird am PIN gemessen. Dieser Wert wird unter der Variable "ZAHL" gespeichert.

map(WERT, VON_MIN, VON_MAX, NACH_MIN, NACH_MAX); <- ändert den Bereich eines Wertes von einem Bereich auf einen anderen 
-> WERT ist der zu ändernde Wert, VON_MIN und VON_MAX sind der alte Bereich, NACH_MIN und NACH_MAX sind der neue Bereich
*/


  //TODO: Definiere Poti mit der ensprechenden AX Nummer auf dem Sensor Kit. Ersetze X mit einer Zahl (A inkulsive -> z.B. A7)
  int Poti = A0;

  //TODO: Defiere die Variabeln Rot, Blau und Gruen mit den jeweiligen PIN-Nummern. Erestze XX mit der richtigen Zahl (Du musst die PINs 9, 10 ,11 und GND wählen)
  int Rot = 11;
  //TODO: Wiederhole dies für Blau und Gruen
  int Blau = 10;
  int Gruen = 9;


void setup() // Hier beginnt das Setup
{ 
  //TODO: Rot, Blau und Gruen werden als Ausgang definiert. Ersetze YY mit OUTPUT oder INPUT
  pinMode(Rot, OUTPUT); 
  //TODO: definiere die weiteren Farben (Nutze die Variabeln)
  pinMode(Gruen, OUTPUT); 
  pinMode(Blau, OUTPUT); 

  //TODO: Der Potentiometer wird als Eingang definiert. 
  pinMode(Poti, INPUT);

} 

void loop() // Hier beginnt das Hauptprogramm
{ 
  //TODO: Definiert die Variable sensorWert und liest den Wert vom Potentiometer. Ersetze YY mit der richtigen Variabel.
  int sensorWert = analogRead(Poti); 


  //Mappe den Sensorwert (0-1023) auf einen PWM-Wert (0-255)
  //Der Potentiometer gibt zahlen zwischen 0 und 1023 aus diese werden umgerechnet da die LED nur mit Zahlen zwischen 0 und 255 arbeiten kann.
  //Beispielsrechnung was map() macht: Potentiometer-Wert=500
  //  500:1023 = 0.4888 -> 0.4888*255 = 124.6334
  //Der Wert 124.6334 wird an die LED weitergegeben (Die LED ist ca. bei 50% Helligkeit)

  int helligkeit = map(sensorWert, 0, 1023, 0, 255);

  //Setze alle Farbkanäle der RGB-LED auf den gleichen Wert, um weißes Licht zu erzeugen
  analogWrite(Rot, helligkeit); // Rot
  //TODO: Wiederhole dies mit den weiteren zwei Farben
  analogWrite(Gruen, helligkeit);
  analogWrite(Blau, helligkeit);

  
  //TODO: Warte 100 Millisekunden, bevor das Programm neu startet
  delay(100);
} 
