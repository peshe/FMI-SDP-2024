#ifndef _TEXT_FILE_NODE_H_
#define _TEXT_FILE_NODE_H_

#include "FileNode.h"

#include <string>


class TextFileNode : public FileNode
{
public:
  TextFileNode(const std::string& name)
  : FileNode(name), sizeInBytes(DEFAULT_SIZE)
  { }

  virtual ~TextFileNode()
  { }

  virtual size_t getNChildren() const
  { return 0; }
  virtual const FileNode* getChild(size_t index) const;

  virtual size_t getSizeInBytes() const
  { return sizeInBytes; }

  virtual FileNode* findChild(const std::string& name);
  virtual FileNode* addChild(const std::string& name, bool isDirectory);

  virtual void removeChild(const std::string& name, bool removeNonEmptyDirectory);

private:
  size_t sizeInBytes;

  static constexpr size_t DEFAULT_SIZE = 4; // Условието не включва начин за указване на размера.
};

#endif // _TEXT_FILE_NODE_H_
