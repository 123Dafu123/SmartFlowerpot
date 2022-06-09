/*** 
 * @Author: Dafu Wang
 * @Date: 2022-02-18 18:18:23
 * @LastEditTime: 2022-03-13 01:00:08
 * @LastEditors: Dafu Wang
 * @FilePath: \GPIOtestc:\Users\24345\Documents\PlatformIO\Projects\Flower AliyunMqtt\src\sensor\sensor.cpp
 */
#include"sensor/sensor.h"

OneWire onewire(TemPin);
DS18B20 sensor(&onewire);
//传感器初始化
void sensorInit(){
    pinMode(HumiPin,INPUT);
    pinMode(TemPin,INPUT);
    sensor.begin();
}

//获取实时温度
float getTemp(){
    sensor.requestTemperatures();
    while (!sensor.isConversionComplete());  // wait until sensor is ready
    float temp=sensor.getTempC();
    Serial.print("temp:");
    Serial.println(temp);
    return temp;
    
}

//获取实时湿度
float getHumi(){
    //湿度0% 920
    //湿度100% 380
    float humi=(920-analogRead(HumiPin))*100/540.0;
    if(humi>=100){
        Serial.println("humi:100.00");
        return 100.00;
    }else if(humi<=0){
        Serial.println("humi:0.00");
        return 0.00;
    }else{
        Serial.print("humi:");
        Serial.println(humi);
        return humi;
    }
}