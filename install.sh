#!/usr/local/bin/bash

HEADER_PREFIX=/usr/include
LIB_PREFIX=/usr/lib

mkdir -vp ${HEADER_PREFIX}/libctf
mkdir -vp ${HEADER_PREFIX}/libctf/api
mkdir -vp ${HEADER_PREFIX}/libctf/file
mkdir -vp ${HEADER_PREFIX}/libctf/type
mkdir -vp ${HEADER_PREFIX}/libctf/io
mkdir -vp ${HEADER_PREFIX}/libctf/io/read
mkdir -vp ${HEADER_PREFIX}/libctf/label
mkdir -vp ${HEADER_PREFIX}/libctf/object
mkdir -vp ${HEADER_PREFIX}/libctf/object/function
mkdir -vp ${HEADER_PREFIX}/libctf/object/data
mkdir -vp ${HEADER_PREFIX}/libctf/util


for header in `find src/ -name '*.h'`
do
	relative=${header/src\//}
	cp -v src/${relative} ${HEADER_PREFIX}/libctf/${relative}
done

cp -v bin/libbsdctf.so ${LIB_PREFIX} 
