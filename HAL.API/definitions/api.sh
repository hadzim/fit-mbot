#!/bin/bash
RELATIVE_PATH="HAL/API"
INCLUDE_PATH="../include/HAL/API"
SRC_PATH="../src"
DOC_PATH="../doc"
JS_PATH="../js"

./../../TBS.Services/TBS.Services.Generator.lin/TBS.Services.Generator --def=movement.xml --name=Movement --src=$SRC_PATH/ --include=$INCLUDE_PATH/ --relative=$RELATIVE_PATH/ --javascript=../js --generate=json
./../../TBS.Services/TBS.Services.Generator.lin/TBS.Services.Generator --def=bioradar.xml --name=BioRadar --src=$SRC_PATH/ --include=$INCLUDE_PATH/ --relative=$RELATIVE_PATH/ --javascript=../js --generate=json
./../../TBS.Services/TBS.Services.Generator.lin/TBS.Services.Generator --def=camera.xml   --name=Camera   --src=$SRC_PATH/ --include=$INCLUDE_PATH/ --relative=$RELATIVE_PATH/ --javascript=../js --generate=json

