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

#include <flitr/flitr_export.h>

#include <osgGA/CameraManipulator>

namespace flitr {

/** 
 * The OSG manipulators normally look down the Y-axis with Z up. Our
 * default geometry for textures are in the X-Y-plane with Y up. This
 * functions adjusts the default home position for the given
 * manipulator.
 * 
 * \param m Pointer to an OSG camera manipulator.
 */
FLITR_EXPORT void adjustCameraManipulatorHomeForYUp(osgGA::CameraManipulator* m);

}
