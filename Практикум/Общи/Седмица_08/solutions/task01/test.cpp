#include <exception>
#include <iostream>

#include "FileSystem.h"


void testAdd(FileSystem& fileSystem) {
    fileSystem.add("/a/b/c.txt", /*isDirectory=*/false, /*createAlongPath=*/true);
    fileSystem.add("/etc/sshd", /*isDirectory=*/true, /*createAlongPath=*/true);

    try {
        fileSystem.add(
            "/home/stoyan/Documents/test.txt", /*isDirectory=*/false, /*createAlongPath=*/false
        );
    } catch (std::exception& e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    try {
        fileSystem.add("/etc/sshd", /*isDirectory=*/true, /*createAlongPath=*/true);
    } catch (std::exception& e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    try {
        fileSystem.add("/a/b/c.txt/test.txt", /*isDirectory=*/false, /*createAlongPath=*/true);
    } catch (std::exception& e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    fileSystem.add("/Общи/Седмица_02/README.md", /*isDirectory=*/false, /*createAlongPath=*/true);
    fileSystem.add(
        "/Общи/Седмица_02/solutions/task_01/DynArrayBool.inl",
        /*isDirectory=*/false,
        /*createAlongPath=*/true
    );
    fileSystem.add("/Общи/Седмица_02/solutions/task_01/README.md", /*isDirectory=*/false);
    fileSystem.add("/Общи/Седмица_02/solutions/task_01/test.cpp", /*isDirectory=*/false);

    fileSystem.print(/*showSize=*/true);
}

void testRemove(FileSystem& fileSystem) {
    try {
        fileSystem.remove("/home/stoyan/Documents/test.txt");
    } catch (std::exception& e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    try {
        fileSystem.remove("/a/b/c.txt/test.txt");
    } catch (std::exception& e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    try {
        fileSystem.remove("/Общи/Седмица_02/solutions");
    } catch (std::exception& e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    try {
        fileSystem.remove("/Общи/Седмица_02/solutions/task_01/haha");
    } catch (std::exception& e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    fileSystem.remove("/a/b/c.txt");
    fileSystem.remove("/etc/sshd");
    fileSystem.remove("/Общи/Седмица_02/solutions/task_01", /*removeNonEmptyDirectory=*/true);

    fileSystem.print();
}

int main () {
    FileSystem fileSystem;

    testAdd(fileSystem);
    testRemove(fileSystem);

    return 0;
}
