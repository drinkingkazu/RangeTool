#!/bin/bash

# clean up previously set env
me="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)"
`python $me/python/clean_env.py LD_LIBRARY_PATH`
`python $me/python/clean_env.py DYLD_LIBRARY_PATH`
`python $me/python/clean_env.py PYTHONPATH`
`python $me/python/clean_env.py PATH`

if [[ -z $FORCE_RANGETOOL_DIR ]]; then
    # If RANGETOOL_DIR not set, try to guess
    # Find the location of this script:
    me="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
    # Find the directory one above.
    export RANGETOOL_DIR="$( cd "$( dirname "$me" )" && pwd )"
else
    export RANGETOOL_DIR=$FORCE_RANGETOOL_DIR
fi
unset me;

echo "RANGETOOL_DIR = $RANGETOOL_DIR"
if [[ -z $RANGETOOL_DIR ]]; then
    echo \$RANGETOOL_DIR not set! 
    echo You have to set this first.
else 
    # Abort if ROOT not installed. Let's check rootcint for this.
    if [[ -z `command -v rootcint` ]]; then
	echo
	echo Looks like you do not have ROOT installed.
	echo You cannot use LArLite w/o ROOT!
	echo Aborting.
	echo
	return;
    fi
    RANGETOOL_OS=`uname -s`

    # Set path to sub directories
    export RANGETOOL_LIBDIR=$RANGETOOL_DIR/lib

    if [[ -z $USER_MODULE ]]; then
	export USER_MODULE=""
    fi

    # Check compiler availability for clang++ and g++
    RANGETOOL_CXX=clang++
    if [ `command -v $RANGETOOL_CXX` ]; then
	export RANGETOOL_CXX="clang++ -std=c++11";
    else
	RANGETOOL_CXX=g++
	if [[ -z `command -v $RANGETOOL_CXX` ]]; then
	    echo
	    echo Looks like you do not have neither clang or g++!
	    echo You need one of those to compile LArLite... Abort config...
	    echo
	    return;
	fi
	export RANGETOOL_CXX;
	if [ $RANGETOOL_OS = 'Darwin' ]; then
	    echo $RANGETOOL_OS
	    echo
	    echo "***************** COMPILER WARNING *******************"
	    echo "*                                                    *"
	    echo "* You are using g++ on Darwin to compile LArLite.    *"
	    echo "* Currently LArLite assumes you do not have C++11    *"
	    echo "* in this combination. Contact the author if this is *"
	    echo "* not the case. At this rate you have no ability to  *"
	    echo "* compile packages using C++11 in LArLite.           *"
	    echo "*                                                    *"
	    echo "* Help to install clang? See manual/contact author!  *"
	    echo "*                                                    *"
	    echo "******************************************************"
	    echo 
	fi
    fi
    if [[ -z $ROOTSYS ]]; then
	case `uname -n` in
	    (houston.nevis.columbia.edu)
	    if [[ -z ${ROOTSYS} ]]; then
		source /usr/nevis/adm/nevis-init.sh
		setup root
		export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH;
	    fi
	    ;;
	    (*)
	    echo
	    echo "****************** PyROOT WARNING ********************"
	    echo "*                                                    *"
	    echo "* Did not find your \$ROOTSYS. To use PyROOT feature, *"
	    echo "* Make sure ROOT.py is installed (comes with ROOT).  *"
	    echo "* You need to export \$PYTHONPATH to include the dir  *"
	    echo "* where ROOT.py exists.                              *"
	    echo "*                                                    *"
	    echo "* Help to install PyROOT? See manual/contact author! *"
	    echo "*                                                    *"
	    echo "******************************************************"
	    echo
	    ;;
	esac
    else
	export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH;
    fi

    export LD_LIBRARY_PATH=$RANGETOOL_LIBDIR:$LD_LIBRARY_PATH
    export PYTHONPATH=$RANGETOOL_DIR:$PYTHONPATH
    if [ $RANGETOOL_OS = 'Darwin' ]; then
	export DYLD_LIBRARY_PATH=$RANGETOOL_LIBDIR:$DYLD_LIBRARY_PATH
    fi
    export PATH=$RANGETOOL_DIR/bin:$PATH
    echo
    echo "Finish configuration. To build, type:"
    echo "> cd \$RANGETOOL_DIR"
    echo "> make"
    echo
fi
