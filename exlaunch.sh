#!/bin/bash

MAKE_ARGS="-j24 V=1"

# Perform user action.
if [ "$1" == "build" ]; then
    MAKE_VERB=""
elif [ "$1" == "clean" ]; then
    MAKE_VERB="clean"
elif [ "$1" == "deploy-sd" ]; then
    MAKE_VERB="deploy-sd"
elif [ "$1" == "deploy-ftp" ]; then
    MAKE_VERB="deploy-ftp"
elif [ "$1" == "deploy-ryu" ]; then
     MAKE_VERB="deploy-ryu"
elif [ "$1" == "make-npdm-json" ]; then
    MAKE_VERB="npdm-json"
else
    echo "Invalid arg. (build/clean/deploy-sd/deploy-ftp/deploy-ryu)"
    exit 1
fi

make $MAKE_ARGS $MAKE_VERB