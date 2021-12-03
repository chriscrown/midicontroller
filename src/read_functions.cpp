#include "read_functions.h"


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


void readPots(const int pots[], int potVal[], byte controlVal[], byte controlValLast[]) {

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
}