#pragma once

#ifndef _OPENGLESRENDERER_H
#define _OPENGLESRENDERER_H

#include "CEGUI/CEGUIBase.h"
#include "CEGUI/CEGUIRenderer.h"
#include "CEGUI/CEGUISize.h"
#include "CEGUI/CEGUIVector.h"
#include <vector>


namespace CEGUI
{

class OpenglesRenderer : public Renderer
{
public:
	OpenglesRenderer(void);
	~OpenglesRenderer(void);

	void beginRendering();
    void endRendering();
    void setDisplaySize(const CEGUISize& sz);
    const CEGUISize& getDisplaySize() const;
    const Vector2& getDisplayDPI() const;
    //uint getMaxTextureSize() const;
    //const String& getIdentifierString() const;

public:
    CEGUISize d_displaySize;
	Vector2 d_displayDPI;
	//String d_rendererID;
};

}
#endif
