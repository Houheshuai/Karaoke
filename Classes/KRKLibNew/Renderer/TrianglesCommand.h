#pragma once
#include <string>

#include "Renderer/RenderCommand.h"
#include "Renderer/GLProgramState.h"
#include "Base/Types.h"

class TrianglesCommand : public RenderCommand
{
public:
    /**The structure of Triangles. */
    struct Triangles
    {
        /**Vertex data pointer.*/
        V3F_C4B_T2F* verts;
        /**Index data pointer.*/
        unsigned short* indices;
        /**The number of vertices.*/
        long vertCount;
        /**The number of indices.*/
        long indexCount;
    };
    /**Construtor.*/
    TrianglesCommand();
    /**Destructor.*/
    ~TrianglesCommand();
    
    /** Initializes the command.
     @param globalOrder GlobalZOrder of the command.
     @param textureID The openGL handle of the used texture.
     @param glProgramState The specified glProgram and its uniform.
     @param blendType Blend function for the command.
     @param triangles Rendered triangles for the command.
     @param mv ModelView matrix for the command.
     @param flags to indicate that the command is using 3D rendering or not.
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv, unsigned int flags);
	void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv);
    /**Apply the texture, shaders, programs, blend functions to GPU pipeline.*/
    void useMaterial() const;
    /**Get the material id of command.*/
    inline unsigned int getMaterialID() const { return _materialID; }
    /**Get the openGL texture handle.*/
    inline GLuint getTextureID() const { return _textureID; }
    /**Get a const reference of triangles.*/
    inline const Triangles& getTriangles() const { return _triangles; }
    /**Get the vertex count in the triangles.*/
    inline long getVertexCount() const { return _triangles.vertCount; }
    /**Get the index count of the triangles.*/
    inline long getIndexCount() const { return _triangles.indexCount; }
    /**Get the vertex data pointer.*/
    inline const V3F_C4B_T2F* getVertices() const { return _triangles.verts; }
    /**Get the index data pointer.*/
    inline const unsigned short* getIndices() const { return _triangles.indices; }
    /**Get the glprogramstate.*/
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    /**Get the blend function.*/
    inline BlendFunc getBlendType() const { return _blendType; }
    /**Get the model view matrix.*/
    inline const Mat4& getModelView() const { return _mv; }
    
protected:
    /**Generate the material ID by textureID, glProgramState, and blend function.*/
    void generateMaterialID();
    
    /**Generated material id.*/
    unsigned int _materialID;
    /**OpenGL handle for texture.*/
    GLuint _textureID;
    /**GLprogramstate for the command. encapsulate shaders and uniforms.*/
    GLProgramState* _glProgramState;
    /**Blend function when rendering the triangles.*/
    BlendFunc _blendType;
    /**Rendered triangles.*/
    Triangles _triangles;
    /**Model view matrix when rendering the triangles.*/
    Mat4 _mv;
};