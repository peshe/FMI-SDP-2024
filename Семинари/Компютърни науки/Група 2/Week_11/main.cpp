#include <iostream>
#include "trie.hpp"

int main() {
	Trie t;
	t.insert("alabala");
	t.insert("alabin");
	t.insert("alala");
	t.insert("portokala");

	//t.print();

	std::cout << t.contains("alabala") << std::endl;	   // true;
	std::cout << t.contains("portokali") << std::endl;	   // false;

	std::cout << t.find("alab") << std::endl;	   // "" -> fail
	std::cout << t.find("alaba") << std::endl;	   // "alabala"
	std::cout << t.find("p") << std::endl;		   // "portokala"

	//t.remove("alabal");							  // -> трие alabala, но alabin още е вътре
	//std::cout << t.find("alab") << std::endl;	  // "alabin"
};
