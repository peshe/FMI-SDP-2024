#include <iostream>
#include <fstream>
#include "trie.hpp"

int main() {
	Trie t;
	t.insert("alabala");
	t.insert("alabin");
	t.insert("alala");
	t.insert("portokala");
	t.insert("portok");

	//t.print();
	std::ofstream os1("before.txt");
	t.writeDot(os1);

	std::cout << t.contains("alabala") << std::endl;	   // true;
	std::cout << t.contains("portokali") << std::endl;	   // false;

	std::cout << t.find("alab") << std::endl;	   // "" -> fail
	std::cout << t.find("alaba") << std::endl;	   // "alabala"
	std::cout << t.find("p") << std::endl;		   // "portokala"


	t.remove("alabal");							  // -> трие alabala, но alabin още е вътре
	std::cout << t.find("alab") << std::endl;	  // "alabin"
	t.remove("portokala");						  // -> трие portokala, но portok остава

	std::ofstream os2("after.txt");
	t.writeDot(os2);

	/*
		dot -Tsvg before.txt > after.svg
		dot -Tsvg after.txt > after.svg
		firefox before.svg
		firefox after.svg
	*/
};
