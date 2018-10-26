package android.skysnow.com.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity
{
    private SkySnowNativeAPI skySnowNativeAPI;
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.sample_text);

        skySnowNativeAPI = new SkySnowNativeAPI();
        tv.setText(skySnowNativeAPI.stringFromJNI());
    }

}
