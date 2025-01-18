#include <iostream>
#include <string>
#include "hashmap.hpp"
#include <unordered_map>
#include <functional>

class CommandInterpreter {
	using Function = std::function<void(std::vector<std::string> &)>;
	struct CallData {
		unsigned argc;
		Function f;
	};
	std::unordered_multimap<std::string, CallData> map;

   public:
	void addCommand(const std::string &name, unsigned argc, const Function &f) { map.insert({name, {argc, f}}); }

	void run(const std::string s) {
		std::string				 name;
		std::vector<std::string> args;

		std::size_t end1 = s.find(' ');
		if (end1 != std::string::npos) {
			name = s.substr(0, end1);

			std::size_t end;
			std::size_t begin = end1 + 1;
			while ((end = s.find(' ', begin)) != std::string::npos) {
				if (begin == end) continue;
				args.push_back(s.substr(begin, end - begin));
				begin = end + 1;
			}
			args.push_back(s.substr(begin, end - begin));
		} else {
			name = s;
		}

		auto it = map.find(name);
		if (it == map.end()) {
			std::cerr << "error : no such command\n";
			return;
		}
		int cnt = map.count(name);

		for (int i = 0; i < cnt; ++i) {
			auto &[key, val] = *it;
			if (val.argc == args.size()) {
				val.f(args);
				return;
			}
			++it;
		}
		std::cerr << "error : wrong number of arguments\n";
	}
};

int main() {
	{
		hashmap<int, std::string> map(10);

		map.insert(1, "gosho");
		map.insert(2, "pesho");
		map.insert(1, "traicho");

		map.insert(11, "pesho");
		map.insert(21, "traicho");

		// map.printAll();
	}

	CommandInterpreter ci;
	ci.addCommand("ls", 0, [](std::vector<std::string> &) { system("ls"); });
	ci.addCommand("printHello", 1,
				  [](std::vector<std::string> &args) { std::cout << "Hello, " << args[0] << "!" << std::endl; });

	ci.addCommand("add", 1, [](std::vector<std::string> &a) { std::cout << (std::stoi(a[0]) + 1); });
	ci.addCommand("add", 2, [](std::vector<std::string> &a) { std::cout << (std::stoi(a[0]) + std::stoi(a[1])); });

	std::string line;
	std::getline(std::cin, line);
	ci.run(line);
}
