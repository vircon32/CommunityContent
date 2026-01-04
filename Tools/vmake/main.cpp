#define ver "1.2"

#include <cctype>
#include <cstdlib>

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>



#include "os_dep.h"


using namespace std;
namespace fs = filesystem;

bool verbose, create, test, help, version, silent, license, purge, bios; // set up all arguments

#include "func.h"


int main(int argc, char* argv[]) {

	set_arguments(argc, argv);

	// If there's no path argument, set current path to work
	std::string path = "./";
	//--------------------------------------
	// Check if any argument is a directory
	//--------------------------------------

	for(int i = 1; i < argc; i++){
		std::string arg = argv[i];
		if(arg.find('/') != std::string::npos || arg.find('\\') != std::string::npos) {

			if(fs::exists(arg) || create) path = argv[i];
			else{
				cerr << "[E] Coudn't find directory " << argv[i] << endl;
				return 1;
			}

		}
	}


	fs::path main_path(path);
	fs::path build_path = main_path / "build";

	if(help) cout << help_info;

	else if(version) cout << ver << "\n";

	else if(license) cout << license_info << "\n";

	else if(purge) purge_build_files(main_path, build_path);

	else if(create){

		create_project(main_path);
		if(!silent) std::cout << "Working directory: " << path << std::endl;


	}else{

		if(!silent) std::cout << "Working directory: " << path << std::endl;
		string command;

		if( !fs::exists(build_path) ) fs::create_directories(build_path);
		if( !fs::exists(build_path / "obj") ) fs::create_directories(build_path / "obj");

		if(!silent) cout << "\n\n--------------------------------------\n" << "  BEGIN FILE CONVERTION PROCESS" << "\n--------------------------------------\n";

		for(const auto &entry : fs::recursive_directory_iterator(main_path, fs::directory_options::follow_directory_symlink)) {

			//----------------------------------------------------------
			// Replicates assets directory structure in build directory
			//----------------------------------------------------------

			fs::path relative = fs::relative(entry.path(), main_path);
    			
			if (relative.string().rfind("build", 0) == 0) {
    		    continue;  //continues if not in build
    		}
			
			if (fs::is_directory(entry) ) {

				if(!fs::exists(build_path / relative)){
					if(!silent) clog << "[+] " << relative << "\n";

					fs::create_directories(build_path / relative);
					if(verbose && !silent) clog << "[P] made path: " + (build_path / relative).string() + "\n\n";
				}



			} else if (fs::is_regular_file(entry)) {

				//----------------------------------------------------------
				// Process files individually based on their extension
				//----------------------------------------------------------

				fs::path file= entry.path().filename().stem();
				string ext= entry.path().filename().extension().string();
				string simple_path=entry.path().string();

				string out_ext;
				fs::path output_file; //will be setted up later
				fs::path relative = fs::relative(entry.path(), main_path);



				for (char& c : ext) {													// turn extension to lowercase,
					c = static_cast<char>(tolower(static_cast<unsigned char>(c)));		// removes case sensitivity
				}

				if(!silent) clog << "[-] size:" << (entry.file_size()/1024.0) << "KB > " << file.string() << ext << "\n";



				if(ext==".png"){
					command = vtex;
					out_ext=".vtex";

				}else if(ext==".wav"){
					command = vsnd;
					out_ext=".vsnd";

				}else if(ext==".tmx"){
					command = vmap;
					out_ext=".vmap";
				}else{
					command = "";
					out_ext="";
				}

				 if(!command.empty()){ output_file= (build_path/relative).replace_extension(out_ext);


					 if( are_sources_older(output_file, (main_path/relative)) ) {

						string shell = command + " '" + simple_path + "' -o '" +
						(build_path/relative).replace_extension(out_ext).string() + "'";

						system(shell.c_str());
						if(verbose && !silent) clog << "[C]" << shell << "\n\n";

					} else if(verbose && !silent) {
						clog << "[W]    Source hasn't changed, skipping.\n\n";
					}


				 }else if(verbose && !silent) clog << "[W]    Unrecognized format, ignoring.\n\n";
		}

	}


		//--------------------------------------------------------
		// run requiered commands to finally create the final ROM
		//--------------------------------------------------------

		if(!silent) cout << "\n\n--------------------------------------\n" << "  BEGIN BUILDING PROCESS" << "\n--------------------------------------\n\n";

		build_rom(main_path, build_path);

	return 0;


	}

}
