/* Framework for Live Image Transformation (FLITr)
 * Copyright (c) 2010 CSIR
 *
 * This file is part of FLITr.
 *
 * FLITr is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * FLITr is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FLITr. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef GLSL_COPY_PASS_H
#define GLSL_COPY_PASS_H 1
#include <iostream>
#include <string>

#include <flitr/glsl_image_processor.h>

#include <flitr/flitr_export.h>
#include <flitr/modules/parameters/parameters.h>
#include <flitr/texture.h>

namespace flitr {

class FLITR_EXPORT GLSLCopyPass : public GLSLImageProcessor
{
  public:
    GLSLCopyPass(flitr::TextureRectangle *in_tex, flitr::TextureRectangle *out_tex = 0, bool read_back_to_CPU = false);
    ~GLSLCopyPass();
    osg::ref_ptr<osg::Group> getRoot() { return RootGroup_; }
    osg::ref_ptr<flitr::TextureRectangle> getOutputTexture() { return OutTexture_; }
    osg::ref_ptr<osg::Image> getOSGImage() { return OutImage_; }
    void setShader();

  private:
    osg::ref_ptr<osg::Group> createTexturedQuad();
    void createOutputTexture(bool read_back_to_CPU);
    void setupCamera();

};
}
#endif //GLSL_SHADER_PASS_H
