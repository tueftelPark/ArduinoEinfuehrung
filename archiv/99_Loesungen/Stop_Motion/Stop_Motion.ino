#include <Arduino_SensorKit.h>

// Test: Hier kannst du die Spielzeit der einzelnen Bilder verändern
const int Spielzeit = 500;

const int Button = 4;
int Buttonstatus = 0;

void setup() {
  Oled.begin();
  Oled.setFlipMode(false);
  Oled.setFont(u8x8_font_chroma48medium8_r);
  pinMode(Button, INPUT);
}
//
void loop() {
Buttonstatus = digitalRead(Button);
// TODO: Rufe die Stop-Motion Bilder auf
// Hier werden die unten definierten Funktionen aufgerufen
// Wenn du den Button drückst geht die Stop-Motion los
  if (Buttonstatus == HIGH) 
  {
  Hund_2();  
  Hund_1();
  Oled.clear();
  }
}


// TODO: Mache die einzelnen Stop-Motion Bilder
// Hier definierst du die einelnen Bilder der Stop-Motion
// Übernimm die vorgegebene Struktur!
void Hund_1() {
  Oled.clear();
  Oled.setCursor(0, 0);
  Oled.println("^..^     /");
  Oled.println("/_/_____/ ");
  Oled.println("   /   /  ");
  Oled.println("  /   /   ");
  Oled.refreshDisplay();
  delay(Spielzeit);
}

void Hund_2() {
  Oled.clear();
  Oled.setCursor(0, 0);
  Oled.println(" ^..^     /");
  Oled.println(" /_/_____/ ");
  Oled.println("    /   /  ");
  Oled.println("   /   /   ");
  Oled.refreshDisplay();
  delay(Spielzeit);
}


/* Beispiele

Oled.println("^..^      /");
Oled.println("/_/_____/");
Oled.println("   /   /");
Oled.println("  /   / ");

Oled.println("   / \\__");
Oled.println("  (    @\\____");
Oled.println("  /         O");
Oled.println(" /   (_____/");
Oled.println("/_____/   U");

Oled.println(" (\\_/)");
Oled.println(" (o.o)");
Oled.println(" (> <)");
*/


/*
Vorlage if - else if  - else:

if (Bedingung) {
    Hund_1();
  } else if (Bedingung2) {
    Hund_2();
  } else if (Bedingung3) {
    ...
  }
  // Wenn keine Regel greift
  else {
    ...
  }

*/
