#include "TextFile.hpp"
#include <iostream>

namespace fs {
    unsigned int TextFile::getSize() const {
        return this->size;
    }

    TextFile::TextFile(const std::string &name, unsigned int size) : FSItem(name), size(size) {}

    void TextFile::print(std::ostream &out, unsigned int level) const {
        FSItem::printTabs(out, level);
        out << this->name << '\n';
    }

    unsigned int TextFile::printAndGetSize(std::ostream &out, unsigned int level) const {
        FSItem::printTabs(out, level);
        out << this->name << '\t' << this->getSize() << '\n';
        return this->getSize();
    }

    void TextFile::addFile(const std::string &path, unsigned int size) {
        throw std::invalid_argument("Invalid path! Cannot add child to text file!");
    }

    void TextFile::addDirectory(const std::string &path, bool addParents) {
        throw std::invalid_argument("Invalid path! Cannot add child to text file!");
    }

    FSItem *TextFile::removeItem(const std::string &path, bool recursive) {
        std::cout << "filerm: " << path << std::endl;
        if (path == this->name) {
            return this;
        }
        throw std::invalid_argument("Invalid path!");
    }
} // fs