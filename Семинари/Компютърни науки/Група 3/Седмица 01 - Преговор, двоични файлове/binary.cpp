#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class BinaryCode {
  virtual void serialize(std::ofstream &file) = 0;
  virtual void deserialize(std::ifstream &file) = 0;
};

class RandomAccessBinaryCodec : public BinaryCode {
  virtual void serialize_at(std::ofstream &file, std::size_t pos) = 0;
  virtual void deserialize_at(std::ifstream &file, std::size_t pos) = 0;
};

class Book : public RandomAccessBinaryCodec {
private:
  static constexpr std::size_t NAME_MAX_LENGHT = 100;
  static constexpr std::size_t AUTHOR_MAX_LENGTH = 50;

public:
  Book(const char name[NAME_MAX_LENGHT] = "",
       const char author[AUTHOR_MAX_LENGTH] = "", unsigned id = 0)
      : id(id) {
    strcpy(this->name, name);
    strcpy(this->author, author);
  }

  void print() const {
    std::cout << name << " " << author << " " << id << '\n';
  }

  void serialize(std::ofstream &file) final {
    file.write(reinterpret_cast<const char *>(this), sizeof(Book));
  }

  void serialize_at(std::ofstream &file, std::size_t pos) final {
    file.seekp(0, std::ios::end);
    std::streampos size = file.tellp();
    std::size_t book_size = size / sizeof(Book);
    if (pos <= book_size) {
      file.seekp((pos - 1) * sizeof(Book));
      file.write(reinterpret_cast<const char *>(this), sizeof(Book));
    }
  }

  void deserialize(std::ifstream &file) final {
    file.read(reinterpret_cast<char *>(this), sizeof(Book));
  }

  void deserialize_at(std::ifstream &file, std::size_t pos) final {
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    std::size_t book_size = size / sizeof(Book);
    if (pos <= book_size) {
      file.seekg((pos - 1) * sizeof(Book));
      file.read(reinterpret_cast<char *>(this), sizeof(Book));
    }
  }

private:
  char name[NAME_MAX_LENGHT];
  char author[AUTHOR_MAX_LENGTH];
  unsigned id;
};

class Library : public BinaryCode {
public:
  Library(const std::string &name) : name(name) {}

  void serialize(std::ofstream &file) final {
    std::size_t name_length = name.size();

    file.write(reinterpret_cast<const char *>(&name_length), sizeof(std::size_t));
    file.write(name.c_str(), name_length);

    std::size_t books_length = books.size();
    file.write(reinterpret_cast<const char *>(&books_length), sizeof(std::size_t));

    for (Book &book : books) {
      book.serialize(file);
    }
  }

  void deserialize(std::ifstream &file) final {
    std::size_t name_size;
    file.read(reinterpret_cast<char *>(&name_size), sizeof(std::size_t));

		name.resize(name_size);
    file.read(name.data(), name_size);

    std::size_t book_size;
    file.read(reinterpret_cast<char *>(&book_size), sizeof(std::size_t));

		books.resize(book_size);
    for (size_t i = 0; i < book_size; i++) {
      books[i].deserialize(file);
    }
  }

  void add(const Book &book) noexcept { books.push_back(book); }

  std::size_t get_list_size() const noexcept { return books.size(); }

  const std::string &get_name() const noexcept { return name; }

	void print() const noexcept {
		for (const Book& book : books) {
			book.print();
		}
	}

private:
  std::string name;
  std::vector<Book> books;
};

int main() {
	Library library("FMI");
  Book book("LOTR", "Tolkien", 5);
  Book next("Hobbit", "Tolkien", 7);

	library.add(book);
	library.add(next);

  std::ofstream os("lib.bin", std::ios::binary);
	
	library.serialize(os);

	os.close();

  std::ifstream is("lib.bin", std::ios::binary);
	
	Library copy("Copy");
	copy.deserialize(is);

	is.close();

	copy.print();

  return 0;
}