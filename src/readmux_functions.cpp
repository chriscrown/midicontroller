#include "readmux_functions.h"

void readMux(Mux mux, const byte midiChannel, const byte midiNotes[], byte historyVal[]) {

  byte data;
  for (byte i = 0; i < mux.channelCount(); i++)
  {
    data = mux.read(i);

    if (data != historyVal[i]) // val changed
    {
      if (data == LOW)
      {
        noteOn(midiChannel, midiNotes[i], 64);   // 64 = normal velocity
        print_note(midiNotes[i]);
      } else
      {
        noteOff(midiChannel, midiNotes[i], 64);
        u8g2.clear();
      }

      MidiUSB.flush();
      historyVal[i] = data;    
    }
  }

}