#!/bin/bash

N=1
Ninc=4
Nmax=100
FILEPREFIX=~/Downloads/cthead/cthead-8bit
FILESUFFIX=.tif.png

Nout=1
OUTPREFIX=cthead4_
OUTSUFFIX=.png

fullN () {
        if [ $1 -lt 10 ]; then
                Nstr=00$1
        elif [ $1 -lt 100 ]; then
                Nstr=0$1
        else
                Nstr=$1
        fi
}

while [ $N -lt ${Nmax} ]; do
        fullN $N
        FILENAME1=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME2=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME3=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME4=${FILEPREFIX}${Nstr}${FILESUFFIX}
        fullN $Nout
        OUTFILE=${OUTPREFIX}${Nstr}${OUTSUFFIX}
        echo inputs: ${FILENAME1} ${FILENAME2} ${FILENAME3} ${FILENAME4}
        echo output: ${OUTFILE}
        ../vol2im -4i ${FILENAME1} ${FILENAME2} ${FILENAME3} ${FILENAME4} -o ${OUTFILE}
        echo ok
        N=`expr $N + ${Ninc}`
        Nout=`expr $Nout + 1`
done
