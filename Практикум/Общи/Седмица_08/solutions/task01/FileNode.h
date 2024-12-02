#ifndef _FILE_NODE_H_
#define _FILE_NODE_H_

#include <string>


class FileNode
{
public:
  FileNode(const std::string& name)
  : name(name)
  { }

  virtual ~FileNode()
  { }

  virtual size_t getNChildren() const = 0;
  virtual const FileNode* getChild(size_t index) const = 0;

  virtual size_t getSizeInBytes() const = 0;

  virtual FileNode* findChild(const std::string& name) = 0;
  virtual FileNode* addChild(const std::string& name, bool isDirectory) = 0;

  virtual void removeChild(const std::string& name, bool removeNonEmptyDirectory) = 0;

public:
  std::string name;
};

#endif // _FILE_NODE_H_
