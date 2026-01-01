ifeq ($(OS),Windows_NT)
    HOST_OS := Windows
else
    HOST_OS := $(shell uname -s)
endif

TARGET ?= $(HOST_OS)


	ifeq ($(HOST_OS), Linux)
		GPP= g++ --std=c++17
		RM = rm -f
		RMDIR = rm -rf
		MKDIR = mkdir -p
# 		CP = cp -rf
		OUT = ./bin/vmake

		ifeq ($(TARGET), Windows)
			GPP= x86_64-w64-mingw32-g++ --std=c++17

		endif


	endif

ifeq ($(HOST_OS), Windows)
	GPP= g++ --std=c++17
	RMDIR = rmdir /S /Q
	MKDIR = if not exist bin mkdir
	CP = xcopy /E /I /Y
	OUT = .\bin\vmake.exe


endif





ARGS= -Wall --static -o $(OUT)

.PHONY: make test test-t test-c test-h

make:
	$(MKDIR) bin
	$(GPP) main.cpp $(ARGS)

test: make
	$(OUT) -v ./example

test-t:make
	$(OUT) -v ./example -t

test-c:make
	$(OUT) -v ./newgame -c

test-h:make
	$(OUT) -v -h
