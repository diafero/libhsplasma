#ifndef _PLRECEIVER_H
#define _PLRECEIVER_H

#include "plCreatable.h"
#include "NucleusLib/pnKeyedObject/plKey.h"
//#include "NucleusLib/pnMessage/plMessage.h"

class plReceiver : public plCreatable {
protected:
    plKey key;

public:
    plReceiver(PlasmaVer pv = pvUnknown);
    ~plReceiver();

    bool msgReceive(class plMessage * msg);
};

#endif

