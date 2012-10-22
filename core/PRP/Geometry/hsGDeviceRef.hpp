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

#ifndef _HSGDEVICEREF_H
#define _HSGDEVICEREF_H

#include "PlasmaDefs.h"

class PLASMA_DLL hsGDeviceRef /*: public hsRefCnt*/ {
public:
    enum { kNone, kDirty };

protected:
    unsigned int flags, useTime;

public:
    hsGDeviceRef() : flags(kNone), useTime(0) { }

    bool isDirty() { return (flags & kDirty); }
    void setDirty(bool dirty) {
        if (dirty)
            flags |= kDirty;
        else
            flags &= ~kDirty;
    }
};

#endif