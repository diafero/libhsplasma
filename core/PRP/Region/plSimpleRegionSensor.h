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

#ifndef _PLSIMPLEREGIONSENSOR_H
#define _PLSIMPLEREGIONSENSOR_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Message/plMessage.h"

class PLASMA_DLL plSimpleRegionSensor : public virtual plSingleModifier {
    CREATABLE(plSimpleRegionSensor, kSimpleRegionSensor, plSingleModifier)

protected:
    plMessage* fEnterMsg;
    plMessage* fExitMsg;

public:
    plSimpleRegionSensor() : fEnterMsg(NULL), fExitMsg(NULL) { }
    virtual ~plSimpleRegionSensor();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void setEnterMsg(plMessage* msg);
    void setExitMsg(plMessage* msg);
};


class PLASMA_DLL plSwimDetector : public virtual plSimpleRegionSensor {
    CREATABLE(plSwimDetector, kSwimDetector, plSimpleRegionSensor)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
};


class PLASMA_DLL plAutoWalkRegion : public virtual plSimpleRegionSensor {
    CREATABLE(plAutoWalkRegion, kAutoWalkRegion, plSimpleRegionSensor)

protected:
    unsigned int fUnknown;

public:
    plAutoWalkRegion() : fUnknown(0) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plRidingAnimatedPhysicalDetector : public virtual plSimpleRegionSensor {
    CREATABLE(plRidingAnimatedPhysicalDetector,
              kRidingAnimatedPhysicalDetector,
              plSimpleRegionSensor)
};

#endif
