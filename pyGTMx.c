#include <Python.h>

#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "gtmxc_types.h"

#define BUF_LEN 1024
#define VAL_LEN 32767

struct termios term_settings;  

gtm_char_t     msgbuf[BUF_LEN];
gtm_status_t   status;

void reset_input_mode (void) {
  tcsetattr (STDIN_FILENO, TCSANOW, &term_settings);
}

void save_input_mode (void) {
  if (isatty (STDIN_FILENO)) {
    tcgetattr (STDIN_FILENO, &term_settings);
    atexit ((void(*)())reset_input_mode);
  } 
}

static PyObject *pyGTMxError;

static PyObject *pyGTM_mstart(PyObject *self, PyObject *args) {
  status = gtm_init();
  if (isatty (STDIN_FILENO))
    tcsetattr (STDIN_FILENO, TCSANOW, &term_settings);
  if (status != 0) {
    gtm_zstatus(msgbuf, BUF_LEN);
    PyErr_SetString(pyGTMxError, msgbuf);
  }
  return Py_BuildValue("i", status);
}

static PyObject *pyGTM_mstop(PyObject *self, PyObject *args) {
  status = gtm_exit();
  if (isatty (STDIN_FILENO)) 
    tcsetattr (STDIN_FILENO, TCSANOW, &term_settings);
  if (status != 0) {
    gtm_zstatus(msgbuf, BUF_LEN);
    PyErr_SetString(pyGTMxError, msgbuf);
  }
  return Py_BuildValue("i", status);
}

static PyObject *pyGTM_mget(PyObject *self, PyObject *args) {
  char *ref;
  char *val[VAL_LEN];
  if (!PyArg_ParseTuple(args, "ss:mget", &ref, &val))
    return NULL;
  status = gtm_ci("get", ref, &val[0]);
  if (isatty (STDIN_FILENO)) 
    tcsetattr (STDIN_FILENO, TCSANOW, &term_settings);
  if (status != 0) {
    gtm_zstatus(msgbuf, BUF_LEN);
    PyErr_SetString(pyGTMxError, msgbuf);
    return Py_BuildValue("i", status);
  }
  return Py_BuildValue("s", val);
}

static PyObject *pyGTM_mset(PyObject *self, PyObject *args) {
  char *ref;
  char *val;
  if (!PyArg_ParseTuple(args, "ss:mset", &ref, &val))
    return NULL;
  status = gtm_ci("set", ref, val);
  if (isatty (STDIN_FILENO)) 
    tcsetattr (STDIN_FILENO, TCSANOW, &term_settings);
  if (status != 0) {
    gtm_zstatus(msgbuf, BUF_LEN);
    PyErr_SetString(pyGTMxError, msgbuf);
  }
  return Py_BuildValue("i", status);
}

static PyObject *pyGTM_mkil(PyObject *self, PyObject *args) {
  char *ref;
  if (!PyArg_ParseTuple(args, "s:mkil", &ref))
    return NULL;
  status = gtm_ci("kil", ref);
  if (isatty (STDIN_FILENO)) 
    tcsetattr (STDIN_FILENO, TCSANOW, &term_settings);
  if (status != 0) {
    gtm_zstatus(msgbuf, BUF_LEN);
    PyErr_SetString(pyGTMxError, msgbuf);    
  }
  return Py_BuildValue("i", status);
}

static PyObject *pyGTM_mtst(PyObject *self, PyObject *args) {
  char *ref;
  if (!PyArg_ParseTuple(args, "s:mtst", &ref))
    return NULL;
  status = gtm_ci("tst", ref);
  if (isatty (STDIN_FILENO)) 
    tcsetattr (STDIN_FILENO, TCSANOW, &term_settings);
  if (status != 0) {
    gtm_zstatus(msgbuf, BUF_LEN);
    PyErr_SetString(pyGTMxError, msgbuf);
  }
  return Py_BuildValue("i", status);
}

static PyObject *pyGTM_msts(PyObject *self, PyObject *args) {
  char *ref;
  char *val[VAL_LEN];
  if (!PyArg_ParseTuple(args, "ss:msts", &ref, &val))
    return NULL;
  status = gtm_ci("sts", ref, &val[0]);
  if (isatty (STDIN_FILENO)) 
    tcsetattr (STDIN_FILENO, TCSANOW, &term_settings);
  if (status != 0) {
    gtm_zstatus(msgbuf, BUF_LEN);
    PyErr_SetString(pyGTMxError, msgbuf);
    return Py_BuildValue("i", status);
  }
  return Py_BuildValue("s", val);
}

static PyObject *pyGTM_mdir(PyObject *self, PyObject *args) {
  PyObject *ref;
  if (!PyArg_ParseTuple(args, "O:mdir", &ref))
    return NULL;
  return PyObject_Dir(ref);
}

static PyMethodDef pyGTMxMethods[] = {
  {"mstart", pyGTM_mstart, METH_VARARGS, "Start pyGTM connection."},
  {"mstop",  pyGTM_mstop,  METH_VARARGS, "Stop pyGTM connection."},
  {"mget",   pyGTM_mget,   METH_VARARGS, "Get GTM global by reference."},
  {"mset",   pyGTM_mset,   METH_VARARGS, "Set GTM global by reference & value."},
  {"mkil",   pyGTM_mkil,   METH_VARARGS, "Kill GTM global by reference."},
  {"mtst",   pyGTM_mtst,   METH_VARARGS, "Test multi-user write."},
  {"msts",   pyGTM_msts,   METH_VARARGS, "Test multi-user read."},
  {"mdir",   pyGTM_mdir,   METH_VARARGS, "Test PyObject_Dir."},
  {NULL,     NULL,         0,            NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initpyGTMx(void) {
  PyObject *m;
  m = Py_InitModule("pyGTMx", pyGTMxMethods);
  pyGTMxError = PyErr_NewException("pyGTMx.error", NULL, NULL);
  Py_INCREF(pyGTMxError);
  PyModule_AddObject(m, "error", pyGTMxError);
  /* edit this path to point to your calltab.ci*/
  putenv("GTMCI=/home/stuffduff/Desktop/pyGTMx/calltab.ci");
  save_input_mode();
}

int main() {
  return 0;
}
