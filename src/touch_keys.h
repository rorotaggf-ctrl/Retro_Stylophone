#ifndef TOUCH_KEYS_H
#define TOUCH_KEYS_H

#include <Arduino.h>

struct KontaktTaste {
    const char* klang_name;
    float ton_hoehe;
    uint8_t esp_pin;
    bool kapazitiv;
    uint16_t basis_linie;
    uint16_t schwellwert;
};

class TouchKeyboard {
public:
    void initialisieren();
    int8_t abfrage_taste();
    float frequenz_bei(int8_t index);
    void pegel_nachfuehren();

private:
    static const uint8_t TASTEN_GESAMT = 13;
    KontaktTaste tasten[TASTEN_GESAMT];
    uint16_t roh_abtastung(uint8_t index);
    unsigned long letzte_anpassung;
};

#endif