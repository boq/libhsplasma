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

#include "plWin32StaticSound.h"

/* plWin32GroupedSound */
void plWin32GroupedSound::IRead(hsStream* S, plResManager* mgr) {
    plWin32Sound::IRead(S, mgr);

    fVolumes.setSizeNull(S->readShort());
    fStartPositions.setSizeNull(fVolumes.getSize());
    for (size_t i=0; i<fVolumes.getSize(); i++) {
        fStartPositions[i] = S->readInt();
        fVolumes[i] = S->readFloat();
    }
}

void plWin32GroupedSound::IWrite(hsStream* S, plResManager* mgr) {
    plWin32Sound::IWrite(S, mgr);

    S->writeShort(fVolumes.getSize());
    for (size_t i=0; i<fVolumes.getSize(); i++) {
        S->writeInt(fStartPositions[i]);
        S->writeFloat(fVolumes[i]);
    }
}

void plWin32GroupedSound::IPrcWrite(pfPrcHelper* prc) {
    plWin32Sound::IPrcWrite(prc);

    prc->writeSimpleTag("Volumes");
    for (unsigned short i=0; i<fVolumes.getSize(); i++) {
        prc->startTag("VolumeSet");
        prc->writeParam("position", fStartPositions[i]);
        prc->writeParam("volume", fVolumes[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plWin32GroupedSound::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Volumes") {
        const pfPrcTag* child = tag->getFirstChild();
        size_t nChildren = tag->countChildren();
        fVolumes.setSizeNull(nChildren);
        fStartPositions.setSizeNull(nChildren);
        for (size_t i=0; i<nChildren; i++) {
            if (child->getName() != "VolumeSet")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fStartPositions[i] = child->getParam("position", "0").toUint();
            fVolumes[i] = child->getParam("volume", "0").toFloat();
        }
    } else {
        plWin32Sound::IPrcParse(tag, mgr);
    }
}

void plWin32GroupedSound::setVolumes(size_t count, unsigned int* positions, float* volumes) {
    fVolumes.setSizeNull(count);
    fStartPositions.setSizeNull(count);
    for (size_t i=0; i<count; i++) {
        fStartPositions[i] = positions[i];
        fVolumes[i] = volumes[i];
    }
}


/* plWin32LinkSound */
void plWin32LinkSound::read(hsStream* S, plResManager* mgr) {
    plSound::read(S, mgr);
    fSynchFlags |= kLocalOnly;
    fProperties |= kPropDontFade;
}
