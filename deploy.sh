#!/bin/sh
export ANDROID_ABI=x86
adb push dist/$ANDROID_ABI/unittest /data/local/tmp/hasher
adb push dist/$ANDROID_ABI/hasher /data/local/tmp/hasher

adb shell chmod 777 /data/local/tmp/hasher/unittest
adb shell chmod 777 /data/local/tmp/hasher/hasher

adb shell ./data/local/tmp/hasher/unittest

