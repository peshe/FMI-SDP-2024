#include <iostream>
#include <algorithm>
#include "Directory.hpp"
#include "TextFile.hpp"

namespace fs {
    unsigned int Directory::getSize() const {
        unsigned int sum = 0;
        for (const auto &item: items) {
            sum += item->getSize();
        }

        return sum;
    }

    void Directory::print(std::ostream &out, unsigned int level) const {
        FSItem::printTabs(out, level);
        out << this->name << '\n';
        for (const auto &item: this->items) {
            item->print(out, level + 1);
        }
    }

    unsigned int Directory::printAndGetSize(std::ostream &out, unsigned int level) const {
        unsigned int sizeSum = 0;
        for (const auto &item: this->items) {
            sizeSum += item->printAndGetSize(out, level + 1);
        }
        FSItem::printTabs(out, level);
        out << this->name << '\t' << sizeSum << '\n';
        return sizeSum;
    }

    void Directory::addFile(const std::string &path, unsigned int size) {
        auto [currentItem, remainingPath] = this->parsePath(path);

        FSItem *child = findByName(currentItem);
        // If the current item is not the file to be added, and it's missing in the children
        if (!child && !remainingPath.empty()) {
            throw std::invalid_argument("Invalid path!");
        }

        // If the current item is the file to be added
        if (remainingPath.empty()) {
            if (!child) {
                auto newItem = new TextFile(currentItem, size);
                this->items.push_back(newItem);
                return;
            }
            throw std::invalid_argument("Invalid path! File already exists");
        }

        // continue traversing
        return child->addFile(remainingPath, size);
    }

    void Directory::addDirectory(const std::string &path, bool addParents) {

        auto [currentItem, remainingPath] = this->parsePath(path);

        FSItem *child = findByName(currentItem);
        // Current item is the dir to be added
        if (!child && remainingPath.empty()) {
            auto newItem = new Directory(currentItem);
            this->items.push_back(newItem);
            return;
        }

        // current path doesn't exist: check whether to create parents
        if (!child && !remainingPath.empty()) {
            if (addParents) {
                auto newItem = new Directory(currentItem);
                this->items.push_back(newItem);
                newItem->addDirectory(remainingPath, addParents);
                return;
            } else {
                throw std::invalid_argument("Invalid path!" + path);
            }
        }

        // Continue traversing
        child->addDirectory(remainingPath, addParents);
    }

    FSItem *Directory::findByName(const std::string &name) const {
        for (const auto &item: this->items) {
            if (item->getName() == name) {
                return item;
            }
        }
        return nullptr;
    }

    FSItem *Directory::removeItem(const std::string &path, bool recursive) {
        auto [currentItem, remainingPath] = this->parsePath(path);

        // if the current item is to be deleted
        if (currentItem == this->name && remainingPath.empty()) {
            return recursive ? this : nullptr;
        }

        FSItem *child = findByName(currentItem);
        if (!child) {
            throw std::invalid_argument("Invalid path!");
        }

        FSItem *toRemove = child->removeItem(remainingPath.empty() ? currentItem : remainingPath, recursive);

        if (toRemove) {
            this->items.erase(
                    std::remove_if(this->items.begin(), this->items.end(),
                                   [toRemove](FSItem *x) { return x == toRemove; }), this->items.end());
            delete toRemove;
        }

        return nullptr;
    }

    Directory::Directory(const std::string &name) : FSItem(name) {}

    Directory::~Directory() {
        for (const auto &item: this->items) {
            delete item;
        }
    }

    std::pair<std::string, std::string> Directory::parsePath(const std::string &path) const {
        auto firstSlash = path.find('/');
        std::string currentItem = path.substr(0, firstSlash);
        std::string remainingPath;
        if (std::string::npos != firstSlash) {
            remainingPath = path.substr(firstSlash + 1);
        }

        return {currentItem, remainingPath};

    }

} // fs