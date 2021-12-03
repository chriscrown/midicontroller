#ifndef MIDI_CONFIG_H
#define MIDI_CONFIG_H

#include <Arduino.h>

// MIDI config
const byte midiChannel = 0;
const byte butNotes[] = { 5, 6, 7, 4, 3, 0, 2, 1 }; // ab C0
const byte arcNotes[] = { 17, 18, 19, 16, 12, 15, 13, 14 }; // ab C1
const byte potNotes[] = { 20, 21, 22 };

#endif