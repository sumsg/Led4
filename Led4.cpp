#include "Led4.h"

void Led4::begin(uint8_t SCLK, uint8_t RCLK, uint8_t DIO)
{
  _SCLK = SCLK;
  _RCLK = RCLK;
  _DIO = DIO;
  if (_SCLK + _RCLK + _DIO == 0)
  {
    Serial.println("please check Led4 pin!");
  }
  pinMode(_SCLK, OUTPUT);
  pinMode(_RCLK, OUTPUT);
  pinMode(_DIO, OUTPUT);
  reset();
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
  delayMicroseconds(4);
}
void Led4::putMinus(int unit)
{
  put(0xbf, unit);
}
void Led4::putFail()
{
  put(0xbf, 0);
  put(0xbf, 1);
  put(0xbf, 2);
  put(0xbf, 3);
}
void Led4::put(unsigned char num, int unit, uint8_t dot)
{
  unsigned char newNum;
  newNum = *(LEDTABLE + num);

  if (dot)
  {
    newNum &= ~'\u0080';
    write(newNum);
  }
  else
  {
    if (num == 0xbf)
    {
      newNum = num;
    }
    write(newNum);
  }
  putUnit(unit);
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
  if (LED <= 9999 && LED >= 0)
  {
    if (LED >= 1000)
    {
      if (dot == 3)
      {
        put(LED / 1000, 3, dot);
      }
      else
      {
        put(LED / 1000, 3);
      }
    }
    if (LED >= 100)
    {
      if (dot == 2)
      {
        put((LED % 1000) / 100, 2, dot);
      }
      else
      {
        put((LED % 1000) / 100, 2);
      }
    }
    if (LED >= 10)
    {
      if (dot == 1)
      {
        put((LED % 100) / 10, 1, dot);
      }
      else
      {
        put((LED % 100) / 10, 1);
      }
    }
    if (LED >= 0)
    {
      if (dot == 0)
      {
        put(LED % 10, 0, dot);
      }
      else
      {
        put(LED % 10, 0);
      }
    }
  }
  else if (LED >= -999 && LED < 0)
  {
    if (LED >= -9)
    {
      putMinus(1);
      if (dot == 0)
      {
        put(abs(LED % 10), 0, dot);
      }
      else
      {
        put(abs(LED % 10), 0);
      }
    }
    else if (LED >= -99)
    {
      putMinus(2);
      if (dot == 1)
      {
        put(abs((LED % 100) / 10), 1, dot);
      }
      else
      {
        put(abs((LED % 100) / 10), 1);
      }
      put(abs(LED % 10), 0);
    }
    else if (LED >= -999)
    {
      putMinus(3);
      if (dot == 1)
      {
        put(abs((LED % 1000) / 100), 2, dot);
      }
      else
      {
        put(abs((LED % 1000) / 100), 2);
      }
      put(abs((LED % 100) / 10), 1);
      put(abs(LED % 10), 0);
    }
  }
  else if (LED > 9999 || LED < -999)
  {
    putFail();
  }
}

void Led4::display(unsigned char LED[4], int dot)
{
  for (int i = 3; i >= 0; i--)
  {
    if (String(LED[i]) == "-")
    {
      LED[i] = 0xbf;
    }

    if (i == dot)
    {
      put(LED[i], (3 - i), 1);
    }
    else
    {
      put(LED[i], (3 - i));
    }
  }
}

void Led4::reset()
{
  digitalWrite(_SCLK, HIGH);
  digitalWrite(_RCLK, HIGH);
  digitalWrite(_DIO, HIGH);
}