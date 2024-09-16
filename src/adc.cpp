#include "adc.h"

// Spannungsteiler
float R1 = 6200.0;
float R2 = 3000.0;
float spannungsteilerFaktor = (R1 + R2) / R2; // Faktor = 3

// Grenzwert für die Spannung
float kritischeSpannung = 3.0;

// Variablen für die LED und den Debug
unsigned long letzte_blinkzeit = 0;
unsigned long letzte_debugzeit = 0;
const unsigned long blink_interval = 500;  // LED blinkt alle 500 ms
const unsigned long debug_interval = 5000; // Debug-Nachrichten alle 5000 ms

// Funktion zum Messen der Batteriespannung
float messenBatteriespannung()
{
    int adcWert = analogRead(BATTERY_ADC_PIN);
    float gemesseneSpannung = (adcWert * 3.3) / 4095; // 12-Bit-ADC und 3,3V Referenzspannung
    return gemesseneSpannung * spannungsteilerFaktor; // Ursprüngliche Batteriespannung berechnen
}

// Funktion für die Debug-Ausgabe
void debugAusgabe(float batterieSpannung)
{
    Serial.print("Batteriespannung: ");
    Serial.print(batterieSpannung);
    Serial.println(" V");

    if (batterieSpannung < kritischeSpannung)
    {
        Serial.println("Warnung: Batteriespannung ist unter den kritischen Wert gefallen!");
    }
}

// Funktion für das Blinken der LED
void ledBlinken(float batterieSpannung, unsigned long aktuelleZeit)
{
    if (batterieSpannung < kritischeSpannung)
    {
        if (aktuelleZeit - letzte_blinkzeit >= blink_interval)
        {
            digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // LED umschalten
            letzte_blinkzeit = aktuelleZeit;              // Letzte Blink-Zeit aktualisieren
        }
    }
    else
    {
        // Wenn die Spannung über dem kritischen Wert ist, LED ausschalten
        digitalWrite(LED_PIN, LOW);
    }
}
// Der Ablauf
void ablauf()
{
    // Aktuelle Zeit abrufen
    unsigned long aktuelleZeit = millis();

    // Batteriespannung messen
    float batterieSpannung = messenBatteriespannung();

    // Debug-Nachrichten nur alle 5 Sekunden senden
    if (aktuelleZeit - letzte_debugzeit >= debug_interval)
    {
        debugAusgabe(batterieSpannung);
        // Letzte Debug-Zeit aktualisieren
        letzte_debugzeit = aktuelleZeit;
    }

    // LED blinken lassen, falls die Spannung kritisch ist
    ledBlinken(batterieSpannung, aktuelleZeit);
}
