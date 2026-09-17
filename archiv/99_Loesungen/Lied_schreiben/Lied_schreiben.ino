// Pin für den Buzzer definieren
const int Buzzer = 5;

// Noten-Frequenzen definieren
const int C = 523;
const int D = 587;
const int E = 659;
const int F = 698;
const int G = 784;
const int A = 880;
const int H = 988;

//TEST: Falls du eine Note eine Oktave höher oder tiefer brauchst, 
//      verdopple oder halbiere die Frequenz-Zahl 

// Dauer jeder Note definieren
// TEST: Du kannst diese Zahl bei Bedarf ändern

const int Spielzeit = 500;

// Benutzerdefinierte Funktion für Ton
void Ton(int frequenz, int spielzeit) {
  tone(Buzzer, frequenz); // Erzeugt den Ton mit der angegebenen Frequenz
  delay(spielzeit);       // Wartet für die angegebene Spielzeit
  noTone(Buzzer);         // Schaltet den Ton aus
  delay(100);             // Wartet zusätzlich 100 ms
}

void setup() {
  // Kein Setup nötig für den Buzzer
}
//TODO: Wähle ein Lied aus (Google) und spiel es ab!
void loop() {
  // Beispiel: "Alle meine Entchen"
  Ton(C, Spielzeit); 
  Ton(D, Spielzeit); 
  Ton(E, Spielzeit); 
  Ton(F, Spielzeit); 
  Ton(G, Spielzeit); 
  Ton(G, Spielzeit); 
  Ton(A, Spielzeit); 
  Ton(A, Spielzeit);
  Ton(A, Spielzeit); 
  Ton(A, Spielzeit);
  Ton(G, Spielzeit); 

  delay(1000); // Kleine Pause vor der nächsten Wiederholung
}
