package com.smartbracelet.smartbraceletapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;

public class infant_home extends AppCompatActivity {

    Button showlive;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_infant_home);
        showlive = (Button) findViewById(R.id.showlive);
        showlive.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent cameraIntent = new Intent(MediaStore.INTENT_ACTION_VIDEO_CAMERA);
                startActivity(cameraIntent);
            }
        });
    }
}