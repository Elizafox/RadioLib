/*
   RadioLib Non-Arduino Raspberry Pi Example

   This example shows how to use RadioLib without Arduino.
   In this case, a Raspberry Pi with WaveShare SX1302 LoRaWAN Hat
   using the pigpio library.

   Can be used as a starting point to port RadioLib to any platform!
   See this API reference page for details on the RadioLib hardware abstraction
   https://jgromes.github.io/RadioLib/class_hal.html

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>

// include the hardware abstraction layer
#include "PiHal.h"

// The module is connected to GPIO dev 0, SPI dev 0, channel 0
PiHal* hal = new PiHal(0, 0, 0);

// RFM95 has the following connections:
// NSS pin:   7
// DIO1 pin:  5
// NRST pin:  25
// BUSY pin:  4
RFM95 radio = new Module(hal, 7, 5, 25, 4);

// the entry point for the program
int main(int argc, char** argv) {
  // initialize just like with Arduino
  printf("[SX1261] Initializing ... ");
  int state = radio.begin();
  if (state != RADIOLIB_ERR_NONE) {
    printf("failed, code %d\n", state);
    return(1);
  }
  printf("success!\n");

  // loop forever
  for(;;) {
    // send a packet
    printf("[SX1261] Transmitting packet ... ");
    state = radio.transmit("Hello World!");
    if(state == RADIOLIB_ERR_NONE) {
      // the packet was successfully transmitted
      printf("success!\n");

      // wait for a second before transmitting again
      hal->delay(1000);

    } else {
      printf("failed, code %d\n", state);

    }

  }

  return(0);
}
