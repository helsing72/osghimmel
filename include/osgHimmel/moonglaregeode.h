
// Copyright (c) 2011-2012, Daniel M�ller <dm@g4t3.de>
// Computer Graphics Systems Group at the Hasso-Plattner-Institute, Germany
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright 
//     notice, this list of conditions and the following disclaimer in the 
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Computer Graphics Systems Group at the 
//     Hasso-Plattner-Institute (HPI), Germany nor the names of its 
//     contributors may be used to endorse or promote products derived from 
//     this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#pragma once
#ifndef __MOONGLAREGEODE_H__
#define __MOONGLAREGEODE_H__

#include <osgHimmel/declspec.h>

#include <osg/Geode>


namespace osgHimmel
{

class Himmel;
class HimmelQuad;


class OSGH_API MoonGlareGeode : public osg::Geode
{
public:

    MoonGlareGeode();
    virtual ~MoonGlareGeode();

    void update(const Himmel &himmel);

    // scale is in n times the size of the moon
    const float setScale(const float scale);
    const float getScale() const;
    static const float defaultScale();

    // intensity is in fraction of moons intensity
    const float setIntensity(const float intensity);
    const float getIntensity() const;
    static const float defaultIntensity();

protected:

    void setupUniforms(osg::StateSet* stateSet);
    void setupNode    (osg::StateSet* stateSet);

    void setupShader  (osg::StateSet* stateSet);

    const std::string getVertexShaderSource();
    const std::string getFragmentShaderSource();

protected:

    HimmelQuad *m_hquad;

    osg::Program *m_program;
    osg::Shader *m_vShader;
    osg::Shader *m_fShader;

    osg::ref_ptr<osg::Uniform> u_scale;
    osg::ref_ptr<osg::Uniform> u_intensity;
    osg::ref_ptr<osg::Uniform> u_phase;

#ifdef OSGHIMMEL_EXPOSE_SHADERS
public:
    osg::Shader *getVertexShader();
    osg::Shader *getGeometryShader();
    osg::Shader *getFragmentShader();
#endif // OSGHIMMEL_EXPOSE_SHADERS
};

} // namespace osgHimmel

#endif // __MOONGLAREGEODE_H__
