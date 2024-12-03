#ifndef _DIRECTORY_NODE_H_
#define _DIRECTORY_NODE_H_

#include "FileNode.h"

#include <string>
#include <vector>


class DirectoryNode : public FileNode
{
public:
  DirectoryNode(const std::string& name)
  : FileNode(name)
  { }

  virtual ~DirectoryNode();

  virtual size_t getNChildren() const
  { return children.size(); }
  virtual const FileNode* getChild(size_t index) const
  { return children.at(index); }

  virtual size_t getSizeInBytes() const
  { return 0; }

  virtual FileNode* findChild(const std::string& name);
  virtual FileNode* addChild(const std::string& name, bool isDirectory);

  virtual void removeChild(const std::string& name, bool removeNonEmptyDirectory);

private:
  DirectoryNode(const DirectoryNode&);
  DirectoryNode& operator=(const DirectoryNode&);

private:
  std::vector<FileNode*> children;
};

#endif // _DIRECTORY_NODE_H_
