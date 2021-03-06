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
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"

extern "C" {

static PyObject* pyBookEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyBookEventData* self = (pyBookEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proBookEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyBookEventData_getEvent(pyBookEventData* self, void*) {
    return PyInt_FromLong(self->fThis->getEvent());
}

static PyObject* pyBookEventData_getLinkID(pyBookEventData* self, void*) {
    return PyInt_FromLong(self->fThis->getLinkID());
}

static int pyBookEventData_setEvent(pyBookEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "event should be an int");
        return -1;
    }
    self->fThis->setEvent(PyInt_AsLong(value));
    return 0;
}

static int pyBookEventData_setLinkID(pyBookEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "linkID should be an int");
        return -1;
    }
    self->fThis->setLinkID(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyBookEventData_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyBookEventData_GetSet[] = {
    { "event", (getter)pyBookEventData_getEvent, (setter)pyBookEventData_setEvent, NULL, NULL },
    { "linkID", (getter)pyBookEventData_getLinkID, (setter)pyBookEventData_setLinkID, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyBookEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proBookEventData",        /* tp_name */
    sizeof(pyBookEventData),            /* tp_basicsize */
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
    "proBookEventData wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyBookEventData_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyBookEventData_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyBookEventData_new,                /* tp_new */
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

PyObject* Init_pyBookEventData_Type() {
    pyBookEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyBookEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyBookEventData_Type);
    return (PyObject*)&pyBookEventData_Type;
}

int pyBookEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyBookEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyBookEventData_Type))
        return 1;
    return 0;
}

PyObject* pyBookEventData_FromBookEventData(proBookEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyBookEventData* pyobj = PyObject_New(pyBookEventData, &pyBookEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
