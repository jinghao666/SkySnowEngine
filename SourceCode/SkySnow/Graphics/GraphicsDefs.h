//
// Created by liuqian8 on 2018/10/2.
//
#pragma once
static const int MAX_VERTEX_STREAMS = 4;
static const int M_MAX_UNSIGNED = 0xffffffff;
/// Primitive type.
enum PrimitiveType
{
    TRIANGLE_LIST = 0,
    LINE_LIST,
    POINT_LIST,
    TRIANGLE_STRIP,
    LINE_STRIP,
    TRIANGLE_FAN

};

// shader type
enum ShaderType
{
    VS = 0,
    FS
};

enum BlendMode
{
    BLEND_REPLACE = 0,
    BLEND_ADD,
    BLEND_MULTIPLY,
    BLEND_ALPHA,
    BLEND_ADDALPHA,
    BLEND_PREMULALPHA,
    BLEND_INVDESTALPHA,
    BLEND_SUBTRACT,
    BLEND_SUBTRACTALPHA,
    MAX_BLENDMODES
};

//深度比较运算符
enum CompareMode
{
    CMP_ALWAYS = 0,//深度测试永远通过
    CMP_EQUAL,//当fragment 的深度值小于被储存的深度值时则通过
    CMP_NOTEQUAL,//当fragment的深度值不等于所存储的深度值则通过
    CMP_LESS,//当fragment的深度值小于所存储的深度值则通过
    CMP_LESSEQUAL,//当fragment的深度值小于等于所存贮的深度值则通过
    CMP_GREATER,//当frament的深度值大于所存储的深度值时则通过
    CMP_GREATEREQUAL,//当fragment的深度值大于等于所存储的深度值时则通过
    MAX_COMPAREMODES//
};

//culling mode  光栅化之前，设置卷绕方式
enum CullMode
{
    CULL_NONE = 0,//不剔除
    CULL_CCW,//逆时针卷绕
    CULL_CW,//顺时针卷绕
    MAX_CULLMODES
};

enum VertexElementType
{
    TYPE_INT = 0,
    TYPE_FLOAT,
    TYPE_VECTOR2,
    TYPE_VECTOR3,
    TYPE_VECTOR4,
    TYPE_UBYTE4,
    TYPE_UBYTE4_NORM,
    MAX_VERTEX_ELEMENT_TYPES
};

enum VertexElementSemantic
{
    SEM_POSITION = 0,//顶点属性
    SEM_NORMAL,//法线属性
    SEM_BINORMAL,//副法线属性
    SEM_TANGENT,//切线属性
    SEM_TEXCOORD,//纹理坐标属性
    SEM_COLOR,//颜色属性
    SEM_BLENDWEIGHTS,//混合权重属性
    SEM_BLENDINDICES,//混合指数属性
    SEM_OBJECTINDEX,//对象索引属性
    MAX_VERTEX_ELEMENT_SEMANTICS//最大的顶点元素数据流属性
};

struct VertexElement
{
    VertexElement():
            type_(TYPE_VECTOR3),
            semantic_(SEM_POSITION),
            index_(0),
            perInstance_(false),
            offset_(0)
    {
    }
    //使用类型、语义、索引和每个实例数据构造。
    VertexElement(VertexElementType type, VertexElementSemantic semantic, string index = 0, bool perInstance = false) :
            type_(type),
            semantic_(semantic),
            index_(index),
            perInstance_(perInstance),
            offset_(0)
    {
    }

    bool operator ==(const VertexElement& rhs) const
    {
        return type_ == rhs.type_ && semantic_ == rhs.semantic_ && index_ == rhs.index_ && perInstance_ == rhs.perInstance_;
    }

    bool operator !=(const VertexElement& rhs) const
    {
        return !(*this == rhs);
    }
    //数据元素类型
    VertexElementType type_;
    //元素属性
    VertexElementSemantic semantic_;
    //元素的名字
    string index_;
    bool perInstance_;
    //Offset of element from vertex start. Filled by VertexBuffer once the vertex declaration is built.
    unsigned offset_;
};
//顶点元素类型的大小
static const unsigned ELEMENT_TYPESIZES[] =
{
        sizeof(int),
        sizeof(float),
        3 * sizeof(float),
        4 * sizeof(float),
        sizeof(unsigned),
        sizeof(unsigned)
};
//每一个顶点数组的属性初始化
static const VertexElement  LEGACY_VERTEXELEMENTS[] =
{
        VertexElement(TYPE_VECTOR3, SEM_POSITION,"pos", false),                //position
        VertexElement(TYPE_VECTOR3, SEM_NORMAL, "normal", false),              // Normal
        VertexElement(TYPE_VECTOR3, SEM_BINORMAL, "binormal", false),         // binormal
        VertexElement(TYPE_UBYTE4_NORM, SEM_COLOR, "color", false),           // Color
        VertexElement(TYPE_VECTOR2, SEM_TEXCOORD, "texCoords", false),        // Texcoord
        VertexElement(TYPE_VECTOR4, SEM_TANGENT, "tangent", false),           // Tangent
        VertexElement(TYPE_VECTOR4, SEM_BLENDWEIGHTS, "blendWeight", false), // Blendweights
        VertexElement(TYPE_UBYTE4, SEM_BLENDINDICES, "blendIndices", false), // Blendindices
        VertexElement(TYPE_INT, SEM_OBJECTINDEX, "objectIndex", false)        // Objectindex
};
//ramp 纹理类型
enum TextureUnit
{
    TU_DIFFUSE = 0,
    TU_ALBEDOBUFFER = 0,
    TU_NORMAL = 1,
    TU_NORMALBUFFER = 1,
    TU_SPECULAR = 2,
    TU_EMISSIVE = 3,
    TU_ENVIRONMENT = 4,
    TU_LIGHTRAMP = 5,
    TU_LIGHTSHAPE = 6,
    TU_SHADOWMAP = 7,
    MAX_MATERIAL_TEXTURE_UNITS = 5,
    MAX_TEXTURE_UNITS = 8
};
