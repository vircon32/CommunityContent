#this makefile is designed to be used in a GNU/linux system, if you are using windows replace the variables and use make for windows https://gnuwin32.sourceforge.net/packages/make.htm


emulator =	/opt/Vircon32/Emulator/Vircon32
vcc =		/usr/local/DevTools/compile
asm =		/usr/local/DevTools/assemble
pack =		/usr/local/DevTools/packrom
p2v =		/usr/local/DevTools/png2vircon
w2v =		/usr/local/DevTools/wav2vircon


PNG_FILES := $(wildcard ./assets/sprites/*.png)
WAV_FILES := $(wildcard ./assets/sound/*.wav)








.PHONY: vtex
vtex: $(PNG_FILES)
	@for file in $(PNG_FILES); do \
		OUT_FILE="./build/a/$$(basename $$file .png).vtex"; \
		$(p2v) $$file -o $$OUT_FILE; \
	done

.PHONY: vsnd
vsnd: $(WAV_FILES)
	@for file in $(WAV_FILES); do \
		OUT_FILE="./build/a/$$(basename $$file .wav).vsnd"; \
		$(w2v) $$file -o $$OUT_FILE; \
	done


bin:
	$(vcc) ./main.c -o ./build/bin/main.asm
	@echo ================ compiled ===============
	$(asm) ./build/bin/main.asm -o ./build/bin/main.vbin
	@echo ================ assembled ==============
	$(pack) ./romdef.xml -o ./build/rom.v32
	@echo ================= packed ================

all:
	@echo compiling everything
	
	make vtex
	make vsnd
	
	@echo assets compiled
	
	make bin
	@echo binaries compiled and packed



test: all
	@echo testing rom
	$(emulator) ./build/rom.v32
