#include "Arduino_SensorKit.h"

/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Der nächste Spieleabend steht an. Hast du noch echte Würfel zu Hause?
Wir nicht - Ziel ist es, dass du hier deinen eigenen Würfel machst mit dem Sensor-Kit.
Du drückst den Button und anschliessend wird dir deine Zahl auf dem OLED-Bildschirm angezeigt. 
Kannst du auch eine Zahl zwischen 1 und 12 Würfeln oder nur 1 bis 6? Probiere mal!

>> Befehle <<
pinMode(PIN, OUTPUT oder INPUT); <- definiert den PIN(wo ist das Objekt angeschlossen), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D), INPUT(Sensor/Signaleingang) OUTPUT(Aktor/Signalausgang)
digitalRead(PIN); <- liest den Zustand eines digitalen Pins (HIGH oder LOW), PIN mit der Zahl auf dem SensorKit ersetzen (ohne D)
random(MIN, MAX+1); <- generiert eine Zufallszahl zwischen MIN (inklusive) und MAX+1 (exklusive)
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
Oled.begin(); <- Startet die Kommunikation mit dem Display
Oled.print("Text"); <- Auf dem Display wird Text angezeigt 
Oled.print(Variabel); <- Auf dem Display die Variabel (Wert nicht der Name: x=2 print(x) => 2 auf Display ) angezeigt 
Oled.println("Text"); <- Am Ende vom Text wird ein Enter eingefügt, sonst gleich wie Oled.print();
*/

//Definiere zuerst die Variabeln
//TODO: PIN an welchem der Button (kleiner Druckknopf) angeschlossen ist - muss mit Zahl ergänzt werden
int Button = ?; 

int Zahl = 0; // nicht ändern. Dies ist ein Startwert und wird definiert damit das Arduino weiss, dass es sich im eine Zahl handelt.

int Tasterstatus = 0; // nicht ändern. Dies ist ein Startwert und wird definiert damit das Arduino weiss, dass es sich im eine Zahl handelt.


void setup() // Hier beginnt das Setup
{

  // TODO: defineire den Button als Input


  // TODO: Starte die Kommunikation mit dem Display


  Oled.setFlipMode(true); // Legt die Orientation vom Diasplay fest

} // Hier endet ein Programmabschnitt

void loop() // Hier beginnt das Hauptprogramm
{
    Oled.setFont(u8x8_font_amstrad_cpc_extended_r); //Schriftart
  // Lese den Zustand des Buttons
  Tasterstatus = digitalRead(Button);
  
  // Überprüfe, ob der Button gedrückt wurde
  if (Tasterstatus == HIGH) {
    Oled.clearDisplay();
    delay(10); 
    Oled.setCursor(4, 1); // Position der Schrift

    // Zeige das Würfelergebnis auf dem OLED-Display an

    Oled.print("...");
    delay(1000);
    Oled.clearDisplay();

    // Generiere eine Zufallszahl zwischen 1 und 6
    Zahl = random(1, 7);
    Oled.setCursor(5, 1);  // Position setzen (mögliche Anpassung je nach Display)

    //TODO: Zeige die Zahl auf dem Arduino OLED an
    
    

    //TODO: Warte eine halbe Sekunde, bevor ein neuer Wurf möglich ist
    
  }

  delay(10); // Kurze Pause, um das Display zu aktualisieren
} // Hier endet ein Programmabschnitt
