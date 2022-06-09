package com.whz.flower;

import android.graphics.Color;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import com.whz.tools.Listener;

public class MainActivity extends AppCompatActivity {
    MQTT mqtt=new MQTT();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Window window=getWindow();
        window.setStatusBarColor(Color.parseColor("#FFFFFF"));
        window.getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN | View.SYSTEM_UI_FLAG_LIGHT_STATUS_BAR);

        setContentView(R.layout.activity_main);

        TextView tv1=findViewById(R.id.tv_1);
        TextView tv2=findViewById(R.id.tv_2);
        TextView tv3=findViewById(R.id.tv_3);
        TextView tv4=findViewById(R.id.tv_4);
        Button button1=findViewById(R.id.button1);
        Button button2=findViewById(R.id.button2);
        Button button3=findViewById(R.id.button3);
        Button button4=findViewById(R.id.button4);

        mqtt.init();
        mqtt.connect(getString(R.string.productKey),getString(R.string.deviceName),getString(R.string.deviceSecret),this);
        Listener listener=new Listener();
        mqtt.setListener(listener);
        mqtt.sub(getString(R.string.subtopic));

        NowSoilData SoilData=new NowSoilData(listener);
        SoilData.start();

        TextViewData textViewDataUpdate=new TextViewData(tv1,tv2,tv3,tv4,SoilData);
        textViewDataUpdate.start();

        button1.setOnClickListener(v -> {
            tv3.setText("开");
            mqtt.pub(getString(R.string.pubtopic), getString(R.string.pubmethod), getString(R.string.relytopic), "led", 1);
        });

        button2.setOnClickListener(v -> {
            tv3.setText("关");
            mqtt.pub(getString(R.string.pubtopic), getString(R.string.pubmethod), getString(R.string.relytopic), "led", 0);
        });

        button3.setOnClickListener(v -> {
            tv4.setText("开");
            mqtt.pub(getString(R.string.pubtopic), getString(R.string.pubmethod), getString(R.string.relytopic), "pump", 1);
        });

        button4.setOnClickListener(v -> {
            tv4.setText("关");
            mqtt.pub(getString(R.string.pubtopic), getString(R.string.pubmethod), getString(R.string.relytopic), "pump", 0);
        });

    }
}