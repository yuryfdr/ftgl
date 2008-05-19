/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2008 Sam Hocevar <sam@zoy.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#include "FTGL/ftgl.h"

#include "FTInternals.h"
#include "FTBufferFontImpl.h"


//
//  FTBufferFont
//


FTBufferFont::FTBufferFont(char const *fontFilePath) :
    FTFont(new FTBufferFontImpl(this, fontFilePath))
{}


FTBufferFont::FTBufferFont(unsigned char const *pBufferBytes,
                           size_t bufferSizeInBytes) :
    FTFont(new FTBufferFontImpl(this, pBufferBytes, bufferSizeInBytes))
{}


FTBufferFont::~FTBufferFont()
{}


FTGlyph* FTBufferFont::MakeGlyph(FT_GlyphSlot ftGlyph)
{
    return new FTBufferGlyph(ftGlyph);
}


//
//  FTBufferFontImpl
//


template <typename T>
inline FTPoint FTBufferFontImpl::RenderI(const T* string, const int len,
                                         FTPoint position, FTPoint spacing,
                                         int renderMode)
{
    return position;
}


FTPoint FTBufferFontImpl::Render(const char * string, const int len,
                                 FTPoint position, FTPoint spacing,
                                 int renderMode)
{
    return RenderI(string, len, position, spacing, renderMode);
}


FTPoint FTBufferFontImpl::Render(const wchar_t * string, const int len,
                                 FTPoint position, FTPoint spacing,
                                 int renderMode)
{
    return RenderI(string, len, position, spacing, renderMode);
}
