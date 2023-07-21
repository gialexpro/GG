package cf.cafelutza.gg;

import static java.lang.Math.abs;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.ToggleButton;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class PresentationActivity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_presentetion);

        SensorManager sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        Sensor gyroscope=sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        sensorManager.registerListener(new SensorEventListener() {
            @Override
            public void onSensorChanged(SensorEvent sensorEvent) {
                if(sensorEvent.sensor.getType()==Sensor.TYPE_GYROSCOPE)
                {

                    ToggleButton toggleGyro=findViewById(R.id.toggleGyro);
                    int gyroscopeX= (int) (sensorEvent.values[2]*-10);
                    int gyroscopeY= (int) (sensorEvent.values[0]*-10);

                    if (toggleGyro.isChecked()) {
                        if(abs(gyroscopeX)>0||abs(gyroscopeY)>0) {
                            MainScreen.client.Send("GG:1|MOUS:0|XYMS:"+gyroscopeX+"|"+gyroscopeY+"|;");
                            Log.d("GYROX:", String.valueOf(gyroscopeX));
                        }

                    }
                }
            }

            @Override
            public void onAccuracyChanged(Sensor sensor, int i) {

            }
        }, gyroscope, SensorManager.SENSOR_DELAY_FASTEST);

        Button bpen=findViewById(R.id.bpen);
        Button berase=findViewById(R.id.berase);
        Button binapoi=findViewById(R.id.binapoi);
        Button binainte=findViewById(R.id.binainte);

        ToggleButton toggleGyro=findViewById(R.id.toggleGyro);

        UDP_Client client = MainScreen.client;

        bpen.setOnClickListener(view -> {
            client.Send("GG:1|KYBD:0|KBKY:b|;");
        });
        berase.setOnClickListener(view -> {
            client.Send("GG:1|KYBD:0|KBKY:e|;");
        });
        binapoi.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HBKS:1|;");
        });
        binainte.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HNTR:1|;");
        });
    }
}
