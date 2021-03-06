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

#include <cstdio>
#include <cmath>
#include "hsMatrix44.h"

hsMatrix44::hsMatrix44() {
    Reset();
}

hsMatrix44::hsMatrix44(const hsMatrix44& init) {
    memcpy(data, init.data, sizeof(data));
}

hsMatrix44 hsMatrix44::Identity() {
    static hsMatrix44 idMat;
    static bool idMatInitialized = false;
    if (!idMatInitialized) {
        idMat.Reset();
        idMatInitialized = true;
    }
    return idMat;
}

hsMatrix44 hsMatrix44::TranslateMat(const hsVector3& translate) {
    hsMatrix44 tMat;
    tMat.setTranslate(translate);
    return tMat;
}

hsMatrix44 hsMatrix44::RotateMat(int axis, float angle) {
    hsMatrix44 rMat;
    rMat.setRotate(axis, angle);
    return rMat;
}

hsMatrix44 hsMatrix44::ScaleMat(const hsVector3& scale) {
    hsMatrix44 sMat;
    sMat.setScale(scale);
    return sMat;
}

void hsMatrix44::Reset() {
    memset(data, 0, sizeof(data));
    data[0][0] = 1.0f;
    data[1][1] = 1.0f;
    data[2][2] = 1.0f;
    data[3][3] = 1.0f;
}

bool hsMatrix44::IsIdentity() const {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if ((x == y && data[y][x] != 1.0) ||
                (x != y && data[y][x] != 0.0))
                return false;
    return true;
}

bool hsMatrix44::operator==(const hsMatrix44& other) const {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if (data[y][x] != other.data[y][x])
                return false;
    return true;
}

const float* hsMatrix44::glMatrix() const {
    static float glmat[16];
    glmat[ 0] = data[0][0];
    glmat[ 1] = data[1][0];
    glmat[ 2] = data[2][0];
    glmat[ 3] = data[3][0];
    glmat[ 4] = data[0][1];
    glmat[ 5] = data[1][1];
    glmat[ 6] = data[2][1];
    glmat[ 7] = data[3][1];
    glmat[ 8] = data[0][2];
    glmat[ 9] = data[1][2];
    glmat[10] = data[2][2];
    glmat[11] = data[3][2];
    glmat[12] = data[0][3];
    glmat[13] = data[1][3];
    glmat[14] = data[2][3];
    glmat[15] = data[3][3];
    return glmat;
}

hsMatrix44 hsMatrix44::operator*(const hsMatrix44& right) const {
    hsMatrix44 result;
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            result.data[y][x] = (data[y][0] * right.data[0][x]) +
                                (data[y][1] * right.data[1][x]) +
                                (data[y][2] * right.data[2][x]) +
                                (data[y][3] * right.data[3][x]);
    return result;
}

hsVector3 hsMatrix44::multPoint(const hsVector3& point) const {
    hsVector3 result;
    result.X = (data[0][0] * point.X) + (data[0][1] * point.Y) +
               (data[0][2] * point.Z) +  data[0][3];
    result.Y = (data[1][0] * point.X) + (data[1][1] * point.Y) +
               (data[1][2] * point.Z) +  data[1][3];
    result.Z = (data[2][0] * point.X) + (data[2][1] * point.Y) +
               (data[2][2] * point.Z) +  data[2][3];
    return result;
}

hsVector3 hsMatrix44::multVector(const hsVector3& vec) const {
    hsVector3 result;
    result.X = (data[0][0] * vec.X) + (data[0][1] * vec.Y) + (data[0][2] * vec.Z);
    result.Y = (data[1][0] * vec.X) + (data[1][1] * vec.Y) + (data[1][2] * vec.Z);
    result.Z = (data[2][0] * vec.X) + (data[2][1] * vec.Y) + (data[2][2] * vec.Z);
    return result;
}

hsMatrix44 hsMatrix44::inverse() const {
    // This function is intentionally unrolled for performance
    float subDet[4][4];

    subDet[0][0] = data[1][1]*(data[2][2]*data[3][3] - data[3][2]*data[2][3]) -
                   data[1][2]*(data[2][1]*data[3][3] - data[3][1]*data[2][3]) +
                   data[1][3]*(data[2][1]*data[3][2] - data[3][1]*data[2][2]);
    subDet[0][1] = data[1][0]*(data[2][2]*data[3][3] - data[3][2]*data[2][3]) -
                   data[1][2]*(data[2][0]*data[3][3] - data[3][0]*data[2][3]) +
                   data[1][3]*(data[2][0]*data[3][2] - data[3][0]*data[2][2]);
    subDet[0][2] = data[1][0]*(data[2][1]*data[3][3] - data[3][1]*data[2][3]) -
                   data[1][1]*(data[2][0]*data[3][3] - data[3][0]*data[2][3]) +
                   data[1][3]*(data[2][0]*data[3][1] - data[3][0]*data[2][1]);
    subDet[0][3] = data[1][0]*(data[2][1]*data[3][2] - data[3][1]*data[2][2]) -
                   data[1][1]*(data[2][0]*data[3][2] - data[3][0]*data[2][2]) +
                   data[1][2]*(data[2][0]*data[3][1] - data[3][0]*data[2][1]);
    subDet[1][0] = data[0][1]*(data[2][2]*data[3][3] - data[3][2]*data[2][3]) -
                   data[0][2]*(data[2][1]*data[3][3] - data[3][1]*data[2][3]) +
                   data[0][3]*(data[2][1]*data[3][2] - data[3][1]*data[2][2]);
    subDet[1][1] = data[0][0]*(data[2][2]*data[3][3] - data[3][2]*data[2][3]) -
                   data[0][2]*(data[2][0]*data[3][3] - data[3][0]*data[2][3]) +
                   data[0][3]*(data[2][0]*data[3][2] - data[3][0]*data[2][2]);
    subDet[1][2] = data[0][0]*(data[2][1]*data[3][3] - data[3][1]*data[2][3]) -
                   data[0][1]*(data[2][0]*data[3][3] - data[3][0]*data[2][3]) +
                   data[0][3]*(data[2][0]*data[3][1] - data[3][0]*data[2][1]);
    subDet[1][3] = data[0][0]*(data[2][1]*data[3][2] - data[3][1]*data[2][2]) -
                   data[0][1]*(data[2][0]*data[3][2] - data[3][0]*data[2][2]) +
                   data[0][2]*(data[2][0]*data[3][1] - data[3][0]*data[2][1]);
    subDet[2][0] = data[0][1]*(data[1][2]*data[3][3] - data[3][2]*data[1][3]) -
                   data[0][2]*(data[1][1]*data[3][3] - data[3][1]*data[1][3]) +
                   data[0][3]*(data[1][1]*data[3][2] - data[3][1]*data[1][2]);
    subDet[2][1] = data[0][0]*(data[1][2]*data[3][3] - data[3][2]*data[1][3]) -
                   data[0][2]*(data[1][0]*data[3][3] - data[3][0]*data[1][3]) +
                   data[0][3]*(data[1][0]*data[3][2] - data[3][0]*data[1][2]);
    subDet[2][2] = data[0][0]*(data[1][1]*data[3][3] - data[3][1]*data[1][3]) -
                   data[0][1]*(data[1][0]*data[3][3] - data[3][0]*data[1][3]) +
                   data[0][3]*(data[1][0]*data[3][1] - data[3][0]*data[1][1]);
    subDet[2][3] = data[0][0]*(data[1][1]*data[3][2] - data[3][1]*data[1][2]) -
                   data[0][1]*(data[1][0]*data[3][2] - data[3][0]*data[1][2]) +
                   data[0][2]*(data[1][0]*data[3][1] - data[3][0]*data[1][1]);
    subDet[3][0] = data[0][1]*(data[1][2]*data[2][3] - data[2][2]*data[1][3]) -
                   data[0][2]*(data[1][1]*data[2][3] - data[2][1]*data[1][3]) +
                   data[0][3]*(data[1][1]*data[2][2] - data[2][1]*data[1][2]);
    subDet[3][1] = data[0][0]*(data[1][2]*data[2][3] - data[2][2]*data[1][3]) -
                   data[0][2]*(data[1][0]*data[2][3] - data[2][0]*data[1][3]) +
                   data[0][3]*(data[1][0]*data[2][2] - data[2][0]*data[1][2]);
    subDet[3][2] = data[0][0]*(data[1][1]*data[2][3] - data[2][1]*data[1][3]) -
                   data[0][1]*(data[1][0]*data[2][3] - data[2][0]*data[1][3]) +
                   data[0][3]*(data[1][0]*data[2][1] - data[2][0]*data[1][1]);
    subDet[3][3] = data[0][0]*(data[1][1]*data[2][2] - data[2][1]*data[1][2]) -
                   data[0][1]*(data[1][0]*data[2][2] - data[2][0]*data[1][2]) +
                   data[0][2]*(data[1][0]*data[2][1] - data[2][0]*data[1][1]);

    float det = data[0][0]*subDet[0][0] - data[0][1]*subDet[0][1] +
                data[0][2]*subDet[0][2] - data[0][3]*subDet[0][3];

    hsMatrix44 result;
    result.data[0][0] = subDet[0][0] / det;
    result.data[0][1] = subDet[1][0] / -det;
    result.data[0][2] = subDet[2][0] / det;
    result.data[0][3] = subDet[3][0] / -det;
    result.data[1][0] = subDet[0][1] / -det;
    result.data[1][1] = subDet[1][1] / det;
    result.data[1][2] = subDet[2][1] / -det;
    result.data[1][3] = subDet[3][1] / det;
    result.data[2][0] = subDet[0][2] / det;
    result.data[2][1] = subDet[1][2] / -det;
    result.data[2][2] = subDet[2][2] / det;
    result.data[2][3] = subDet[3][2] / -det;
    result.data[3][0] = subDet[0][3] / -det;
    result.data[3][1] = subDet[1][3] / det;
    result.data[3][2] = subDet[2][3] / -det;
    result.data[3][3] = subDet[3][3] / det;
    return result;
}

hsMatrix44& hsMatrix44::translate(const hsVector3& translate) {
    data[0][3] += translate.X;
    data[1][3] += translate.Y;
    data[2][3] += translate.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::rotate(int axis, float angle) {
    hsMatrix44 rMat = RotateMat(axis, angle);
    (*this) = rMat * (*this);
    return (*this);
}

hsMatrix44& hsMatrix44::scale(const hsVector3& scale) {
    data[0][0] *= scale.X;
    data[0][1] *= scale.X;
    data[0][2] *= scale.X;
    data[0][3] *= scale.X;
    data[1][0] *= scale.Y;
    data[1][1] *= scale.Y;
    data[1][2] *= scale.Y;
    data[1][3] *= scale.Y;
    data[2][0] *= scale.Z;
    data[2][1] *= scale.Z;
    data[2][2] *= scale.Z;
    data[2][3] *= scale.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::setTranslate(const hsVector3& translate) {
    data[0][3] = translate.X;
    data[1][3] = translate.Y;
    data[2][3] = translate.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::setRotate(int axis, float angle) {
    // Note: This is only for rotation around the global axes.
    //   You should get Local-To-World coordinates first before using this
    //   function if you want a local axis rotation.
    int c1, c2;
    switch(axis) {
    case kRight:
        c1 = 1;
        c2 = 2;
        break;
    case kUp:
        c1 = 0;
        c2 = 2;
        break;
    case kView:
        c1 = 0;
        c2 = 1;
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__);
    }
    data[c1][c1] = cos(angle);
    data[c2][c2] = cos(angle);
    data[c1][c2] = sin(angle);
    data[c2][c1] = -sin(angle);
    return (*this);
}

hsMatrix44& hsMatrix44::setScale(const hsVector3& scale) {
    data[0][0] = scale.X;
    data[1][1] = scale.Y;
    data[2][2] = scale.Z;
    return (*this);
}

void hsMatrix44::read(hsStream* S) {
    bool hasData = true;
    if (S->getVer().isLive() || S->getVer().isHexIsle())
        hasData = S->readBool();

    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                data[y][x] = S->readFloat();
    } else {
        Reset();
    }
}

void hsMatrix44::write(hsStream* S) {
    bool hasData = true;
    if (S->getVer().isLive() || S->getVer().isHexIsle()) {
        hasData = !IsIdentity();
        S->writeBool(hasData);
    }

    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                S->writeFloat(data[y][x]);
    }
}

void hsMatrix44::prcWrite(pfPrcHelper* prc) {
    if (IsIdentity()) {
        prc->startTag("hsMatrix44");
        prc->writeParam("identity", true);
        prc->endTag(true);
    } else {
        prc->writeTagNoBreak("hsMatrix44");
        plString buf = plString::Format("[%f,%f,%f,%f ; %f,%f,%f,%f ; %f,%f,%f,%f ; %f,%f,%f,%f]",
            data[0][0], data[0][1], data[0][2], data[0][3],
            data[1][0], data[1][1], data[1][2], data[1][3],
            data[2][0], data[2][1], data[2][2], data[2][3],
            data[3][0], data[3][1], data[3][2], data[3][3]);
        prc->getStream()->writeStr(buf);
        prc->closeTagNoBreak();
    }
}

void hsMatrix44::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsMatrix44")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    if (tag->getParam("identity", "false").toBool()) {
        Reset();
    } else {
        hsTList<plString> contents = tag->getContents();
        if (contents.pop() != "[")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[0][0] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[0][1] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[0][2] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[0][3] = contents.pop().toFloat();
        if (contents.pop() != ";")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[1][0] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[1][1] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[1][2] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[1][3] = contents.pop().toFloat();
        if (contents.pop() != ";")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[2][0] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[2][1] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[2][2] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[2][3] = contents.pop().toFloat();
        if (contents.pop() != ";")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[3][0] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[3][1] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[3][2] = contents.pop().toFloat();
        if (contents.pop() != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        data[3][3] = contents.pop().toFloat();
        if (contents.pop() != "]")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
    }
}

plString hsMatrix44::toString() const {
    return plString::Format("[ %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f\n"
                            "  %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f ]",
        data[0][0], data[0][1], data[0][2], data[0][3],
        data[1][0], data[1][1], data[1][2], data[1][3],
        data[2][0], data[2][1], data[2][2], data[2][3],
        data[3][0], data[3][1], data[3][2], data[3][3]);
}
