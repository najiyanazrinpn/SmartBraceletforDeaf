package com.smartbracelet.smartbraceletapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class OtpGenerate extends AppCompatActivity {
    Button confirmotp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_otp_generate);
        confirmotp = findViewById(R.id.confirmotp);
        confirmotp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(OtpGenerate.this, infant_home.class);
                startActivity(i);
            }
        });
    }
}