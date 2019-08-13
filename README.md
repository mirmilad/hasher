## Project
Hasher is a C/C++ cross-platform binary for android that receive a string as input, hashing it by using [libsodium](https://github.com/jedisct1/libsodium "libsodium") generic hash function, and show result as hex-string.

## UI Logic
Since this project is a binary, there is no UI. Use this command to run:
./hasher SOME_INPUT_TEXT

## Project Structure
This project using [Cmake](https://cmake.org/) as build system and  [make](https://linux.die.net/man/1/make) as make command.

## Testing
This project is using [Google Test](https://github.com/google/googletest) as a test framework to make sure every part works fine.

## Documentation, Run and Build Instructions
### Build Requirements
+ Ubuntu Environment
+ Android-NDK
+ Cmake (min version: 3.10.2)
+ build-essential package (gcc, g++, make)
+ Python

### How to build:
1. clone the project
2. open `build.sh` file and set the following variables:
	+ ANDROID_NDK_HOME
	+ ABI (values: x86, x86_64, armv7-a, armv8-a)
3. run `./build.sh`

It will run `cmake` command with android ndk toolchain and after that run `make` to build project. So, it downloads libsodium-1.0.17 source code, cross-compile it based on required ABI, complie project files, and finally makes two executable binary files named `hasher` and `unittest` in `dist` directory.

### How to run:
1. Copy `hasher` and `unittest` to and executable folder on android emulator like `/data/local/tmp`
2. Make both of files executable by running `chmod 777 hasher unittest`
3. First run `./unittest` to test everything and be sure the binary works fine
4. Now you are ready to use `hasher` and hash your strings with libsodium

Also you can use `deploy.sh` file to deploy and run test as another way.
