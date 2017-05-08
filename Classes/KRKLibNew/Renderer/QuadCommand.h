#ifndef _QUADCOMMAND_H_
#define _QUADCOMMAND_H_

#include "Renderer/TrianglesCommand.h"
#include "Renderer/GLProgramState.h"
#include <vector>
/** 
 Command used to render one or more Quads, similar to TrianglesCommand.
 Every QuadCommand will have generate material ID by give textureID, glProgramState, Blend function
 if the material id is the same, these QuadCommands could be batched to save draw call.
 */
class QuadCommand : public TrianglesCommand
{
public:
    /**Constructor.*/
    QuadCommand();
    /**Destructor.*/
    ~QuadCommand();
    
    /** Initializes the command.
     @param globalOrder GlobalZOrder of the command.
     @param textureID The openGL handle of the used texture.
     @param shader The specified glProgram and its uniform.
     @param blendType Blend function for the command.
     @param quads Rendered quads for the command.
     @param quadCount The number of quads when rendering.
     @param mv ModelView matrix for the command.
     @param flags to indicate that the command is using 3D rendering or not.
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* shader, const BlendFunc& blendType, V3F_C4B_T2F_Quad* quads, long quadCount,
              const Mat4& mv, unsigned int flags);

    void init(float globalOrder, Texture2D* textureID, GLProgramState* glProgramState, const BlendFunc& blendType, V3F_C4B_T2F_Quad* quads, unsigned int quadCount,
        const Mat4& mv, unsigned int flags);

protected:
    void reIndex(int indices);

    int _indexSize;
    std::vector<GLushort*> _ownedIndices;

    // shared across all instances
    static int __indexCapacity;
    static GLushort* __indices;
};

#endif //_QUADCOMMAND_H_
