#include <PyPlasma.h>
#include <PRP/GUI/pfGUIControlHandlers.h>
#include "pyGUIControlHandlers.h"

extern "C" {

static PyObject* pyGUIConsoleCmdProc_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGUIConsoleCmdProc* self = (pyGUIConsoleCmdProc*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new pfGUIConsoleCmdProc();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyGUIConsoleCmdProc_getCmd(pyGUIConsoleCmdProc* self, void*) {
    return PyString_FromString(self->fThis->getCommand().cstr());
}

static int pyGUIConsoleCmdProc_setCmd(pyGUIConsoleCmdProc* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setCommand("");
    } else {
        if (!PyString_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "command should be a string");
            return -1;
        }
        self->fThis->setCommand(PyString_AsString(value));
    }
    return 0;
}

static PyGetSetDef pyGUIConsoleCmdProc_GetSet[] = {
    { "command", (getter)pyGUIConsoleCmdProc_getCmd, (setter)pyGUIConsoleCmdProc_setCmd, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyGUIConsoleCmdProc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.pfGUIConsoleCmdProc",     /* tp_name */
    sizeof(pyGUIConsoleCmdProc),        /* tp_basicsize */
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
    "pfGUIConsoleCmdProc wrapper",      /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyGUIConsoleCmdProc_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGUIConsoleCmdProc_new,            /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyGUIConsoleCmdProc_Type() {
    pyGUIConsoleCmdProc_Type.tp_base = &pyGUICtrlProcWriteableObject_Type;
    if (PyType_Ready(&pyGUIConsoleCmdProc_Type) < 0)
        return NULL;

    Py_INCREF(&pyGUIConsoleCmdProc_Type);
    return (PyObject*)&pyGUIConsoleCmdProc_Type;
}

int pyGUIConsoleCmdProc_Check(PyObject* obj) {
    if (obj->ob_type == &pyGUIConsoleCmdProc_Type
        || PyType_IsSubtype(obj->ob_type, &pyGUIConsoleCmdProc_Type))
        return 1;
    return 0;
}

PyObject* pyGUIConsoleCmdProc_FromGUIConsoleCmdProc(pfGUIConsoleCmdProc* proc) {
    if (proc == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyGUIConsoleCmdProc* pyobj = PyObject_New(pyGUIConsoleCmdProc, &pyGUIConsoleCmdProc_Type);
    pyobj->fThis = proc;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
