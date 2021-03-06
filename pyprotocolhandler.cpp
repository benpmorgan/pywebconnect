#include <Python.h>
#include "wx/wxPython/wxPython.h"
#include "wx/wxPython/pyclasses.h"
#include "webconnect/protocolhandler.h"
#include "pyprotocolhandler.h"

#if wxUSE_UNICODE
#define PYSTRING_FROM_WXSTRING(str) PyUnicode_FromWideChar((str).c_str(), (str).Len());
#else
#define PYSTRING_FROM_WXSTRING(str) PyString_FromStringAndSize((str).c_str(), (str).Len());
#endif

wxPyProtocolHandler::wxPyProtocolHandler(PyObject *handler): m_handler(handler) {
    Py_INCREF(m_handler);
}

wxPyProtocolHandler::~wxPyProtocolHandler() {
    Py_DECREF(m_handler);
    m_handler = NULL;
}

wxString wxPyProtocolHandler::GetContent(const wxString &url)   {
    PyGILState_STATE gstate = PyGILState_Ensure();
    PyObject *method_name = PyString_FromString("GetContent");

    PyObject *python_url = PYSTRING_FROM_WXSTRING(url);
    PyObject *result = PyObject_CallMethodObjArgs(m_handler, method_name, python_url, NULL);
    Py_DECREF(python_url);
    if (!result) {
        PyErr_WriteUnraisable(method_name);
        Py_DECREF(method_name);
        PyGILState_Release(gstate);
        return wxT("");
    }
    Py_DECREF(method_name);

    wxString *temp_string = wxString_in_helper(result);
    if (!temp_string)  {
        PyErr_SetString(PyExc_ValueError, "GetContent must return a string.");
        PyGILState_Release(gstate);
        return wxT("");
    }
    wxString wxResult(*temp_string);
    PyGILState_Release(gstate);
    return wxResult;
}

wxString wxPyProtocolHandler::GetContentType(const wxString &url)   {
    PyGILState_STATE gstate = PyGILState_Ensure();

    PyObject *method_name = PyString_FromString((char *)"GetContentType");
    PyObject *python_url = PYSTRING_FROM_WXSTRING(url);

    PyObject *result = PyObject_CallMethodObjArgs(m_handler, method_name, python_url, NULL);
    Py_DECREF(python_url);
    if (!result) {
        PyErr_WriteUnraisable(method_name);
        Py_DECREF(method_name);
        PyGILState_Release(gstate);
        return wxT("");
    }
    Py_DECREF(method_name);

    wxString *temp_string = wxString_in_helper(result);
    if (!temp_string)  {
        PyErr_SetString(PyExc_ValueError, "GetContentType must return a string.");
        PyGILState_Release(gstate);
        return wxT("");
    }
    wxString wxResult(*temp_string);
    PyGILState_Release(gstate);

    return wxResult;
}
