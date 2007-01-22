#ifndef _PLFACTORY_H
#define _PLFACTORY_H

#include "plCreatable.h"
#include "../../CoreLib/hsRefCnt.h"

class plFactory : hsRefCnt {
private:
    PlasmaVer ver;

public:
    plFactory();
    plFactory(PlasmaVer pv);
    virtual ~plFactory();

    PlasmaVer getVer();
    virtual void setVer(PlasmaVer pv, bool mutate = false);

    virtual plCreatable* Create(short typeIdx);
};

#endif
