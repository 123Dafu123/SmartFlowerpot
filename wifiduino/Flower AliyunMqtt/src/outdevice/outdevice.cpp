/*** 
 * @Author: Dafu Wang
 * @Date: 2022-02-18 18:18:11
 * @LastEditTime: 2022-03-13 01:01:34
 * @LastEditors: Dafu Wang
 * @FilePath: \GPIOtestc:\Users\24345\Documents\PlatformIO\Projects\Flower AliyunMqtt\src\outdevice\outdevice.cpp
 */
#include"outdevice/outdevice.h"

//外设初始化
void outdeviceInit(){
    pinMode(LedPin,OUTPUT);
    pinMode(PumpPin,OUTPUT);
    digitalWrite(LedPin,0);
    digitalWrite(PumpPin,0);
}

//外设状态更新
void outdeviceUpdate(int serverled,int serverpump){
    if(serverled==0){
        if(getTemp()<=30){
            digitalWrite(LedPin,1);
        }else{
            digitalWrite(LedPin,0);
        }
    }else{
        digitalWrite(LedPin,1);
    }

    if(serverpump==0){
        if(getHumi()<=60){
            digitalWrite(PumpPin,1);
        }else{
            digitalWrite(PumpPin,0);
        }
    }else{
        digitalWrite(PumpPin,1);
    }
}

//补光灯状态
int getLedData(){
    int led=digitalRead(LedPin);
    Serial.print("led");
    Serial.println(led);
    return led;
}

//
int getPumpData(){
    int pump=digitalRead(PumpPin);
    Serial.print("pump");
    Serial.println(pump);
    return pump;
}
