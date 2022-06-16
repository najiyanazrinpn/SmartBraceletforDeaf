package com.smartbracelet.smartbraceletapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Registration extends AppCompatActivity {
    Button register;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_registration);
         register = (Button) findViewById(R.id.register);
         register.setOnClickListener(new View.OnClickListener() {
             @Override
             public void onClick(View view) {
                 Intent otpintent = new Intent(Registration.this, OtpGenerate.class);
                 startActivity(otpintent);
             }
         });
    }
}