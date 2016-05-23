package com.example.user.myapplication;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Button;
import android.widget.Toast;


/**
 * Created by USER on 2016/5/22.
 */
public class DataActivity extends Activity {
    public static TextView textView;
    private Button button_map;
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dataayout);
        textView = (TextView) findViewById(R.id.dataView);
        button_map = (Button) findViewById(R.id.Map);
        button_map.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(v.getContext(), R.string.toast, Toast.LENGTH_LONG).show();
                Intent intent = new Intent();
                intent.setClass(DataActivity.this, MapActivity.class);
                startActivity(intent);
            }
        });
    }
}
