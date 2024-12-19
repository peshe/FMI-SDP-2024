#include <string>

class Trie {
public:
	void insert(const std::string &word);
	void remove(const std::string &word);


	void print();

	std::string find(const std::string &word);
	bool contains(const std::string &word);



};
