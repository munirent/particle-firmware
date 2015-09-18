#include "application.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

void setup()
{
  // Make LED orange
  RGB.control(true);
  RGB.color(255, 128, 0);

  // This call will lock up the application thread
  Particle.publish("test");
}

void blink_led()
{
  static bool on = true;
  if(on) {
    RGB.color(0, 0, 0);
  } else {
    RGB.color(255, 128, 0);
  }
  on = !on;
  HAL_Delay_Milliseconds(50);
}

void loop()
{
  blink_led();
}

