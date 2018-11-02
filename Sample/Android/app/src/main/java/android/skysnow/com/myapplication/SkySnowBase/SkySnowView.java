/**
 * auther: liuqian
 * Date:2018/10/28
 * https://github.com/SkySnowEngine/SkySnowEngine
 */
package android.skysnow.com.myapplication.SkySnowBase;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class SkySnowView extends GLSurfaceView
{
    private SkySnowRenderer mSkySnowRenderer;
    public SkySnowView(Context context) {
        this(context, (AttributeSet)null);
    }

    public SkySnowView(Context context, AttributeSet attributeSet)
    {
        super(context, attributeSet);
        mSkySnowRenderer = new SkySnowRenderer();
        setEGLContextClientVersion(2);
        setPreserveEGLContextOnPause(true);
        setRenderer(mSkySnowRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }
}
