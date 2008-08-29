#include "plWaveSet6.h"

plWaveSet6::plWaveSet6() { }
plWaveSet6::~plWaveSet6() { }

IMPLEMENT_CREATABLE(plWaveSet6, kWaveSet6, plWaveSetBase)

void plWaveSet6::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plWaveSet6::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plWaveSet6::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);
    prc->writeComment("plWaveSet6 Not Implemented");
}

void plWaveSet6::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}