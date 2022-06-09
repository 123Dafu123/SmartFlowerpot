/*** 
 * @Author: Dafu Wang
 * @Date: 2022-02-17 19:43:51
 * @LastEditTime: 2022-04-05 14:25:09
 * @LastEditors: Dafu Wang
 * @FilePath: \Flower AliyunMqtt\src\main.cpp
 */
#include <Arduino.h>
#include"outdevice/outdevice.h"
#include"sensor/sensor.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/* 连接您的WIFI SSID和密码 */
#define WIFI_SSID         "wangdafu"
#define WIFI_PASSWD       "12345678"

/* 设备的三元组信息*/
#define PRODUCT_KEY       "a1QkjBJJJKM"
#define DEVICE_NAME       "esp8266"
#define DEVICE_SECRET     "7f5fd0e1c0217f6d9f72314a1aeec365"
#define REGION_ID         "cn-shanghai"

/* 线上环境域名和端口号，不需要改 */
#define MQTT_SERVER       "a1QkjBJJJKM.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define MQTT_PORT         1883
#define MQTT_USRNAME      "esp8266&a1QkjBJJJKM"

#define CLIENT_ID         "a1QkjBJJJKM.esp8266|securemode=2,signmethod=hmacsha256,timestamp=2524608000000|"
#define MQTT_PASSWD       "6bccd7eca9bbf9df0cef7456002bf72edb1e2186c5f9d01b93c8e4e88b946235"


#define ALINK_BODY_FORMAT         "{\"id\":\"123\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"

int lastMs=0;

WiFiClient espClient;
PubSubClient client(espClient);

int serverled=0,serverpump=0;

//wifi连接
void wifiInit(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.println("WiFi not Connect");
    }
}

//mqtt连接
void mqttConnect(){
    client.setServer(MQTT_SERVER, MQTT_PORT);   /* 连接WiFi之后，连接MQTT服务器 */
    while (!client.connected())
    {
        client.connect(CLIENT_ID, MQTT_USRNAME, MQTT_PASSWD);
        Serial.println("MQTT Not Connected");
    }
    if(client.connected())
    {
      Serial.println("MQTT Connected");
      client.subscribe("/sys/a1QkjBJJJKM/esp8266/thing/service/property/set");
      
    }
}


//上报数据
void mqttPost(){
    char param[300];
    char jsonBuf[500];

    sprintf(param, "{\"soilTemperature\":%2f,\"soilHumidity\":%2f,\"led\":%d,\"pump\":%d,}", getTemp(),getHumi(),getLedData(),getPumpData());
    sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
    client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
}

//下载回传数据
void callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.println("] ");

    payload[length]='\0';
    Serial.println((char*)payload);
 
    DynamicJsonBuffer jsonBuffer(700U);
    JsonObject& root = jsonBuffer.parseObject((char*)payload);

    serverled = root["items"]["led"]["value"]; // 1
    serverpump = root["items"]["pump"]["value"]; // 1

    outdeviceUpdate(serverled,serverpump);

    mqttPost();
}

void setup(){
    Serial.begin(9600);
    sensorInit();
    outdeviceInit();
    wifiInit();
    client.setCallback(callback);
    mqttConnect();
}


void loop(){
    //心跳包 每五秒发送一次
    if (millis() - lastMs >=10000){
        lastMs=millis();
        mqttConnect();
        outdeviceUpdate(serverled,serverpump);
        mqttPost();
    }


    client.loop();
}

