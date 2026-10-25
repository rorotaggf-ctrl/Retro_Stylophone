# Retro Stylophone

A retro-style pocket synthesizer built with an ESP32 for **Hack Club Half-Life (Week 3: Design Your Instrument)**.

The instrument utilizes the ESP32's built-in capacitive touch peripheral to create a 13-pad chromatic keyboard directly out of exposed PCB copper pads, completely eliminating mechanical button wear and complex key soldering.

---

## Features

- **Microcontroller:** ESP32 NodeMCU (USB-C, dual-core 240 MHz, 320 KB SRAM)
- **Keyboard:** 13 capacitive touch PCB pads (Full chromatic octave: C4 to C5 including sharps/flats)
- **Sound Generation:** 5V Passive Piezo Buzzer driven via hardware PWM / DAC output
- **Modulation & Pitch-Bend:** 10K linear potentiometer for dynamic pitch modulation and glide effects
- **Octave / Mode Select:** SPDT mini slide switch for octave shifting and sound mode toggling
- **Form Factor:** Compact 2-layer PCB designed in KiCad with integrated GND planes

---

## Pinout Configuration

Everything is mounted using through-hole female pin headers so the ESP32 can be swapped or serviced at any time.

| Component | Pin Function | ESP32 Pin Header | Pin / GPIO | Notes |
| :--- | :--- | :--- | :--- | :--- |
| **Touch Keyboard** | C4 (Root) | `J2` Pin 13 | GPIO 4 | Capacitive Touch 0 |
| | C#4 | `J2` Pin 14 | GPIO 0 | Capacitive Touch 1 |
| | D4 | `J2` Pin 16 | GPIO 15 | Capacitive Touch 3 |
| | D#4 | `J2` Pin 15 | GPIO 2 | Capacitive Touch 2 |
| | E4 | `J1` Pin 15 | GPIO 13 | Capacitive Touch 4 |
| | F4 | `J1` Pin 13 | GPIO 12 | Capacitive Touch 5 |
| | F#4 | `J1` Pin 3 | GPIO 36 | High-impedance ADC antenna pad |
| | G4 | `J1` Pin 12 | GPIO 14 | Capacitive Touch 6 |
| | G#4 | `J1` Pin 4 | GPIO 39 | High-impedance ADC antenna pad |
| | A4 | `J1` Pin 11 | GPIO 27 | Capacitive Touch 7 |
| | A#4 | `J1` Pin 6 | GPIO 35 | High-impedance ADC antenna pad |
| | B4 (H4) | `J1` Pin 8 | GPIO 33 | Capacitive Touch 8 |
| | C5 (High C) | `J1` Pin 7 | GPIO 32 | Capacitive Touch 9 |
| **Audio Output** | Buzzer (+) | `J1` Pin 9 | GPIO 25 | Hardware PWM Audio Output |
| | Buzzer (-) | `J1` Pin 14 | GND | Common Ground |
| **Pitch Control** | Poti Wiper | `J1` Pin 5 | GPIO 34 | ADC1 Analog Input (0 - 3.3V) |
| | Poti Pin 1 / 3 | `J1` Pin 1 / 14 | 3V3 / GND | Potentiometer Reference Rails |
| **Octave Switch** | SW1 Center | `J2` Pin 8 | GPIO 19 | Active LOW (Internal Pull-Up) |
| | SW1 Pin 3 | `J1` Pin 14 | GND | Ground Reference Rail |

---

## Bill of Materials (BoM)

### Grant Funded Components (Tier 1 Limit: $30.00)

> [!NOTE]
> This parts list covers multipack items funded via Hack Club Half-Life. For the raw CSV file, see `BOM.csv`.

| Part | What it's for | Qty | Price (USD) | Price (EUR) | Vendor | Purchase Link |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| ESP32 NodeMCU USB-C (2-Pack) | Synthesizer sound engine & touch controller | 1 | $15.66 | 13,98 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B0DB8CYQBS) |
| 10K Linear Potentiometer WH148 (10-Pack) | Pitch-bend and waveform modulation | 1 | $7.04 | 6,29 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B0GVP99HZ2) |
| SPDT Mini Slide Switch (40-Pack) | Power and octave mode switch | 1 | $5.59 | 4,99 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B07M9Z4CBP) |
| **Total** | | | **$28.29** | **25,26 €** | | |

*Remaining Tier 1 Budget: $1.71*

### Additional Self-Funded Components

> [!IMPORTANT]
> The following components are funded personally or sourced from existing workshop inventory to complete the build without exceeding the grant limit.

| Part | What it's for | Qty | Price (USD) | Price (EUR) | Vendor | Purchase Link |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Custom 2-Layer PCB (5 copies) | Main stylophone PCB with capacitive touch pads | 1 | $8.10 | 7,23 € | JLCPCB | [JLCPCB Quote](https://jlcpcb.com/quote) |
| PCB Shipping (Standard Line) | Tracked delivery to Germany | 1 | $9.55 | 8,53 € | JLCPCB | [JLCPCB Quote](https://jlcpcb.com/quote) |
| Passive Piezo Buzzer 5V (20-Pack) | Acoustic square-wave chiptune audio output | 1 | $8.83 | 7,88 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B0179I6LIK) |
| 100nF Ceramic Capacitors | Decoupling & noise filtering | 2 | $0.00 | 0,00 € | Inventory | Existing parts |
| Female Pin Headers 2.54mm | Removable socket for ESP32 | 2 | $0.00 | 0,00 € | Inventory | Existing parts |
| **Total Self-Funded** | | | **$26.48** | **23,64 €** | | |

---

## Software & Firmware

Developed in **VS Code** with PlatformIO and the Arduino framework.

- [ ] Hardware bench test (validating touch threshold tolerances, pot readings, and buzzer PWM)
- [ ] **Capacitive Touch Core:** Zero-bounce touch scanning for native touch pins (T0-T9) with adaptive baseline calibration
- [ ] **ADC Touch Matrix:** High-impedance antenna detection for remaining accidentals
- [ ] **Pitch-Bend & Glide:** Continuous frequency bend calculation via 10K potentiometer ADC readings
- [ ] **Octave Engine:** Real-time transposition (+12 semitones) via hardware slide switch
- [ ] **Chiptune Audio Driver:** Square-wave audio generation with low latency and distinct synth tone modes

---

## Hardware Previews & Design

### Initial Concept Sketch
Original top-down sketch outlining component placement, the 13-pad keyboard layout, potentiometer modulation, and buzzer position.

![Concept Sketch](images/concept_sketch.png)

### KiCad Schematic
Full schematic featuring the 38-pin ESP32 socket headers, passive piezo buzzer, modulation potentiometer, slide switch, and 13 touch pad nets.

![KiCad Schematic](images/schematic.png)

### PCB Layout
Completed 2-layer routing in KiCad with top and bottom ground copper pours and 0 DRC errors.

![PCB Layout](images/pcb_layout.png)

### 3D Render
Interactive 3D model view from KiCad showing the through-hole component headers, control pot, and exposed keyboard pads.

![PCB 3D View](images/pcb_3d.png)
