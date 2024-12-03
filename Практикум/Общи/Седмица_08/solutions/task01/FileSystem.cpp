#include "FileSystem.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "FileNode.h"


using std::cout;
using std::string;

static constexpr char DELIMITER = '/';


static FileNode* findContainingDirectory(
    FileNode* root,
    const string& path,
    /*out*/ string& finalNodeName,
    bool createAlongPath = false
) {
    assert(path[0] == DELIMITER);
    FileNode* currentNode = root;

    size_t nextNodeNameStart = 1;
    size_t nextNodeNameEnd = path.find(DELIMITER, nextNodeNameStart);

    while (nextNodeNameEnd < string::npos) {
        string nextNodeName = path.substr(
            nextNodeNameStart,
            nextNodeNameEnd - nextNodeNameStart
        );
        FileNode* nextNode = currentNode->findChild(nextNodeName);

        if (nextNode == nullptr) {
            if (!createAlongPath) {
                throw std::domain_error("Unknown directory encountered in path!");
            }
            nextNode = currentNode->addChild(nextNodeName, /*isDirectory=*/true);
            assert(nextNode != nullptr);
        }
        currentNode = nextNode;

        nextNodeNameStart = nextNodeNameEnd + 1;
        nextNodeNameEnd = path.find(DELIMITER, nextNodeNameStart);
    }

    finalNodeName = path.substr(nextNodeNameStart);
    return currentNode;
}

void FileSystem::add(const string& path, bool isDirectory, bool createAlongPath) {
    string finalNodeName;
    FileNode* containingDirectory = findContainingDirectory(
        &root, path, finalNodeName, createAlongPath
    );

    containingDirectory->addChild(finalNodeName, isDirectory);
}

void FileSystem::remove(const string& path, bool removeNonEmptyDirectory) {
    string finalNodeName;
    FileNode* containingDirectory = findContainingDirectory(
        &root, path, finalNodeName, /*createAlongPath=*/false
    );

    containingDirectory->removeChild(finalNodeName, removeNonEmptyDirectory);
}

static void printFileSimple(const FileNode* file, size_t indent) {
    assert(file != nullptr);
    for (size_t i = 0; i < indent; ++i) {
        cout << '\t';
    }
    cout << file->name << std::endl;

    for (size_t i = 0; i < file->getNChildren(); ++i) {
        printFileSimple(file->getChild(i), indent + 1);
    }
}

// Връща и целия размер на йерархията на файла, т.е.:
// - неговия размер, ако е текстов;
// - сумата от целите размери на всичките му деца, ако е директория.
static size_t printFileWithSizes(const FileNode* file, size_t indent) {
    assert(file != nullptr);
    size_t totalSize = file->getSizeInBytes();

    for (size_t i = 0; i< file->getNChildren(); ++i) {
        totalSize += printFileWithSizes(file->getChild(i), indent + 1);
    }

    for (size_t i = 0; i < indent; ++i) {
        cout << '\t';
    }
    cout << file->name << '\t' << totalSize << std::endl;

    return totalSize;
}

void FileSystem::print(bool showSize) const {
    if (!showSize) {
        printFileSimple(&root, /*indent=*/0);
    }
    else {
        printFileWithSizes(&root, /*indent=*/0);
    }
}
