#ifndef MIDI_FUNCTIONS_H
#define MIDI_FUNCTIONS_H

#include <Arduino.h>
#include "MIDIUSB.h"

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity);

void noteOff(byte channel, byte pitch, byte velocity);

void controlChange(byte channel, byte control, byte value);


#endif



