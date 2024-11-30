#include <iostream>
#include "FileSystem.hpp"
#include "Directory.hpp"

namespace fs {
    FileSystem::FileSystem() {
        this->root = new Directory("/");
    }

    FileSystem::~FileSystem() {
        delete this->root;
    }

    void FileSystem::addItem(const std::string &path, FSItemType type, unsigned int size, bool createParents) {
        if (path.empty() || path[0] != '/') {
            throw std::invalid_argument("Invalid path!");
        }
        switch (type) {
            case TEXT_FILE: {
                this->root->addFile(path.substr(1), size);
                break;
            }
            case DIRECTORY: {
                this->root->addDirectory(path.substr(1), createParents);
                break;
            }
            default:
                throw std::invalid_argument("Invalid file type!");
        }
    }

    void FileSystem::removeItem(const std::string &path, bool recursive) {
        if (path.empty() || path[0] != '/') {
            throw std::invalid_argument("Invalid path!");
        }
        this->root->removeItem(path.substr(1), recursive);
    }

    void FileSystem::printWithSize() const {
        this->root->printAndGetSize(std::cout, 0);
    }

    void FileSystem::print() const {
        this->root->print(std::cout, 0);
    }

} // fs