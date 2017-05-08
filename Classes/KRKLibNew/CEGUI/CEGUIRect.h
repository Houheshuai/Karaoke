/***********************************************************************
	filename: 	CEGUIRect.h
	created:	8/3/2004
	author:		Paul D Turner
	
	purpose:	Defines 'CEGUIRect' class
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CEGUIRect_h_
#define _CEGUIRect_h_

#include "CEGUIBase.h"
#include "CEGUIVector.h"
#include "CEGUISize.h"

// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
	Class encapsulating operations on a Rectangle
*/
class  CEGUIRect
{
public:
	CEGUIRect(void) {}


	/*!
	\brief
		Constructor for a CEGUIRect.
	*/
	CEGUIRect(float left, float top, float right, float bottom);

    CEGUIRect(Point pos, CEGUISize sz);


	/*!
	\brief
		Return top-left postion of CEGUIRect as a Point
	*/
	Point	getPosition(void) const		{return Point(d_left, d_top);}

	/*!
	\brief
		return width of CEGUIRect area
	*/
	float	getWidth(void) const		{return d_right - d_left;}


	/*!
	\brief
		return height of CEGUIRect area
	*/
	float	getHeight(void) const		{return d_bottom - d_top;}


	/*!
	\brief
		return the size of the CEGUIRect area
	*/
	CEGUISize	getSize(void) const			{return CEGUISize(getWidth(), getHeight());}


	/*!
	\brief
		set the position of the CEGUIRect (leaves size in tact)
	*/
	void	setPosition(const Point& pt);


	/*!
	\brief
		set the width of the CEGUIRect object
	*/
	void	setWidth(float width)		{d_right = d_left + width;}

	/*!
	\brief
		set the height of the CEGUIRect object
	*/
	void	setHeight(float height)		{d_bottom = d_top + height;}


	/*!
	\brief
		set the size of the CEGUIRect area
	*/
	void	setSize(const CEGUISize& sze)	{setWidth(sze.d_width); setHeight(sze.d_height);}


	/*!
	\brief
		return a CEGUIRect that is the intersection of 'this' CEGUIRect with the CEGUIRect 'rect'

	\note
		It can be assumed that if d_left == d_right, or d_top == d_bottom, or getWidth() == 0, or getHeight() == 0, then
		'this' rect was totally outside 'rect'.
	*/
	CEGUIRect	getIntersection(const CEGUIRect& rect) const;


	/*!
	\brief
		Applies an offset the CEGUIRect object

	\param pt
		Point object containing the offsets to be applied to the CEGUIRect.

	\return
		this CEGUIRect after the offset is performed
	*/
	CEGUIRect&	offset(const Point& pt);


	/*!
	\brief
		Return true if the given Point falls within this CEGUIRect

	\param pt
		Point object describing the position to test.

	\return
		true if position \a pt is within this CEGUIRect's area, else false
	*/
	bool	isPointInRect(const Point& pt) const;


	/*!
	\brief
		check the size of the CEGUIRect object and if it is bigger than \a sz, resize it so it isn't.

	\param sz
		CEGUISize object that describes the maximum dimensions that this CEGUIRect should be limited to.

	\return
		'this' CEGUIRect object after the constrain operation
	*/
	CEGUIRect&	constrainSizeMax(const CEGUISize& sz);


	/*!
	\brief
		check the size of the CEGUIRect object and if it is smaller than \a sz, resize it so it isn't.

	\param sz
		CEGUISize object that describes the minimum dimensions that this CEGUIRect should be limited to.

	\return
		'this' CEGUIRect object after the constrain operation
	*/
	CEGUIRect&	constrainSizeMin(const CEGUISize& sz);


	/*!
	\brief
		check the size of the CEGUIRect object and if it is bigger than \a max_sz or smaller than \a min_sz, resize it so it isn't.

	\param max_sz
		CEGUISize object that describes the maximum dimensions that this CEGUIRect should be limited to.

	\param min_sz
		CEGUISize object that describes the minimum dimensions that this CEGUIRect should be limited to.

	\return
		'this' CEGUIRect object after the constrain operation
	*/
	CEGUIRect&	constrainSize(const CEGUISize& max_sz, const CEGUISize& min_sz);


	/*************************************************************************
		Operators
	*************************************************************************/
	bool	operator==(const CEGUIRect& rhs) const
	{
		return ((d_left == rhs.d_left) && (d_right == rhs.d_right) && (d_top == rhs.d_top) && (d_bottom == rhs.d_bottom));
	}

	bool	operator!=(const CEGUIRect& rhs) const		{return !operator==(rhs);}

	CEGUIRect&	operator=(const CEGUIRect& rhs);

    CEGUIRect operator*(float scalar) const      { return CEGUIRect(d_left * scalar, d_top * scalar, d_right * scalar, d_bottom * scalar); }
    const CEGUIRect& operator*=(float scalar)    { d_left *= scalar; d_top *= scalar; d_right *= scalar; d_bottom *= scalar; return *this; }


	/*************************************************************************
		Data Fields
	*************************************************************************/
	float	d_top, d_bottom, d_left, d_right;
};

} // End of  CEGUI namespace section


#endif	// end of guard _CEGUIRect_h_
