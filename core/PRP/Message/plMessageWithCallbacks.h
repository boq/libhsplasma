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

#ifndef _PLMESSAGEWITHCALLBACKS_H
#define _PLMESSAGEWITHCALLBACKS_H

#include "plMessage.h"

class PLASMA_DLL plMessageWithCallbacks : public plMessage {
    CREATABLE(plMessageWithCallbacks, kMessageWithCallbacks, plMessage)

protected:
    hsTArray<plMessage*> fCallbacks;

public:
    plMessageWithCallbacks() { }
    virtual ~plMessageWithCallbacks();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plMessage*>& getCallbacks() const { return fCallbacks; }
    hsTArray<plMessage*>& getCallbacks() { return fCallbacks; }
    void addCallback(plMessage* callback) { fCallbacks.append(callback); }
    void delCallback(size_t idx);
    void clearCallbacks();
};

#endif
