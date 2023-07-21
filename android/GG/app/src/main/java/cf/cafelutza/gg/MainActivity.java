package cf.cafelutza.gg;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;


public class MainActivity extends AppCompatActivity {

    Button select;
    Button start;
    Button leftb;
    Button rightb;
    Button upb;
    Button downb;

    Button leftb2;
    Button rightb2;
    Button upb2;
    Button downb2;

    Button l1b;
    Button r1b;
    Button l2b;
    Button r2b;
    //FrameLayout frameLayout;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        select=findViewById(R.id.select);
        start=findViewById(R.id.start);
        leftb=findViewById(R.id.leftb);
        rightb=findViewById(R.id.rightb);
        upb=findViewById(R.id.upb);
        downb=findViewById(R.id.downb);

        leftb2=findViewById(R.id.leftb2);
        rightb2=findViewById(R.id.rightb2);
        upb2=findViewById(R.id.upb2);
        downb2=findViewById(R.id.downb2);

        l1b=findViewById(R.id.l1b);
        r1b=findViewById(R.id.r1b);
        l2b=findViewById(R.id.l2b);
        r2b=findViewById(R.id.r2b);


        UDP_Client client = MainScreen.client;

        //frameLayout=findViewById(R.id.framelayout);

        //frameLayout.addView(new TrackpadView(getBaseContext()));

        leftb.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send("GG:1|BTTN:4|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send("GG:1|BTTN:4|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }

            }
        });

        rightb.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send("GG:1|BTTN:1|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send("GG:1|BTTN:1|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        upb.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ("GG:1|BTTN:3|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ("GG:1|BTTN:3|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        downb.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ("GG:1|BTTN:0|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ( "GG:1|BTTN:0|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });



        //DPAD







        leftb2.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ( "GG:1|DBTN:7|DBUD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ( "GG:1|DBTN:7|DBUD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        rightb2.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send  ("GG:1|DBTN:3|DBUD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send  ("GG:1|DBTN:3|DBUD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        upb2.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ( "GG:1|DBTN:1|DBUD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ( "GG:1|DBTN:1|DBUD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        downb2.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send("GG:1|DBTN:5|DBUD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send("GG:1|DBTN:5|DBUD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });













        //SHOULDERS






        l1b.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ( "GG:1|BTTN:6|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ( "GG:1|BTTN:6|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        r1b.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send  ("GG:1|BTTN:7|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ( "GG:1|BTTN:7|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        l2b.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ("GG:1|BTTN:8|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ( "GG:1|BTTN:8|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        r2b.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ("GG:1|BTTN:9|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ( "GG:1|BTTN:9|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });


        select.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ( "GG:1|BTTN:10|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ( "GG:1|BTTN:10|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

        start.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        client.Send ("GG:1|BTTN:11|BUPD:1|;");
                        return true;
                    case MotionEvent.ACTION_UP:
                        client.Send ("GG:1|BTTN:11|BUPD:0|;");
                        return true;
                    default:
                        return false;
                }
            }
        });

    }
}