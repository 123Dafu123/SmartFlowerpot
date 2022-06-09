/*** 
 * @Author: Dafu Wang
 * @Date: 2022-02-21 16:07:53
 * @LastEditTime: 2022-02-21 17:15:54
 * @LastEditors: Dafu Wang
 * @FilePath: \Flower AliyunMqtt\include\outdevice\outdevice.h
 */
#ifndef _OUTDEVICE_H_
#define _OUTDEVICE_H_

#include <Arduino.h>
#include"sensor/sensor.h"
#define PumpPin D4//补水
#define LedPin D3//补光

void outdeviceInit();
void outdeviceUpdate(int serverled,int serverpump);

int getLedData();
int getPumpData();

#endif // !_OUTDEVICE
