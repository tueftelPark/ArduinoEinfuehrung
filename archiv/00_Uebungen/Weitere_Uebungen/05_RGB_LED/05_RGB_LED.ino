/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
RGB steht für ROT - GRÜN - BLAU. 
Du sollst jetzt die RGB-LED anschliessen und anschliessend kannst du Farben mischen.
Welche Farben enstehen? Probiere es aus?

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang)
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
analogWrite(PIN, 0 bis 255); <- NEU: neben digitalen gibt es auch analoge Signale. Hier gibt es nicht nur HIGH oder LOW, sondern jede Zahl zwischen 0 und 255 ist möglich.
*/

//Zuerst die Variabeln definieren

// TODO: Verbinde die RGB LED mit dem Sensorkit. Am Besten verbindest du die [- R G B] Pins mit den Pins [GND 11~ 10~ 9~]. - mit GND, R mit 11, G mit 10 und B mit 9

// TODO: Farbe rot an Pin ?? -> Wichtig nur PWM(~) nutzen! Auf deinem Arduino sind dies die Nummern mit einer kleinen Welle -> z.B. 10~
int LEDrot = ??; 
// TODO: Farbe gruen an Pin ?? -> Wichtig nur PWM(~) nutzen! 
int LEDgruen = ??; 
// TODO: Farbe blau an Pin ?? -> Wichtig nur PWM(~) nutzen! 


int RotHelligkeit = 150; //TEST: Variable für das Einschalten
int GruenHelligkeit = 150; //TEST: Variable für das Einschalten
int BlauHelligkeit = 150; //TEST: Variable für das Einschalten

//TODO: Ersetze das ? mit der Zahl zum Ausschalten - denke daran das jetzt bei analog Zahlen zwischen 0 und 255 möglich sind

int RotAus = ?; //TEST: Variable für das Ausschalten
int GruenAus = ?; //TEST: Variable für das Ausschalten
int BlauAus = ?; //TEST: Variable für das Ausschalten

void setup()
{
//TODO: Definiere den richtigen Pin für die rote LED (INPUT oder OUTPUT?)

//TODO: Definiere den richtigen Pin für die grüne LED

//TODO: Definiere den richtigen Pin für die blaue LED
  
}

void loop()
{
  analogWrite(LEDrot, RotHelligkeit); //Jetzt wird der PIN für die rote LED genommen und die Helligkeit von der Variabel
  delay(1000);
  analogWrite(LEDrot, RotAus);
  // TODO: Lasse alle anderen RGB-Farben auch NACHEINANDER leuchten -> Vergiss den delay nicht!

  
  // TODO: Lasse alle Farben gleichzeitig leuchten -> Was passiert?
  

  // TODO: Lasse Rot und Grün gleichzeitig leuchten -> Was passiert?


  // TEST: Was passiert, wenn du die Helligkeit mit einer Zahl zwischen 0-255 ersetzt? 
  
  
  //TEST: Was passiert wenn alle Farben verschiedene Zahlen haben?
  

}
