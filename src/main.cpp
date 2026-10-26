#include <Arduino.h>
#include "synth_engine.h"
#include "touch_keys.h"

static const uint8_t leiter_summs  = 25;
static const uint8_t leiter_dreher = 34;
static const uint8_t leiter_kippe  = 19;

static SynthEngine dorn;
static TouchKeyboard tastenblock;

static int8_t aktive_taste = -1;
static int8_t speicher_taste = -1;
static unsigned long prell_stempel = 0;
static unsigned long schritt_stempel = 0;
static bool arp_modus = false;

void setup() {
    Serial.begin(115200);

    pinMode(leiter_kippe, INPUT_PULLUP);
    pinMode(leiter_dreher, INPUT);

    dorn.initialisieren(leiter_summs);
    tastenblock.initialisieren();

    dorn.anschlagen(261.63f, 0, 1.0f);
    delay(40);
    dorn.anschlagen(329.63f, 0, 1.0f);
    delay(40);
    dorn.anschlagen(392.00f, 0, 1.0f);
    delay(40);
    dorn.anschlagen(523.25f, 0, 1.0f);
    delay(70);
    dorn.loslassen();
}

void loop() {
    bool schalter_gelegt = (digitalRead(leiter_kippe) == LOW);
    int8_t oktaven_sprung = schalter_gelegt ? 1 : 0;

    int adc_poti = analogRead(leiter_dreher);

    float klang_biegung;
    if (adc_poti > 3950) {
        arp_modus = true;
        klang_biegung = 1.0f;
    } else {
        arp_modus = false;
        klang_biegung = (float)map(adc_poti, 0, 3950, 70, 140) / 100.0f;
    }

    int8_t tasten_fund = tastenblock.abfrage_taste();

    if (tasten_fund != speicher_taste) {
        prell_stempel = millis();
        speicher_taste = tasten_fund;
    }

    if (millis() - prell_stempel > 10) {
        aktive_taste = tasten_fund;
    }

    if (aktive_taste != -1) {
        float grund_frequenz = tastenblock.frequenz_bei(aktive_taste);
        if (arp_modus) {
            dorn.muster_lauf(grund_frequenz, oktaven_sprung);
        } else {
            dorn.anschlagen(grund_frequenz, oktaven_sprung, klang_biegung);
        }
    } else {
        dorn.loslassen();
    }

    if (millis() - schritt_stempel > 15) {
        schritt_stempel = millis();
        dorn.schritt();
    }

    tastenblock.pegel_nachfuehren();
    delay(2);
}