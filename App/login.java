package com.smartbracelet.smartbraceletapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;

import org.w3c.dom.Text;

public class login extends AppCompatActivity {
    TextView registerlink;
    Intent intentRegistration;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        registerlink = (TextView) findViewById(R.id.registerlink);
        registerlink.setClickable(true);

        registerlink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                intentRegistration = new Intent(login.this, Registration.class);
                startActivity(intentRegistration);
            }
        });
    }
}