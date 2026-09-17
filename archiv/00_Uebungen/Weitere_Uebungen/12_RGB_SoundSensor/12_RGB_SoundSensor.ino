/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Hier wird eine Ampel programmiert die auf die Lautstärke reagiert. 
Je nach dem wie laut es ist, leuchtete eine andere Farbe.

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang)
analogRead(PIN); <- liest den Wert eines analogen Pins, PIN mit einer Zahl ersetzen, gibt einen Zahlen Wert zurück (je nach dem wie laut es ist)
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
analogWrite(PIN, 0 bis 255); <- NEU: neben digitalen gibt es auch analoge Signale. Hier gibt es nicht nur HIGH oder LOW, sondern jede Zahl zwischen 0 und 255 ist möglich.
*/


// TODO: Verbinde die RGB LED mit dem Sensorkit. Am Besten verbindest du die [- R G B] Pins mit den Pins [GND 11~ 10~ 9~]. 


// TODO: Speichere die PIN-Nummer der RGB LED unter den Variabeln LEDrot, LEDgruen und LEDblau

// TODO: Farbe rot an Pin ? -> Wichtig nur PWM(~) nutzen! Auf deinem Arduino sind dies die Nummern mit einer kleinen Welle -> z.B. 10~
int LEDrot = ?; 
// TODO: Farbe gruen an Pin ? -> Wichtig nur PWM(~) nutzen! 
int LEDgruen = ?; 
// TODO: Farbe blau an Pin ? -> Wichtig nur PWM(~) nutzen! 


int RotAn = 150; //TEST: Variable für das Einschalten
int GruenAn = 150; //TEST: Variable für das Einschalten
int BlauAn = 150; //TEST: Variable für das Einschalten

//TODO: Ersetze das ? mit der Zahl zum Ausschalten

int RotAus = ?; //TEST: Variable für das Ausschalten
int GruenAus = ?; //TEST: Variable für das Ausschalten
int BlauAus = ?; //TEST: Variable für das Ausschalten


void setup() { //Das Setup wird nur einmal ausgeführt -> Beim Start des Arduinos

//TODO: Definiere den richtigen Pin für die rote LED als Ausgang. Ersetze ? mit INPUT oder OUTPUT
pinMode(LEDrot, ?);
//TODO: Definiere den richtigen Pin für die grüne LED als Ausgang.
pinMode(LEDgruen, ?);
//TODO: Definiere den richtigen Pin für die blaue LED als Ausgang.


Serial.begin(9600); //Starte die Kommunikation mit dem Serial Monitor

}

void loop() { //Der Loop-Bereich wird immer wiederholt solange das Arduino läuft

//TODO: Welche PIN Nummer hat der Geräuschsensor -> schaue dazu auf dem Sensor-Kit und ersetze unten das ? mit der Nummer (inklusive das A)
  int sound = analogRead(A?); // lese die Werte aus dem Geräuschsensor und speichere diese auf der Variable (Wort) Licht ab.

   Serial.println(sound); //print the value of sound sensor

// TODO: Öffne den Serial Monitor (oben rechts die Lupe) und schaue welche Werte der Sound hat 
// -> Versuche den Code unten anzupassen, damit du mit schnipsen, reden und klatschen die verschiedenen Farben zum leuchten bringst

  if (sound > 1000) { //wenn der Sound-Wert grösser als 1000 ist, dann mache...
    Serial.println(sound);
    analogWrite(LEDrot, RotAn); //Schalte die rote LED an
    delay(1000); //LED leuchtet für 1 Sekunde
    analogWrite(LEDrot, RotAus); //schaltet die rote LED wieder aus
  }

  else if (sound < 1000) { //wenn der Sound-Wert kleiner als 1000 ist, dann mache...
    Serial.println(sound);
    analogWrite(LEDgruen, GruenAn); //Schalte die grüne LED an
    delay(1000);
    analogWrite(LEDgruen, GruenAus);
  }

  else { //falls das if nicht zutrifft, dann mache...
    Serial.println(sound);
    analogWrite(LEDblau, BlauAn); //Schalte die blaue LED an
    delay(1000);
    analogWrite(LEDblau, BlauAus);
  }
  
}
