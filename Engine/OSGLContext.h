/* ***** BEGIN LICENSE BLOCK *****
 * This file is part of Natron <http://www.natron.fr/>,
 * Copyright (C) 2016 INRIA and Alexandre Gauthier-Foichat
 *
 * Natron is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Natron is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Natron.  If not, see <http://www.gnu.org/licenses/gpl-2.0.html>
 * ***** END LICENSE BLOCK ***** */

//========================================================================
// GLFW 3.2 - www.glfw.org
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2010 Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================



#ifndef OSGLCONTEXT_H
#define OSGLCONTEXT_H

// ***** BEGIN PYTHON BLOCK *****
// from <https://docs.python.org/3/c-api/intro.html#include-files>:
// "Since Python may define some pre-processor definitions which affect the standard headers on some systems, you must include Python.h before any standard headers are included."
#include <Python.h>
// ***** END PYTHON BLOCK *****

#include "Engine/EngineFwd.h"
#include "Global/GLIncludes.h"

NATRON_NAMESPACE_ENTER;


/* @brief Framebuffer configuration.
 *
 *  This describes buffers and their sizes.  It also contains
 *  a platform-specific ID used to map back to the backend API object.
 *
 *  It is used to pass framebuffer parameters from shared code to the platform
 *  API and also to enumerate and select available framebuffer configs.
 */
class FramebufferConfig
{
public:

    static const int ATTR_DONT_CARE = -1;

    int         redBits;
    int         greenBits;
    int         blueBits;
    int         alphaBits;
    int         depthBits;
    int         stencilBits;
    int         accumRedBits;
    int         accumGreenBits;
    int         accumBlueBits;
    int         accumAlphaBits;
    int         auxBuffers;
    GLboolean         stereo;
    int         samples;
    GLboolean         sRGB;
    GLboolean         doublebuffer;
    uintptr_t   handle;

    FramebufferConfig()
    : redBits(8)
    , greenBits(8)
    , blueBits(8)
    , alphaBits(8)
    , depthBits(24)
    , stencilBits(8)
    , accumRedBits(0)
    , accumGreenBits(0)
    , accumBlueBits(0)
    , accumAlphaBits(0)
    , auxBuffers(0)
    , stereo(GL_FALSE)
    , samples(0)
    , sRGB(GL_FALSE)
    , doublebuffer(GL_TRUE)
    , handle(0)
    {

    }
};

/**
 * @brief This class encapsulates a cross-platform OpenGL context used for offscreen rendering.
 **/
struct OSGLContextPrivate;
class OSGLContext
{
public:


    OSGLContext(const FramebufferConfig& pixelFormatAttrs, int major = GLVersion.major, int minor = GLVersion.minor);

    ~OSGLContext();

    static const FramebufferConfig& chooseFBConfig(const FramebufferConfig& desired, const std::vector<FramebufferConfig>& alternatives, int count);

    /*  @brief Makes the context current for the calling
     *  thread. A context can only be made current on
     *  a single thread at a time and each thread can have only a single current
     *  context at a time.
     *
     *  @thread_safety This function may be called from any thread.
     */
    static void makeContextCurrent(const OSGLContextPtr& context);

    /**
     * @brief Returns the current context for this thread.
     **/
    static OSGLContextPtr getCurrentContext();

    static bool stringInExtensionString(const char* string, const char* extensions);

private:

    boost::scoped_ptr<OSGLContextPrivate> _imp;
};

NATRON_NAMESPACE_EXIT;

#endif // OSGLCONTEXT_H
