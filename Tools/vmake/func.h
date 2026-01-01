string help_info = "\nVmake: simple build system for Vircon32 games\n\
  Usage: Vmake [command] [directory]\n\n\
  Commands:\n\
    -v --verbose Displays extra information.\n\
    -c --create  Creates all files and folders needed to\n\
                 work with Vmake.\n\
    -t --test    Opens the rom with the vircon32 emulator.\n\
    -h --help    Shows this message.\n\
    --version    Displays current version\n\
";



bool are_sources_older(fs:: path output_file, fs::path source){
	return (!fs::exists(output_file) || fs::last_write_time(source.string()) > fs::last_write_time(output_file.string() ) );
}


void set_arguments(int argc, char* argv[]){

	for(int i = 1; i < argc; i++){
		std::string arg = argv[i];

		if(arg == "-v" || arg == "--verbose" || arg == "verbose"){
				verbose=true;

		}else if(arg == "-c" || arg == "--create" || arg == "create"){
				create=true;

		}else if(arg == "-t" || arg == "--test" || arg == "test"){
				test=true;

		}else if(arg == "-h" || arg == "--help" || arg == "help"){
				help=true;

		}else if(arg == "--version" || arg == "version"){
			version=true;
		}

	}
}


int build_rom(fs::path main_path, fs::path build_path){

	string command;
	fs::create_directories(build_path / "obj");
	cout << "[P] made path: " + (build_path / "obj").string() << "\n\n";



	cout << "compiling ROM...\n";
	command=compiler;
	if(system(
		(string(command) + " "
		+ (main_path / "main.c -o ").string().c_str() +
		(build_path / "obj" / "main.asm").string().c_str()
		).c_str() ) !=0 ){

		cerr << "Exiting.\n";
		return 1;



	}else{
		cout << "assembling ROM...\n";
		command=assembler;
		if(system(
			(string(command) + " "
			+ (build_path / "obj" / "main.asm -o ").string().c_str()
			+ (build_path / "obj" / "main.vbin").string().c_str()
			).c_str())!=0 ) {

			cerr << "Exiting.\n";
			return 1;



		}else{
		cout << "packing final ROM...\n";
		command=packrom;

		if(system(
			(string(command) + " "
			+ (main_path / "romdef.xml -o ").string().c_str()
			+ (main_path / "main.v32").string().c_str()
			).c_str()
			)!=0){

			cerr << "Exiting.\n";
			return 1;

		}

		cout << "\n\n--------------------------------------\n" << "  ROM BUILT!" << "\n--------------------------------------\n\n";

		if(test)quick_test( (main_path / "main.v32").string().c_str() );

		}

	}

	return 0;
}


void create_project(fs::path main_path){

	cout << main_path.string()<<endl;
	if( !fs::exists(main_path) ) fs::create_directories(main_path);


	if( !fs::exists(main_path / "build" / "obj") ) fs::create_directories(main_path / "build" / "obj");


	if( !fs::exists(main_path / "main.c" ) ){

		ofstream main_c;
		main_c.open((main_path / "main.c"));

		main_c << "// #include \"video.h\""		<< "\n";
		main_c << "// #include \"audio.h\"" 	<< "\n";
		main_c << "// #include \"input.h\""		<< "\n";
		main_c << "// #include \"math.h\""		<< "\n";
		main_c << "// #include \"string.h\""	<< "\n";
		main_c << "// #include \"time.h\"" 		<< "\n";
		main_c << "// #include \"memcard.h\"" 	<< "\n";
		main_c << "// #include \"misc.h\""		<< "\n\n\n";
		main_c << "void main(void){"			<< "\n\n";
		main_c << "	/* Your code goes here! */"	<< "\n\n";
		main_c << "}";
	}

	if( !fs::exists(main_path / "romdef.xml") ){

		ofstream romdef;
		romdef.open( (main_path / "romdef.xml") );

		romdef << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" 	<< "\n";
		romdef << "<rom-definition version=\"1.0\">" 								<< "\n";
		romdef << "	<rom type=\"cartridge\" title=\"Game\" version=\"1.0\" />" 		<< "\n";
		romdef << "	<binary path= \"./build/obj/main.vbin\" />" 					<< "\n\n\n";
		romdef << "	<textures>" 													<< "\n";
		romdef << "		<!--texture path=\"build/texture.vtex\"/-->" 				<< "\n\n";
		romdef << "	</textures>" 													<< "\n\n";
		romdef << "	<sounds>" 														<< "\n";
		romdef << "		<!--sound path=\"build/sound.vsnd\"/-->" 					<< "\n\n";
		romdef << "	</sounds>" 														<< "\n\n\n";
		romdef << "</rom-definition>" 												<< "\n";

	}

}

