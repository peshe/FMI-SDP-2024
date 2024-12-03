#include <iostream>
#include "Directory.hpp"
#include "TextFile.hpp"
#include "FileSystem.hpp"

int main() {
    fs::FileSystem fs;
    std::cout << "Initial:\n";
    fs.print();

    fs.addItem("/dirA", fs::DIRECTORY, 0, false);
    fs.addItem("/dirA/dirB/dirC", fs::DIRECTORY, 0, true);
    fs.addItem("/dirA/dirB/fileOne.txt", fs::TEXT_FILE, 100);
    fs.addItem("/dirA/dirB/fileTwo.txt", fs::TEXT_FILE, 100);
    fs.addItem("/dirD/dirE/test6", fs::DIRECTORY, 0, true);
    fs.addItem("/dirD/dirE/test7", fs::DIRECTORY, 0, true);
    fs.addItem("/dirD/dirE/test8", fs::DIRECTORY, 0, true);
    fs.addItem("/dirD/dirE/test7/meow", fs::TEXT_FILE, 214);
    std::cout << "After adding stuff:\n";
    fs.printWithSize();

    fs.removeItem("/dirA/dirB/fileOne.txt");
    std::cout << "----------------------" << std::endl;
    std::cout << "After first remove:\n";
    fs.print();

    fs.removeItem("/dirD/dirE", true);
    std::cout << "----------------------" << std::endl;
    std::cout << "After second remove:\n";
    fs.print();
    return 0;
}