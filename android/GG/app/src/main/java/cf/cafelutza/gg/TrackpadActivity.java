package cf.cafelutza.gg;

import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class TrackpadActivity extends AppCompatActivity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.trackpad_activity);

        Button b00=findViewById(R.id.b00);
        Button b01=findViewById(R.id.b01);
        Button b02=findViewById(R.id.b02);
        Button b03=findViewById(R.id.b03);
        Button b10=findViewById(R.id.b10);
        Button b11=findViewById(R.id.b11);
        Button b12=findViewById(R.id.b12);
        Button b13=findViewById(R.id.b13);
        Button b20=findViewById(R.id.b20);
        Button b21=findViewById(R.id.b21);
        Button b22=findViewById(R.id.b22);
        Button b23=findViewById(R.id.b23);

        UDP_Client client = MainScreen.client;

        b00.setOnClickListener(view -> {
            client.Send("GG:1|MBTN:4|MBUD:1|;");

            client.Send("GG:1|MBTN:4|MBUD:0|;");
            
        });

        b10.setOnClickListener(view -> {
            client.Send("GG:1|MBTN:5|MBUD:1|;");
            
            client.Send("GG:1|MBTN:5|MBUD:0|;");
            
        });


        b01.setOnClickListener(view -> {
            client.Send("GG:1|MBTN:2|MBUD:1|;");
            
            client.Send("GG:1|MBTN:2|MBUD:0|;");
            
        });

        b02.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HNTR:1|;");
            
        });

        b03.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HSTB:1|;");
            
        });

        b13.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HTAB:1|;");
            
        });

        b11.setOnClickListener(view -> {
            client.Send("GG:1|MBTN:6|MBUD:1|;");
            
            client.Send("GG:1|MBTN:6|MBUD:0|;");
            
        });

        b12.setOnClickListener(view -> {
            client.Send("GG:1|MBTN:7|MBUD:1|;");
            
            client.Send("GG:1|MBTN:7|MBUD:0|;");
            
        });

        b20.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HCMI:1|;");
            
        });

        b21.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HCPL:1|;");
            
        });

        b22.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HCTW:1|;");
            
        });

        b23.setOnClickListener(view -> {
            client.Send("GG:1|HTKY:0|HCTT:1|;");
            
        });
    }
}
