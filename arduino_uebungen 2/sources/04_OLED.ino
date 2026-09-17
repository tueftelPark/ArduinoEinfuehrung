/* 
>> Was soll passieren? <<
Der OLED-Bildschirm auf deinem SensorKit kann nicht nur Text schreiben, sondern auch kleine Bilder zeigen!
Du baust dein Bild aus normalen Tastatur-Zeichen wie ^ . _ / \ o O - das nennt man Pixel-Kunst mit Text.
Jede Zeile Code ist eine Zeile deines Bildes. Übereinander ergeben sie ein Bild, zum Beispiel ein Gesicht.

>> Befehle <<
Oled.begin(); <- Startet die Verbindung zum Display.
Oled.clear(); <- Löscht den Bildschirm, bevor ein neues Bild gezeichnet wird.
Oled.setCursor(X, Y); <- Setzt die Schreibposition auf dem Display.
Oled.println("Text"); <- Schreibt eine Zeile Text und springt danach automatisch eine Zeile tiefer.
Oled.refreshDisplay(); <- Zeigt das gezeichnete Bild wirklich an. Ohne diesen Befehl siehst du nichts!
*/

#include <Arduino_SensorKit.h>

void setup()
{
  //TODO: Starte die Verbindung zum Display
  //EXPECT: ^Oled\.begin\s*\(\s*\)\s*;$

  
  Oled.setFlipMode(true);
  Oled.setFont(u8x8_font_chroma48medium8_r);
}

void loop()
{
  //TODO: Lösche zuerst den Bildschirm, damit sich nichts überlagert
  //EXPECT: ^Oled\.clear\s*\(\s*\)\s*;$

  
  Oled.setCursor(0, 0);

  //TODO: Schreibe hier deine erste Bild-Zeile mit Oled.println("...")
  //EXPECT: ^Oled\.println\s*\(\s*".*"\s*\)\s*;$

  //TODO: Schreibe hier deine zweite Bild-Zeile
  //EXPECT: ^Oled\.println\s*\(\s*".*"\s*\)\s*;$

  //TODO: Schreibe hier deine dritte Bild-Zeile
  //EXPECT: ^Oled\.println\s*\(\s*".*"\s*\)\s*;$

  //TODO: Jetzt das Bild wirklich anzeigen
  //EXPECT: ^Oled\.refreshDisplay\s*\(\s*\)\s*;$


  delay(2000);
}
