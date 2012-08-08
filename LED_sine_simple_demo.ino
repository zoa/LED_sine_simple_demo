#include "SPI.h"
#include "Zoa_WS2801.h"
#include "Sine_generator.h"
#include "MsTimer2.h"

int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels
int stripLen = 50;

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Zoa_WS2801 strip = Zoa_WS2801(stripLen, dataPin, clockPin);

Sine_generator sine_green = Sine_generator( 0, 255, 13/4, 0 );
Sine_generator sine_blue = Sine_generator( 0, 255, 7/4, 0 );
Sine_generator sine_red = Sine_generator( 0, 30, 5/4, 0 );


void setup()
{
  Serial.begin(9600);
  strip.begin();
  
  // sets the update function to be called at a given interval (ms)
  MsTimer2::set(40, &update_sine );
  MsTimer2::start();
}


void loop()
{  
  /*
  // This produces essentially the same result as the interrupt callback
  // If you uncomment this, comment out the MsTimer2 initialization lines in setup.
  for ( unsigned int i = 1; i >= 0; ++i )
  {
    update_sine();
    delay(200);
  }
  */
}

void update_sine()
{
  strip.pushFront( sine_green.next_value(), sine_red.next_value(), sine_blue.next_value() );
  strip.show();
}
