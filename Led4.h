#pragma once
#include <Arduino.h>

class Led4
{
protected:
  //字符表                         0     1	   2	    3	   4	   5	   6	   7    	8	   9	   A	   b	   C     d	   E     F     -
  unsigned char LEDTABLE[17] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x8C, 0xBF, 0xC6, 0xA1, 0x86, 0xFF, 0xbf};

  uint8_t _SCLK = 0;
  uint8_t _RCLK = 0;
  uint8_t _DIO = 0;
  void write(unsigned char c);
  //放置数字
  // unit 指定位置放置,可选： 0，1 ，2，3
  //是否显示小数点
  void put(unsigned char num, int unit, uint8_t dot = 0);
  //指定位置放置 unit 可选： 0，1 ，2，3
  void putUnit(int unit);
  //放置负号 unit 指定位置放置,可选： 0，1 ，2，3
  void putMinus(int unit);
  //数字溢出
  void putFail();
  void relock(const uint8_t flag);
  //重置引脚
  void reset();

public:
  //初始化
  void begin(uint8_t SCLK, uint8_t RCLK, uint8_t DIO);
  // void loop();
  //数码管刷新显示
  //数组,dot点位置:0,1,2,3
  void display(unsigned char LED[4], int dot = -1);
  //字符
  void display(String LED, int dot = -1);
  //整数
  void display(int LED, int dot = -1);
  // TODO 小数
  // void display(float LED);
};
extern Led4 led4;