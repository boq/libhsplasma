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

#ifndef _PLSTATEDESCRIPTOR_H
#define _PLSTATEDESCRIPTOR_H

#include "plSDL.h"

/* Note: for plStateDescriptor::fVersion, -1 on a search from plSDLMgr means
 * "get the latest version", whereas -1 on a returned plStateDescriptor means
 * "this descriptor is invalid".  Outside of these classes, it should only be
 * necessary to specify the version when needed in plSDLMgr, and to use the
 * isValid() function on returned plStateDescriptor objects.
 */

class PLASMA_DLL plVarDescriptor {
public:
    enum Type {
        kNone = 0xFF,
        kInt = 0, kFloat, kBool, kString, kKey, kStateDescriptor, kCreatable,
        kDouble, kTime, kByte, kShort, kAgeTimeOfDay,
        kVector3 = 50, kPoint3, kRGB, kRGBA, kQuaternion, kRGB8, kRGBA8,

        // For Myst 5
        kUint, kChar, kMatrix44, kBuffer, kAgeTimeElapsed, kGameTimeElapsed
    };

    enum Flags {
        kInternal = 0x1,
        kAlwaysNew = 0x2,
        kVariableLength = 0x4
    };

protected:
    plString fName, fDefault, fDisplay;
    size_t fCount;
    Type fType;
    unsigned int fFlags;
    plString fStateDescType;
    int fStateDescVer;
    class plStateDescriptor* fStateDesc;

public:
    plVarDescriptor();

    void read(hsStream* S);
    void write(hsStream* S);

public:
    plString getName() const { return fName; }
    plString getDefault() const { return fDefault; }
    plString getDisplay() const { return fDisplay; }
    size_t getCount() const { return fCount; }
    Type getType() const { return fType; }
    plString getStateDescType() const { return fStateDescType; }
    int getStateDescVer() const { return fStateDescVer; }
    plStateDescriptor* getStateDesc() const { return fStateDesc; }
    bool isInternal() const { return (fFlags & kInternal) != 0; }
    bool isAlwaysNew() const { return (fFlags & kAlwaysNew) != 0; }
    bool isVariableLength() const { return (fFlags & kVariableLength) != 0; }
    bool isValid() const { return fType != kNone; }

    void setName(const plString& name) { fName = name; }
    void setDefault(const plString& def) { fDefault = def; }
    void setDisplay(const plString& disp) { fDisplay = disp; }
    void setCount(size_t count) { fCount = count; }
    void setType(Type type) { fType = type; }
    void setStateDescType(const plString& type) { fStateDescType = type; }
    void setStateDescVer(int ver) { fStateDescVer = ver; }
    void setStateDesc(plStateDescriptor* desc);
    void setInternal(bool internal);
    void setAlwaysNew(bool alwaysNew);
    void setVariableLength(bool varLength);

    static Type GetTypeFromString(const plString& type, bool isEoa);
};


class PLASMA_DLL plStateDescriptor {
protected:
    plString fName;
    int fVersion;
    hsTArray<plVarDescriptor*> fVariables;

public:
    plStateDescriptor();
    ~plStateDescriptor();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

public:
    plString getName() const { return fName; }
    int getVersion() const { return fVersion; }
    bool isValid() const { return fVersion != -1; }

    void setName(const plString& name) { fName = name; }
    void setVersion(int ver) { fVersion = ver; }

    plVarDescriptor* get(size_t idx) { return fVariables[idx]; }
    plVarDescriptor* get(const plString& name);
    void set(size_t idx, plVarDescriptor* var) { fVariables[idx] = var; }
    void set(const plString& name, plVarDescriptor* var);

    size_t getNumVars() const { return fVariables.getSize(); }
    void addVariable(plVarDescriptor* var) { fVariables.append(var); }
    void delVariable(size_t idx);
    void delVariable(const plString& name);
    void clearVariables();
};

#endif
