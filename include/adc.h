#ifndef BATTERIE_H
#define BATTERIE_H

#include <Arduino.h>

// Spannungsteiler-Werte
extern float R1;
extern float R2;
extern float spannungsteilerFaktor;

// Grenzwert für die Spannung
extern float kritischeSpannung;

// Funktionen definieren
float messenBatteriespannung();                                      // Funktion zum Messen der Batteriespannung
void debugAusgabe(float batterieSpannung);                           // Funktion für die Debug-Ausgabe
void ledBlinken(float batterieSpannung, unsigned long aktuelleZeit); // Funktion für die LED-Steuerung
void ablauf();                                                       // Funktion für den Ablauf

#endif
