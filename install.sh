#!/usr/local/bin/bash

HEADER_PREFIX=/usr/include
LIB_PREFIX=/usr/lib
CTF_DIR=ctf

mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/api
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/file
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/type
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/io
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/io/read
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/label
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/object
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/object/function
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/object/data
mkdir -vp ${HEADER_PREFIX}/${CTF_DIR}/util

for header in `find src/ -name '*.h'`
do
	relative=${header/src\//}
	cp -v src/${relative} ${HEADER_PREFIX}/${CTF_DIR}/${relative}
done

cp -v bin/libbsdctf.so ${LIB_PREFIX} 
