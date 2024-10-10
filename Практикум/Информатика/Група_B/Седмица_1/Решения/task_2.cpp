#include "week1.h"

#include <iostream>
#include <sstream>

/*----------------------------------------------------------------------------*/

char* readCString(std::istream& in)
{
  int stringLength = 0;
  in >> stringLength;
  if (stringLength < 0) {
    return nullptr;
  }

  try {
    char* result = new char[stringLength + 1];
    in.get();
    in.read(result, stringLength);

    if (!in) {
      delete[] result;
      return nullptr;
    }

    result[stringLength] = '\0';
    return result;
  }
  catch (std::bad_alloc& e) {
    return nullptr;
  }
}

void printCString(const char *const cstr)
{
  if (cstr != nullptr) {
    std::cout << cstr << '\n';
  }
  else {
    std::cout << "nullptr\n";
  }
}

void Week1::task2()
{
  {
    std::stringstream stream;
    stream << "2 abc";
    char* cstr = readCString(stream);
    printCString(cstr);
    delete[] cstr;
  }

  {
    std::stringstream stream;
    stream << "5 a b c d";
    char* cstr = readCString(stream);
    printCString(cstr);
    delete[] cstr;
  }

  {
    std::stringstream stream;
    stream << "4 1";
    char* cstr = readCString(stream);
    printCString(cstr);
    delete[] cstr;
  }

  {
    std::stringstream stream;
    stream << "-200 abc";
    char* cstr = readCString(stream);
    printCString(cstr);
    delete[] cstr;
  }
}
