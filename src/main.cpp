#include <Arduino.h>
#include "Mux.h"

#include "midi_functions.h"
#include "display_functions.h"
#include "readmux_functions.h"

using namespace admux;

// pin config
#define buttonMpSignal 8 // button multiplexer
#define arcadeMpSignal 7 // arcade multiplexer

#define mpA 4 // multiplexer select A
#define mpB 5 // multiplexer select B
#define mpC 6 // multiplexer select C

const int pots[] = { A0, A1, A2 }; // pot 1, 2, 3

// MIDI config
const byte midiChannel = 0;
const byte butNotes[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
const byte arcNotes[] = { 11, 12, 13, 14, 15, 16, 17, 18 };
const byte potNotes[] = { 21, 22, 23 };

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
  for (byte i = 0; i < 3; i++)
  {
    potVal[i] = (potVal[i] * 12) + (analogRead(pots[i]) * 4);
    potVal[i] = (potVal[i] + 8) >> 4;
    potVal[i] = min(potVal[i], 1020);
    potVal[i] = max(potVal[i], 2);
    controlVal[i] = map(potVal[i], 2, 1020, 0, 127);
    
    if (controlVal[i] != controlValLast[i]) // val changed
    {
      Serial.print("potVal[");
      Serial.print(i);
      Serial.print("]=");
      Serial.print(potVal[i]);
      Serial.print("\tControlVal=");
      Serial.print(controlVal[i]);
      Serial.print("\tControlValLast=");
      Serial.print(controlValLast[i]);
      Serial.println();
      
      controlChange(0, potNotes[i], controlVal[i]);
      print_control(potNotes[i], controlVal[i]);
      MidiUSB.flush();
      controlValLast[i] = controlVal[i];
    }

    delay(5); 
  }

  // todo:
  // - Display-Timeouts, zurück zum Splash!?
  // - MIDI Note off anzeigen
  // - Versions-Anzeige
  // - Setup-Mode, ggf. unterschiedliche Maps, Map-Auswahl im EEPROM speichern
  
}

