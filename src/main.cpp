#include <Arduino.h>
#include "Mux.h"

#include "read_functions.h"

using namespace admux;


// pin config
#define buttonMpSignal 8 // button multiplexer
#define arcadeMpSignal 7 // arcade multiplexer

#define mpA 4 // multiplexer select A
#define mpB 5 // multiplexer select B
#define mpC 6 // multiplexer select C

const int pots[] = { A0, A1, A2 }; // pot 1, 2, 3

// val history
byte butValLast[8] = { HIGH,  HIGH,  HIGH,  HIGH,  HIGH,  HIGH,  HIGH,  HIGH };
byte arcValLast[8] = { HIGH,  HIGH,  HIGH,  HIGH,  HIGH,  HIGH,  HIGH,  HIGH };

int potVal[3] = { 0, 0, 0 };
byte controlVal[3] = { 0, 0, 0 };
byte controlValLast[3] = { 0, 0, 0 };

// Mux setup
Mux butMux(Pin(buttonMpSignal, INPUT_PULLUP, PinType::Digital), Pinset(mpA, mpB, mpC));
Mux arcMux(Pin(arcadeMpSignal, INPUT_PULLUP, PinType::Digital), Pinset(mpA, mpB, mpC));


void setup() {
  Serial.begin(9600);

  // pot setup
  for (byte i = 0; i < 3; i++)
  {
    pinMode(pots[i], INPUT);
  }  

  u8g2.begin();
  u8g2.enableUTF8Print();
  print_splash();
  u8g2.sendBuffer();

  //print_note(23);
}


void loop() {

  // read multiplexers
  readMux(butMux, midiChannel, butNotes, butValLast);
  readMux(arcMux, midiChannel, arcNotes, arcValLast);

  // read pots
  readPots(pots, potVal, controlVal, controlValLast);

  // todo:
  // - Display-Timeouts, zurück zum Splash!?
  // - MIDI Note off anzeigen
  // - Versions-Anzeige
  // - Setup-Mode, ggf. unterschiedliche Maps, Map-Auswahl im EEPROM speichern
  // - init von Vals mit den richtigen Werten, um springen beim Einschalten zu vermeiden!?
  
}