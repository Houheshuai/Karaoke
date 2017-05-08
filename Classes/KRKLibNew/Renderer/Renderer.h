#pragma once
#include <string>
#include <stack>

//#include "KRKPlayer/InterfaceRenderer.h"

#include "Renderer/GLProgramCache.h"
#include "Renderer/GLProgramState.h"
#include "Renderer/RenderCommand.h"

#include "Renderer/SpecialFunctionCharCache.h"
#include "Platform/GLView.h"

#include "Action/ActionManager.h"
#include "Base/Scheduler.h"


class TrianglesCommand;
class QuadCommand;
/** Class that knows how to sort `RenderCommand` objects.
 Since the commands that have `z == 0` are "pushed back" in
 the correct order, the only `RenderCommand` objects that need to be sorted,
 are the ones that have `z < 0` and `z > 0`.
*/
class RenderQueue {
public:
    /**
    RenderCommand will be divided into Queue Groups.
    */
    enum QUEUE_GROUP
    {
        /**Objects with globalZ smaller than 0.*/
        GLOBALZ_NEG = 0,
        /**Opaque 3D objects with 0 globalZ.*/
        OPAQUE_3D = 1,
        /**Transparent 3D objects with 0 globalZ.*/
        TRANSPARENT_3D = 2,
        /**2D objects with 0 globalZ.*/
        GLOBALZ_ZERO = 3,
        /**Objects with globalZ bigger than 0.*/
        GLOBALZ_POS = 4,
        QUEUE_COUNT = 5,
    };

public:
    /**Constructor.*/
    RenderQueue();
    /**Push a renderCommand into current renderqueue.*/
    void push_back(RenderCommand* command);
    /**Return the number of render commands.*/
    long size() const;
    /**Sort the render commands.*/
    void sort();
    /**Treat sorted commands as an array, access them one by one.*/
    RenderCommand* operator[](long index) const;
    /**Clear all rendered commands.*/
    void clear();
    /**Realloc command queues and reserve with given size. Note: this clears any existing commands.*/
    void realloc(size_t reserveSize);
    /**Get a sub group of the render queue.*/
    inline std::vector<RenderCommand*>& getSubQueue(QUEUE_GROUP group) { return _commands[group]; }
    /**Get the number of render commands contained in a subqueue.*/
    inline long getSubQueueSize(QUEUE_GROUP group) const { return _commands[group].size();}

    /**Save the current DepthState, CullState, DepthWriteState render state.*/
    void saveRenderState();
    /**Restore the saved DepthState, CullState, DepthWriteState render state.*/
    void restoreRenderState();
    
protected:
    /**The commands in the render queue.*/
    std::vector<RenderCommand*> _commands[QUEUE_COUNT];
    
    /**Cull state.*/
    bool _isCullEnabled;
    /**Depth test enable state.*/
    bool _isDepthEnabled;
    /**Depth buffer write state.*/
    GLboolean _isDepthWrite;
};

/**
 * @brief Matrix stack type.
 */
enum MATRIX_STACK_TYPE
{
    /// Model view matrix stack
    MATRIX_STACK_MODELVIEW,
    
    /// projection matrix stack
    MATRIX_STACK_PROJECTION,
    
    /// texture matrix stack
    MATRIX_STACK_TEXTURE
};


class GroupCommandManager;

class Renderer : public Ref
{ 
public: 
	Renderer ();
    ~Renderer ();

	 /**The max number of vertices in a vertex buffer object.*/
    static const int VBO_SIZE = 65536;
    /**The max number of indices in a index buffer.*/
    static const int INDEX_VBO_SIZE = VBO_SIZE * 6 / 4;
    /**The rendercommands which can be batched will be saved into a list, this is the reversed size of this list.*/
    static const int BATCH_TRIAGCOMMAND_RESERVED_SIZE = 64;
    /**Reserved for material id, which means that the command could not be batched.*/
    static const int MATERIAL_ID_DO_NOT_BATCH = 0;

	void init(int w, int h, int res_w, int res_h, std::string defaultfontName);                                                                                                                                                 
	void clear();
	void render();
	void deinit();

	void addCommand(RenderCommand* command);
	//Adds a `RenderComamnd` into the renderer specifying a particular render queue ID
    void addCommand(RenderCommand* command, int renderQueue);

    /** Pushes a group into the render queue */
    void pushGroup(int renderQueueID);
    /** Pops a group from the render queue */
    void popGroup();
	/** Creates a render queue and returns its Id */
    int createRenderQueue();
	//This will not be used outside.
    inline GroupCommandManager* getGroupCommandManager() const { return _groupCommandManager; };

	void setClearColor(const Color4F& clearColor);

	void visitRenderQueue(RenderQueue& queue);

	void flush();
    
    void flush2D();
    
    void flushTriangles();

	void processRenderCommand(RenderCommand* command);


	void fillVerticesAndIndices(const TrianglesCommand* cmd);
	//void fillQuads(const QuadCommand *cmd);

	void drawBatchedTriangles();
    //void drawBatchedQuads();

	void setGLDefaultValues();

	void setAlphaBlending(bool on);
    void setDepthTest(bool on);
    void setProjection();  //2D

	void mapBuffers();
	void setupVBO();
	void setupBuffer();

	void clean();

	const Size& getWinSize(void) const;
	Size getWinSizeInPixels() const;

	 /** 
     * Gets the distance between camera and near clipping frame.
     * It is correct for default camera that near clipping frame is same as the screen.
     */
    float getZEye() ;

	void addDrawnBatches(long number) { _drawnBatches += number; };
	void addDrawnVertices(long number) { _drawnVertices += number; };
	/* clear draw stats */
    void clearDrawStats() { _drawnBatches = _drawnVertices = 0; }

	long getDrawnBatches() const { return _drawnBatches; }
	long getDrawnVertices() const { return _drawnVertices; }

	bool _isRendering;

	/** 
     * Clones a specified type matrix and put it to the top of specified type of matrix stack.
     * @js NA
     */
    void pushMatrix(MATRIX_STACK_TYPE type);
    /** Pops the top matrix of the specified type of matrix stack.
     * @js NA
     */
    void popMatrix(MATRIX_STACK_TYPE type);
    /** Adds an identity matrix to the top of specified type of matrix stack.
     * @js NA
     */
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    /**
     * Adds a matrix to the top of specified type of matrix stack.
     * 
     * @param type Matrix type.
     * @param mat The matrix that to be added.
     * @js NA
     */
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    /**
     * Multiplies a matrix to the top of specified type of matrix stack.
     *
     * @param type Matrix type.
     * @param mat The matrix that to be multiplied.
     * @js NA
     */
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    /**
     * Gets the top matrix of specified type of matrix stack.
     * @js NA
     */
    const Mat4& getMatrix(MATRIX_STACK_TYPE type);
    /**
     * Clear all types of matrix stack, and add identity matrix to these matrix stacks.
     * @js NA
     */
    void resetMatrixStack();

	/** 
     * Returns visible size of the OpenGL view in points.
     * The value is equal to `Director::getWinSize()` if don't invoke `GLView::setDesignResolutionSize()`.
     */
    Size getVisibleSize() ;
    
    /** Returns visible origin coordinate of the OpenGL view in points. */
    Vec2 getVisibleOrigin() ;

	/** 
     * Converts a screen coordinate to an OpenGL coordinate.
     * Useful to convert (multi) touch coordinates to the current layout (portrait or landscape).
     */
    Vec2 convertToGL(const Vec2& point);

    /** 
     * Converts an OpenGL coordinate to a screen coordinate.
     * Useful to convert node points to window points for calls such as glScissor.
     */
    Vec2 convertToUI(const Vec2& point);

	/** Sets the glViewport.*/
    void setViewport();

	//Mat4 _modelViewMatrix;
	//Mat4 _mvpMatrix;

	Size _winSizeInPoints;			//按照分辨率设计的宽高

	bool _isDepthTestFor2D;

	GLProgramCache *ProgramCache;

	GLView *getGLView() { return _glView;};

private: 
	void calculateDeltaTime();

    static Renderer *p_instance_; 
    int count_; 

	Color4F _clearColor;

	std::stack<int> _commandGroupStack;
    std::vector<RenderQueue> _renderGroups;

	std::vector<TrianglesCommand*> _queuedTriangleCommands;
	//std::vector<TrianglesCommand*> _batchedCommands;
    //std::vector<QuadCommand*> _batchQuadCommands;

	void initMatrixStack();

    std::stack<Mat4> _modelViewMatrixStack;
    std::stack<Mat4> _projectionMatrixStack;
    std::stack<Mat4> _textureMatrixStack;

	//std::stack<Mat4> _projectionMatrix;

	 //for TrianglesCommand
    V3F_C4B_T2F _verts[VBO_SIZE];
    GLushort _indices[INDEX_VBO_SIZE];
    GLuint _buffersVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

	// Internal structure that has the information for the batches
    struct TriBatchToDraw {
        TrianglesCommand* cmd;  // needed for the Material
        GLsizei indicesToDraw;
        GLsizei offset;
    };
    // capacity of the array of TriBatches
    int _triBatchesToDrawCapacity;
    // the TriBatches
    TriBatchToDraw* _triBatchesToDraw;

	// stats
    unsigned long _drawnBatches;
    unsigned long _drawnVertices;
    int _filledVertex;
    int _filledIndex;

	//for QuadCommand
	/*
    V3F_C4B_T2F _quadVerts[VBO_SIZE];
    GLushort _quadIndices[INDEX_VBO_SIZE];
    GLuint _quadVAO;
    GLuint _quadbuffersVBO[2]; //0: vertex  1: indices
	int _numberQuads;
	*/

	unsigned int _lastMaterialID;

	bool _glViewAssigned;

	GLView *_glView;

	float _contentScaleFactor;

	SpecialFunctionCharCache *SpecialCharCache;

	GroupCommandManager* _groupCommandManager;

	friend class GLView;
}; 
