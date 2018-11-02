package android.skysnow.com.myapplication;

import android.skysnow.com.myapplication.SkySnowBase.SkySnowView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity
{
    private SkySnowView mSkySnowView;
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        mSkySnowView =  new SkySnowView(this);
        setContentView(mSkySnowView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mSkySnowView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mSkySnowView.onResume();
    }
    @Override
    protected void onDestroy(){
        super.onDestroy();
    }

}
