#include <PyPlasma.h>
#include <PRP/GUI/pfGUIControlHandlers.h>
#include "pyGUIControlHandlers.h"

extern "C" {

static PyObject* pyGUIPythonScriptProc_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGUIPythonScriptProc* self = (pyGUIPythonScriptProc*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new pfGUIPythonScriptProc();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PyTypeObject pyGUIPythonScriptProc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.pfGUIPythonScriptProc",   /* tp_name */
    sizeof(pyGUIPythonScriptProc),      /* tp_basicsize */
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
    "pfGUIPythonScriptProc wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGUIPythonScriptProc_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyGUIPythonScriptProc_Type() {
    pyGUIPythonScriptProc_Type.tp_base = &pyGUICtrlProcWriteableObject_Type;
    if (PyType_Ready(&pyGUIPythonScriptProc_Type) < 0)
        return NULL;

    Py_INCREF(&pyGUIPythonScriptProc_Type);
    return (PyObject*)&pyGUIPythonScriptProc_Type;
}

int pyGUIPythonScriptProc_Check(PyObject* obj) {
    if (obj->ob_type == &pyGUIPythonScriptProc_Type
        || PyType_IsSubtype(obj->ob_type, &pyGUIPythonScriptProc_Type))
        return 1;
    return 0;
}

PyObject* pyGUIPythonScriptProc_FromGUIPythonScriptProc(pfGUIPythonScriptProc* proc) {
    if (proc == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyGUIPythonScriptProc* pyobj = PyObject_New(pyGUIPythonScriptProc, &pyGUIPythonScriptProc_Type);
    pyobj->fThis = proc;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
