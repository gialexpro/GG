package cf.cafelutza.gg;

import android.os.Bundle;
import android.text.InputFilter;
import android.text.SpannableStringBuilder;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ToggleButton;

import androidx.appcompat.app.AppCompatActivity;

public class TextboxActivity extends AppCompatActivity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.textbox_activity);
        EditText text=findViewById(R.id.editTextText);
        ToggleButton lctrl=findViewById(R.id.lctrl);
        ToggleButton lshift=findViewById(R.id.lshift);
        ToggleButton lalt=findViewById(R.id.lalt);
        ToggleButton lgui=findViewById(R.id.lgui);
        ToggleButton rctrl=findViewById(R.id.rctrl);
        ToggleButton rshift=findViewById(R.id.rshift);
        ToggleButton ralt=findViewById(R.id.ralt);
        ToggleButton rgui=findViewById(R.id.rgui);
        Button send=findViewById(R.id.send);

        UDP_Client client = MainScreen.client;
        text.setSingleLine(true);
        text.setFilters(new InputFilter[]{
                (source, start, end, spanned, i2, i3) -> {
                    if (source instanceof SpannableStringBuilder) {
                        SpannableStringBuilder sourceAsSpannableBuilder = (SpannableStringBuilder)source;
                        for (int i = end - 1; i >= start; i--) {
                            char currentChar = source.charAt(i);
                            if (!(currentChar>='!'&&currentChar<='~')) {
                                sourceAsSpannableBuilder.delete(i, i+1);
                            }
                        }
                        return source;
                    } else {
                        StringBuilder filteredStringBuilder = new StringBuilder();
                        for (int i = start; i < end; i++) {
                            char currentChar = source.charAt(i);
                            if (!(currentChar>='!'&&currentChar<='~')) {
                                filteredStringBuilder.append(currentChar);
                            }
                        }
                        return filteredStringBuilder.toString();
                    }
                }
        });
/*
        lctrl.setOnClickListener(view -> lctrl.toggle() );
        lshift.setOnClickListener(view-> lshift.toggle());
        lalt.setOnClickListener(view  -> lalt.toggle()  );
        lgui.setOnClickListener(view  -> lgui.toggle()  );

        rctrl.setOnClickListener(view -> rctrl.toggle() );
        rshift.setOnClickListener(view-> rshift.toggle());
        ralt.setOnClickListener(view  -> ralt.toggle()  );
        rgui.setOnClickListener(view  -> rgui.toggle()  );*/

        send.setOnClickListener(view -> {
            boolean holdlctrl=lctrl.isChecked();
            boolean holdlshift=lshift.isChecked();
            boolean holdlalt=lalt.isChecked();
            boolean holdlgui=lgui.isChecked();
            boolean holdrctrl=rctrl.isChecked();
            boolean holdrshift=rshift.isChecked();
            boolean holdralt=ralt.isChecked();
            boolean holdrgui=rgui.isChecked();
            int mods=0;
            int bits=1;

            if(holdlctrl)   { mods|=bits; } bits<<=1;
            if(holdlshift)  { mods|=bits; } bits<<=1;
            if(holdlalt)    { mods|=bits; } bits<<=1;
            if(holdlgui)    { mods|=bits; } bits<<=1;
            if(holdrctrl)   { mods|=bits; } bits<<=1;
            if(holdrshift)  { mods|=bits; } bits<<=1;
            if(holdralt)    { mods|=bits; } bits<<=1;
            if(holdrgui)    { mods|=bits; } bits<<=1;

            client.Send("GG:1|KYBD:0|KBMD:"+mods+"|;");
            

            String tosend=text.getText().toString();
            client.Send( "GG:1|KYBD:"+tosend.length()+"|KBKS:"+tosend+"|;");

//            for (int i=0;i<tosend.length();i++) {
//                client.Send( "GG:1|KYBD:0|KBKY:"+tosend.charAt(i)+"|;");
//
//            }


            client.Send("GG:1|KYBD:0|KBRA:0|;");
            
        });
    }
}