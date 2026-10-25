#include "touch_keys.h"

void TouchKeyboard::initialisieren() {
    letzte_anpassung = 0;

    tasten[0]  = {"C4",  261.63f, 4,  true,  0, 0};
    tasten[1]  = {"CS4", 277.18f, 0,  true,  0, 0};
    tasten[2]  = {"D4",  293.66f, 15, true,  0, 0};
    tasten[3]  = {"DS4", 311.13f, 2,  true,  0, 0};
    tasten[4]  = {"E4",  329.63f, 13, true,  0, 0};
    tasten[5]  = {"F4",  349.23f, 12, true,  0, 0};
    tasten[6]  = {"FS4", 369.99f, 36, false, 0, 750};
    tasten[7]  = {"G4",  392.00f, 14, true,  0, 0};
    tasten[8]  = {"GS4", 415.30f, 39, false, 0, 750};
    tasten[9]  = {"A4",  440.00f, 27, true,  0, 0};
    tasten[10] = {"AS4", 466.16f, 35, false, 0, 750};
    tasten[11] = {"H4",  493.88f, 33, true,  0, 0};
    tasten[12] = {"C5",  523.25f, 32, true,  0, 0};

    pinMode(36, INPUT);
    pinMode(39, INPUT);
    pinMode(35, INPUT);

    delay(120);

    for (uint8_t t = 0; t < TASTEN_GESAMT; t++) {
        if (tasten[t].kapazitiv) {
            uint32_t summe = 0;
            for (uint8_t m = 0; m < 8; m++) {
                summe += touchRead(tasten[t].esp_pin);
                delay(4);
            }
            tasten[t].basis_linie = summe / 8;
            tasten[t].schwellwert = (tasten[t].basis_linie * 68) / 100;
        }
    }
}

uint16_t TouchKeyboard::roh_abtastung(uint8_t index) {
    if (tasten[index].kapazitiv) {
        return (uint16_t)touchRead(tasten[index].esp_pin);
    }
    return (uint16_t)analogRead(tasten[index].esp_pin);
}

int8_t TouchKeyboard::abfrage_taste() {
    for (uint8_t i = 0; i < TASTEN_GESAMT; i++) {
        uint16_t messpunkt = roh_abtastung(i);
        if (tasten[i].kapazitiv) {
            if (messpunkt > 0 && messpunkt < tasten[i].schwellwert) {
                return i;
            }
        } else {
            if (messpunkt > tasten[i].schwellwert) {
                return i;
            }
        }
    }
    return -1;
}

float TouchKeyboard::frequenz_bei(int8_t index) {
    if (index >= 0 && index < TASTEN_GESAMT) {
        return tasten[index].ton_hoehe;
    }
    return 0.0f;
}

void TouchKeyboard::pegel_nachfuehren() {
    if (millis() - letzte_anpassung < 1500) return;
    letzte_anpassung = millis();

    for (uint8_t k = 0; k < TASTEN_GESAMT; k++) {
        if (!tasten[k].kapazitiv) continue;
        uint16_t direkt = (uint16_t)touchRead(tasten[k].esp_pin);
        if (direkt > tasten[k].schwellwert + 4) {
            tasten[k].basis_linie = (tasten[k].basis_linie * 7 + direkt) / 8;
            tasten[k].schwellwert = (tasten[k].basis_linie * 68) / 100;
        }
    }
}