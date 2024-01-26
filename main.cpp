// Include the necessary libraries
#include <iostream>
#include <cstring>
// Include the header file for the compression functions
#include "utils/compresser.h"

// Function to print the help message
void printHelp() {
    std::cout << "Usage: \n";
    std::cout << "  ./BinaryCompresser --file-to-binary <input_file_path> <output_binary_path> [key]\n";
    std::cout << "  ./BinaryCompresser --binary-to-file <input_binary_path> <output_file_path> [key]\n";
    std::cout << "Options: \n";
    std::cout << "  --help\t\tShow this help message\n";
}

// Main function
int main(int argc, char** argv) {
    // If the user didn't provide enough arguments or asked for help, print the help message
    if(argc < 3 || strcmp(argv[1], "--help") == 0) {
        printHelp();
        return 0;
    }

    // If the user wants to convert a file to a binary string
    if(strcmp(argv[1], "--file-to-binary") == 0 && argc >= 4) {
        // If the user provided a key, use it. Otherwise, use nullptr.
        const char* key = (argc >= 5) ? argv[4] : nullptr;
        // Call the file_to_binary_string function with the provided arguments
        file_to_binary_string(argv[2], argv[3], key);
    } 
    // If the user wants to convert a binary string to a file
    else if(strcmp(argv[1], "--binary-to-file") == 0 && argc >= 4) {
        // If the user provided a key, use it. Otherwise, use nullptr.
        const char* key = (argc >= 5) ? argv[4] : nullptr;
        // Call the binary_string_to_file function with the provided arguments
        binary_string_to_file(argv[2], argv[3], key);
    } 
    // If the user provided an invalid command, print the help message
    else {
        printHelp();
    }

    return 0;
}
