#ifndef _PYGUICONTROLHANDLERS_H
#define _PYGUICONTROLHANDLERS_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class pfGUICtrlProcObject* fThis;
    bool fPyOwned;
} pyGUICtrlProcObject;

typedef struct {
    PyObject_HEAD
    class pfGUIDialogProc* fThis;
    bool fPyOwned;
} pyGUIDialogProc;

typedef struct {
    PyObject_HEAD
    class pfGUICtrlProcWriteableObject* fThis;
    bool fPyOwned;
} pyGUICtrlProcWriteableObject;

typedef struct {
    PyObject_HEAD
    class pfGUICloseDlgProc* fThis;
    bool fPyOwned;
} pyGUICloseDlgProc;

typedef struct {
    PyObject_HEAD
    class pfGUIConsoleCmdProc* fThis;
    bool fPyOwned;
} pyGUIConsoleCmdProc;

typedef struct {
    PyObject_HEAD
    class pfGUIPythonScriptProc* fThis;
    bool fPyOwned;
} pyGUIPythonScriptProc;

extern PyTypeObject pyGUICtrlProcObject_Type;
PyObject* Init_pyGUICtrlProcObject_Type();
int pyGUICtrlProcObject_Check(PyObject* obj);
PyObject* pyGUICtrlProcObject_FromGUICtrlProcObject(class pfGUICtrlProcObject* obj);

extern PyTypeObject pyGUIDialogProc_Type;
PyObject* Init_pyGUIDialogProc_Type();
int pyGUIDialogProc_Check(PyObject* obj);
PyObject* pyGUIDialogProc_FromGUIDialogProc(class pfGUIDialogProc* obj);

extern PyTypeObject pyGUICtrlProcWriteableObject_Type;
PyObject* Init_pyGUICtrlProcWriteableObject_Type();
int pyGUICtrlProcWriteableObject_Check(PyObject* obj);
PyObject* pyGUICtrlProcWriteableObject_FromGUICtrlProcWriteableObject(class pfGUICtrlProcWriteableObject* obj);

extern PyTypeObject pyGUICloseDlgProc_Type;
PyObject* Init_pyGUICloseDlgProc_Type();
int pyGUICloseDlgProc_Check(PyObject* obj);
PyObject* pyGUICloseDlgProc_FromGUICloseDlgProc(class pfGUICloseDlgProc* obj);

extern PyTypeObject pyGUIConsoleCmdProc_Type;
PyObject* Init_pyGUIConsoleCmdProc_Type();
int pyGUIConsoleCmdProc_Check(PyObject* obj);
PyObject* pyGUIConsoleCmdProc_FromGUIConsoleCmdProc(class pfGUIConsoleCmdProc* obj);

extern PyTypeObject pyGUIPythonScriptProc_Type;
PyObject* Init_pyGUIPythonScriptProc_Type();
int pyGUIPythonScriptProc_Check(PyObject* obj);
PyObject* pyGUIPythonScriptProc_FromGUIPythonScriptProc(class pfGUIPythonScriptProc* obj);

}

#endif
