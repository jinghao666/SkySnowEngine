//
// Created by liuqian8 on 2018/11/21.
//
#include "Technique.h"

Pass::Pass(const string &passName)
{

}

Pass::~Pass()
{

}

void Pass::SetBlendMode(BlendMode mode)
{
    blendMode_ = mode;
}

void Pass::SetCullMode(CullMode mode)
{
    cullMode_ = mode;
}

void Pass::SetDepthTestMode(CompareMode mode)
{
    depthTestMode_ = mode;
}

void Pass::SetLightingMode(PassLightingMode mode)
{
    lightingMode_ = mode;
}

void Pass::SetDepthWrite(bool enable)
{
    depthWrite_ = enable;
}

void Pass::SetAlphaToCoverage(bool enable)
{
    alphaToCoverage_ = enable;
}


void Pass::SetIsDesktop(bool enable)
{
    isDesktop_ = enable;
}

void Pass::SetVertexShader(const string& name)
{
    vertexShaderName_ = name;
    ReleaseShaders();
}

void Pass::SetPixelShader(const string& name)
{
    pixelShaderName_ = name;
    ReleaseShaders();
}

void Pass::SetVertexShaderDefines(const string& defines)
{
    vertexShaderDefines_ = defines;
    ReleaseShaders();
}

void Pass::SetPixelShaderDefines(const string& defines)
{
    pixelShaderDefines_ = defines;
    ReleaseShaders();
}

void Pass::SetVertexShaderDefineExcludes(const string& excludes)
{
    vertexShaderDefineExcludes_ = excludes;
    ReleaseShaders();
}

void Pass::SetPixelShaderDefineExcludes(const string& excludes)
{
    pixelShaderDefineExcludes_ = excludes;
    ReleaseShaders();
}

void Pass::ReleaseShaders()
{
    vertexShaders_.clear();
    pixelShaders_.clear();
    extraVertexShaders_.clear();
    extraPixelShaders_.clear();
}

void Pass::MarkShadersLoaded(unsigned frameNumber)
{
    shadersLoadedFrameNumber_ = frameNumber;
}

string Pass::GetEffectiveVertexShaderDefines() const
{
    // Prefer to return just the original defines if possible
//    if (vertexShaderDefineExcludes_.empty())
//        return vertexShaderDefines_;
//
//    vector<string> vsDefines = vertexShaderDefines_.Split(' ');
//    vector<string> vsDefines = vertexShaderDefines_.Split(' ');
//    vector<string> vsExcludes = vertexShaderDefineExcludes_.Split(' ');
////    for (unsigned i = 0; i < vsExcludes.Size(); ++i)
//    for (unsigned i = 0; i < vsExcludes.size(); ++i)
////        vsDefines.remove(vsExcludes[i]);
//        vsDefines.erase(vsExcludes[i]);
//
//    return string::Joined(vsDefines, " ");
    return NULL;
}

string Pass::GetEffectivePixelShaderDefines() const
{
    // Prefer to return just the original defines if possible
//    if (pixelShaderDefineExcludes_.empty())
//        return pixelShaderDefines_;
//
//    vector<string> psDefines = pixelShaderDefines_.Split(' ');
//    vector<string> psDefines = pixelShaderDefines_.substr(' ');
//    vector<string> psExcludes = pixelShaderDefineExcludes_.Split(' ');
//    for (unsigned i = 0; i < psExcludes.size(); ++i)
//        psDefines.Remove(psExcludes[i]);

//    return string::Joined(psDefines, " ");
    return NULL;
}

vector<ShaderVariation>& Pass::GetVertexShaders(const string& extraDefinesHash)
{
    // If empty hash, return the base shaders
    if (!extraDefinesHash.data())
        return vertexShaders_;
    else
        return extraVertexShaders_[extraDefinesHash];
}

vector<ShaderVariation>& Pass::GetPixelShaders(const string& extraDefinesHash)
{
    if (!extraDefinesHash.data())
        return pixelShaders_;
    else
        return extraPixelShaders_[extraDefinesHash];
}



unsigned Technique::basePassIndex = 0;
unsigned Technique::alphaPassIndex = 0;
unsigned Technique::materialPassIndex = 0;
unsigned Technique::deferredPassIndex = 0;
unsigned Technique::lightPassIndex = 0;
unsigned Technique::litBasePassIndex = 0;
unsigned Technique::litAlphaPassIndex = 0;
unsigned Technique::shadowPassIndex = 0;

SN_HashMap<string, unsigned> Technique::passIndices;

Technique::Technique(Context* context) :
        Object(context),
        isDesktop_(false)
{

}

Technique::~Technique()
{
}

void Technique::RegisterObject(Context* context)
{
//    context->RegisterFactory<Technique>();
}

bool Technique::BeginLoad(File& source)
{
    passes_.clear();
    cloneTechniques_.clear();

//    SetMemoryUse(sizeof(Technique));
//
//    SharedPtr<XMLFile> xml(new XMLFile(context_));
//    if (!xml->Load(source))
//        return false;
//
//    XMLElement rootElem = xml->GetRoot();
//    if (rootElem.HasAttribute("desktop"))
//        isDesktop_ = rootElem.GetBool("desktop");
//
//    String globalVS = rootElem.GetAttribute("vs");
//    String globalPS = rootElem.GetAttribute("ps");
//    String globalVSDefines = rootElem.GetAttribute("vsdefines");
//    String globalPSDefines = rootElem.GetAttribute("psdefines");
//    // End with space so that the pass-specific defines can be appended
//    if (!globalVSDefines.Empty())
//        globalVSDefines += ' ';
//    if (!globalPSDefines.Empty())
//        globalPSDefines += ' ';
//
//    XMLElement passElem = rootElem.GetChild("pass");
//    while (passElem)
//    {
//        if (passElem.HasAttribute("name"))
//        {
//            Pass* newPass = CreatePass(passElem.GetAttribute("name"));
//
//            if (passElem.HasAttribute("desktop"))
//                newPass->SetIsDesktop(passElem.GetBool("desktop"));
//
//            // Append global defines only when pass does not redefine the shader
//            if (passElem.HasAttribute("vs"))
//            {
//                newPass->SetVertexShader(passElem.GetAttribute("vs"));
//                newPass->SetVertexShaderDefines(passElem.GetAttribute("vsdefines"));
//            }
//            else
//            {
//                newPass->SetVertexShader(globalVS);
//                newPass->SetVertexShaderDefines(globalVSDefines + passElem.GetAttribute("vsdefines"));
//            }
//            if (passElem.HasAttribute("ps"))
//            {
//                newPass->SetPixelShader(passElem.GetAttribute("ps"));
//                newPass->SetPixelShaderDefines(passElem.GetAttribute("psdefines"));
//            }
//            else
//            {
//                newPass->SetPixelShader(globalPS);
//                newPass->SetPixelShaderDefines(globalPSDefines + passElem.GetAttribute("psdefines"));
//            }
//
//            newPass->SetVertexShaderDefineExcludes(passElem.GetAttribute("vsexcludes"));
//            newPass->SetPixelShaderDefineExcludes(passElem.GetAttribute("psexcludes"));
//
//            if (passElem.HasAttribute("lighting"))
//            {
//                String lighting = passElem.GetAttributeLower("lighting");
//                newPass->SetLightingMode((PassLightingMode)GetStringListIndex(lighting.CString(), lightingModeNames,
//                                                                              LIGHTING_UNLIT));
//            }
//
//            if (passElem.HasAttribute("blend"))
//            {
//                String blend = passElem.GetAttributeLower("blend");
//                newPass->SetBlendMode((BlendMode)GetStringListIndex(blend.CString(), blendModeNames, BLEND_REPLACE));
//            }
//
//            if (passElem.HasAttribute("cull"))
//            {
//                String cull = passElem.GetAttributeLower("cull");
//                newPass->SetCullMode((CullMode)GetStringListIndex(cull.CString(), cullModeNames, MAX_CULLMODES));
//            }
//
//            if (passElem.HasAttribute("depthtest"))
//            {
//                String depthTest = passElem.GetAttributeLower("depthtest");
//                if (depthTest == "false")
//                    newPass->SetDepthTestMode(CMP_ALWAYS);
//                else
//                    newPass->SetDepthTestMode((CompareMode)GetStringListIndex(depthTest.CString(), compareModeNames, CMP_LESS));
//            }
//
//            if (passElem.HasAttribute("depthwrite"))
//                newPass->SetDepthWrite(passElem.GetBool("depthwrite"));
//
//            if (passElem.HasAttribute("alphatocoverage"))
//                newPass->SetAlphaToCoverage(passElem.GetBool("alphatocoverage"));
//        }
//        else
//            URHO3D_LOGERROR("Missing pass name");
//
//        passElem = passElem.GetNext("pass");
//    }

    return true;
}

void Technique::SetIsDesktop(bool enable)
{
    isDesktop_ = enable;
}

void Technique::ReleaseShaders()
{
//    for (vector<Pass >::iterator i = passes_.begin(); i != passes_.end(); ++i)
//    {
//        Pass* pass = i;
//        if (pass)
//            pass->ReleaseShaders();
//    }
    for(int i = 0 ; i < passes_.size(); i++)
    {
        Pass* pass = passes_[i];
        if(pass)
            pass->ReleaseShaders();
    }
}

Technique* Technique::Clone(const string& cloneName) const
{
    Technique* ret = new Technique(context_);
//    ret->SetIsDesktop(isDesktop_);
//    ret->SetName(cloneName);
//
//    // Deep copy passes
//    for (Vector<SharedPtr<Pass> >::ConstIterator i = passes_.Begin(); i != passes_.End(); ++i)
//    {
//        Pass* srcPass = i->Get();
//        if (!srcPass)
//            continue;
//
//        Pass* newPass = ret->CreatePass(srcPass->GetName());
//        newPass->SetBlendMode(srcPass->GetBlendMode());
//        newPass->SetDepthTestMode(srcPass->GetDepthTestMode());
//        newPass->SetLightingMode(srcPass->GetLightingMode());
//        newPass->SetDepthWrite(srcPass->GetDepthWrite());
//        newPass->SetAlphaToCoverage(srcPass->GetAlphaToCoverage());
//        newPass->SetIsDesktop(srcPass->IsDesktop());
//        newPass->SetVertexShader(srcPass->GetVertexShader());
//        newPass->SetPixelShader(srcPass->GetPixelShader());
//        newPass->SetVertexShaderDefines(srcPass->GetVertexShaderDefines());
//        newPass->SetPixelShaderDefines(srcPass->GetPixelShaderDefines());
//        newPass->SetVertexShaderDefineExcludes(srcPass->GetVertexShaderDefineExcludes());
//        newPass->SetPixelShaderDefineExcludes(srcPass->GetPixelShaderDefineExcludes());
//    }

    return ret;
}

Pass* Technique::CreatePass(const string& name)
{
    Pass* oldPass = GetPass(name);
    if (oldPass)
        return oldPass;

//    SharedPtr<Pass> newPass(new Pass(name));
//    unsigned passIndex = newPass->GetIndex();
//    if (passIndex >= passes_.Size())
//        passes_.Resize(passIndex + 1);
//    passes_[passIndex] = newPass;
//
//    // Calculate memory use now
//    SetMemoryUse((unsigned)(sizeof(Technique) + GetNumPasses() * sizeof(Pass)));

//    return newPass;
    return NULL;
}

void Technique::RemovePass(const string& name)
{
//    HashMap<String, unsigned>::ConstIterator i = passIndices.Find(name.ToLower());
//    if (i == passIndices.End())
//        return;
//    else if (i->second_ < passes_.Size() && passes_[i->second_].Get())
//    {
//        passes_[i->second_].Reset();
//        SetMemoryUse((unsigned)(sizeof(Technique) + GetNumPasses() * sizeof(Pass)));
//    }
}

bool Technique::HasPass(const string& name) const
{
//    HashMap<string, unsigned>::ConstIterator i = passIndices.Find(name.ToLower());
//    return i != passIndices.End() ? HasPass(i->second_) : false;
    return false;
}

Pass* Technique::GetPass(const string& name) const
{
//    HashMap<String, unsigned>::ConstIterator i = passIndices.Find(name.ToLower());
//    return i != passIndices.End() ? GetPass(i->second_) : nullptr;
    return nullptr;
}

Pass* Technique::GetSupportedPass(const string& name) const
{
//    SN_HashMap<string, unsigned>::const_iterator i = passIndices.find(name.c_str());
//    return i != passIndices.end() ? GetSupportedPass(i->second) : nullptr;
    return  nullptr;
}

unsigned Technique::GetNumPasses() const
{
    unsigned ret = 0;

//    for (Vector<SharedPtr<Pass> >::ConstIterator i = passes_.Begin(); i != passes_.End(); ++i)
//    {
//        if (i->Get())
//            ++ret;
//    }

    return ret;
}

vector<string> Technique::GetPassNames() const
{
    vector<string> ret;

//    for (vector<Pass>::iterator i = passes_.begin(); i != passes_.end(); ++i)
//    {
//        Pass* pass = i;
//        if (pass)
//            ret.push(pass->GetName());
//    }

    return ret;
}

vector<Pass*> Technique::GetPasses() const
{
    vector<Pass*> ret;

//    for (vector<Pass* >::const_iterator i = passes_.begin(); i != passes_.end(); ++i)
//    {
//        Pass* pass = i;
//        if (pass)
//            ret.push(pass);
//    }

    return ret;
}

Technique Technique::CloneWithDefines(const string& vsDefines, const string& psDefines)
{
    // Return self if no actual defines
//    if (vsDefines.Empty() && psDefines.Empty())
//        return SharedPtr<Technique>(this);
//
//    Pair<StringHash, StringHash> key = MakePair(StringHash(vsDefines), StringHash(psDefines));
//
//    // Return existing if possible
//    HashMap<Pair<StringHash, StringHash>, SharedPtr<Technique> >::Iterator i = cloneTechniques_.Find(key);
//    if (i != cloneTechniques_.End())
//        return i->second_;
//
//    // Set same name as the original for the clones to ensure proper serialization of the material. This should not be a problem
//    // since the clones are never stored to the resource cache
//    i = cloneTechniques_.Insert(MakePair(key, Clone(GetName())));
//
//    for (Vector<SharedPtr<Pass> >::ConstIterator j = i->second_->passes_.Begin(); j != i->second_->passes_.End(); ++j)
//    {
//        Pass* pass = (*j);
//        if (!pass)
//            continue;
//
//        if (!vsDefines.Empty())
//            pass->SetVertexShaderDefines(pass->GetVertexShaderDefines() + " " + vsDefines);
//        if (!psDefines.Empty())
//            pass->SetPixelShaderDefines(pass->GetPixelShaderDefines() + " " + psDefines);
//    }
//
//    return i->second_;
    return NULL ;
}

unsigned Technique::GetPassIndex(const string& passName)
{
    // Initialize built-in pass indices on first call
    if (passIndices.empty())
    {
        basePassIndex = passIndices["base"] = 0;
        alphaPassIndex = passIndices["alpha"] = 1;
        materialPassIndex = passIndices["material"] = 2;
        deferredPassIndex = passIndices["deferred"] = 3;
        lightPassIndex = passIndices["light"] = 4;
        litBasePassIndex = passIndices["litbase"] = 5;
        litAlphaPassIndex = passIndices["litalpha"] = 6;
        shadowPassIndex = passIndices["shadow"] = 7;
    }

//    string nameLower = passName.ToLower();
//    SN_HashMap<string, unsigned>::Iterator i = passIndices.find(nameLower);
//    if (i != passIndices.end())
//        return i->second_;
//    else
//    {
//        unsigned newPassIndex = passIndices.size();
//        passIndices[nameLower] = newPassIndex;
//        return newPassIndex;
//    }
}
