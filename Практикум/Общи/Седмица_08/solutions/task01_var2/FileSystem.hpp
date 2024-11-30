#ifndef PRACT_PREP8_FILESYSTEM_HPP
#define PRACT_PREP8_FILESYSTEM_HPP

#include "FsItem.hpp"

namespace fs {

    enum FSItemType {
        TEXT_FILE,
        DIRECTORY
    };

    class FileSystem {
    public:
        FileSystem();

        ~FileSystem();

        void addItem(const std::string &path, FSItemType type, unsigned int size = 0, bool createParents = false);

        void removeItem(const std::string &path, bool recursive = false);

        void print() const;

        void printWithSize() const;

    private:
        FSItem *root;
    };

} // fs

#endif //PRACT_PREP8_FILESYSTEM_HPP
