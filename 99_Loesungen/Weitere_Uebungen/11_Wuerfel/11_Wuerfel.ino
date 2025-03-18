#include "Arduino_SensorKit.h"

// Definiere den Button-Pin
int Button = 4; 

int Zahl = 0; // Startwert für die Würfelzahl
int Tasterstatus = 0; // Startwert für den Button-Status

void setup() 
{
  pinMode(Button, INPUT);  // Button als Eingabe definieren
  Oled.begin();            // OLED-Display starten
  Oled.setFlipMode(true);  // Display-Orientierung einstellen
}

void loop() 
{
  Oled.setFont(u8x8_font_amstrad_cpc_extended_r); // Schriftart setzen

  // Lese den Zustand des Buttons
  Tasterstatus = digitalRead(Button);

  if (Tasterstatus == HIGH) { 
    Oled.clearDisplay();   // Display leeren
    delay(10); 
    
    Oled.setCursor(4, 1);  // Position setzen
    Oled.print("...");     // Animation für den Würfelwurf
    delay(1000);

    Oled.clearDisplay();   // Display erneut leeren
    
    Zahl = random(1, 7);   // Zufallszahl zwischen 1 und 6 generieren
    Oled.setCursor(5, 1);  // Position setzen (mögliche Anpassung je nach Display)
    Oled.print(Zahl);      // Zahl anzeigen
    
    delay(500);  // Wartezeit nach dem Wurf
  }

  delay(10); // Kurze Pause zur Stabilisierung
}
