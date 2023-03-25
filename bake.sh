#!/bin/bash

COMPILER="g++"
SOURCE_FOLDER="src"
BUILD_FOLDER="build"
PROJECT_NAME="gl"

mkdir -p $BUILD_FOLDER
$COMPILER -c $SOURCE_FOLDER/Main.cpp
$COMPILER *.o -o $BUILD_FOLDER/$PROJECT_NAME
rm *.o