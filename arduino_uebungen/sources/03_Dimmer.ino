/* 
>> Was soll passieren? <<
Kennst du Dimmer-Schalter, mit denen man Licht heller oder dunkler drehen kann?
Auf deinem SensorKit gibt es so einen Drehknopf - das Potentiometer (kurz: Poti).
Damit stellst du gleich die Helligkeit deiner LED ein. Probier es aus!

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- Sagt dem Arduino: Ist an diesem PIN etwas, das AUSGIBT (OUTPUT) oder etwas, das MISST (INPUT)?
delay(ZEIT); <- Macht eine Pause in Millisekunden.
analogWrite(PIN, ZAHL); <- Neu: Hier gibt es nicht nur EIN/AUS, sondern jede Zahl zwischen 0 und 255. Das steuert die Helligkeit.
ZAHL = analogRead(PIN); <- Misst einen Wert zwischen 0 und 1023 am PIN.
*/

  int Helligkeit = 0;
  int Sensorwert = 0;

  //TODO: Definiere das Poti mit der passenden A-Nummer auf dem SensorKit. Ersetze ? mit einer Zahl (z.B. A7)
  //EXPECT: ^\d+$
  int Poti = A?;

  //TODO: Definiere die LED mit der passenden PIN-Nummer (nutze einen PIN mit einer Welle ~, z.B. 5)
  //EXPECT: ^\d+$
  int LED = ?;


void setup()
{ 
  //TODO: Definiere die LED als Ausgang. Ersetze ? mit OUTPUT oder INPUT
  //EXPECT: ^(OUTPUT|INPUT)$
  pinMode(LED, ?); 

  //TODO: Definiere das Poti als Eingang
  //EXPECT: ^pinMode\s*\(\s*Poti\s*,\s*INPUT\s*\)\s*;$
  
} 

void loop()
{ 
  //TODO: Miss den Wert vom Poti und speichere ihn in "Sensorwert"
  //EXPECT: ^Poti$
  Sensorwert = analogRead(?); 

  Helligkeit = Sensorwert/4; //1023 / 4 = 255, weil analogWrite nur bis 255 geht

  //TODO: Setze die LED auf "Helligkeit", damit sie heller oder dunkler leuchtet
  //EXPECT: ^analogWrite\s*\(\s*LED\s*,\s*Helligkeit\s*\)\s*;$
  

  //TODO: Warte 100 Millisekunden
  //EXPECT: ^delay\s*\(\s*100\s*\)\s*;$

} 
