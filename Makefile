
# you should use $gtm_dist from the associated gtm installation
# use gtmprofile for bash or sh and gtmcsrhc for csh or tcsh
# WARNING 64bit GT.M must be compiled from source, the binary
# distribution is i686 (32bit)
GTM_DIST = ${gtm_dist}

# 
PYTHON_VER = 2.6

# Need to setup LD_LIBRARY_PATH in order to use GT.M
# Need to setup GTMCI

CC = gcc
CFLAGS = -g
INCLUDES = -I. -I/usr/include/python${PYTHON_VER} -I${GTM_DIST}
LIBS = -L${GTM_DIST} -lgtmshr -lc -lpython${PYTHON_VER}

all: pyGTMx pyGTMx.so

/usr/include/python${PYTHON_VER}:
	@/bin/echo "Please install the python ${PYTHON_VER} development packages"
	@/bin/echo "These are the installed versions that you have"
	@ls -d /usr/include/python*
	@exit 1

$GTMCI:
	/bin/echo -e "\${GTMCI} not defined"
	/bin/echo 'setenv GTMCI `pwd`/calltab.ci'

$LD_LIBRARY_PATH:
	/bin/echo -e "\${LD_LIBRARY_PATH} not defined"
	/bin/echo 'setenv LD_LIBRARY_PATH `pwd`:${gtm_dbg}'

${GTM_DIST}:
	@/bin/echo "Please install GT.M from http://fis-gtm.com"
	@/bin/echo "These are the installed versions that you have"
	@ls /opt/gtm
	@exit 2

setup.py: setup.py.in
	sed -e 's,GTMDIST,${GTM_DIST},' -e 's,PYVER,${PYTHON_VER},' setup.py.in > setup.py

pyGTMx.so: setup.py
	python setup.py clean
	python setup.py build

pyGTMx.o: pyGTMx.c /usr/include/python${PYTHON_VER} ${GTM_DIST}
	${CC} -c ${CFLAGS} pyGTMx.c ${INCLUDES}

pyGTMx: pyGTMx.o
	${CC} pyGTMx.o -o pyGTMx ${LIBS}

install:
	python setup.py install

clean:
	rm -rf pyGTMx *.o build

distclean: clean
	rm -f setup.py

