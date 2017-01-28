#include <Python.h>


static PyObject *spam_greet(PyObject *self, PyObject *args)
{
    const char *name;

    if (!PyArg_ParseTuple(args, "s", &name)) return NULL;

    printf("Hi %s!", name);
    Py_RETURN_NONE;
}


static PyObject *spam_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command)) return NULL;

    sts = system(command);
    return Py_BuildValue("i", sts);
}


static PyObject *spam_strlen(PyObject *self, PyObject *args)
{
    const char *string;

    if (!PyArg_ParseTuple(args, "s", &string)) return NULL;

    unsigned long len = strlen(string);
    return Py_BuildValue("i", len);
}


PyObject *makelist(int array[], int len)
{
    PyObject *py_list = PyList_New(len);
    for (int i = 0; i < len; i++) {
        PyList_SET_ITEM(py_list, i, Py_BuildValue("i", array[i]));
    }
    return py_list;
}


static PyObject *SpamError;


static PyObject *spam_fibonacci(PyObject *self, PyObject *args)
{
    int num_terms;

    if (!PyArg_ParseTuple(args, "i", &num_terms)) return NULL;

    if (num_terms < 0) {
        PyErr_SetString(SpamError, "Number of terms cannot be negative.");
        return NULL;
    }

    int numbers[num_terms];
    int first = 0;
    int second = 1;
    int next;

    for (int i = 0; i < num_terms; i++) {
        if (i <= 1) {
            next = i;
        } else {
            next = first + second;
            first = second;
            second = next;
        }
        numbers[i] = next;
    }
    return makelist(numbers, num_terms);
}


static PyMethodDef SpamMethods[] = {
    {"greet", spam_greet, METH_VARARGS, "Print greeting."},
    {"system", spam_system, METH_VARARGS, "Execute a shell command."},
    {"strlen", spam_strlen, METH_VARARGS, "Return length of a string"},
    {"fibonacci", spam_fibonacci, METH_VARARGS, "Return fibonacci series."},
    // ...
    {NULL, NULL, 0, NULL}   /* sentinel */
};


PyMODINIT_FUNC initspam(void)
{
    PyObject *m = Py_InitModule("spam", SpamMethods);
    if (m == NULL) return;

    SpamError = PyErr_NewException("spam.error", NULL, NULL);
    Py_INCREF(SpamError);
    PyModule_AddObject(m, "error", SpamError);
}


int main(int argc, char *argv[])
{
    // Pass argv[0] to the Python interpreter
    Py_SetProgramName(argv[0]);

    // Initialize the Python interpreter. Required
    Py_Initialize();

    // Add a static module
    initspam();
}

