#include "Zadanie_7.h"

long long wrapped_factorial(unsigned n) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    long long result = -1;

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("zadanie_3_iter");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "factorial");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            PyTuple_SetItem(pArgs, 0, PyLong_FromUnsignedLong(n));

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                result = PyLong_AsLongLong(pValue);
                Py_DECREF(pValue);
            }
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }

    Py_FinalizeEx();
    return result;
}

unsigned wrapped_gcd(unsigned a, unsigned b) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    unsigned result = -1;

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("zadanie_3_iter");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "gcd");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);
            PyTuple_SetItem(pArgs, 0, PyLong_FromUnsignedLong(a));
            PyTuple_SetItem(pArgs, 1, PyLong_FromUnsignedLong(b));

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                result = PyLong_AsUnsignedLong(pValue);
                Py_DECREF(pValue);
            }
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }

    Py_FinalizeEx();
    return result;
}

EquationSolution wrapped_diophantine(int a, int b, int c) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    EquationSolution result = {-1, -1};

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("zadanie_3_iter");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "diophantine");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);
            PyTuple_SetItem(pArgs, 0, PyLong_FromLong(a));
            PyTuple_SetItem(pArgs, 1, PyLong_FromLong(b));
            PyTuple_SetItem(pArgs, 2, PyLong_FromLong(c));

            pValue = PyObject_CallObject(pFunc, pArgs);
            if (pValue != NULL) {
                result.x = PyLong_AsLong(PyTuple_GetItem(pValue, 0));
                result.y = PyLong_AsLong(PyTuple_GetItem(pValue, 1));
                result.gcd = PyLong_AsLong(PyTuple_GetItem(pValue, 2));
                Py_DECREF(pValue);
            }
            Py_DECREF(pArgs);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }

    Py_FinalizeEx();
    return result;
}

