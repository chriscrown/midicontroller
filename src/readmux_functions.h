#ifndef READMUX_FUNCTIONS_H
#define READMUX_FUNCTIONS_H

#include <Arduino.h>
#include "Mux.h"
#include "midi_functions.h"
#include "midi_config.h"
#include "display_functions.h"


using namespace admux;

void readMux(Mux mux, const byte midiChannel, const byte midiNotes[], byte historyVal[]);
void readPots(const int pots[], int potVal[], byte controlVal[], byte controlValLast[]);

#endif