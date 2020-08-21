extern "C" {
#include "fmif.h"
}
#include "fmsd1.h"

unsigned char note;
void setup() {
  // put your setup code here, to run once:

  note = 0x3c;
  initSPI();
  initSD1();
  Fmdriver_init();
}

void loop() {
  // put your main code here, to run repeatedly:

  Fmdriver_sendMidi(0x90);
  Fmdriver_sendMidi(note);
  Fmdriver_sendMidi(0x7f);

  delay(500);

  Fmdriver_sendMidi(0x90);
  Fmdriver_sendMidi(note);
  Fmdriver_sendMidi(0x00);

  delay(100);

  note++;
  if ( note > 0x48 ){ note = 0x3c;}
}
