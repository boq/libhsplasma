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

#ifndef _PLLOADAVATARMSG_H
#define _PLLOADAVATARMSG_H

#include "plLoadCloneMsg.h"
#include "PRP/Avatar/plAvTask.h"

class PLASMA_DLL plLoadAvatarMsg : public plLoadCloneMsg {
    CREATABLE(plLoadAvatarMsg, kLoadAvatarMsg, plLoadCloneMsg)

protected:
    bool fIsPlayer;
    plKey fSpawnPoint;
    plAvTask* fInitialTask;
    plString fUserStr;

public:
    plLoadAvatarMsg();
    virtual ~plLoadAvatarMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getIsPlayer() const { return fIsPlayer; }
    plKey getSpawnPoint() const { return fSpawnPoint; }
    plAvTask* getInitialTask() const { return fInitialTask; }
    plString getUserStr() const { return fUserStr; }

    void setIsPlayer(bool isPlayer) { fIsPlayer = isPlayer; }
    void setSpawnPoint(plKey spawnPoint) { fSpawnPoint = spawnPoint; }
    void setUserStr(plString userStr) { fUserStr = userStr; }

    void setInitialTask(plAvTask* InitialTask);
};

#endif
