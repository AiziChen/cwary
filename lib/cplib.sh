#!/bin/sh
# 1. copy `libhttp.h` header
cp /Users/coq/CLionProjects/http_lib/libhttp.h ./web
# 2. copy `libhttp.dylib" dynamic library
cp /Users/coq/CLionProjects/http_lib/target/release/libhttp.dylib ./web

# 4: copy `libcmysql-ffi.dylib` dylib
cp /Users/coq/CLionProjects/test-c/libcmysql-ffi.dylib ./mysql
cp /Users/coq/CLionProjects/test-c/libcmysql-ffi.h ./mysql
