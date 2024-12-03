#ifndef PRACT_PREP8_DIRECTORY_HPP
#define PRACT_PREP8_DIRECTORY_HPP

#include <vector>
#include "FsItem.hpp"

namespace fs {

    class Directory : public FSItem {
    public:
        explicit Directory(const std::string &name);

        ~Directory();

    public:
        unsigned int getSize() const override;

        void print(std::ostream &out, unsigned int level) const override;

        unsigned int printAndGetSize(std::ostream &out, unsigned int level) const override;

        void addFile(const std::string &path, unsigned int size) override;

        FSItem *removeItem(const std::string &path, bool recursive) override;

        void addDirectory(const std::string &path, bool addParents) override;

    private:
        FSItem *findByName(const std::string &name) const;

        std::pair<std::string, std::string> parsePath(const std::string &path) const;

    private:
        std::vector<FSItem *> items;
    };

} // fs

#endif //PRACT_PREP8_DIRECTORY_HPP
