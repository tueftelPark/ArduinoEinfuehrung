/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Das LED leuchtet, wenn es genug dunkel ist. 
Starte mit dem programmieren, indem du alle TODO's löst. 
Wenn es funktioniert, ändere noch die Helligkeitsgrenze bei der das LED an geht oder ändere den AusleseAbstand...

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang)
digitalWrite (PIN, HIGH oder LOW); <- schaltet etwas EIN (HIGH) oder AUS (LOW) - PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), dann HIGH oder LOW
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
Serial.println(Variable); <- So kann man den Inhalt einer Variable auf die Konsole ausgeben

>> Erklärungen <<
WERT = analogRead(PIN); <- Der Wert zwischen 0 und 1023, welcher gemessen wurde, speichern wir in der Variable WERT 
    (Achtung WERT muss bei den Variabel noch definiert werden!)
Serial.begin(9600); <- Dieser Befehl wird gebraucht, damit auf die Konsole geschrieben werden kann (Weiter unten).
*/

//Definiere zuerst die Variabeln
//TODO: XX mit PIN-Nummer für den Licht ersetzen (siehe SensorKit (mit A))
int LichtSensor = A3 ;

//TODO: XX mit PIN-Nummer für den LED ersetzen (auf dem SensorKit (ohne D))
int LED = 6 ;

int Helligkeit = 0;
int Helligkeitsgrenze = 5; // Wert zwischen 0 und 1023 der die Helligkeit angibt bei der das Licht an-/abgeschaltet werden soll.

int AusleseAbstand = 1000; // Prüfe die Helligkeit alle 1000 Millisekunden/ 1 Mal in der Sekunde.

void setup() // Hier beginnt das Setup
{ 
  Serial.begin(9600); // Dieser Befehl wird gebraucht, damit auf die Konsole geschrieben werden kann (Weiter unten).
  pinMode(LichtSensor, INPUT); // Hier nutzen wir das Wort LichtSensor als PIN-Nummer welche oben definiert ist in den Variabeln 
  // und der LichtSensor in ein Input, da wir den Strom messen am PIN

  // TODO: Definiere den PIN für das LED. Nutze hier die Variabel! Ist es INPUT oder OUTPUT?
  

} // Hier endet ein Programmabschnitt

void loop() // Hier beginnt das Hauptprogramm
{ 
  Helligkeit = analogRead(LichtSensor); // hier lesen wir am PIN mit digitalRead(PIN) einen Wert aus 
  // Der Wert wird unter Helligkeit abgespeichert.
  
  // TODO: Mit diesem Befehl wird die Helligkeit auf die Konsole ausgegeben. TEST: Halte den Sensor ins Licht und schaue wie sich der Wert verändert. 
  

  //NEU: Wir lernen if & else - wenn das passiert mache das (if) und anonsten das andere (else)
  if (Helligkeit >= Helligkeitsgrenze) { // Hier wird geprüft, ob die Helligkeit aus dem Sensor den in der "Helligkeitsgrenze" definierten Grenzwert überschreitet.
    // Wenn es genug Hell ist, kann das Licht (LED) abgeschaltet werden.
    // TODO: schalte die LED wieder aus
    
  } else {
    // Ansonsten ist es dunkel und das Licht (LED) kann eingeschaltet werden.
    // TODO: schalte eine LED ein

  }

  delay(AusleseAbstand);
} // Hier endet ein Programmabschnitt

