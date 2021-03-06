/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLSPAWNPOINTINFO_H
#define _PLSPAWNPOINTINFO_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

class PLASMA_DLL plSpawnPointInfo {
protected:
    enum { kHasTitle, kHasSpawnPt, kHasCameraStack };

    plString fTitle, fSpawnPt, fCameraStack;

public:
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    void clear();

    plString getTitle() const { return fTitle; }
    plString getSpawnPt() const { return fSpawnPt; }
    plString getCameraStack() const { return fCameraStack; }

    void setTitle(plString title) { fTitle = title; }
    void setSpawnPt(plString spawn) { fSpawnPt = spawn; }
    void setCameraStack(plString stack) { fCameraStack = stack; }
};

#endif
