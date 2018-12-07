//
// Created by liuqian8 on 2018/11/21.
//

#pragma once

#include "GraphicsDefs.h"
#include "Common.h"
#include <string>
#include <vector>
#include <Input/File.h>
#include "Object.h"
using namespace std;

class ShaderVariation;

enum PassLightingMode
{
    LIGHTING_UNLIT = 0,//
    LIGHTING_PERVERTEX,
    LIGHTING_PERPIXEL
};

class Pass
{
public:
    Pass(const string& passName);

    virtual ~Pass();

    void SetBlendMode(BlendMode mode);
    //设置选择模式覆盖。默认的选择模式是从材料中读取的。设置非法剔除模式max_cullmode以再次禁用覆盖。
    void SetCullMode(CullMode mode);

    void SetDepthTestMode(CompareMode mode);

    void SetLightingMode(PassLightingMode mode);
    /// Set depth write on/off.
    void SetDepthWrite(bool enable);
    /// Set alpha-to-coverage on/off.
    void SetAlphaToCoverage(bool enable);
    /// Set whether requires desktop level hardware.
    void SetIsDesktop(bool enable);
    /// Set vertex shader name.
    void SetVertexShader(const string& name);
    /// Set pixel shader name.
    void SetPixelShader(const string& name);
    /// Set vertex shader defines. Separate multiple defines with spaces.
    void SetVertexShaderDefines(const string& defines);
    /// Set pixel shader defines. Separate multiple defines with spaces.
    void SetPixelShaderDefines(const string& defines);
    /// Set vertex shader define excludes. Use to mark defines that the shader code will not recognize, to prevent compiling redundant shader variations.
    void SetVertexShaderDefineExcludes(const string& excludes);
    /// Set pixel shader define excludes. Use to mark defines that the shader code will not recognize, to prevent compiling redundant shader variations.
    void SetPixelShaderDefineExcludes(const string& excludes);
    /// Reset shader pointers.
    void ReleaseShaders();
    /// Mark shaders loaded this frame.
    void MarkShadersLoaded(unsigned frameNumber);

    /// Return pass name.
    const string& GetName() const { return name_; }

    /// Return pass index. This is used for optimal render-time pass queries that avoid map lookups.
    unsigned GetIndex() const { return index_; }

    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }

    /// Return culling mode override. If pass is not overriding culling mode (default), the illegal mode MAX_CULLMODES is returned.
    CullMode GetCullMode() const { return cullMode_; }

    /// Return depth compare mode.
    CompareMode GetDepthTestMode() const { return depthTestMode_; }

    /// Return pass lighting mode.
    PassLightingMode GetLightingMode() const { return lightingMode_; }

    /// Return last shaders loaded frame number.
    unsigned GetShadersLoadedFrameNumber() const { return shadersLoadedFrameNumber_; }

    /// Return depth write mode.
    bool GetDepthWrite() const { return depthWrite_; }

    /// Return alpha-to-coverage mode.
    bool GetAlphaToCoverage() const { return alphaToCoverage_; }

    /// Return whether requires desktop level hardware.
    bool IsDesktop() const { return isDesktop_; }

    /// Return vertex shader name.
    const string& GetVertexShader() const { return vertexShaderName_; }

    /// Return pixel shader name.
    const string& GetPixelShader() const { return pixelShaderName_; }

    /// Return vertex shader defines.
    const string& GetVertexShaderDefines() const { return vertexShaderDefines_; }

    /// Return pixel shader defines.
    const string& GetPixelShaderDefines() const { return pixelShaderDefines_; }

    /// Return vertex shader define excludes.
    const string& GetVertexShaderDefineExcludes() const { return vertexShaderDefineExcludes_; }

    /// Return pixel shader define excludes.
    const string& GetPixelShaderDefineExcludes() const { return pixelShaderDefineExcludes_; }

    /// Return vertex shaders.
    vector<ShaderVariation>& GetVertexShaders() { return vertexShaders_; }

    /// Return pixel shaders.
    vector<ShaderVariation >& GetPixelShaders() { return pixelShaders_; }

    /// Return vertex shaders with extra defines from the renderpath.
    vector<ShaderVariation>& GetVertexShaders(const string& extraDefinesHash);
    /// Return pixel shaders with extra defines from the renderpath.
    vector<ShaderVariation>& GetPixelShaders(const string& extraDefinesHash);
    /// Return the effective vertex shader defines, accounting for excludes. Called internally by Renderer.
    string GetEffectiveVertexShaderDefines() const;
    /// Return the effective pixel shader defines, accounting for excludes. Called internally by Renderer.
    string GetEffectivePixelShaderDefines() const;

private:
    /// Pass index.
    unsigned index_;
    /// Blend mode.
    BlendMode blendMode_;
    /// Culling mode.
    CullMode cullMode_;
    /// Depth compare mode.
    CompareMode depthTestMode_;
    /// Lighting mode.
    PassLightingMode lightingMode_;
    /// Last shaders loaded frame number.
    unsigned shadersLoadedFrameNumber_;
    /// Depth write mode.
    bool depthWrite_;
    /// Alpha-to-coverage mode.
    bool alphaToCoverage_;
    /// Require desktop level hardware flag.
    bool isDesktop_;
    /// Vertex shader name.
    string vertexShaderName_;
    /// Pixel shader name.
    string pixelShaderName_;
    /// Vertex shader defines.
    string vertexShaderDefines_;
    /// Pixel shader defines.
    string pixelShaderDefines_;
    /// Vertex shader define excludes.
    string vertexShaderDefineExcludes_;
    /// Pixel shader define excludes.
    string pixelShaderDefineExcludes_;
    /// Vertex shaders.
    vector<ShaderVariation> vertexShaders_;
    /// Pixel shaders.
    vector<ShaderVariation> pixelShaders_;
    /// Vertex shaders with extra defines from the renderpath.
//    HashMap<StringHash, Vector<SharedPtr<ShaderVariation> > > extraVertexShaders_;
    SN_HashMap<string, vector<ShaderVariation> > extraVertexShaders_;
    /// Pixel shaders with extra defines from the renderpath.
    SN_HashMap<string, vector<ShaderVariation> > extraPixelShaders_;
    /// Pass name.
    string name_;
};


class Technique:public Object
{
    ENGINE_OBJECT(Technique,Object);
    friend class Renderer;
public:
    /// Construct.
    Technique(Context* context);
    /// Destruct.
    virtual ~Technique() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(File& source);

    /// Set whether requires desktop level hardware.
    void SetIsDesktop(bool enable);
    /// Create a new pass.
    Pass* CreatePass(const string& passName);
    /// Remove a pass.
    void RemovePass(const string& passName);
    /// Reset shader pointers in all passes.
    void ReleaseShaders();
    /// Clone the technique. Passes will be deep copied to allow independent modification.
    Technique* Clone(const string& cloneName = NULL) const;

    /// Return whether requires desktop level hardware.
    bool IsDesktop() const { return isDesktop_; }

    /// Return whether technique is supported by the current hardware.
    bool IsSupported() const { return !isDesktop_ || desktopSupport_; }

    /// Return whether has a pass.
    bool HasPass(unsigned passIndex) const { return passIndex < passes_.size() && passes_[passIndex] != nullptr; }

    /// Return whether has a pass by name. This overload should not be called in time-critical rendering loops; use a pre-acquired pass index instead.
    bool HasPass(const string& passName) const;

    /// Return a pass, or null if not found.
    Pass* GetPass(unsigned passIndex) const { return passIndex < passes_.size() ? passes_[passIndex] : nullptr; }

    /// Return a pass by name, or null if not found. This overload should not be called in time-critical rendering loops; use a pre-acquired pass index instead.
    Pass* GetPass(const string& passName) const;

    /// Return a pass that is supported for rendering, or null if not found.
    Pass* GetSupportedPass(unsigned passIndex) const
    {
        Pass* pass = passIndex < passes_.size() ? passes_[passIndex]: nullptr;
        return pass && (!pass->IsDesktop() || desktopSupport_) ? pass : nullptr;
    }

    /// Return a supported pass by name. This overload should not be called in time-critical rendering loops; use a pre-acquired pass index instead.
    Pass* GetSupportedPass(const string& passName) const;

    /// Return number of passes.
    unsigned GetNumPasses() const;
    /// Return all pass names.
    vector<string> GetPassNames() const;
    /// Return all passes.
    vector<Pass*> GetPasses() const;

    /// Return a clone with added shader compilation defines. Called internally by Material.
    Technique CloneWithDefines(const string& vsDefines, const string& psDefines);

    /// Return a pass type index by name. Allocate new if not used yet.
    static unsigned GetPassIndex(const string& passName);

    /// Index for base pass. Initialized once GetPassIndex() has been called for the first time.
    static unsigned basePassIndex;
    /// Index for alpha pass. Initialized once GetPassIndex() has been called for the first time.
    static unsigned alphaPassIndex;
    /// Index for prepass material pass. Initialized once GetPassIndex() has been called for the first time.
    static unsigned materialPassIndex;
    /// Index for deferred G-buffer pass. Initialized once GetPassIndex() has been called for the first time.
    static unsigned deferredPassIndex;
    /// Index for per-pixel light pass. Initialized once GetPassIndex() has been called for the first time.
    static unsigned lightPassIndex;
    /// Index for lit base pass. Initialized once GetPassIndex() has been called for the first time.
    static unsigned litBasePassIndex;
    /// Index for lit alpha pass. Initialized once GetPassIndex() has been called for the first time.
    static unsigned litAlphaPassIndex;
    /// Index for shadow pass. Initialized once GetPassIndex() has been called for the first time.
    static unsigned shadowPassIndex;

private:
    /// Require desktop GPU flag.
    bool isDesktop_;
    /// Cached desktop GPU support flag.
    bool desktopSupport_;
    /// Passes.
    vector<Pass*> passes_;
    /// Cached clones with added shader compilation defines.
    SN_HashMap<std::pair<string, string>, Technique> cloneTechniques_;

    /// Pass index assignments.
    static SN_HashMap<string, unsigned> passIndices;
};
