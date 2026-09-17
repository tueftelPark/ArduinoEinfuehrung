/* 
>> Was soll passieren? Was ist das Ziel der Übung? <<
Ein Bildschirm kann auch hilfreich sein, um verschiedene Informationen anzuzeigen.
Bei den Übungen zuvor haben wir den Poti gebraucht. Aber weisst du wie fest du den Poti aufgedreht hast?
Auf dem OLED-Bildschirm soll es jetzt anzeigen, wie viel % du das Poti aufgedreht hast...

>> Befehle <<
delay(ZEIT); <- macht eine Pause mit der ZEIT in Millisekunden
ZAHL = analogRead(PIN); <- Wert zwischen 0 und 1023 wird am PIN gemessen. Dieser Wert wird unter der Variable "ZAHL" gespeichert.
map(WERT, VON_MIN, VON_MAX, NACH_MIN, NACH_MAX); <- ändert den Bereich eines Wertes von einem Bereich auf einen anderen 
-> WERT ist der zu ändernde Wert, VON_MIN und VON_MAX sind der alte Bereich, NACH_MIN und NACH_MAX sind der neue Bereich

Oled.begin(); <- Startet die Kommunikation mit dem Display
Oled.setFlipMode(true oder false); <- Text auf Dsiplay wird entweder normal angezeigt oder auf dem Kopf angezeigt.
Oled.setFont(Schriftart); <- Legt die Schriftart vom Text fest
Oled.print("Text"); <- Auf dem Display wird Text angezeigt 
Oled.println("Text"); <- Am Ende vom Text wird ein Enter eingefügt, sonst gleich wie Oled.print();
*/

#include <Arduino_SensorKit.h>


void setup()
{

// TODO: Starte die Kommunikation mit dem Display


// TEST: Was passiert wenn du true mit false ersetzt?
Oled.setFlipMode(true); // Legt die Orientation vom Diasplay fest

}

void loop()
{
  // TODO: ersetze ? mit der nummer für den Drehregler
  int Sensorwert = analogRead(A?);

  
  int prozent = map(Sensorwert, 0, 1023, 100, 0); // Rechnet Zahlen zwischen 1 und 1023 in Prozentwerte um.
  Oled.setFont(u8x8_font_px437wyse700b_2x2_r); // Schriftart
  Oled.setCursor(0, 0);    // Position des Textes auf dem Display 
  Oled.print(prozent);  // Der Wert welcher unter der Variabel gespeichert ist wird auf dem Display angezeigt.
  Oled.println("%"); 
  Oled.refreshDisplay();  // Aktualisiert das Diaplay
  delay(10); // kurze Wartezeit für ein flüssiges Bild auf dem Display
  
}
