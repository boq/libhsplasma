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

#include "plAvatarMsg.h"

/* plArmatureUpdateMsg */
plArmatureUpdateMsg::plArmatureUpdateMsg() {
    fBCastFlags |= kBCastByExactType;
}

void plArmatureUpdateMsg::read(hsStream* S, plResManager* mgr) { }
void plArmatureUpdateMsg::write(hsStream* S, plResManager* mgr) { }
void plArmatureUpdateMsg::IPrcWrite(pfPrcHelper* prc) { }

void plArmatureUpdateMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    plCreatable::IPrcParse(tag, mgr);
}


/* plAvatarSetTypeMsg */
plAvatarSetTypeMsg::plAvatarSetTypeMsg() : fIsPlayer(false) { }

void plAvatarSetTypeMsg::read(hsStream* S, plResManager* mgr) {
    fIsPlayer = S->readBool();
}

void plAvatarSetTypeMsg::write(hsStream* S, plResManager* mgr) {
    S->writeBool(fIsPlayer);
}

void plAvatarSetTypeMsg::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("AvatarType");
    prc->writeParam("IsPlayer", fIsPlayer);
    prc->endTag(true);
}

void plAvatarSetTypeMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AvatarType") {
        fIsPlayer = tag->getParam("IsPlayer", "False").toBool();
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}


/* plAvatarStealthModeMsg */
plAvatarStealthModeMsg::plAvatarStealthModeMsg() {
    fBCastFlags |= kBCastByExactType;
}

void plAvatarStealthModeMsg::read(hsStream* S, plResManager* mgr) { }
void plAvatarStealthModeMsg::write(hsStream* S, plResManager* mgr) { }
void plAvatarStealthModeMsg::IPrcWrite(pfPrcHelper* prc) { }

void plAvatarStealthModeMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    plCreatable::IPrcParse(tag, mgr);
}


/* plAvBrainGenericMsg */
plAvBrainGenericMsg::plAvBrainGenericMsg()
                   : fType(0), fWhichStage(0), fSetTime(false), fSetDirection(false),
                     fNewDirection(false), fNewTime(0.0f), fTransitionTime(0.0f) { }

void plAvBrainGenericMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fType = S->readInt();
    fWhichStage = S->readInt();
    fSetTime = S->readBool();
    fNewTime = S->readFloat();
    fSetDirection = S->readBool();
    fNewDirection = S->readBool();
    fTransitionTime = S->readFloat();
}

void plAvBrainGenericMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeInt(fType);
    S->writeInt(fWhichStage);
    S->writeBool(fSetTime);
    S->writeFloat(fNewTime);
    S->writeBool(fSetDirection);
    S->writeBool(fNewDirection);
    S->writeFloat(fTransitionTime);
}

void plAvBrainGenericMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("AvBrainGenericParams");
    prc->writeParam("Type", fType);
    prc->writeParam("Stage", fWhichStage);
    prc->writeParam("SetTime", fSetTime);
    prc->writeParam("NewTime", fNewTime);
    prc->writeParam("SetDirection", fSetDirection);
    prc->writeParam("NewDirection", fNewDirection);
    prc->writeParam("TransitionTime", fTransitionTime);
    prc->endTag(true);
}

void plAvBrainGenericMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AvBrainGenericParams") {
        fType = tag->getParam("Type", "0").toUint();
        fWhichStage = tag->getParam("Stage", "0").toUint();
        fSetTime = tag->getParam("SetTime", "False").toBool();
        fNewTime = tag->getParam("NewTime", "0").toFloat();
        fSetDirection = tag->getParam("SetDirection", "False").toBool();
        fNewDirection = tag->getParam("NewDirection", "False").toBool();
        fTransitionTime = tag->getParam("TransitionTime", "0").toFloat();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}


/* plAvTaskSeekDoneMsg */
plAvTaskSeekDoneMsg::plAvTaskSeekDoneMsg() : fAborted(false) { }

void plAvTaskSeekDoneMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fAborted = S->readBool();
}

void plAvTaskSeekDoneMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeBool(fAborted);
}

void plAvTaskSeekDoneMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("SeekDoneParams");
    prc->writeParam("Aborted", fAborted);
    prc->endTag(true);
}

void plAvTaskSeekDoneMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SeekDoneParams") {
        fAborted = tag->getParam("Aborted", "False").toBool();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
