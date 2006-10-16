#include <stdlib.h>
#include "hsStream.h"

#define TARR_CAP_INCREMENT  32

template <class T>
class hsTArray {
private:
    int count, max;
    T** data;

    void ensureCap(int cap) {
        if (max < cap) {
            while (cap > max) max += TARR_CAP_INCREMENT;
            T* newData[] = new T*[max];
            for (int i=0; i<count; i++)
                newData[i] = data[i];
            data = newData;
        }
    }

public:
    hsTArray() : count(0), max(TARR_CAP_INCREMENT) {
        data = new T*[TARR_CAP_INCREMENT];
    }
    ~hsTArray<T>() {
        for (int i=0; i<count; i++)
            delete data[i];
        delete [] data;
    }

    void empty() {
        for (int i=0; i<count; i++)
            delete data[i];
        delete [] data;
        count = 0;
        max = TARR_CAP_INCREMENT;
        data = new T*[max];
    }

    void read(hsStream *S) {
        count = S->readLong();
        ensureCap(count);
        for (int i=0; i<count; i++) {
            data[i] = new T;
            data[i]->read(S);
        }
    }

    void write(hsStream *S) {
        S->writeLong(count);
        for (int i=0; i<count; i++)
            data[i]->write(S);
    }
};

