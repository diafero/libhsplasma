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
#include <PRP/Audio/plAudible.h>
#include "pyAudible.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* py2WayWinAudible_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    py2WayWinAudible* self = (py2WayWinAudible*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new pl2WayWinAudible();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyMethodDef py2WayWinAudible_Methods[] = {
    { NULL, NULL, 0, NULL }
};

PyTypeObject py2WayWinAudible_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.pl2WayWinAudible",      /* tp_name */
    sizeof(py2WayWinAudible),           /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "pl2WayWinAudible wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    py2WayWinAudible_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    py2WayWinAudible_new,               /* tp_new */
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

PyObject* Init_py2WayWinAudible_Type() {
    py2WayWinAudible_Type.tp_base = &pyWinAudible_Type;
    if (PyType_Ready(&py2WayWinAudible_Type) < 0)
        return NULL;

    Py_INCREF(&py2WayWinAudible_Type);
    return (PyObject*)&py2WayWinAudible_Type;
}

int py2WayWinAudible_Check(PyObject* obj) {
    if (obj->ob_type == &py2WayWinAudible_Type
        || PyType_IsSubtype(obj->ob_type, &py2WayWinAudible_Type))
        return 1;
    return 0;
}

PyObject* py2WayWinAudible_From2WayWinAudible(pl2WayWinAudible* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    py2WayWinAudible* pyobj = PyObject_New(py2WayWinAudible, &py2WayWinAudible_Type);
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
