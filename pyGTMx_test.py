#!/usr/bin/python
import pyGTMx
pyGTMx.mstart()
x="^pyGTM"
y="This was set from pyGTM."
z=pyGTMx.mset(x, y)
y=""
z=""
print "y=", y
print "z=", z
z=pyGTMx.mget(x)
print "y=", y
print "z=", z
z=pyGTMx.mkil(x)
pyGTMx.mstop()



