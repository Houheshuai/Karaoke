/***********************************************************************
    filename:   CEGUIRegexMatcher.h
    created:    Mon Jul 27 2009
    author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2009 Paul D Turner & The CEGUI Development Team
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
#ifndef _CEGUIRegexMatcher_h_
#define _CEGUIRegexMatcher_h_

#include "CEGUIString.h"

// Start of CEGUI namespace section
namespace CEGUI
{

//! Interface for Regex matching support classes
class RegexMatcher
{
public:
    //! Destructor.
    virtual ~RegexMatcher() {}
    //! Set the regex string that will be matched against.
    virtual void setRegexString(const String& regex) = 0;
    //! Return reference to current regex string set.
    virtual const String& getRegexString() const = 0;
    //! Return whether a given string matches the set regex.
    virtual bool matchRegex(const String& str) const = 0;
};

} // End of  CEGUI namespace section

#endif  // end of guard _CEGUIRegexMatcher_h_