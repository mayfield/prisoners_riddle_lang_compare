/*
 * Low level bindings to prisoner riddle.
 */

#include "Python.h"
#include "structmember.h"
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

int _rand_init = 0;


int _shuffle(void* buf, int size, int itemsize) {
    ptrdiff_t len = size / itemsize;

    #define REORDER(TYPE) { \
        TYPE *arr = buf; \
        for (ptrdiff_t i = 0; i < len; i++) { \
            ptrdiff_t to = rand() % len; \
            TYPE a = arr[to]; \
            TYPE b = arr[i]; \
            arr[i] = a; \
            arr[to] = b; \
        } \
    }

    if (itemsize == 1) {
        REORDER(uint8_t);
    } else if (itemsize == 2) {
        REORDER(uint16_t);
    } else if (itemsize == 4) {
        REORDER(uint32_t);
    } else if (itemsize == 8) {
        REORDER(uint64_t);
    } else {
        return -1;
    }
    return 0;
}
    

static PyObject *shuffle(PyObject *mod, PyObject *args) {
    Py_buffer o;
    if (!PyArg_ParseTuple(args, "y*:shuffle", &o))
        return NULL;
    if (o.ndim != 1) {
        PyBuffer_Release(&o);
        return PyErr_Format(PyExc_ValueError, "Only 1 dim buffers supported");
    }
    if (_rand_init == 0) {
        srand((unsigned int) time(NULL));
        _rand_init = 1;
    }
    if (_shuffle(o.buf, o.len, o.itemsize)) {
        PyBuffer_Release(&o);
        return PyErr_Format(PyExc_ValueError, "Invalid array/buffer element size");
    }
    PyObject *ret = o.obj;
    Py_INCREF(ret);
    PyBuffer_Release(&o);
    return ret;
}
 

static PyObject *run(PyObject *mod, PyObject *args) {
    Py_buffer o;
    char *typecode;
    if (!PyArg_ParseTuple(args, "y*s:run", &o, &typecode))
        return NULL;
    if (o.ndim != 1) {
        PyBuffer_Release(&o);
        return PyErr_Format(PyExc_ValueError, "Only 1 dim buffers supported");
    }
    if (strcmp(typecode, "I")) {
        PyBuffer_Release(&o);
        printf("typecode: %s\n", typecode);
        return PyErr_Format(PyExc_ValueError, "array.array with u32 requried");
    }
    unsigned int *boxes = o.buf;
    if (_shuffle(o.buf, o.len, o.itemsize)) {
        PyBuffer_Release(&o);
        return PyErr_Format(PyExc_ValueError, "Invalid array/buffer element size");
    }
    ptrdiff_t len = o.len / o.itemsize;
    unsigned int max_attempts = len / 2 - 1;
    for (unsigned int n = 0; n < len; n++) {
        unsigned int b = boxes[n];
        int attempts = 0;
        while (b != n && attempts < max_attempts) {
            b = boxes[b];
            attempts += 1;
        }
        if (b != n) {
            return PyLong_FromLong(0);
        }
    }
    return PyLong_FromLong(1);
}


static PyMethodDef _accel_methods[] = {
    {"run", run, METH_VARARGS, NULL},
    {"shuffle", shuffle, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


static struct PyModuleDef _accel_module = {
    PyModuleDef_HEAD_INIT,
    "pr._accel",
    "C bindings for prisoner riddle",
    -1,
    _accel_methods,
};


PyMODINIT_FUNC PyInit__accel(void) {
    return PyModule_Create(&_accel_module);
}
