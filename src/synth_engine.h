#ifndef SYNTH_ENGINE_H
#define SYNTH_ENGINE_H

#include <Arduino.h>

class SynthEngine {
public:
    void initialisieren(uint8_t pin);
    void anschlagen(float basis_ton, int8_t oktave_versatz, float biegung);
    void loslassen();
    void muster_lauf(float basis_ton, int8_t oktave_versatz);
    void naechste_wellenform();
    void trommel_schlag();
    void schritt();

private:
    uint8_t ton_pin;
    uint8_t pwm_kanal;
    uint8_t form_index;
    bool ist_aktiv;
    float ist_frequenz;
    float ziel_frequenz;
    unsigned long letzte_zeit;
};

#endif