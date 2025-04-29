#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem; // Alias for std::filesystem

// cd command behavior
fs::path change_directory(const fs::path& currentDir, const std::string& path) {
    fs::path newPath;

    if (path[0] == '/') {
        newPath = path; // Absolute path
    }
    else {
        newPath = currentDir / path;    // Relative path
    }

    if (fs::exists(newPath)) {
        return fs::canonical(newPath);  // Resolves ".." references
    }
    else {
        std::cout << "Path does not exist" << std::endl;
        return currentDir;
    }
}

// Lists contents of the current directory
void list_directory(const fs::path& currentDir) {
    // Separate vectors for directories and files
    std::vector<fs::path> directories;
    std::vector<fs::path> files;

    for (const auto& entry : fs::directory_iterator(currentDir)) {
        if (entry.is_directory()) {
            directories.push_back(entry.path());
        }
        else {
            files.push_back(entry.path());
        }
    }

    // Sort both vectors
    std::sort(directories.begin(), directories.end());
    std::sort(files.begin(), files.end());

    // Print directories first
    for (const auto& dir : directories) {
        std::cout << dir.filename().string() << " (Directory)" << std::endl;
    }

    // Print files second
    for (const auto& file : files) {
        std::cout << file.filename().string() << std::endl;
    }
}

// Print the current working directory prompt
void workDir(const fs::path& workingDir) {
    std::cout << workingDir.string() << " $ ";
}

// Quits the program
void quit() {
    exit(0);
}

int main() {
    std::cout << "Welcome to ElbeeShell" << "\n\n";
    fs::path workingDir = "/";

    while (true) {
        // Print the prompt
        workDir(workingDir);

        // Read input
        std::string input;
        std::getline(std::cin, input);


        // Parse command and argument
        std::string command;    // Stores the command (e.g. "cd" "list")
        std::string argument;   // Stores arguments after the command
        size_t space = input.find(' ');
        if (space != std::string::npos) {
            command = input.substr(0, space);
            argument = input.substr(space + 1);
        }
        else {
            command = input;
            argument = "";
        }

        // Process commands
        if (command == "workdir") {
            std::cout << "Working directory: " << workingDir.string() << std::endl;
        }
        else if (command == "cd") {
            workingDir = change_directory(workingDir, argument);
        }
        else if (command == "list") {
            list_directory(workingDir);
        }
        else if (command == "exit") {
            quit();
        }
        else {
            std::cout << "Unknown command" << std::endl;
        }

        // Print blank line after each command
        std::cout << std::endl;
    }
    return 0;
}