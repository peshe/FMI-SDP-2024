#include "TextFileNode.h"

#include <stdexcept>
#include <string>

#include "FileNode.h"


/*virtual*/ const FileNode* TextFileNode::getChild(size_t index) const {
    throw std::domain_error("Text files cannot have children!");
}

/*virtual*/ FileNode* TextFileNode::findChild(const std::string& name) {
    throw std::domain_error("Text files cannot have children!");
}

/*virtual*/ FileNode* TextFileNode::addChild(const std::string& name, bool isDirectory) {
    throw std::domain_error("Text files cannot have children!");
}

/*virtual*/ void TextFileNode::removeChild(const std::string& name, bool removeNonEmptyDirectory) {
    throw std::domain_error("Text files cannot have children!");
}
