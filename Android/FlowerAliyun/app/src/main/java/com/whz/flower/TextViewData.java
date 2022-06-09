package com.whz.flower;

import android.annotation.SuppressLint;
import android.widget.TextView;

public class TextViewData extends Thread{
    TextView tv1;
    TextView tv2;
    TextView tv3;
    TextView tv4;
    NowSoilData nowSoilData;
    public TextViewData(TextView tv1,TextView tv2,TextView tv3,TextView tv4,NowSoilData nowSoilData){
        this.tv1=tv1;
        this.tv2=tv2;
        this.tv3=tv3;
        this.tv4=tv4;
        this.nowSoilData=nowSoilData;
    }


    @SuppressLint("DefaultLocale")
    @Override
    public void run(){
        while (true){
            tv1.setText(String.format("%.2f",nowSoilData.getTemp()));
            tv2.setText(String.format("%.2f",nowSoilData.getHumi() ));

            if (nowSoilData.getLed() == 1) {
                tv3.setText("开");
            } else {
                tv3.setText("关");
            }

            if(nowSoilData.getPump() ==1){
                tv4.setText("开");
            }else{
                tv4.setText("关");
            }
        }
    }
}
