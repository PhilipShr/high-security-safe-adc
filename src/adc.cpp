#include "adc.h"
#include "pin_defs.h"
// Spannungsteiler
float R1 = 6200.0;
float R2 = 3000.0;
float spannungsteilerFaktor = (R1 + R2) / R2;

// Grenzwert für die Spannung
float kritischeSpannung = 3.3;

// Variablen für die LED und den Debug
unsigned long letzte_blinkzeit = 0;
unsigned long letzte_debugzeit = 0;
const unsigned long blink_interval = 500;  // LED blinkt alle 500 ms
const unsigned long debug_interval = 3000; // Debug-Nachrichten alle 3000 ms

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
            digitalWrite(LED_PIN_ADC, !digitalRead(LED_PIN_ADC)); // LED umschalten
<<<<<<< HEAD
            letzte_blinkzeit = aktuelleZeit;
=======
            letzte_blinkzeit = aktuelleZeit;                      // Letzte Blink-Zeit aktualisieren
>>>>>>> 80d3962b726ef60299a5119174fea991cfd4a426
        }
    }
    else
    {
<<<<<<< HEAD
        // LED ausschalten
=======
        // Wenn die Spannung über dem kritischen Wert ist, LED ausschalten
>>>>>>> 80d3962b726ef60299a5119174fea991cfd4a426
        digitalWrite(LED_PIN_ADC, LOW);
    }
}
// Der Ablauf
void ablauf()
{
    // Zeit vom Programmstart
    unsigned long aktuelleZeit = millis();

    // Batteriespannung messen
    float batterieSpannung = messenBatteriespannung();

    // Debug Nachrichten
    if (aktuelleZeit - letzte_debugzeit >= debug_interval)
    {
        debugAusgabe(batterieSpannung);
        // Letzte Debug-Zeit aktualisieren
        letzte_debugzeit = aktuelleZeit;
    }

    // LED blinkt wenn die Spannung kritisch ist
    ledBlinken(batterieSpannung, aktuelleZeit);
}
