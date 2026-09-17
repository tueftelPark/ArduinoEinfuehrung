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

//INFO: Hier oben werden Variabeln definiert - das sind Namen für Werte, die du weiter unten im Code wiederverwendest. Wichtig: Sobald eine Variable definiert ist (z.B. "LED" oder "Poti"), schreibst du im Code danach immer ihren NAMEN, nicht mehr die Zahl!

  int Helligkeit = 0;
  int Sensorwert = 0;

  //TODO: Definiere das Poti mit der passenden A-Nummer auf dem SensorKit. Ersetze ? mit einer Zahl
  //EXPECT: ^0$
  int Poti = A?;

  //TODO: Definiere die LED mit der passenden PIN-Nummer
  //EXPECT: ^6$
  int LED = ?;


void setup()
{ 
  //TODO: Definiere die LED als Ausgang. Ersetze ? mit OUTPUT oder INPUT
  //EXPECT: ^OUTPUT$
  pinMode(LED, ?); 

  //TODO: Definiere das Poti als Eingang
  //EXPECT: ^pinMode\s*\(\s*Poti\s*,\s*INPUT\s*\)\s*;$
  
} 

void loop()
{ 
  //TODO: Miss den Wert vom Poti und speichere ihn in "Sensorwert". Nutze dazu die Variabel "Poti" - nicht die Zahl!
  //EXPECT: ^Poti$
  Sensorwert = analogRead(?); 

  Helligkeit = Sensorwert/4; //1023 / 4 = 255, weil analogWrite nur bis 255 geht

  //TODO: Lasse die LED leuchten, und zwar in der Helligkeit, welche mit dem Poti eingestellt wird. Nutze dabei die Variabeln "LED" und "Helligkeit" - nicht die Zahlen!
  //EXPECT: ^analogWrite\s*\(\s*LED\s*,\s*Helligkeit\s*\)\s*;$
  

  //TODO: Warte 100 Millisekunden
  //EXPECT: ^delay\s*\(\s*100\s*\)\s*;$

} 
