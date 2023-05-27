package com.example.udptest000;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;

public class MainActivity extends AppCompatActivity {

    Button button;
    Button left;
    FrameLayout frameLayout;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button=findViewById(R.id.button);
        left=findViewById(R.id.left);

        frameLayout=findViewById(R.id.framelayout);

        frameLayout.addView(new TrackpadView(getBaseContext()));

        button.setOnClickListener(v -> {
            UDP_Client Client = new UDP_Client();
            Client.Message = "HW";
            Client.Send();
        });

        left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                UDP_Client Client = new UDP_Client();
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Client.Message = "BLD";
                        break;
                    case MotionEvent.ACTION_UP:
                        Client.Message = "BLU";
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