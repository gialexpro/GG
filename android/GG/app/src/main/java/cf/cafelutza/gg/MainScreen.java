package cf.cafelutza.gg;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.Spinner;

import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;


import java.util.Random;

public class MainScreen extends AppCompatActivity {
    public static UDP_Client client = null;
    @Override protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mainscreen);

        client = new UDP_Client();

        Button startbutt = findViewById(R.id.startbutt);
        Button settbutt = findViewById(R.id.settbutt);
        Button sendbutt = findViewById(R.id.sendbutt);

        Spinner spinner = findViewById(R.id.spinner);

        SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(this);
        final String[] sel = {"Default"};

        String ip = pref.getString("ip", "192.168.4.1");
        String port = pref.getString("port", "9696");
        boolean isHidden = pref.getBoolean("isHidden", false);
        String ssid = pref.getString("ssid", "ggwifi");
        String pass = pref.getString("pass", "password");
        int adminToken = Integer.parseInt(pref.getString("admintoken", "1234"));


        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                sel[0] = spinner.getSelectedItem().toString();
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
                sel[0] ="Default";
            }
        });



        startbutt.setOnTouchListener((view, motionEvent) -> {
            Intent switchActivityIntent= new Intent(MainScreen.this, MainActivity.class);
            switch (sel[0]) {
                case "Presentation":
                    switchActivityIntent = new Intent(MainScreen.this, PresentationActivity.class);
                    break;
                case "Textbox":
                    switchActivityIntent = new Intent(MainScreen.this, TextboxActivity.class);
                    break;
                case "Trackpad":
                    switchActivityIntent = new Intent(MainScreen.this, TrackpadActivity.class);
                    break;
                case "Default":
                    switchActivityIntent = new Intent(MainScreen.this, MainActivity.class);
                    break;
                default:
                    switchActivityIntent = new Intent(MainScreen.this, MainActivity.class);
                    break;
            }
            startActivity(switchActivityIntent);
            return true;
        });

        settbutt.setOnTouchListener((view, motionEvent) -> {
            Intent switchActivityIntent = new Intent(MainScreen.this, SettingsActivity.class);
            startActivity(switchActivityIntent);
            return true;
        });

        sendbutt.setOnTouchListener((view, motionEvent) -> {
            client.Send("GG:1|PREF:" + String.valueOf(adminToken) + "|LCIP:" + ip + "|;");
            
            client.Send("GG:1|PREF:" + String.valueOf(adminToken) + "|PORT:" + port + "|;");
            
            client.Send("GG:1|PREF:" + String.valueOf(adminToken) + "|HIDD:" + (isHidden?"1":"0") + "|;");
            
            client.Send("GG:1|PREF:" + String.valueOf(adminToken) + "|SSID:" + ssid + "|;");
            
            client.Send("GG:1|PREF:" + String.valueOf(adminToken) + "|PASS:" + pass + "|;");
            

            Random rnd = new Random(System.currentTimeMillis());
            int newtok = rnd.nextInt(100000);
            client.Send("GG:1|PREF:" + String.valueOf(adminToken) + "|ATOK:" + String.valueOf(newtok) + "|;");
            
            pref.edit().putString("admintoken", String.valueOf(newtok)).apply();
            Log.d("TEST ", String.valueOf(newtok));


            return true;
        });
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        client.Close();
    }
}
