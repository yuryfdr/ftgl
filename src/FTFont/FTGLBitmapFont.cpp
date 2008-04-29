/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
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

#include "FTInternals.h"

#include "FTGLBitmapFont.h"
#include "FTGLBitmapFontImpl.h"
#include "FTBitmapGlyph.h"


//
//  FTGLBitmapFont
//


FTGLBitmapFont::FTGLBitmapFont(char const *fontFilePath)
{
    impl = new FTGLBitmapFontImpl(fontFilePath);
}


FTGLBitmapFont::FTGLBitmapFont(unsigned char const *pBufferBytes,
                               size_t bufferSizeInBytes)
{
    impl = new FTGLBitmapFontImpl(pBufferBytes, bufferSizeInBytes);
}


FTGLBitmapFont::~FTGLBitmapFont()
{
    ;
}


//
//  FTGLBitmapFontImpl
//


FTGlyph* FTGLBitmapFontImpl::MakeGlyph(unsigned int g)
{
    FT_GlyphSlot ftGlyph = face.Glyph(g, FT_LOAD_DEFAULT);

    if(ftGlyph)
    {
        FTBitmapGlyph* tempGlyph = new FTBitmapGlyph(ftGlyph);
        return tempGlyph;
    }

    err = face.Error();
    return NULL;
}


template <typename T>
inline void FTGLBitmapFontImpl::RenderI(const T *string)
{
    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
    glPushAttrib(GL_ENABLE_BIT);

    glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glDisable(GL_BLEND);

    FTFontImpl::Render(string);

    glPopAttrib();
    glPopClientAttrib();
}


void FTGLBitmapFontImpl::Render(const char* string)
{
    RenderI(string);
}


void FTGLBitmapFontImpl::Render(const wchar_t* string)
{
    RenderI(string);
}
