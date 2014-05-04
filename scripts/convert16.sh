#!/bin/bash

N=1
Ninc=1
Nmax=100
FILEPREFIX=~/Downloads/cthead/cthead-8bit
FILESUFFIX=.tif.png

Nout=1
OUTPREFIX=cthead16_
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
        #
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
        N=`expr $N + ${Ninc}`
        #
        fullN $N
        FILENAME5=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME6=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME7=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME8=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        #
        fullN $N
        FILENAME9=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME10=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME11=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME12=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        #
        fullN $N
        FILENAME13=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME14=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME15=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`
        fullN $N
        FILENAME16=${FILEPREFIX}${Nstr}${FILESUFFIX}
        N=`expr $N + ${Ninc}`

        # output file
        fullN $Nout
        Nout=`expr $Nout + 1`
        OUTFILE=${OUTPREFIX}${Nstr}${OUTSUFFIX}

        echo inputs: ${FILENAME1} ${FILENAME2} ${FILENAME3} ${FILENAME4} \
        ${FILENAME5} ${FILENAME6} ${FILENAME7} ${FILENAME8} ${FILENAME9} \
        ${FILENAME10} ${FILENAME11} ${FILENAME12} ${FILENAME13} \
        ${FILENAME14} ${FILENAME15} ${FILENAME16}
        echo output: ${OUTFILE}
        ../vol2im -16i \
                ${FILENAME1} ${FILENAME2} ${FILENAME3} ${FILENAME4} \
                ${FILENAME5} ${FILENAME6} ${FILENAME7} ${FILENAME8} \
                ${FILENAME9} ${FILENAME10} ${FILENAME11} ${FILENAME12} \
                ${FILENAME13} ${FILENAME14} ${FILENAME15} ${FILENAME16} \
                -o ${OUTFILE}
        echo ok
done
