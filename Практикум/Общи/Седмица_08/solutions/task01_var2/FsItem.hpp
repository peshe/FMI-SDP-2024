#ifndef PRACT_PREP8_FSITEM_HPP
#define PRACT_PREP8_FSITEM_HPP

#include <string>
#include <ostream>

namespace fs {

    class FSItem {
    public:
        explicit FSItem(const std::string &name) : name(name) {}

        virtual unsigned int getSize() const = 0;

        virtual void print(std::ostream &out, unsigned int level = 0) const = 0;

        virtual unsigned int printAndGetSize(std::ostream &out, unsigned int level = 0) const = 0;

        virtual void addFile(const std::string &path, unsigned int size) = 0;

        virtual void addDirectory(const std::string &path, bool addParents = false) = 0;

        virtual FSItem *removeItem(const std::string &path, bool recursive = false) = 0;

        virtual ~FSItem() = default;

    public:
        const std::string &getName() const {
            return name;
        }

    protected:
        static void printTabs(std::ostream &out, unsigned int count) {
            for (unsigned int i = 0; i < count; ++i) {
                out << '\t';
            }
        }

    protected:
        std::string name;
    };

} // fs

#endif //PRACT_PREP8_FSITEM_HPP
