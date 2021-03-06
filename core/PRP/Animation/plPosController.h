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

#ifndef _PLPOSCONTROLLER_H
#define _PLPOSCONTROLLER_H

#include "plKeyControllers.hpp"

class PLASMA_DLL plPosController : public plController {
    CREATABLE(plPosController, kPosController, plController)

public:
    enum { kSimple = 1, kCompound };

public:
    virtual int getType() const = 0;
};


class PLASMA_DLL plSimplePosController : public plPosController {
    CREATABLE(plSimplePosController, kSimplePosController, plPosController)

protected:
    plPoint3Controller* fPosition;

public:
    plSimplePosController() : fPosition(NULL) { }
    virtual ~plSimplePosController();

    virtual int getType() const { return kSimple; }
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plPoint3Controller* getPosition() const { return fPosition; }
    void setPosition(plPoint3Controller* pos);
};


class PLASMA_DLL plCompoundPosController : public plPosController {
    CREATABLE(plCompoundPosController, kCompoundPosController, plPosController)

protected:
    plScalarController* fXController;
    plScalarController* fYController;
    plScalarController* fZController;

public:
    enum { kX, kY, kZ, kNumControllers };

    plCompoundPosController()
        : fXController(NULL), fYController(NULL), fZController(NULL) { }
    virtual ~plCompoundPosController();

    virtual int getType() const { return kCompound; }
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plScalarController* getX() const { return fXController; }
    plScalarController* getY() const { return fYController; }
    plScalarController* getZ() const { return fZController; }
    plScalarController* getController(unsigned int index) const {
        switch (index)
        {
        case kX:
            return fXController;
        case kY:
            return fYController;
        case kZ:
            return fZController;
        default:
            return NULL;
        }
    }

    void setController(unsigned int index, plScalarController* controller);
    void setX(plScalarController* controller);
    void setY(plScalarController* controller);
    void setZ(plScalarController* controller);
};

#endif
