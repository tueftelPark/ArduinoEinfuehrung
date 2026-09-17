/* Befehle:
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN, OUTPUT gibt Strom und INPUT misst den Strom am PIN, PIN mit der Zahl auf dem SensorKit ersetzen (ohne D)
digitalWrite (PIN, HIGH oder LOW); <- schaltet etwas EIN (HIGH) oder AUS (LOW) - PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), dann HIGH oder LOW
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
random(Startzahl, Schlusszahl); <- generiert eine zufällige Zahl zwischen Startzahl-Schlusszahl
*/

  //TODO: Definiere die LED mit einer Variable.
int LED = 6; 

void setup() // Hier beginnt das Setup
{ 
  //TODO: LED wird als Ausgang definiert 
  pinMode(LED, OUTPUT); 
} // Hier endet ein Programmabschnitt

void loop() // Hier beginnt das Hauptprogramm
{ 
  //TODO: schalte die LED ein
  digitalWrite(LED, HIGH);

  //Hier wird unter der Variable Zeit eine zufällige Zahl abgespeichert. Ersetze XX mit zwei Zahlen. ACHTUNG: Millisekunden
  int ZeitEin = random(100, 2000);

  //TODO: warte für das zufällige Zeitintervall
  delay(ZeitEin);

  //TODO: schalte die LED wieder aus
  digitalWrite(LED, LOW);

  //TODO: Ersetze XX mit zwei Zahlen. ACHTUNG: Millisekunden
  int ZeitAus = random(10, 1000);

  //TODO: warte für das zweite zufällige Zeitintervall
  delay(ZeitAus);
} // Hier endet ein Programmabschnitt
