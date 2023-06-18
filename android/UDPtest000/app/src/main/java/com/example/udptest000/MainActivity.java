package com.example.udptest000;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;

public class MainActivity extends AppCompatActivity {

    Button button;
    Button leftb;
    Button rightb;
    Button upb;
    Button downb;
    //FrameLayout frameLayout;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button=findViewById(R.id.button);
        leftb=findViewById(R.id.leftb);
        rightb=findViewById(R.id.rightb);
        upb=findViewById(R.id.upb);
        downb=findViewById(R.id.downb);

        //frameLayout=findViewById(R.id.framelayout);

        //frameLayout.addView(new TrackpadView(getBaseContext()));

        button.setOnClickListener(v -> {
            UDP_Client Client = new UDP_Client();
            Client.Message = "HW";
            Client.Send();
        });

        leftb.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                UDP_Client Client = new UDP_Client();
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Client.Message = "GG:1|BTTN:1|BUPD:1|;";
                        break;
                    case MotionEvent.ACTION_UP:
                        Client.Message = "GG:1|BTTN:1|BUPD:0|;";
                }
                if(Client.Message!=null) {
                    Client.Send();
                    return true;
                }
                return false;
            }
        });

        rightb.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                UDP_Client Client = new UDP_Client();
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Client.Message = "GG:1|BTTN:2|BUPD:1|;";
                        break;
                    case MotionEvent.ACTION_UP:
                        Client.Message = "GG:1|BTTN:2|BUPD:0|;";
                }
                if(Client.Message!=null) {
                    Client.Send();
                    return true;
                }
                return false;
            }
        });

        upb.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                UDP_Client Client = new UDP_Client();
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Client.Message = "GG:1|BTTN:3|BUPD:1|;";
                        break;
                    case MotionEvent.ACTION_UP:
                        Client.Message = "GG:1|BTTN:3|BUPD:0|;";
                }
                if(Client.Message!=null) {
                    Client.Send();
                    return true;
                }
                return false;
            }
        });

        downb.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                UDP_Client Client = new UDP_Client();
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Client.Message = "GG:1|BTTN:4|BUPD:1|;";
                        break;
                    case MotionEvent.ACTION_UP:
                        Client.Message = "GG:1|BTTN:1|BUPD:0|;";
                }
                if(Client.Message!=null) {
                    Client.Send();
                    return true;
                }
                return false;
            }
        });
    }
}