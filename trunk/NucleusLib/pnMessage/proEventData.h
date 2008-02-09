#ifndef _PROEVENTDATA_H
#define _PROEVENTDATA_H

#include "PlasmaDefs.h"
#include "CoreLib/hsStream.h"
#include "CoreLib/hsGeometry3.h"
#include "NucleusLib/pnKeyedObject/plKey.h"
#include "PubUtilLib/plResMgr/plResManager.h"

DllClass proEventData {
public:
    enum eventType {
        kCollision = 1, kPicked, kControlKey, kVariable, kFacing, kContained,
        kActivate, kCallback, kResponderState, kMultiStage, kSpawned,
        kClickDrag, kCoop, kOfferLinkBook, kBook, kClimbingBlockerHit,
        kNone
    };

    enum dataType { kNumber, kKey, kNotta };

    enum multiStageEventType {
        kEnterStage = 1, kBeginningOfLoop, kAdvanceNextStage,
        kRegressPrevStage, kNothing
    };

private:
    static const char* const fEventNames[];

protected:
    int fEventType;

public:
    proEventData();
    virtual ~proEventData();

    static proEventData* ICreateEventDataType(int type);
    static proEventData* read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);

protected:
    virtual void IRead(hsStream* S, plResManager* mgr)=0;
    virtual void IWrite(hsStream* S, plResManager* mgr)=0;
    virtual void IPrcWrite(pfPrcHelper* prc)=0;
};

DllClass proCollisionEventData : public proEventData {
protected:
    bool fEnter;
    plKey fHitter;
    plKey fHittee;

public:
    proCollisionEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proPickedEventData : public proEventData {
protected:
    plKey fPicker;
    plKey fPicked;
    bool fEnabled;
    hsPoint3 fHitPoint;

public:
    proPickedEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proControlKeyEventData : public proEventData {
protected:
    int fControlKey;
    bool fDown;

public:
    proControlKeyEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proVariableEventData : public proEventData {
protected:
    plString fName;
    int fDataType;
    float fNumber;
    plKey fKey;

public:
    proVariableEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proFacingEventData : public proEventData {
protected:
    plKey fFacer;
    plKey fFacee;
    float dot;
    bool enabled;

public:
    proFacingEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proContainedEventData : public proEventData {
protected:
    plKey fContained;
    plKey fContainer;
    bool fEntering;

public:
    proContainedEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proActivateEventData : public proEventData {
protected:
    bool fActive, fActivate;

public:
    proActivateEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proCallbackEventData : public proEventData {
protected:
    int fCallbackEventType;

public:
    proCallbackEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proResponderStateEventData : public proEventData {
protected:
    int fState;

public:
    proResponderStateEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proMultiStageEventData : public proEventData {
protected:
    int fStage, fEvent;
    plKey fAvatar;

public:
    proMultiStageEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proSpawnedEventData : public proEventData {
protected:
    plKey fSpawner;
    plKey fSpawnee;

public:
    proSpawnedEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proClickDragEventData : public proEventData {
public:
    proClickDragEventData();
};

DllClass proCoopEventData : public proEventData {
protected:
    unsigned int fID;
    unsigned short fSerial;

public:
    proCoopEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proOfferLinkBookEventData : public proEventData {
protected:
    plKey offerer;
    int targetAge, offeree;

public:
    proOfferLinkBookEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proBookEventData : public proEventData {
protected:
    unsigned int fEvent, fLinkID;

public:
    proBookEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proClimbingBlockerHitEventData : public proEventData {
protected:
    plKey fBlockerKey;

public:
    proClimbingBlockerHitEventData();

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif