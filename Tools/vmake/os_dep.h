
#ifdef _WIN32
    
	#define vtex "png2vircon"
	#define vsnd "wav2vircon"
	#define vmap "tiled2vircon"
	#define compiler "compile"
	#define assembler "assemble"
	#define packrom "packrom"

	void quick_test(std::string com){
		std::cout << "\nQuick test is limited on Microsoft Windows, opening file.\n";
		system(com.c_str());
	}

#elif __unix__

	#define vtex "/usr/local/Vircon32/DevTools/png2vircon"
	#define vsnd "/usr/local/Vircon32/DevTools/wav2vircon"
	#define vmap "/usr/local/Vircon32/DevTools/tiled2vircon"
	#define compiler "/usr/local/Vircon32/DevTools/compile"
	#define assembler "/usr/local/Vircon32/DevTools/assemble"
	#define packrom "/usr/local/Vircon32/DevTools/packrom"

	void quick_test(std::string com){
		system((std::string("/usr/local/Vircon32/Emulator/Vircon32 ") + com).c_str());

	}
#endif
