#!/bin/sh

set cwd=`pwd`
gtmgbldir=${cwd}/pygtm.gld
export gtmgbldir
$gtm_exe/mumps -run GDE <<GTM
change -segment DEFAULT -block=4096 -alloc=75000 -ext=2000 -glob=2048 -file=${cwd}/pygtm.dat
change -region DEFAULT -rec=4080 -key=255 -std
exit
GTM

$gtm_exe/mupip create

echo "To use this DB you should"
echo "sh/bash/ksh"
echo "gtmgbldir=`pwd`/pygtm.gld; export gtmgbldir"
echo "tcsh/csh:"
echo "setenv gtmgbldir `pwd`pygtm.gld"
