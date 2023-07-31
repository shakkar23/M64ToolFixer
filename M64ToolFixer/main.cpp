// SDL2playground.cpp : Defines the entry point for the application.
//

#include "main.hpp"
#include <span>
#include <iostream>
#include <filesystem>


int main(int argc, char** args)
{
    // make sure the argc is 4
    if (argc != 4) {
		std::cout << "Usage: " << args[0] << " <mtl or bmp> <input_dir> <output_dir>\n";
		return 1;
	}

    std::string extension = args[1];

    if (extension != "mtl" && extension != "bmp") {
        std::cout << "Usage: " << args[0] << " <mtl or bmp> <input_dir> <output_dir>\n";
		return 1;
    }

    std::string input_dir = args[2];

    if (!std::filesystem::exists(input_dir)) {
		std::cout << "Input directory does not exist\n";
		return 1;
	}

    std::string output_dir = args[3];

    if (!std::filesystem::exists(output_dir)) {
        std::cout << "Output directory does not exist\n";
    }

    auto fixer = extension == "mtl" ? fix_mtl : fix_file;
    // prepend a . to the extension
    extension.insert(0, ".");

    // get every folder in the directory
    std::vector<std::string> folders;

    for (const auto& entry : std::filesystem::directory_iterator(input_dir)) {
        if (entry.is_directory()) {
            folders.push_back(entry.path().string());
        }
    }

    // for each folder
    for (auto& folder : folders) {
        // get every file in the folder
        std::vector<std::string> files;
        for (const auto& entry : std::filesystem::directory_iterator(folder)) {
            if (entry.is_regular_file()) {
                // if the file is a bmp
                if (entry.path().extension() == extension) {
                    files.push_back(entry.path().string());
                }
            }
        }
    
        // for each file
        for (auto& file : files) {
            // fix the file
            fixer(file);
        }
    }

    return 0;
}