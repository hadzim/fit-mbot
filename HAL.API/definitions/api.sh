#!/bin/bash
RELATIVE_PATH="TSeries/Services"
INCLUDE_PATH="../include/TSeries/Services"
SRC_PATH="../src"
DOC_PATH="../doc"
JS_PATH="../js"

./../../TBS.Services/TBS.Services.Generator.lin/TBS.Services.Generator --def=movement.xml --name=Movement --src=$SRC_PATH/ --include=$INCLUDE_PATH/ --relative=$RELATIVE_PATH/ --generate=dbus
