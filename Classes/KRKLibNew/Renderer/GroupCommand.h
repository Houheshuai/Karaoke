#ifndef __GROUPCOMMAND_H_
#define __GROUPCOMMAND_H_

#include <vector>
#include <unordered_map>

#include "Base/Ref.h"
#include "Renderer/RenderCommand.h"

//Used for internal
class GroupCommandManager : public Ref
{
public:
    int getGroupID();
    void releaseGroupID(int groupID);

protected:
    friend class Renderer;
    GroupCommandManager();
    ~GroupCommandManager();
    bool init();
    std::unordered_map<int, bool> _groupMapping;
    std::vector<int> _unusedIDs;
};

/**
 GroupCommand is used to group several command together, and more, it can be nested.
 So it is used to generate the hierarchy for the rendcommands. Every group command will be assigned by a group ID.
 */
class GroupCommand : public RenderCommand
{
public:
    /**@{
     Constructor and Destructor.
     */
    GroupCommand();
    ~GroupCommand();
    /**@}*/
    
    /**Init function for group command*/
    void init(float globalOrder);
    
    /**called by renderer, get the group ID.*/
    inline int getRenderQueueID() const {return _renderQueueID;}
    
protected:
    int _renderQueueID;
};

#endif //__GROUPCOMMAND_H_
