package com.whz.flower;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.whz.tools.Listener;

public class NowSoilData extends Thread{
    private double temp;
    private double humi;
    private int led;
    private int pump;
    Listener listener;
    public NowSoilData(Listener listener){
        this.listener=listener;
    }

    @SuppressWarnings("InfiniteLoopStatement")
    @Override
    public void run(){
        while (true){
            String data=listener.getData();
            if(data!=null){
                JSONObject DataObj = JSON.parseObject(data);
                temp = DataObj.getJSONObject("items").getJSONObject("soilTemperature").getDouble("value");
                humi = DataObj.getJSONObject("items").getJSONObject("soilHumidity").getDouble("value");
                led = DataObj.getJSONObject("items").getJSONObject("led").getInteger("value");
                pump = DataObj.getJSONObject("items").getJSONObject("pump").getInteger("value");
            }
        }

    }

    public double getTemp() {
        return temp;
    }

    public double getHumi() {
        return humi;
    }

    public int getLed() {
        return led;
    }

    public int getPump() {
        return pump;
    }
}