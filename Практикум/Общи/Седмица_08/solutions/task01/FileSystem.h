#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

#include <string>

#include "DirectoryNode.h"


class FileSystem
{
public:
  FileSystem()
  : root("/")
  { }

  void add(const std::string& path, bool isDirectory, bool createAlongPath = false);
  void remove(const std::string& path, bool removeNonEmptyDirectory = false);

  void print(bool showSize = false) const;

private:
  DirectoryNode root;
};

#endif // _FILE_SYSTEM_H_
