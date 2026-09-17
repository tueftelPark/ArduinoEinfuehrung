/* Befehle:
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN (ohne D), OUTPUT gibt Strom und INPUT misst den Strom am PIN
WERT = digitalRead(PIN); <- das HIGH oder LOW welches gemessen wurde, speichern wir in der Variable WERT (Achtung WERT muss bei den Variabel noch definiert werden!)
tone(PIN, FREQUENZ); <- erzeugt einen Ton mit einer bestimmten Frequenz am PIN, PIN mit einer Zahl und FREQUENZ mit einer Zahl in Hertz ersetzen
noTone(PIN); <- stoppt den Ton am PIN, PIN mit einer Zahl ersetzen
delay(ZEIT); <- macht eine Pause mit der ZEIT in millisekunden
*/

//Die Erzeugung des Tones basiert massgeblich auf dem Befehl „tone(x, y)“, 
//wobei der x-Wert den Pin angibt, an dem der Lautsprecher mit der positiven Seite angeschlossen ist und der y-Wert, der die Tonhöhe angibt.


//Definiere zuerst die Variabeln
//TODO: PIN-Nummer für den Button auf dem SensorKit (ohne D)
int Taster = 4 ; 
//TODO: PIN-Nummer für den Buzzer auf dem SensorKit (ohne D) - muss mit Zahl ergänzt werden - der Buzzer ist der kleine schwarze "Lautsprecher"
int Buzzer = 5; 
//TODO: Millisekunden anpassen. hier definieren wir die Zeit im Befehl delay(ZEIT) - den kennst du noch von der LED Übung! 
int Spielzeit = 1000; 

int Tasterstatus=0; // nicht ändern. Dies ist ein Startwert und wird definiert damit das Arduino weiss, dass es sich im eine Zahl handelt.


void setup()
{

pinMode(Taster, INPUT); // Hier nutzen wir das Wort Taster als PIN-Nummer welche oben definiert ist in den Variabeln 
// und der Taster in ein Input, da wir den Strom messen am PIN

// TODO: Nutze hier die Variabel für den Buzzer und der Buzzer soll einen Ton ausgeben. Ist es ein INPUT oder OUTPUT?
pinMode(Buzzer, OUTPUT);


}

void loop()
{
Tasterstatus = digitalRead(Taster); // hier lesen wir den PIN aus mit digitalRead(PIN) und speichern den Wert in Tasterstatus
//NEU: Wir lernen if/else - wenn das passiert mache das (if) und anonsten das andere (else)
if (Tasterstatus == HIGH) // Wenn der Taster gedrückt ist... also wenn der PIN Strom bekommt, dann ist das Signal HIGH
{
tone(Buzzer, 300); // …spiele diesen Ton... //TEST: Verändere die Zahl in diesem Befehel - was passiert?
  
//TODO: Füge hier eine Pause mit der Länge "Spielzeit" ein. Nutze die Variabel nicht die Zahl.
delay(Spielzeit);

noTone(Buzzer); // Ton abschalten
}
else {
  // wenn nichts gedrückt wird, mache nichts
  // hier musst du nichts ergänzen
  //TEST: Falls du möchtest kannst du hier etwas programmieren - was soll passieren wenn der Taster nicht gedrückt wird? 
  //TEST: Leuchtet eine LED? Du darfst dein Wissen von Übung 1 und 2 auch hier anwenden
}
}

