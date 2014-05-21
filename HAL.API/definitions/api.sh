#!/bin/bash
RELATIVE_PATH="HAL/API"
INCLUDE_PATH="../include/HAL/API"
SRC_PATH="../src"
DOC_PATH="../doc"
JS_PATH="../js"

./../../TBS.Services/TBS.Services.Generator.lin/TBS.Services.Generator --def=movement.xml --name=Movement --src=$SRC_PATH/ --include=$INCLUDE_PATH/ --relative=$RELATIVE_PATH/ --generate=dbus

./../../TBS.Services/TBS.Services.Generator.lin/TBS.Services.Generator --def=remote.xml --name=Remote --src=$SRC_PATH/ --include=$INCLUDE_PATH/ --relative=$RELATIVE_PATH/ --javascript=$JS_PATH/ --generate=json
