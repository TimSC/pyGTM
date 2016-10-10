Welcome to pyGTM.  As you are about to discover, this is very much a work in progress.  Hopefully this won't put you off and these notes will provide enough clues.  If you are expecting a 1.0 release and an easy setup I advise you that this is probably not what you are looking for.



Prerequisites:

This experimental example is running on Fedora 10.92. Python 2.6 & GT.M V53003

Python 2.6:   

[root@localhost pyGTMx]# /sbin/ldconfig -p | grep python
	libpython2.6.so.1.0 (libc6) => /usr/lib/libpython2.6.so.1.0
	libpython2.6.so (libc6) => /usr/lib/libpython2.6.so

requires python-devel

[root@localhost pyGTMx]# yum install python-devel


GT.M V53003: (Copyright 2001, 2003 Sanchez Computer Associates, Inc.)

using gtm_V53003_linux_i686_pro.tar.gz

tar -zxvf gtm_V53003_linux_i686_pro.tar.gz

cd GT.M

./configure

install to /opt/gtm/V53003

manually edited .bash_profile (not perfect)

# GTM - swd

gtm_dist='/opt/gtm/V53003'
export gtm_dist
gtmgbldir='mumps.gld'
export gtmgbldir
gtmroutines=". $gtm_dist"
export gtmroutines
alias gtm='$gtm_dist/mumps -direct'
alias mupip='$gtm_dist/mupip'
alias lke='$gtm_dist/lke'
alias gde='$gtm_dist/mumps -r ^GDE'
alias dse='$gtm_dist/dse'

PATH=$PATH:$gtm_dist

# GTM - swd

Configure the mumps.gld file

mumps -r ^GDE

change -segment DEFAULT -block=4096 -alloc=75000 -ext=2000 -glob=2048 -file=/opt/gtm/mumps.dat
change -region DEFAULT -rec=4080 -key=255 -std
e

Create the mumps.dat file

mupip create

make libgtmshr visable

[root@localhost pyGTMx]#echo /opt/gtm/V53003 > /etc/ld.so.conf.d/gtm.conf
[root@localhost pyGTMx]# /sbin/ldconfig
[root@localhost pyGTMx]# /sbin/ldconfig -p | grep gtmshr
	libgtmshr.so (libc6) => /opt/gtm/V53003/libgtmshr.so


Once you have The heart of the matter.

switch to folder pyGTMx:

fix the path in pyGTMx.c, change:

  putenv("GTMCI=/home/stuffduff/Desktop/pyGTMx/calltab.ci");

to:

  putenv("GTMCI=/path/to/your/pyGTMx/calltab.ci");

get a copy of the file gtmxc_types.h from your gtm directory and put it in the pyGTMx directory


[stuffduff@localhost pyGTMx]# ./doit
[stuffduff@localhost pyGTMx]# ./toit
running clean
running build
running build_ext
building 'pyGTMx' extension
creating build/temp.linux-i686-2.6
gcc -pthread -fno-strict-aliasing -DNDEBUG -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4 -m32 -march=i586 -mtune=generic -fasynchronous-unwind-tables -D_GNU_SOURCE -fPIC -fPIC -DMAJOR_VERSION=0 -DMINOR_VERSION=1 -I/usr/include/python2.6 -I/opt/gtm/V53003 -I/usr/include/python2.6 -c pyGTMx.c -o build/temp.linux-i686-2.6/pyGTMx.o
gcc -pthread -shared build/temp.linux-i686-2.6/pyGTMx.o -L/opt/gtm/V53003 -L/usr/lib -lgtmshr -lpython2.6 -lpython2.6 -o build/lib.linux-i686-2.6/pyGTMx.so
Switch to root and install.
[root@localhost pyGTMx]# python setup.py install
running install
running build
running build_ext
running install_lib
copying build/lib.linux-i686-2.6/pyGTMx.so -> /usr/lib/python2.6/site-packages
running install_egg_info
Removing /usr/lib/python2.6/site-packages/pyGTMx-0.1-py2.6.egg-info
Writing /usr/lib/python2.6/site-packages/pyGTMx-0.1-py2.6.egg-info
[root@localhost pyGTMx]# python
Python 2.6 (r26:66714, Mar 17 2009, 11:44:21) 
[GCC 4.4.0 20090313 (Red Hat 4.4.0-0.26)] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import pyGTMx
>>> 

Once the module is ok look at 

