#include <Arduino.h>
// #include <Ticker.h>
#include <Led4.h>
Led4 led4;

void showLed()
{

  led4.display("-1000", 0);

  // led4.display(22, 1);

  // led4.display(-995, 2);

  // led4.display(99999);
}

void setup()
{
  Serial.begin(115200);
  /// SCLK,  RCLK,  DIO
  led4.begin(2, 14, 13);
  ///
  // flipper.attach_ms(1, flip);
}

void loop()
{
  showLed();
  delayMicroseconds(500);
}