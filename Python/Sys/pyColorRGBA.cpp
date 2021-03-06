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
#include <Sys/hsColor.h>
#include "pyColor.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyColorRGBA_dealloc(pyColorRGBA* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyColorRGBA___init__(pyColorRGBA* self, PyObject* args, PyObject* kwds) {
    float red = 0.0f, green = 0.0f, blue = 0.0f, alpha = 1.0f;
    PyObject* init = NULL;
    static char* kwlist[] = { "red", "green", "blue", "alpha", NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "fff|f", kwlist,
                                    &red, &green, &blue, &alpha)) {
        self->fThis->set(red, green, blue, alpha);
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "|O", &init)) {
        if (init == NULL)
            return 0;
        if (pyColorRGBA_Check(init)) {
            self->fThis->set(*((pyColorRGBA*)init)->fThis);
        } else {
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

static PyObject* pyColorRGBA_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyColorRGBA* self = (pyColorRGBA*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsColorRGBA();
    return (PyObject*)self;
}

static PyObject* pyColorRGBA_Repr(pyColorRGBA* self) {
    plString repr = plString::Format("hsColorRGBA(%f, %f, %f, %f)",
        self->fThis->r, self->fThis->g, self->fThis->b, self->fThis->a);
    return PlStr_To_PyStr(repr);
}

static PyObject* pyColorRGBA_set(pyColorRGBA* self, PyObject* args, PyObject* kwds) {
    float red = 0.0f, green = 0.0f, blue = 0.0f, alpha = 1.0f;
    static char* kwlist[] = { "red", "green", "blue", "alpha", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ffff", kwlist,
                                     &red, &green, &blue, &alpha)) {
        PyErr_SetString(PyExc_TypeError, "set expects 0-4 floats");
        return NULL;
    }

    self->fThis->set(red, green, blue, alpha);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColorRGBA_setFrom(pyColorRGBA* self, PyObject* args) {
    pyColorRGBA* from;
    if (!PyArg_ParseTuple(args, "O", &from)) {
        PyErr_SetString(PyExc_TypeError, "setFrom expects an hsColorRGBA");
        return NULL;
    }
    if (!pyColorRGBA_Check((PyObject*)from)) {
        PyErr_SetString(PyExc_TypeError, "setFrom expects an hsColorRGBA");
        return NULL;
    }
    self->fThis->set(*from->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColorRGBA_read(pyColorRGBA* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColorRGBA_write(pyColorRGBA* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColorRGBA_readRGB(pyColorRGBA* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB expects a hsStream");
        return NULL;
    }
    self->fThis->readRGB(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColorRGBA_writeRGB(pyColorRGBA* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB expects a hsStream");
        return NULL;
    }
    self->fThis->writeRGB(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColorRGBA_getRed(pyColorRGBA* self, void* closure) {
    return PyFloat_FromDouble(self->fThis->r);
}

static PyObject* pyColorRGBA_getGreen(pyColorRGBA* self, void* closure) {
    return PyFloat_FromDouble(self->fThis->g);
}

static PyObject* pyColorRGBA_getBlue(pyColorRGBA* self, void* closure) {
    return PyFloat_FromDouble(self->fThis->b);
}

static PyObject* pyColorRGBA_getAlpha(pyColorRGBA* self, void* closure) {
    return PyFloat_FromDouble(self->fThis->a);
}

static int pyColorRGBA_setRed(pyColorRGBA* self, PyObject* value, void* closure) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "red should be a float");
        return -1;
    }
    self->fThis->r = PyFloat_AsDouble(value);
    return 0;
}

static int pyColorRGBA_setGreen(pyColorRGBA* self, PyObject* value, void* closure) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "green should be a float");
        return -1;
    }
    self->fThis->g = PyFloat_AsDouble(value);
    return 0;
}

static int pyColorRGBA_setBlue(pyColorRGBA* self, PyObject* value, void* closure) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "blue should be a float");
        return -1;
    }
    self->fThis->b = PyFloat_AsDouble(value);
    return 0;
}

static int pyColorRGBA_setAlpha(pyColorRGBA* self, PyObject* value, void* closure) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "alpha should be a float");
        return -1;
    }
    self->fThis->a = PyFloat_AsDouble(value);
    return 0;
}

static PyMethodDef pyColorRGBA_Methods[] = {
    { "set", (PyCFunction)pyColorRGBA_set, METH_VARARGS | METH_KEYWORDS,
      "Params: red, green, blue, alpha (all optional)\n"
      "Sets the color" },
    { "setFrom", (PyCFunction)pyColorRGBA_setFrom, METH_VARARGS,
      "Params: color\n"
      "Sets the color" },
    { "read", (PyCFunction)pyColorRGBA_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "write", (PyCFunction)pyColorRGBA_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { "readRGB", (PyCFunction)pyColorRGBA_readRGB, METH_VARARGS,
      "Params: stream\n"
      "Same as read(), but does not read alpha" },
    { "writeRGB", (PyCFunction)pyColorRGBA_writeRGB, METH_VARARGS,
      "Params: stream\n"
      "Same as write(), but does not write alpha" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyColorRGBA_GetSet[] = {
    { "red", (getter)pyColorRGBA_getRed, (setter)pyColorRGBA_setRed, NULL, NULL },
    { "green", (getter)pyColorRGBA_getGreen, (setter)pyColorRGBA_setGreen, NULL, NULL },
    { "blue", (getter)pyColorRGBA_getBlue, (setter)pyColorRGBA_setBlue, NULL, NULL },
    { "alpha", (getter)pyColorRGBA_getAlpha, (setter)pyColorRGBA_setAlpha, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyColorRGBA_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsColorRGBA",             /* tp_name */
    sizeof(pyColorRGBA),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyColorRGBA_dealloc,    /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyColorRGBA_Repr,         /* tp_repr */
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
    "hsColorRGBA wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyColorRGBA_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyColorRGBA_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyColorRGBA___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyColorRGBA_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyColorRGBA_Type() {
    if (PyType_Ready(&pyColorRGBA_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kBlack",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kBlack));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kWhite",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kWhite));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kRed",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kRed));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kGreen",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kGreen));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kBlue",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kBlue));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kYellow",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kYellow));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kMagenta",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kMagenta));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kCyan",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kCyan));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kGray",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kGray));
    PyDict_SetItemString(pyColorRGBA_Type.tp_dict, "kNone",
                         pyColorRGBA_FromColorRGBA(hsColorRGBA::kNone));

    Py_INCREF(&pyColorRGBA_Type);
    return (PyObject*)&pyColorRGBA_Type;
}

int pyColorRGBA_Check(PyObject* obj) {
    if (obj->ob_type == &pyColorRGBA_Type
        || PyType_IsSubtype(obj->ob_type, &pyColorRGBA_Type))
        return 1;
    return 0;
}

PyObject* pyColorRGBA_FromColorRGBA(const hsColorRGBA& color) {
    pyColorRGBA* pc = PyObject_New(pyColorRGBA, &pyColorRGBA_Type);
    pc->fThis = new hsColorRGBA(color);
    return (PyObject*)pc;
}

}
