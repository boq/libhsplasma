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

#include "plAvatarInputStateMsg.h"
#include "Debug/plDebug.h"

plAvatarInputStateMsg::plAvatarInputStateMsg() : fState(0) { }

void plAvatarInputStateMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fState = S->readShort();
}

void plAvatarInputStateMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeShort(fState);
}

void plAvatarInputStateMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("State");
    prc->writeParamHex("value", fState);
    prc->endTag(true);
}

void plAvatarInputStateMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "State") {
        fState = tag->getParam("value", "0").toUint();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
