string help_info = R"(Vmake: simple build system for Vircon32 games


  Usage: Vmake [command] [directory]
  Commands:
    -v --verbose  Displays extra information.
    -c --create   Creates all files and folders needed to
                  work with Vmake.
    -t --test     Opens the rom with the vircon32 emulator.
    -s --silent   Hides all logs except error messages.
    -p --purge    Removes all cached building resources.
    -V --version  Shows current version
    -l --license  Shows licensing details
    -h --help     Shows this message.
)";

string license_info = R"(

MIT License

Copyright (c) 2026 Palta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
)";



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

		}else if(arg == "-s" || arg == "--silent" || arg == "silent" || arg == "-q" || arg == "--quiet" || arg == "quiet"){
			silent=true;

		}else if(arg == "-p" || arg == "--purge" || arg == "purge"){
			purge=true;

		}else if(arg == "-t" || arg == "--test" || arg == "test"){
			test=true;

		}else if(arg == "-V" || arg == "--version" || arg == "version"){
			version=true;

		}else if(arg == "-l" || arg == "--license" || arg == "license"){
			license=true;

		}else if(arg == "-h" || arg == "--help" || arg == "help"){
			help=true;

		}
	}
}


int build_rom(fs::path main_path, fs::path build_path){

	string command;
	fs::create_directories(build_path / "obj");
	if(!silent) clog << "[P] made path: " + (build_path / "obj").string() << "\n\n";


	if(!silent) cout << "compiling ROM...\n";
	command=compiler;
	if(system(
		(string(command) + " "
		+ (main_path / "main.c -o ").string().c_str() +
		(build_path / "obj" / "main.asm").string().c_str()
		).c_str() ) !=0 ){

		cerr << "Exiting.\n";
		return 1;



	}else{

		if(!silent) cout << "assembling ROM...\n";
		command=assembler;
		if(system(
			(string(command) + " "
			+ (build_path / "obj" / "main.asm -o ").string().c_str()
			+ (build_path / "obj" / "main.vbin").string().c_str()
			).c_str())!=0 ) {

			cerr << "Exiting.\n";
			return 1;



		}else{

		if(!silent) cout << "packing final ROM...\n";
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

		if(!silent) cout << "\n\n--------------------------------------\n" << "  ROM BUILT!" << "\n--------------------------------------\n\n";

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

void purge_build_files(fs::path main_path, fs::path build_path){

	if(fs::exists(main_path /"romdef.xml")){

		if (fs::exists(build_path)){
			fs::remove_all(build_path);
			if(!silent) clog << "[P] Deleted build folder\n";
		}

		if(fs::exists(main_path / "main.v32")){
			fs::remove(main_path / "main.v32");
			if(!silent) clog << "[P] Deleted main.v32 file\nBuild files have been purged.\n";
		}


	}

}
