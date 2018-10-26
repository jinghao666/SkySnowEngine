package android.skysnow.com.myapplication;

/**
 * Created by liuqian8 on 2018/10/26.
 */

public class SkySnowNativeAPI
{
    // Used to load the 'SkySnow' library on application startup.
    static {
        System.loadLibrary("SkySnow_Lib");
    }

    public SkySnowNativeAPI()
    {
    }

    public native String stringFromJNI();
}
