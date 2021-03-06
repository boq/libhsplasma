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

#ifndef _PLCLUSTERGROUP_H
#define _PLCLUSTERGROUP_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Misc/plRenderLevel.h"
#include "plCluster.h"
#include "plSpanTemplate.h"

class PLASMA_DLL plLODDist {
protected:
    float fMinDist, fMaxDist;

public:
    plLODDist();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    float getMin() const { return fMinDist; }
    float getMax() const { return fMaxDist; }
    void setMin(float dist) { fMinDist = dist; }
    void setMax(float dist) { fMaxDist = dist; }
};

class PLASMA_DLL plClusterGroup : public virtual hsKeyedObject {
    CREATABLE(plClusterGroup, kClusterGroup, hsKeyedObject)

protected:
    plSpanTemplate fTemplate;
    plKey fMaterial;
    hsTArray<plCluster*> fClusters;
    hsTArray<plKey> fRegions, fLights;
    plLODDist fLOD;
    plKey fSceneNode, fDrawable;
    unsigned int fRenderLevel;

public:
    plClusterGroup();
    virtual ~plClusterGroup();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plLODDist& getLOD() const { return fLOD; }
    plLODDist& getLOD() { return fLOD; }
    const plSpanTemplate& getTemplate() const { return fTemplate; }
    plSpanTemplate& getTemplate() { return fTemplate; }

    plKey getMaterial() const { return fMaterial; }
    plKey getSceneNode() const { return fSceneNode; }
    plKey getDrawable() const { return fDrawable; }
    unsigned int getRenderLevel() const { return fRenderLevel; }

    void setMaterial(plKey mat) { fMaterial = mat; }
    void setSceneNode(plKey node) { fSceneNode = node; }
    void setDrawable(plKey draw) { fDrawable = draw; }
    void setRenderLevel(unsigned int level) { fRenderLevel = level; }

    const hsTArray<plCluster*>& getClusters() const { return fClusters; }
    hsTArray<plCluster*>& getClusters() { return fClusters; }
    void addCluster(plCluster* cluster) { fClusters.append(cluster); }
    void delCluster(size_t idx);
    void clearClusters();

    const hsTArray<plKey>& getRegions() const { return fRegions; }
    hsTArray<plKey>& getRegions() { return fRegions; }
    void addRegion(plKey region) { fRegions.append(region); }
    void delRegion(size_t idx) { fRegions.remove(idx); }
    void clearRegions() { fRegions.clear(); }

    const hsTArray<plKey>& getLights() const { return fLights; }
    hsTArray<plKey>& getLights() { return fLights; }
    void addLight(plKey light) { fLights.append(light); }
    void delLight(size_t idx) { fLights.remove(idx); }
    void clearLights() { fLights.clear(); }
};

#endif
