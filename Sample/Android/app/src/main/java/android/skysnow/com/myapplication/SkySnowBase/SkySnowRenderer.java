/**
 * auther: liuqian
 * Date:2018/10/28
 * https://github.com/SkySnowEngine/SkySnowEngine
 */
package android.skysnow.com.myapplication.SkySnowBase;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class SkySnowRenderer implements GLSurfaceView.Renderer
{
    private SkySnowNativeAPI skySnowNativeAPI;
    public SkySnowRenderer()
    {
        skySnowNativeAPI = new SkySnowNativeAPI();
    }
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        skySnowNativeAPI.skySnowCreate();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        skySnowNativeAPI.skySnowChange(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT|GLES20.GL_DEPTH_BUFFER_BIT);
        GLES20.glClearColor(1,1,0,1);
        skySnowNativeAPI.renderOneFrame();
    }
}
