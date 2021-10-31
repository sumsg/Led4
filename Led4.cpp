#include "Led4.h"

void Led4::begin(uint8_t SCLK, uint8_t RCLK, uint8_t DIO)
{
  _SCLK = SCLK;
  _RCLK = RCLK;
  _DIO = DIO;
  if (_SCLK + _RCLK + _DIO == 0)
  {
    Serial.println("Please check Led4 pin!");
  }
  pinMode(_SCLK, OUTPUT);
  pinMode(_RCLK, OUTPUT);
  pinMode(_DIO, OUTPUT);
  digitalWrite(_SCLK, HIGH);
  digitalWrite(_RCLK, HIGH);
  digitalWrite(_DIO, HIGH);
}

void Led4::write(unsigned char c)
{
  for (unsigned char i = 8; i >= 1; i--)
  {
    if (c & 0x80)
    {
      digitalWrite(_DIO, HIGH);
    }
    else
    {
      digitalWrite(_DIO, LOW);
    }
    c <<= 1;
    relock(0x1);
    if (digitalRead(_DIO) == 0)
      pinMode(_DIO, HIGH);
  }
}
void Led4::putUnit(int unit)
{
  write(pow(2, unit));
  relock(0x0);
}
void Led4::putDot(int unit)
{
  if (unit >= 0 && unit <= 3)
  {
    putCode(0x7F, unit);
  }
};
void Led4::putMinus(int unit)
{
  putCode(0xbf, unit);
}
//
void Led4::putCode(int code, int unit)
{
  write(code);
  putUnit(unit);
}

void Led4::put(unsigned char num, int unit)
{
  write(*(LEDTABLE + num));
  putUnit(unit);
}

// void Led4::display(float LED)
// {
//   int LED1 = String(LED).toFloat();
//   display(LED1, dot);
// }
void Led4::display(String LED, int dot)
{
  int LED1 = String(LED).toInt();
  display(LED1, dot);
}
void Led4::display(int LED, int dot)
{
  putDot(dot);

  if (LED <= 9999 && LED > 999)
  {
    put(LED / 1000, 3);
    put((LED % 1000) / 100, 2);
    put((LED % 100) / 10, 1);
    put(LED % 10, 0);
  }
  else if (LED <= 999 && LED > 99)
  {
    put(LED / 100, 2);
    put((LED % 100) / 10, 1);
    put(LED % 10, 0);
  }
  else if (LED <= 99 && LED > 9)
  {
    put(LED / 10, 1);
    put(LED % 10, 0);
  }
  else if (LED <= 9 && LED >= 0)
  {
    put(LED, 0);
  }
  ///
  else if (LED >= -999 && LED < 0)
  {
    LED = abs(LED);
    if (LED <= 999 && LED > 99)
    {
      putMinus(3);
    }
    else if (LED <= 99 && LED > 9)
    {
      putMinus(2);
    }
    else if (LED <= 9 && LED >= 0)
    {
      putMinus(1);
    }
    display(LED, dot);
  }
  else if (LED > 9999 || LED < -999)
  {
    putFail();
  }
}

void Led4::display(unsigned char LED[4], int dot)
{
  putDot(dot);

  for (int i = 3; i >= 0; i--)
  {
    if (String(LED[i]) == "-")
    {
      LED[i] = 0xbf;
    }

    if (i == dot)
    {
      put(LED[i], (3 - i));
    }
    else
    {
      put(LED[i], (3 - i));
    }
  }
}

void Led4::relock(const uint8_t flag)
{
  if (flag == 0x1)
  {
    digitalWrite(_SCLK, LOW);
    digitalWrite(_SCLK, HIGH);
  }
  else
  {
    digitalWrite(_RCLK, LOW);
    digitalWrite(_RCLK, HIGH);
  }
}
void Led4::loading()
{
  unsigned char code[6] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF};
  for (size_t i = 0; i < 6; i++)
  {
    write(code[i]);
    putUnit(0);
    delay(300);
  }
}
void Led4::putFail()
{
  for (size_t i = 0; i < 4; i++)
  {
    putCode(0xbf, i);
  }
}