#include "DirectoryNode.h"

#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

#include "FileNode.h"
#include "TextFileNode.h"


/*virtual*/ DirectoryNode::~DirectoryNode() {
    for (FileNode* child : children) {
        delete child;
    }
}

static constexpr int NON_FOUND_INDEX = -1;

static int findChildIndex(const std::vector<FileNode*>& children, const std::string& childName) {
    for (int i = 0; i < children.size(); ++i) {
        const FileNode* child = children[i];
        assert(child != nullptr);

        if (child->name == childName) {
            return i;
        }
    }
    return NON_FOUND_INDEX;
}

/*virtual*/ FileNode* DirectoryNode::findChild(const std::string& name) {
    int childIndex = findChildIndex(children, name);
    if (childIndex != NON_FOUND_INDEX) {
        return children[childIndex];
    }
    return nullptr;
}

/*virtual*/ FileNode* DirectoryNode::addChild(const std::string& name, bool isDirectory) {
    FileNode* existingChild = findChild(name);
    if (existingChild != nullptr) {
        throw std::domain_error("Path already exists!");
    }

    FileNode* newChild = nullptr;
    if (isDirectory) {
        newChild = new DirectoryNode(name);
    }
    else {
        newChild = new TextFileNode(name);
    }

    assert(newChild != nullptr);
    children.push_back(newChild);

    return newChild;
}

/*virtual*/ void DirectoryNode::removeChild(const std::string& name, bool removeNonEmptyDirectory) {
    int childIndex = findChildIndex(children, name);
    if (childIndex == NON_FOUND_INDEX) {
        throw std::domain_error("Cannot remove non-existent file!");
    }

    if (children[childIndex]->getNChildren() > 0 && !removeNonEmptyDirectory) {
        throw std::logic_error("Trying to remove non-empty directory without specifying that.");
    }

    children[childIndex] = children[children.size() - 1];
    children.pop_back();
}
