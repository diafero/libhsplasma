#include "hsKeyedObject.h"
#include "Stream/hsRAMStream.h"

/* hsKeyedObject */
void hsKeyedObject::init(const plString& name) {
    myKey = new plKeyData();
    myKey->setType(ClassIndex());
    myKey->setName(name);
    myKey->setObj(this);
}

void hsKeyedObject::read(hsStream* S, plResManager* mgr) {
    if (S->getVer() == pvLive)
        myKey = mgr->readKey(S);
    else
        myKey = mgr->readUoid(S);
    if (myKey != NULL) {
        // In case we're replacing a key
        delete myKey->getObj();
        myKey->setObj(this);
    }
}

void hsKeyedObject::write(hsStream* S, plResManager* mgr) {
    if (S->getVer() == pvLive)
        mgr->writeKey(S, myKey);
    else
        mgr->writeUoid(S, myKey);
}

void hsKeyedObject::IPrcWrite(pfPrcHelper* prc) {
    myKey->prcWrite(prc);
}

void hsKeyedObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plKey") {
        myKey = mgr->prcParseKey(tag);
        if (myKey != NULL)
            myKey->setObj(this);
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void hsKeyedObject::setKey(plKey key) {
    myKey = key;
    if (myKey != NULL)
        myKey->setObj(this);
}


/* hsKeyedObjectStub */
hsKeyedObjectStub::hsKeyedObjectStub() : fStub(NULL) { }

hsKeyedObjectStub::~hsKeyedObjectStub() {
    delete fStub;
}

void hsKeyedObjectStub::write(hsStream* S, plResManager* mgr) {
    fStub->write(S, mgr);
}

void hsKeyedObjectStub::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);
    fStub->prcWrite(prc);
}

void hsKeyedObjectStub::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plCreatableStub")
        fStub->prcParse(tag, mgr);
    else
        hsKeyedObject::IPrcParse(tag, mgr);
}

void hsKeyedObjectStub::setStub(plCreatableStub* stub) {
    delete fStub;
    fStub = stub;
}
