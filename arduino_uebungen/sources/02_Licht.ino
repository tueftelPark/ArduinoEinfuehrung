/* 
>> Was soll passieren? <<
Die LED soll angehen, wenn es dunkel ist - so wie eine Strassenlaterne!
Löse zuerst alle Aufgaben. Ganz am Schluss stellst du die Helligkeitsgrenze noch genau ein.

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- Sagt dem Arduino: Ist an diesem PIN etwas, das AUSGIBT (OUTPUT) oder etwas, das MISST (INPUT)?
digitalWrite(PIN, HIGH oder LOW); <- Schaltet etwas EIN (HIGH) oder AUS (LOW).
delay(ZEIT); <- Macht eine Pause in Millisekunden.
Serial.println(Variable); <- Zeigt den Wert einer Variable im Serial-Monitor an (das ist wie ein kleiner Bildschirm für Zahlen).

>> Erklärungen <<
WERT = analogRead(PIN); <- Misst einen Wert zwischen 0 und 1023 am PIN und speichert ihn in der Variable WERT.
Serial.begin(9600); <- Startet die Verbindung zum Serial-Monitor. Ohne diesen Befehl funktioniert Serial.println() nicht.
*/

//Definiere zuerst die Variabeln
//TODO: Ersetze XX mit der PIN-Nummer für den Lichtsensor. Achtung: Auf dem SensorKit steht dort ein "A" davor - schreibe es mit (z.B. A3)
//EXPECT: ^A\d+$
int LichtSensor = XX ;

//TODO: Ersetze XX mit der PIN-Nummer für die LED (auf dem SensorKit ohne "D" davor)
//EXPECT: ^\d+$
int LED = XX ;

int Helligkeit = 0;

//TODO: Ersetze XX mit dem Helligkeitswert zwischen (0-1023), ab dem die LED einschalten soll. Du kannst zu Beginn den Wert 5 wählen.
//EXPECT: ^\d+$
int Helligkeitsgrenze = XX; // Ab welchem Wert (0-1023) soll die LED angehen?

int AusleseAbstand = 1000; // Miss die Helligkeit jede Sekunde (1000 Millisekunden)

void setup()
{ 
  Serial.begin(9600); // Startet den Serial-Monitor
  pinMode(LichtSensor, INPUT); // Der Lichtsensor misst etwas, darum INPUT

  // TODO: Definiere den PIN für die LED. Nutze die Variabel "LED". Ist es INPUT oder OUTPUT?
  //EXPECT: ^pinMode\s*\(\s*LED\s*,\s*OUTPUT\s*\)\s*;$
  

} 

void loop()
{ 
  Helligkeit = analogRead(LichtSensor); // Miss die Helligkeit und speichere sie in der Variable
  
  // TODO: Zeige den Wert von "Helligkeit" im Serial-Monitor an (Befehl siehe oben!)
  //EXPECT: ^Serial\.println\s*\(\s*Helligkeit\s*\)\s*;$
  

  if (Helligkeit >= Helligkeitsgrenze) { // Ist es hell genug?
    // TODO: Dann soll die LED ausgehen
    //EXPECT: ^digitalWrite\s*\(\s*LED\s*,\s*LOW\s*\)\s*;$
    
  } else {
    // Sonst ist es dunkel - die LED soll angehen
    // TODO: Schalte die LED ein
    //EXPECT: ^digitalWrite\s*\(\s*LED\s*,\s*HIGH\s*\)\s*;$

  }

  delay(AusleseAbstand);

  //INFO: Fast fertig! Lade jetzt deinen Code hoch. Öffne oben rechts mit dem Lupen-Symbol den Serial-Monitor - dort siehst du laufend Zahlen, das ist die gemessene Helligkeit. Halte die Hand über den Sensor und schau, wie sich die Zahl verändert. Passe danach oben die Zahl bei "Helligkeitsgrenze" an, bis die LED genau bei der richtigen Helligkeit angeht.
} 
