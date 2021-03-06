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

#include <PyPlasma.h>
#include "pyGeometrySpan.h"
#include "pyTempVertex.h"
#include "Math/pyMatrix.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Region/pyBounds.h"

extern "C" {

static void pyGeometrySpan_dealloc(pyGeometrySpan* self) {
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pyGeometrySpan_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGeometrySpan* self = (pyGeometrySpan*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis.reset(new plGeometrySpan);
    return (PyObject*)self;
}

static PyObject* pyGeometrySpan_addPermaLight(pyGeometrySpan* self, PyObject* args) {
    PyObject* light;
    if (!(PyArg_ParseTuple(args, "O", &light) && pyKey_Check(light))) {
        PyErr_SetString(PyExc_TypeError, "addPermaLight expects a plKey");
        return NULL;
    }

    self->fThis->addPermaLight(*((pyKey*)light)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGeometrySpan_delPermaLight(pyGeometrySpan* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPermaLight expects an int");
        return NULL;
    }

    self->fThis->delPermaLight((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGeometrySpan_clearPermaLights(pyGeometrySpan* self) {
    self->fThis->clearPermaLights();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGeometrySpan_addPermaProj(pyGeometrySpan* self, PyObject* args) {
    PyObject* light;
    if (!(PyArg_ParseTuple(args, "O", &light) && pyKey_Check(light))) {
        PyErr_SetString(PyExc_TypeError, "addPermaProj expects a plKey");
        return NULL;
    }

    self->fThis->addPermaProj(*((pyKey*)light)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGeometrySpan_delPermaProj(pyGeometrySpan* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPermaProj expects an int");
        return NULL;
    }

    self->fThis->delPermaProj((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGeometrySpan_clearPermaProjs(pyGeometrySpan* self) {
    self->fThis->clearPermaProjs();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGeometrySpan_getBaseMatrix(pyGeometrySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getBaseMatrix());
}

static PyObject* pyGeometrySpan_getFogEnvironment(pyGeometrySpan* self, void*) {
    return pyKey_FromKey(self->fThis->getFogEnvironment());
}

static PyObject* pyGeometrySpan_getFormat(pyGeometrySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getFormat());
}

static PyObject* pyGeometrySpan_getIndices(pyGeometrySpan* self, void*) {
    PyObject* list = PyList_New(self->fThis->getIndices().size());
    for (size_t i = 0; i < self->fThis->getIndices().size(); ++i)
        PyList_SET_ITEM(list, i, PyInt_FromLong(self->fThis->getIndices()[i]));
    return list;
}

static PyObject* pyGeometrySpan_getLocalBounds(pyGeometrySpan* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getLocalBounds());
}

static PyObject* pyGeometrySpan_getLocalToWorld(pyGeometrySpan* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLocalToWorld());
}

static PyObject* pyGeometrySpan_getLocalUVWChans(pyGeometrySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getLocalUVWChans());
}

static PyObject* pyGeometrySpan_getMaterial(pyGeometrySpan* self, void*) {
    return pyKey_FromKey(self->fThis->getMaterial());
}

static PyObject* pyGeometrySpan_getMaxBoneIdx(pyGeometrySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getMaxBoneIdx());
}

static PyObject* pyGeometrySpan_getMaxDist(pyGeometrySpan* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMaxDist());
}

static PyObject* pyGeometrySpan_getMinDist(pyGeometrySpan* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMinDist());
}

static PyObject* pyGeometrySpan_getNumMatrices(pyGeometrySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getNumMatrices());
}

static PyObject* pyGeometrySpan_getPenBoneIdx(pyGeometrySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getPenBoneIdx());
}

static PyObject* pyGeometrySpan_getProps(pyGeometrySpan* self, void*) {
    return PyInt_FromLong(self->fThis->getProps());
}

static PyObject* pyGeometrySpan_getVertices(pyGeometrySpan* self, void*) {
    std::vector<plGeometrySpan::TempVertex> verts = self->fThis->getVertices();
    PyObject* list = PyList_New(verts.size());
    for (size_t i = 0; i < verts.size(); ++i)
        PyList_SET_ITEM(list, i, pyTempVertex_FromTempVertex(verts[i]));
    return list;
}

static PyObject* pyGeometrySpan_getWaterHeight(pyGeometrySpan* self, void*) {
    return PyFloat_FromDouble(self->fThis->getWaterHeight());
}

static PyObject* pyGeometrySpan_getWorldBounds(pyGeometrySpan* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getWorldBounds());
}

static PyObject* pyGeometrySpan_getWorldToLocal(pyGeometrySpan* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getWorldToLocal());
}

static PyObject* pyGeometrySpan_getPermaLights(pyGeometrySpan* self, void*) {
    const std::vector<plKey>& lights = self->fThis->getPermaLights();
    PyObject* tup = PyTuple_New(lights.size());
    for (size_t i = 0; i < lights.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(lights[i]));
    return tup;
}

static PyObject* pyGeometrySpan_getPermaProjs(pyGeometrySpan* self, void*) {
    const std::vector<plKey>& lights = self->fThis->getPermaProjs();
    PyObject* tup = PyTuple_New(lights.size());
    for (size_t i = 0; i < lights.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(lights[i]));
    return tup;
}

static int pyGeometrySpan_setBaseMatrix(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "baseMatrix should be an int");
        return -1;
    }
    self->fThis->setBaseMatrix(PyInt_AsLong(value));
    return 0;
}

static int pyGeometrySpan_setFogEnvironment(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fogEnvironment should be a plKey");
        return -1;
    }
    self->fThis->setFogEnvironment(*((pyKey*)value)->fThis);
    return 0;
}

static int pyGeometrySpan_setFormat(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "format should be an int");
        return -1;
    }
    self->fThis->setFormat(PyInt_AsLong(value));
    return 0;
}

static int pyGeometrySpan_setIndices(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "indices should be a sequence of unsigned shorts");
        return -1;
    }
    size_t count = PySequence_Size(value);
    for (size_t i = 0; i < count; ++i) {
        if (!PyInt_Check(PySequence_Fast_GET_ITEM(value, i))) {
            PyErr_SetString(PyExc_TypeError, "indices should be a sequence of unsigned shorts");
            return -1;
        }
    }

    std::vector<unsigned short> idx(PySequence_Size(value));
    for (size_t i = 0; i < idx.size(); ++i)
        idx[i] = PyInt_AsLong(PySequence_Fast_GET_ITEM(value, i));
    self->fThis->setIndices(idx);
    return 0;
}

static int pyGeometrySpan_setLocalBounds(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setLocalBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static int pyGeometrySpan_setLocalToWorld(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localToWorld should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLocalToWorld(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyGeometrySpan_setLocalUVWChans(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localUVWChans should be an int");
        return -1;
    }
    self->fThis->setLocalUVWChans(PyInt_AsLong(value));
    return 0;
}

static int pyGeometrySpan_setMaterial(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "material should be a plKey");
        return -1;
    }
    self->fThis->setMaterial(*((pyKey*)value)->fThis);
    return 0;
}

static int pyGeometrySpan_setMaxBoneIdx(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxBoneIdx should be an int");
        return -1;
    }
    self->fThis->setMaxBoneIdx(PyInt_AsLong(value));
    return 0;
}

static int pyGeometrySpan_setMaxDist(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxDist should be a float");
        return -1;
    }
    self->fThis->setMaxDist(PyFloat_AsDouble(value));
    return 0;
}

static int pyGeometrySpan_setMinDist(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minDist should be a float");
        return -1;
    }
    self->fThis->setMinDist(PyFloat_AsDouble(value));
    return 0;
}

static int pyGeometrySpan_setNumMatrices(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "numMatrices should be an int");
        return -1;
    }
    self->fThis->setNumMatrices(PyInt_AsLong(value));
    return 0;
}

static int pyGeometrySpan_setPenBoneIdx(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "penBoneIdx should be an int");
        return -1;
    }
    self->fThis->setPenBoneIdx(PyInt_AsLong(value));
    return 0;
}

static int pyGeometrySpan_setProps(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "props should be an int");
        return -1;
    }
    self->fThis->setProps(PyInt_AsLong(value));
    return 0;
}

static int pyGeometrySpan_setVertices(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "vertices should be a sequence of TempVertex");
        return -1;
    }
    size_t count = PySequence_Size(value);
    for (size_t i = 0; i < count; ++i) {
        if (!pyTempVertex_Check(PySequence_Fast_GET_ITEM(value, i))) {
            PyErr_SetString(PyExc_TypeError, "vertices should be a sequence of TempVertex");
            return -1;
        }
    }

    std::vector<plGeometrySpan::TempVertex> verts(PySequence_Size(value));
    for (size_t i = 0; i < verts.size(); ++i)
        verts[i] = *((pyTempVertex*)PySequence_Fast_GET_ITEM(value, i))->fThis;
    self->fThis->setVertices(verts);
    return 0;
}

static int pyGeometrySpan_setWaterHeight(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "waterHeight should be a float");
        return -1;
    }
    self->fThis->setWaterHeight(PyFloat_AsDouble(value));
    return 0;
}

static int pyGeometrySpan_setWorldBounds(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "worldBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setWorldBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static int pyGeometrySpan_setWorldToLocal(pyGeometrySpan* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "worldToLocal should be an hsMatrix44");
        return -1;
    }
    self->fThis->setWorldToLocal(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyGeometrySpan_setPermaLights(pyGeometrySpan* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add PermaLights, use addPermaLight");
    return -1;
}

static int pyGeometrySpan_setPermaProjs(pyGeometrySpan* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add PermaProjs, use addPermaLight");
    return -1;
}

static PyMethodDef pyGeometrySpan_Methods[] = {
    { "addPermaLight", (PyCFunction)pyGeometrySpan_addPermaLight, METH_VARARGS,
      "Params: light\n"
      "Adds a permalight" },
    { "delPermaLight", (PyCFunction)pyGeometrySpan_delPermaLight, METH_VARARGS,
      "Params: idx\n"
      "Removes a permalight" },
    { "clearPermaLight", (PyCFunction)pyGeometrySpan_clearPermaLights, METH_NOARGS,
      "Clears all permalights" },
    { "addPermaProj", (PyCFunction)pyGeometrySpan_addPermaProj, METH_VARARGS,
      "Params: light\n"
      "Adds a permaproj" },
    { "delPermaProj", (PyCFunction)pyGeometrySpan_delPermaProj, METH_VARARGS,
      "Params: idx\n"
      "Removes a permaproj" },
    { "clearPermaProj", (PyCFunction)pyGeometrySpan_clearPermaProjs, METH_NOARGS,
      "Clears all permaprojs" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyGeometrySpan_GetSet[] = {
    { _pycs("baseMatrix"), (getter)pyGeometrySpan_getBaseMatrix,
        (setter)pyGeometrySpan_setBaseMatrix, NULL, NULL },
    { _pycs("fogEnvironment"), (getter)pyGeometrySpan_getFogEnvironment,
        (setter)pyGeometrySpan_setFogEnvironment, NULL, NULL },
    { _pycs("format"), (getter)pyGeometrySpan_getFormat,
        (setter)pyGeometrySpan_setFormat, NULL, NULL },
    { _pycs("indices"), (getter)pyGeometrySpan_getIndices,
        (setter)pyGeometrySpan_setIndices, NULL, NULL },
    { _pycs("localBounds"), (getter)pyGeometrySpan_getLocalBounds,
        (setter)pyGeometrySpan_setLocalBounds, NULL, NULL },
    { _pycs("localToWorld"), (getter)pyGeometrySpan_getLocalToWorld,
        (setter)pyGeometrySpan_setLocalToWorld, NULL, NULL },
    { _pycs("localUVWChans"), (getter)pyGeometrySpan_getLocalUVWChans,
        (setter)pyGeometrySpan_setLocalUVWChans, NULL, NULL },
    { _pycs("material"), (getter)pyGeometrySpan_getMaterial,
        (setter)pyGeometrySpan_setMaterial, NULL, NULL},
    { _pycs("maxBoneIdx"), (getter)pyGeometrySpan_getMaxBoneIdx,
        (setter)pyGeometrySpan_setMaxBoneIdx, NULL, NULL },
    { _pycs("maxDist"), (getter)pyGeometrySpan_getMaxDist,
        (setter)pyGeometrySpan_setMaxDist, NULL, NULL},
    { _pycs("minDist"), (getter)pyGeometrySpan_getMinDist,
        (setter)pyGeometrySpan_setMinDist, NULL, NULL},
    { _pycs("numMatrices"), (getter)pyGeometrySpan_getNumMatrices,
        (setter)pyGeometrySpan_setNumMatrices, NULL, NULL},
    { _pycs("penBoneIdx"), (getter)pyGeometrySpan_getPenBoneIdx,
        (setter)pyGeometrySpan_setPenBoneIdx, NULL, NULL },
    { _pycs("props"), (getter)pyGeometrySpan_getProps,
        (setter)pyGeometrySpan_setProps, NULL, NULL },
    { _pycs("vertices"), (getter)pyGeometrySpan_getVertices,
        (setter)pyGeometrySpan_setVertices, NULL, NULL },
    { _pycs("waterHeight"), (getter)pyGeometrySpan_getWaterHeight,
        (setter)pyGeometrySpan_setWaterHeight, NULL, NULL },
    { _pycs("worldBounds"), (getter)pyGeometrySpan_getWorldBounds,
        (setter)pyGeometrySpan_setWorldBounds, NULL, NULL },
    { _pycs("worldToLocal"), (getter)pyGeometrySpan_getWorldToLocal,
        (setter)pyGeometrySpan_setWorldToLocal, NULL, NULL },
    { _pycs("permaLights"), (getter)pyGeometrySpan_getPermaLights,
        (setter)pyGeometrySpan_setPermaLights, NULL, NULL },
    { _pycs("permaProjs"), (getter)pyGeometrySpan_getPermaProjs,
        (setter)pyGeometrySpan_setPermaProjs, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyGeometrySpan_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plGeometrySpan",        /* tp_name */
    sizeof(pyGeometrySpan),             /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyGeometrySpan_dealloc, /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plGeometrySpan wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGeometrySpan_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyGeometrySpan_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGeometrySpan_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyGeometrySpan_Type() {
    if (PyType_Ready(&pyGeometrySpan_Type) < 0)
        return NULL;

    // Format
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kUVCountMask",
                         PyInt_FromLong(plGeometrySpan::kUVCountMask));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kSkinNoWeights",
                         PyInt_FromLong(plGeometrySpan::kSkinNoWeights));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kSkin1Weight",
                         PyInt_FromLong(plGeometrySpan::kSkin1Weight));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kSkin2Weights",
                         PyInt_FromLong(plGeometrySpan::kSkin2Weights));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kSkin3Weights",
                         PyInt_FromLong(plGeometrySpan::kSkin3Weights));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kSkinWeightMask",
                         PyInt_FromLong(plGeometrySpan::kSkinWeightMask));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kSkinIndices",
                         PyInt_FromLong(plGeometrySpan::kSkinIndices));

    // Properties
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kLiteMaterial",
                         PyInt_FromLong(plGeometrySpan::kLiteMaterial));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kPropRunTimeLight",
                         PyInt_FromLong(plGeometrySpan::kPropRunTimeLight));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kPropNoPreShade",
                         PyInt_FromLong(plGeometrySpan::kPropNoPreShade));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kLiteVtxPreshaded",
                         PyInt_FromLong(plGeometrySpan::kLiteVtxPreshaded));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kLiteVtxNonPreshaded",
                         PyInt_FromLong(plGeometrySpan::kLiteVtxNonPreshaded));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kLiteMask",
                         PyInt_FromLong(plGeometrySpan::kLiteMask));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kRequiresBlending",
                         PyInt_FromLong(plGeometrySpan::kRequiresBlending));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kInstanced",
                         PyInt_FromLong(plGeometrySpan::kInstanced));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kUserOwned",
                         PyInt_FromLong(plGeometrySpan::kUserOwned));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kPropNoShadow",
                         PyInt_FromLong(plGeometrySpan::kPropNoShadow));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kPropForceShadow",
                         PyInt_FromLong(plGeometrySpan::kPropForceShadow));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kDiffuseFoldedIn",
                         PyInt_FromLong(plGeometrySpan::kDiffuseFoldedIn));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kPropReverseSort",
                         PyInt_FromLong(plGeometrySpan::kPropReverseSort));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kWaterHeight",
                         PyInt_FromLong(plGeometrySpan::kWaterHeight));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kFirstInstance",
                         PyInt_FromLong(plGeometrySpan::kFirstInstance));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kPartialSort",
                         PyInt_FromLong(plGeometrySpan::kPartialSort));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kVisLOS",
                         PyInt_FromLong(plGeometrySpan::kVisLOS));
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "kPropNoShadowCast",
                         PyInt_FromLong(plGeometrySpan::kPropNoShadowCast));

    // TempVertex class thing
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "TempVertex",
                         Init_pyTempVertex_Type());

    Py_INCREF(&pyGeometrySpan_Type);
    return (PyObject*)&pyGeometrySpan_Type;
}

int pyGeometrySpan_Check(PyObject* obj) {
    if (obj->ob_type == &pyGeometrySpan_Type
        || PyType_IsSubtype(obj->ob_type, &pyGeometrySpan_Type))
        return 1;
    return 0;
}

PyObject* pyGeometrySpan_FromGeometrySpan(const std::shared_ptr<plGeometrySpan>& span) {
    if (span == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyGeometrySpan* pspan = PyObject_New(pyGeometrySpan, &pyGeometrySpan_Type);
    pspan->fThis = span;
    return (PyObject*)pspan;
}

};
