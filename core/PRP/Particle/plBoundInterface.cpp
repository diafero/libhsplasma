#include "plBoundInterface.h"

plBoundInterface::plBoundInterface() : fBounds(NULL) { }

plBoundInterface::~plBoundInterface() {
    delete fBounds;
}

void plBoundInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    setBounds(plConvexVolume::Convert(mgr->ReadCreatable(S)));
}

void plBoundInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    mgr->WriteCreatable(S, fBounds);
}

void plBoundInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Bounds");
    fBounds->prcWrite(prc);
    prc->closeTag();
}

void plBoundInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Bounds") {
        if (tag->hasChildren())
            setBounds(plConvexVolume::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}

void plBoundInterface::setBounds(plConvexVolume* bounds) {
    delete fBounds;
    fBounds = bounds;
}
