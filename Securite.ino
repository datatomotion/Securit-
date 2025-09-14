/*
/////////////////////////////////////////////////////////////
//                   DATA To Motion
//                   Laser Security System
//
// Matériel utilisé :
// - Arduino UNO
// - Module KY-018 (photorésistance) -> A0
// - Buzzer -> D8
// - LED rouge -> D9
// - LED verte -> D10
// - Laser diode pointant sur la LDR
//
// Fonctionnement :
// - Si le faisceau laser est coupé → LED rouge ON + buzzer ON
// - Sinon → LED verte ON
//
/////////////////////////////////////////////////////////////
*/

// Déclaration des broches utilisées
const int buzzerPin = 8;     // Buzzer branché sur D8
const int ldrPin    = A0;    // Capteur KY-018 branché sur A0 (entrée analogique)
const int ledRouge  = 9;     // LED rouge branchée sur D9
const int ledVerte  = 10;    // LED verte branchée sur D10

// Valeur seuil pour détecter si le faisceau est coupé ou non
// À ajuster selon la lumière ambiante
const int threshold = 200;

void setup() {
  // Démarrage de la communication série (permet d'afficher des valeurs sur PC)
  Serial.begin(9600);

  // Affiche un message de bienvenue au lancement
  Serial.println("==================================");
  Serial.println("   DATA To MOTION");
  Serial.println("   Laser Security System");
  Serial.println("==================================");

  // Définition des broches en sortie
  pinMode(buzzerPin, OUTPUT);  // Buzzer en sortie
  pinMode(ledRouge, OUTPUT);   // LED rouge en sortie
  pinMode(ledVerte, OUTPUT);   // LED verte en sortie
}

void loop() {
  // Lecture de la valeur envoyée par le capteur KY-018 (entre 0 et 1023)
  int valeurLDR = analogRead(ldrPin);

  // Affiche la valeur mesurée dans le moniteur série
  Serial.print("Valeur capteur LDR : ");
  Serial.println(valeurLDR);

  // Test de la condition : si la valeur dépasse le seuil → laser coupé
  if (valeurLDR > threshold) {
    // Laser bloqué : alarme ON
    digitalWrite(buzzerPin, HIGH);   // Active le buzzer
    digitalWrite(ledRouge, HIGH);    // Allume LED rouge
    digitalWrite(ledVerte, LOW);     // Éteint LED verte
  } else {
    // Laser détecté : sécurité OK
    digitalWrite(buzzerPin, LOW);    // Coupe le buzzer
    digitalWrite(ledRouge, LOW);     // Éteint LED rouge
    digitalWrite(ledVerte, HIGH);    // Allume LED verte
  }

  // Pause de 100 ms pour éviter trop de lecture rapide
  delay(100);
}
