package android.skysnow.com.myapplication.SkySnowBase;

import android.util.Log;

/**
 * Created by liuqian8 on 2018/10/26.
 */
public class SkySnowNativeAPI
{
    static {
        System.loadLibrary("SkySnow_Lib");
    }
    protected long mClassId;

    public SkySnowNativeAPI()
    {
    }

    public void skySnowCreate(Object assetsManager)
    {
        mClassId = createSkySnow(assetsManager);
        if(mClassId < 0)
            Log.e("SkySnow:","Create SkySnow Scence failure! ---SkySnowNativeAPI.java");
    }

    public boolean skySnowChange(int viewWidth,int viewHeight)
    {
        if(mClassId < 0) {
            Log.e("SkySnow:", "you have to sure SkySnow is create! ---SkySnowNativeAPI.java");
            return false;
        }
        boolean tempFlag = changeSkySnow(mClassId,viewWidth,viewHeight);
        if(!tempFlag){
            Log.e("SkySnow:","Native is change Scence failure!---SkySnowNativeAPI.java");
            return false;
        }
        return true;
    }

    public boolean renderOneFrame()
    {
        if(mClassId < 0) {
            Log.e("SkySnow:", "you have to sure SkySnow is create! ---SkySnowNativeAPI.java");
            return false;
        }
        boolean tempFlag = drawOneFrameSkySnow(mClassId);
        if(!tempFlag){
            Log.e("SkySnow:","Native is Draw Scence failure!---SkySnowNativeAPI.java");
            return false;
        }
        return true;
    }

    public boolean skySnowRelease()
    {
        if(mClassId < 0) {
            Log.e("SkySnow:", "you have to sure SkySnow is create! ---SkySnowNativeAPI.java");
            return false;
        }
        boolean tempFlag = releaseSkySnow(mClassId);
        if(!tempFlag){
            Log.e("SkySnow:","Native is Release Scence failure!---SkySnowNativeAPI.java");
            return false;
        }
        return true;
    }

    private native long createSkySnow(Object assetsManager);

    private native boolean changeSkySnow(long classId, int viewWidth,int viewHeight);

    private native boolean drawOneFrameSkySnow(long classId);

    private native boolean releaseSkySnow(long classId);
}
