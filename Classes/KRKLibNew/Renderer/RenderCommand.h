#pragma once
#include <string>
#include "Math/Math.h"

class RenderCommand
{
public:
	enum Type
    {
        /** Reserved type.*/
        UNKNOWN_COMMAND,
        /** Quad command, used for draw quad.*/
        QUAD_COMMAND,
        /**Custom command, used for calling callback for rendering.*/
        CUSTOM_COMMAND,
        /**Batch command, used for draw batches in texture atlas.*/
        BATCH_COMMAND,
        /**Group command, which can group command in a tree hierarchy.*/
        GROUP_COMMAND,
        /**Mesh command, used to draw 3D meshes.*/
        MESH_COMMAND,
        /**Primitive command, used to draw primitives such as lines, points and triangles.*/
        PRIMITIVE_COMMAND,
        /**Triangles command, used to draw triangles.*/
        TRIANGLES_COMMAND
    };

	void init(float globalZOrder, const Mat4& modelViewTransform, int flags);

	/** Get global Z order. */
    inline float getGlobalOrder() const { return _globalOrder; }

    /** Returns the Command type. */
    inline Type getType() const { return _type; }
    
    /** Returns whether is transparent. */
    inline bool isTransparent() const { return _isTransparent; }
    
    /** Set transparent flag. */
    inline void setTransparent(bool isTransparent) { _isTransparent = isTransparent; }
    /**
     Get skip batching status, if a rendering is skip batching, it will be forced to be rendering separately.
     */
    inline bool isSkipBatching() const { return _skipBatching; }
    /**Set skip batching.*/
    inline void setSkipBatching(bool value) { _skipBatching = value; }
    /**Whether the command should be rendered at 3D mode.*/
    inline bool is3D() const { return _is3D; }
    /**Set the command rendered in 3D mode or not.*/
    inline void set3D(bool value) { _is3D = value; }
    /**Get the depth by current model view matrix.*/
    inline float getDepth() const { return _depth; }

protected:
    /**Constructor.*/
    RenderCommand();
    /**Destructor.*/
    virtual ~RenderCommand();
    //used for debug but it is not implemented.
    void printID();

    /**Type used in order to avoid dynamic cast, faster. */
    Type _type;

    /** Commands are sort by global Z order. */
    float _globalOrder;
    
    /** Transparent flag. */
    bool  _isTransparent;
    
    /**
     QuadCommand and TrianglesCommand could be auto batched if there material ID is the same, however, if
     a command is skip batching, it would be forced to draw in a separate function call, and break the batch.
     */
    bool _skipBatching;
    
    /** Is the command been rendered on 3D pass. */
    bool _is3D;
    
    /** Depth from the model view matrix.*/
    float _depth;

};

