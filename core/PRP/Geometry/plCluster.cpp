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

#include "plCluster.h"
#include "plClusterGroup.h"

plCluster::~plCluster() {
    for (size_t i=0; i<fInstances.getSize(); i++)
        delete fInstances[i];
}

void plCluster::read(hsStream* S, plClusterGroup* group) {
    fEncoding.read(S);
    fGroup = group;
    unsigned int numVerts = fGroup->getTemplate().getNumVerts();
    clearInstances();
    fInstances.setSizeNull(S->readInt());
    for (size_t i=0; i<fInstances.getSize(); i++) {
        fInstances[i] = new plSpanInstance();
        fInstances[i]->read(S, fEncoding, numVerts);
    }
}

void plCluster::write(hsStream* S) {
    fEncoding.write(S);
    S->writeInt(fInstances.getSize());
    for (size_t i=0; i<fInstances.getSize(); i++)
        fInstances[i]->write(S);
}

void plCluster::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plCluster");

    prc->writeSimpleTag("Encoding");
    fEncoding.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Instances");
    for (size_t i=0; i<fInstances.getSize(); i++)
        fInstances[i]->prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}

void plCluster::prcParse(const pfPrcTag* tag, plClusterGroup* group) {
    if (tag->getName() != "plCluster")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fGroup = group;
    unsigned int numVerts = fGroup->getTemplate().getNumVerts();
    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Encoding") {
            if (child->hasChildren())
                fEncoding.prcParse(child->getFirstChild());
        } else if (child->getName() == "Instances") {
            clearInstances();
            fInstances.setSizeNull(child->countChildren());
            const pfPrcTag* inst = child->getFirstChild();
            for (size_t i=0; i<fInstances.getSize(); i++) {
                fInstances[i] = new plSpanInstance();
                fInstances[i]->prcParse(inst, fEncoding, numVerts);
                inst = inst->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

void plCluster::delInstance(size_t idx) {
    delete fInstances[idx];
    fInstances.remove(idx);
}

void plCluster::clearInstances() {
    for (size_t i=0; i<fInstances.getSize(); i++)
        delete fInstances[i];
    fInstances.clear();
}
