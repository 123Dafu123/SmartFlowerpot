/*** 
 * @Author: Dafu Wang
 * @Date: 2022-02-18 18:15:15
 * @LastEditTime: 2022-02-21 17:11:08
 * @LastEditors: Dafu Wang
 * @FilePath: \Flower AliyunMqtt\include\sensor\sensor.h
 */
#ifndef _SENSOR_H_
#define _SENSOR_H_
#include <Arduino.h>
#include <OneWire.h>
#include <DS18B20.h>
#define HumiPin A0
#define TemPin D5



void sensorInit();
float getTemp();
float getHumi();


#endif // !_SENSOR_H_

