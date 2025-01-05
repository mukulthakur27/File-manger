#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void listFiles(const fs::path& path) {
    std::cout << "Listing files in: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << "\n";
    }
}

void createDirectory(const fs::path& path) {
    if (fs::create_directory(path)) {
        std::cout << "Directory created: " << path << "\n";
    } else {
        std::cerr << "Failed to create directory: " << path << "\n";
    }
}

void copyFile(const fs::path& source, const fs::path& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied from " << source << " to " << destination << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << "\n";
    }
}

void moveFile(const fs::path& source, const fs::path& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved from " << source << " to " << destination << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << "\n";
    }
}

void readFile(const fs::path& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return;
    }

    std::cout << "Contents of " << filePath << ":\n";
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
}

int main() {
    char choice;
    std::string path, source, destination;

    do {
        std::cout << "\nCommand-Line File Manager\n";
        std::cout << "1. List files in a directory\n";
        std::cout << "2. Create a directory\n";
        std::cout << "3. Copy a file\n";
        std::cout << "4. Move a file\n";
        std::cout << "5. View a file\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter directory path: ";
                std::cin >> path;
                listFiles(path);
                break;

            case '2':
                std::cout << "Enter directory path to create: ";
                std::cin >> path;
                createDirectory(path);
                break;

            case '3':
                std::cout << "Enter source file path: ";
                std::cin >> source;
                std::cout << "Enter destination path: ";
                std::cin >> destination;
                copyFile(source, destination);
                break;

            case '4':
                std::cout << "Enter source file path: ";
                std::cin >> source;
                std::cout << "Enter destination path: ";
                std::cin >> destination;
                moveFile(source, destination);
                break;

            case '5':
                std::cout << "Enter file path to view: ";
                std::cin >> path;
                readFile(path);
                break;

            case '6':
                std::cout << "Exiting file manager. Goodbye!\n";
                break;

            default:
                std::cerr << "Invalid choice. Please try again.\n";
        }

    } while (choice != '6');

    return 0;
}
