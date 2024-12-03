#ifndef PRACT_PREP8_TEXTFILE_HPP
#define PRACT_PREP8_TEXTFILE_HPP

#include "FsItem.hpp"

namespace fs {

    class TextFile : public FSItem {
    public:
        TextFile(const std::string &name, unsigned int size);

        unsigned int getSize() const override;

        void print(std::ostream &out, unsigned int level) const override;

        unsigned int printAndGetSize(std::ostream &out, unsigned int level) const override;

        void addFile(const std::string &path, unsigned int size) override;

        void addDirectory(const std::string &path, bool addParents) override;

        FSItem *removeItem(const std::string &path, bool recursive) override;

    private:
        unsigned int size;
    };

} // fs

#endif //PRACT_PREP8_TEXTFILE_HPP
