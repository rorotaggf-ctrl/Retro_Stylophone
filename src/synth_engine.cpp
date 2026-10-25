#include "synth_engine.h"

void SynthEngine::initialisieren(uint8_t pin) {
    ton_pin = pin;
    pwm_kanal = 0;
    form_index = 0;
    ist_aktiv = false;
    ist_frequenz = 0.0f;
    ziel_frequenz = 0.0f;
    letzte_zeit = 0;

    ledcSetup(pwm_kanal, 1000, 8);
    ledcAttachPin(ton_pin, pwm_kanal);
    ledcWrite(pwm_kanal, 0);
}

void SynthEngine::anschlagen(float basis_ton, int8_t oktave_versatz, float biegung) {
    if (basis_ton <= 0.0f) {
        loslassen();
        return;
    }

    float berechnet = basis_ton;
    if (oktave_versatz > 0) {
        berechnet *= (float)(1 << oktave_versatz);
    } else if (oktave_versatz < 0) {
        berechnet /= (float)(1 << (-oktave_versatz));
    }

    berechnet *= biegung;

    if (berechnet < 25.0f) berechnet = 25.0f;
    if (berechnet > 7500.0f) berechnet = 7500.0f;

    ziel_frequenz = berechnet;

    if (!ist_aktiv || ist_frequenz <= 0.0f) {
        ist_frequenz = ziel_frequenz;
    }

    ist_aktiv = true;
    schritt();
}

void SynthEngine::loslassen() {
    if (ist_aktiv) {
        ledcWrite(pwm_kanal, 0);
        ist_aktiv = false;
        ist_frequenz = 0.0f;
        ziel_frequenz = 0.0f;
    }
}

void SynthEngine::naechste_wellenform() {
    form_index = (form_index + 1) % 4;
}

void SynthEngine::trommel_schlag() {
    for (uint8_t t = 0; t < 25; t++) {
        uint16_t krach = random(80, 2200);
        ledcWriteTone(pwm_kanal, (double)krach);
        ledcWrite(pwm_kanal, 128);
        delayMicroseconds(600);
    }
    loslassen();
}

void SynthEngine::muster_lauf(float basis_ton, int8_t oktave_versatz) {
    if (basis_ton <= 0.0f) return;
    const float akkord_stufen[4] = {1.0f, 1.2599f, 1.4983f, 2.0f};
    for (uint8_t a = 0; a < 4; a++) {
        anschlagen(basis_ton * akkord_stufen[a], oktave_versatz, 1.0f);
        delay(32);
    }
}

void SynthEngine::schritt() {
    if (!ist_aktiv) return;

    if (fabs(ziel_frequenz - ist_frequenz) > 0.5f) {
        ist_frequenz += (ziel_frequenz - ist_frequenz) * 0.35f;
    } else {
        ist_frequenz = ziel_frequenz;
    }

    ledcWriteTone(pwm_kanal, (double)ist_frequenz);

    uint8_t tastgrade[4] = {128, 64, 32, 192};
    ledcWrite(pwm_kanal, tastgrade[form_index]);
}