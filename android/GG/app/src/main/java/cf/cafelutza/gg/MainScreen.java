package cf.cafelutza.gg;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;


import java.util.Random;

public class MainScreen extends AppCompatActivity {
    @Override protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mainscreen);


        Button startbutt = findViewById(R.id.startbutt);
        Button settbutt = findViewById(R.id.settbutt);
        Button sendbutt = findViewById(R.id.sendbutt);

        SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(this);

        String ip = pref.getString("ip", "192.168.4.1");
        String port = pref.getString("port", "9696");
        boolean isHidden = pref.getBoolean("isHidden", false);
        String ssid = pref.getString("ssid", "ggwifi");
        String pass = pref.getString("pass", "password");
        int adminToken = Integer.parseInt(pref.getString("admintoken", "1234"));




        startbutt.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                Intent switchActivityIntent = new Intent(MainScreen.this, MainActivity.class);
                startActivity(switchActivityIntent);
                return true;
            }


        });

        settbutt.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                Intent switchActivityIntent = new Intent(MainScreen.this, SettingsActivity.class);
                startActivity(switchActivityIntent);
                return true;
            }
        });

        sendbutt.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                UDP_Client client = new UDP_Client();
                client.Message = "GG:1|PREF:" + String.valueOf(adminToken) + "|LCIP:" + ip + "|;";
                client.Send();
                client.Message = "GG:1|PREF:" + String.valueOf(adminToken) + "|PORT:" + port + "|;";
                client.Send();
                client.Message = "GG:1|PREF:" + String.valueOf(adminToken) + "|HIDD:" + (isHidden?"1":"0") + "|;";
                client.Send();
                client.Message = "GG:1|PREF:" + String.valueOf(adminToken) + "|SSID:" + ssid + "|;";
                client.Send();
                client.Message = "GG:1|PREF:" + String.valueOf(adminToken) + "|PASS:" + pass + "|;";
                client.Send();

                Random rnd = new Random(System.currentTimeMillis());
                int newtok = rnd.nextInt(100000);
                client.Message = "GG:1|PREF:" + String.valueOf(adminToken) + "|ATOK:" + String.valueOf(newtok) + "|;";
                client.Send();
                pref.edit().putString("admintoken", String.valueOf(newtok)).apply();
                Log.d("TEST ", String.valueOf(newtok));


                return true;
            }
        });
    }
}
