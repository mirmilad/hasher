#!/bin/sh
export ANDROID_NDK_HOME=/home/milad/Android/ndk/android-ndk-r18b
export ABI=x86
###export MINSDKVERSION=16
cmake \
    	-DCMAKE_MAKE_PROGRAM=make \
	-DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
    	-DANDROID_ABI=$ABI \
	-DANDROID_NATIVE_API_LEVEL=$MINSDKVERSION \
   . 
make

