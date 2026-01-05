#include "templates.h"

// todo: finish assembly only


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

		}else if(arg == "-b" || arg == "--bios" || arg == "bios"){
			bios=true;

		}else if(arg == "-a" || arg == "--assembly" || arg == "assembly"){
			assembly=true;

		}else if(arg == "-s" || arg == "--silent" || arg == "silent" || arg == "-q" || arg == "--quiet" || arg == "quiet"){
			silent=true;

		}else if(arg == "-t" || arg == "--test" || arg == "test"){
			test=true;

		}else if(arg == "-p" || arg == "--purge" || arg == "purge"){
			purge=true;

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


	//compiles if it's not an assembly only project
	if (!assembly) {
		command = compiler;
		if(system(
			(string(command) + " "
			+ (main_path / "main.c -o ").string().c_str() +
			(build_path / "obj" / "main.asm").string().c_str()
			).c_str() ) !=0 ){
			cerr << "Exiting.\n";
		return 1;
			}if(!silent) clog << "[V] correctly compiled\n";
	}


	command = assembler;
	if(system(
		(string(command) + " "
		+ (assembly ? (main_path / "main.asm -o ") : (build_path / "obj" / "main.asm -o ")).string().c_str()
		+ (build_path / "obj" / "main.vbin").string().c_str()
		).c_str())!=0 ) {
		cerr << "Exiting.\n";
	return 1;
		}else if(!silent) clog << "[V] correctly assembled\n";


	command=packrom;
	if(system(
		(string(command) + " "
		+ (main_path / "romdef.xml -o ").string().c_str()
		+ (main_path / "main.v32").string().c_str()
		).c_str()
	)!=0){
		cerr << "Exiting.\n";
		return 1;
	}else{
		if(!silent) clog << "[V] correctly assembled\n";
		if(!silent) cout << "\n\n--------------------------------------\n" << "  ROM BUILT CORRECTLY!" << "\n--------------------------------------\n\n";

		if(test && !bios) quick_test( (main_path / "main.v32").string().c_str() );
		if(test &&  bios) cerr << "[W] Can't quick test bios files \ntest them as cartridges instead!\n";

		}

	return 0;

}



void create_project(fs::path main_path){

	cout << main_path.string()<<endl;
	if( !fs::exists(main_path) ) fs::create_directories(main_path);


	if( !fs::exists(main_path / "build" / "obj") ) fs::create_directories(main_path / "build" / "obj");


	if(!assembly){
		if( !fs::exists(main_path / "main.c" ) ){

			ofstream main_c;
			main_c.open((main_path / "main.c"));

			if(bios)	main_c << template_main_c_b;
			else 		main_c << template_main_c;


			main_c.close();
		}

	}else{
		if( !fs::exists(main_path / "main.asm" ) ){

			ofstream main_asm;
			main_asm.open((main_path / "main.asm"));

			if(bios)	main_asm << template_main_asm_b;
			else		main_asm << template_main_asm;

			main_asm.close();
		}


	}

	if( !fs::exists(main_path / "romdef.xml") ){

		ofstream romdef;
		romdef.open( (main_path / "romdef.xml") );


		if(bios)	romdef << template_romdef_xml_b;
		else		romdef << template_romdef_xml;

		romdef.close();
		}


	if(bios){

		if(!assembly){

			if(!fs::exists(main_path / "biosutils.h")){
				ofstream biosutils;

				biosutils.open( (main_path / "biosutils.h") );
				biosutils << template_biosutils_h;

				biosutils.close();
			}

		}


		if(!fs::exists(main_path / "texture.png")){
			ofstream texture;

			texture.open( (main_path / "texture.png"), std::ios::binary );
			texture.write(reinterpret_cast<const char*>(png_file), 90);

			texture.close();

		}


		if(!fs::exists(main_path / "sound.wav")){

			ofstream sound;

			sound.open( (main_path / "sound.wav"), std::ios::binary );
			sound.write(reinterpret_cast<const char*>(wav_file), 82);

			sound.close();

		}

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
