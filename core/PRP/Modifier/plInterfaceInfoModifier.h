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

#ifndef _PLINTERFACEINFOMODIFIER_H
#define _PLINTERFACEINFOMODIFIER_H

#include "plModifier.h"

class PLASMA_DLL plInterfaceInfoModifier : public virtual plSingleModifier {
    CREATABLE(plInterfaceInfoModifier, kInterfaceInfoModifier, plSingleModifier)

protected:
    hsTArray<plKey> fKeyList;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getIntfKeys() const { return fKeyList; }
    hsTArray<plKey>& getIntfKeys() { return fKeyList; }
    void addIntfKey(plKey key) { fKeyList.append(key); }
    void delIntfKey(size_t idx) { fKeyList.remove(idx); }
    void clearIntfKeys() { fKeyList.clear(); }
};

#endif
