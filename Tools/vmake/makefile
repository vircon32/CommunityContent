ifeq ($(OS),Windows_NT)
    HOST_OS := Windows
else
    HOST_OS := $(shell uname -s)
endif

TARGET ?= $(HOST_OS)


	ifeq ($(HOST_OS), Linux)
		GPP= g++ --std=c++17
		OUT = ./bin/vmake
		MKDIR=mkdir -p

		ifeq ($(TARGET), Windows)
			GPP= x86_64-w64-mingw32-g++ --std=c++17

		endif


	endif

ifeq ($(HOST_OS), Windows)
	GPP= g++ --std=c++17
	MKDIR = if not exist bin mkdir
	OUT = .\bin\vmake.exe


endif





ARGS= -Wall --static -o $(OUT)

.PHONY: make test test-cb test-b clean

make:
	$(MKDIR) bin
	$(GPP) main.cpp $(ARGS)

test: make
	$(OUT)




