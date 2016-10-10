Welcome to pyGTM.  As you are about to discover, this is very much a work in progress.  Hopefully this won't put you off and these notes will provide enough clues.  If you are expecting a 1.0 release and an easy setup I advise you that this is probably not what you are looking for.

Prerequisites:

Tested Platforms:
Fedora 10.92 (i686) with Python 2.6 and GT.M V53003 (i686)
Ubuntu 8.10 (x86_64) with Python 2.5 and GT.M V53003 (x86_64 compiled from sources)

This experimental example is running on Fedora 10.92. Python 2.6 & GT.M V53003

-------------------------------------------------------------------------------
Install Python 2.6:   

[root@localhost pyGTMx]# /sbin/ldconfig -p | grep python
	libpython2.6.so.1.0 (libc6) => /usr/lib/libpython2.6.so.1.0
	libpython2.6.so (libc6) => /usr/lib/libpython2.6.so

requires python-devel

[root@localhost pyGTMx]# yum install python-devel


-------------------------------------------------------------------------------
Install GT.M V53003: (Copyright 2001, 2003 Sanchez Computer Associates, Inc.)

1. Download and unpack GT.M
mkdir gtm
cd gtm
download gtm_V53003_linux_i686_pro.tar.gz from https://sourceforge.net/projects/fis-gtm
tar -zxvf gtm_V53003_linux_i686_pro.tar.gz

2. Install GT.M
sudo sh configure
- choose /opt/gtm/V53003 as your install directory
- you can safely answer no or default for the rest of the options

3. Setup your environment to use GT.M
add the following lines to your .bash_profile
# GTM - swd
source /opt/gtm/V53003/gtmprofile

4. Add libgtmshr.so as a trusted library
As root, the following commands complete this
[root@localhost pyGTMx]#echo /opt/gtm/V53003 > /etc/ld.so.conf.d/gtm.conf
[root@localhost pyGTMx]# /sbin/ldconfig
[root@localhost pyGTMx]# /sbin/ldconfig -p | grep gtmshr
	libgtmshr.so (libc6) => /opt/gtm/V53003/libgtmshr.so

An alternative is to use the LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/gtm/V53003

-------------------------------------------------------------------------------
Create you GT.M database files

The script dbcreate.sh will create a GT.M global directory (think table directory) named
pygtm.gld and a database file called pygtm.dat in your current working directory

/Path/To/pyGTMx/dbcreate.sh
export gtmgbldir=`pwd`/pygtm.gld

-------------------------------------------------------------------------------
Once you have The heart of the matter.

1. Setup the path to the GT.M Call-In table
GTMCI=/path/to/your/pyGTMx/calltab.ci;export GTMCI

2. Build pyGTMx
[stuffduff@localhost pyGTMx]# make
running clean
running build
running build_ext
building 'pyGTMx' extension
creating build/temp.linux-i686-2.6
gcc -pthread -fno-strict-aliasing -DNDEBUG -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4 -m32 -march=i586 -mtune=generic -fasynchronous-unwind-tables -D_GNU_SOURCE -fPIC -fPIC -DMAJOR_VERSION=0 -DMINOR_VERSION=1 -I/usr/include/python2.6 -I/opt/gtm/V53003 -I/usr/include/python2.6 -c pyGTMx.c -o build/temp.linux-i686-2.6/pyGTMx.o
gcc -pthread -shared build/temp.linux-i686-2.6/pyGTMx.o -L/opt/gtm/V53003 -L/usr/lib -lgtmshr -lpython2.6 -lpython2.6 -o build/lib.linux-i686-2.6/pyGTMx.so
Switch to root and install.

3. Install pyGTMx (needs root privileges)
[root@localhost pyGTMx]# make install
running install
running build
running build_ext
running install_lib
copying build/lib.linux-i686-2.6/pyGTMx.so -> /usr/lib/python2.6/site-packages
running install_egg_info
Removing /usr/lib/python2.6/site-packages/pyGTMx-0.1-py2.6.egg-info
Writing /usr/lib/python2.6/site-packages/pyGTMx-0.1-py2.6.egg-info

3. Inspect your work
[root@localhost pyGTMx]# python
Python 2.6 (r26:66714, Mar 17 2009, 11:44:21) 
[GCC 4.4.0 20090313 (Red Hat 4.4.0-0.26)] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import pyGTMx
>>> 

Once the module is ok look at pyGTMx_test.py.

