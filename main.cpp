#include <iostream>
#include <filesystem>
#include <vector>


// Print the current working directory
void working_dir(std::filesystem::path workingDir) {
    std::cout << workingDir.string();
}

// Change the working directory to the path given



// Prin the names of each file or directory in the current working directory



// Quits the program
void quit() {
    std::cout << "Exiting..." << std::endl;
    exit(0);
}

int main() {

    std::cout << "Welcome to ElbeeShell" << "\n\n";

    std::vector<std::filesystem::path> directory_paths;
    std::vector<std::filesystem::path> file_paths;

    namespace fs = std::filesystem;
    fs::path workingDir = "/";
    while (true) {

        // Print the current working directory, followed by a space, then a dollar sign, then another space.
        working_dir(workingDir);
        std::cout << " $ ";

        // Read a line of input using std::getline.
        std::string input;
        std::cin >> input;
        std::getline(std::cin, input);

        if (input == "workingdir") {
            std::cout << "Working directory: " << workingDir.string() << "\n";
        }



        // Execute the requested operation.


        // Print a blank line.

        // Exits the shell
        if (input == "exit") {
            quit();
        }
    }
    return 0;
}