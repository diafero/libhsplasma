#ifndef _PLLOADMASK_H
#define _PLLOADMASK_H

#include "hsStream.h"

class plLoadMask {
protected:
    union {
        unsigned char quality[2];
        unsigned short mask;
    };

public:
    plLoadMask();
    ~plLoadMask();
    
    void read(hsStream* S);
    void write(hsStream* S);

    bool isUsed();
    plLoadMask& setMask(unsigned char m1, unsigned char m2);
    plLoadMask& setAlways();
};

#endif
