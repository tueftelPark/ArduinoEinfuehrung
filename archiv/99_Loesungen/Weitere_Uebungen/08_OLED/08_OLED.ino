/* Befehle:
Oled.begin(); <- Startet die Kommunikation mit dem Display
Oled.setFlipMode(true oder false); <- Text auf Dsiplay wird entweder normal angezeigt oder auf dem Kopf angezeigt.
Oled.setFont(Schriftart); <- Legt die Schriftart vom Text fest
Oled.print("Text"); <- Auf dem Display wird Text angezeigt 
Oled.println(); <- Am Ende vom Text wird ein Enter eingefügt, sonst gleich wie Oled.print();
*/

#include <Arduino_SensorKit.h>


void setup()
{

// TODO: Starte die Kommunikation mit dem Display
Oled.begin();

Oled.setFlipMode(true); // Legt die Orientation vom Diasplay fest

}

void loop()
{
  
  Oled.setFont(u8x8_font_chroma48medium8_r); // Schriftart

  // TEST: Was passiert, wenn du die Zahlen änderst?
  Oled.setCursor(33, 33);    // Position des Textes auf dem Display

  // TODO: Ersetze YY mit deinem eigenen Text. -> Falls du mehr als eine Zeile schreiben willst, nutze Oled.println(;)
  Oled.print("Hello world.");   

  Oled.refreshDisplay();  // Aktualisiert das Diaplay
  delay(10); // kurze Wartezeit für ein flüssiges Bild auf dem Display
  
}
