/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Hier wird ganz zufällig bestimmt wann deine LED eingeschaltet und augeschaltet wird.
Mit dem Befehl random wird eine zufällig Zahl aus deinem Bereich ausgewählt.

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang)
digitalWrite (PIN, HIGH oder LOW); <- schaltet etwas EIN (HIGH) oder AUS (LOW) - PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), dann HIGH oder LOW
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
random(Startzahl, Schlusszahl); <- generiert eine zufällige Zahl zwischen Startzahl-Schlusszahl
*/

//TODO: Definiere die LED mit einer Variable.


void setup() // Hier beginnt das Setup
{ 
  //TODO: LED als Ausgang definieren

} // Hier endet ein Programmabschnitt

void loop() // Hier beginnt das Hauptprogramm
{ 
  //TODO: schalte die LED ein
  

  //TODO: Hier wird unter der Variable Zeit eine zufällige Zahl abgespeichert. Ersetze ?? mit zwei Zahlen. ACHTUNG: Millisekunden
  int ZeitEin = random(??, ??);

  //TODO: warte für das zufällige Zeitintervall
  

  //TODO: schalte die LED wieder aus
  

  //TODO: Ersetze XX mit zwei Zahlen. ACHTUNG: Millisekunden
  int ZeitAus = random(??, ??);

  //TODO: warte für das zweite zufällige Zeitintervall



  
} // Hier endet ein Programmabschnitt
