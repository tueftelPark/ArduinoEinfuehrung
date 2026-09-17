/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Ein OLED-Bildschirm kennst du vileicht von deinem Fernseher zu Hause.
In dieser Übung kannst du jetzt verschiedene Sachen auf deinen Bildschirm auf dem Sensor-Kit schreiben.

>> Befehle <<
Oled.begin(); <- Startet die Kommunikation mit dem Display
Oled.setFlipMode(true oder false); <- Text auf Dsiplay wird entweder normal angezeigt oder auf dem Kopf angezeigt.
Oled.print("Text"); <- Auf dem Display wird Text angezeigt 
Oled.println("Text"); <- Am Ende vom Text wird ein Enter eingefügt, sonst gleich wie Oled.print();

Oled.setFont(Schriftart); <- Legt die Schriftart vom Text fest

Schriftarten: 
kleine Schrift: u8x8_font_chroma48medium8_r
grosse Schrift: u8x8_font_px437wyse700b_2x2_r
*/

#include <Arduino_SensorKit.h>


void setup()
{

// TODO: Starte die Kommunikation mit dem Display


Oled.setFlipMode(true); // Legt die Orientation vom Diasplay fest

}

void loop()
{
  //TEST: Ändere die Schriftarten: 
  Oled.setFont(u8x8_font_chroma48medium8_r); // Schriftart

  // TEST: Was passiert, wenn du die Zahlen änderst?
  Oled.setCursor(33, 33);    // Position des Textes auf dem Display

  // TODO: Ersetze ?? mit deinem eigenen Text. (Lass " " stehen!) -> Falls du mehr als eine Zeile schreiben willst, nutze Oled.println(""); Maximal 15 Zeichen pro Zeile!
  Oled.print("??");   


  Oled.refreshDisplay();  // Aktualisiert das Diaplay
  delay(10); // kurze Wartezeit für ein flüssiges Bild auf dem Display
  
}
