#include <functional>
#include <stdexcept>
#include <string>
#include <ostream>
#include <format>

class Trie {
   public:
	Trie() {}
	~Trie() {
		for (int i = 0; i < A_SIZE; ++i) {
			free(root.next[i]);
		}
	}
	Trie(const Trie &)			  = delete;
	Trie &operator=(const Trie &) = delete;
	Trie(Trie &&)				  = delete;
	Trie &operator=(Trie &&)	  = delete;

	static const int A_SIZE = 26;
	void			 insert(const std::string &word) { insertH(&root, word.data()); }
	void			 remove(const std::string &word) {
		std::string myword = find(word);

		Node *lastKeep = &root;
		char  key		= myword[0];
		Node *final		= iterate(&root, myword.data(), [&lastKeep, &key](Node *curr, char a) {
			if (curr->isFinal || curr->childrenCount > 1) {
				lastKeep = curr;
				key		  = a;
			}
		});

		if (!final || !final->isFinal) return;
		final->isFinal = false;
		if (final->childrenCount == 0) {
			lastKeep->childrenCount--;
			free(lastKeep->next[key - 'a']);
			lastKeep->next[key - 'a'] = nullptr;
		}
	}

	void writeDot(std::ostream &out) {
		out << "digraph {rankdir=\"LR\"";
		dfs(&root, [&out](Node *curr, char c) {
			out << std::format("\"{}\" [label={}, shape={}]", (void *)curr, c,
							   curr->isFinal ? "doublecircle" : "circle")
				<< std::endl;
			for (std::size_t i = 0; i < A_SIZE; ++i) {
				if (curr->next[i]) out << "\"" << curr << "\" -> \"" << curr->next[i] << "\";\n";
			}
		});

		out << "}";
	}

	void print();

	std::string find(const std::string &word) { return findH(&root, word.data()); }
	bool		contains(const std::string &word) { return containsH(&root, word.data()); }

   private:
	struct Node {
		bool  isFinal		= false;
		int	  childrenCount = 0;
		Node *next[A_SIZE]	= {0};
	};

	Node root;

   private:
	void insertH(Node *curr, const char *word) {
		int index = *word - 'a';
		if (*word == '\0') {
			curr->isFinal = true;
			return;
		}

		if (!curr->next[index]) {
			curr->next[index] = new Node();
			curr->childrenCount++;
		}

		insertH(curr->next[index], word + 1);
	}

	bool containsH(Node *curr, const char *word) {
		int index = *word - 'a';
		if (*word == '\0') { return curr->isFinal; }

		if (!curr->next[index]) return false;

		return containsH(curr->next[index], word + 1);
	}

	bool hasBranch(Node *curr) {
		if (curr->childrenCount == 0) return false;
		if (curr->childrenCount == 1) {
			for (int i = 0; i < A_SIZE; ++i) {
				if (curr->next[i]) { return hasBranch(curr->next[i]); }
			}
		}
		return true;
	}

	std::string getString(Node *curr) {
		if (curr->childrenCount == 0) return "";
		if (curr->childrenCount == 1) {
			for (int i = 0; i < A_SIZE; ++i) {
				if (curr->next[i]) {
					std::string a(1, i + 'a');
					return a + getString(curr->next[i]);
				}
			}
		} else throw std::runtime_error("mistake!!!");
		throw std::runtime_error("mistake!!!");
	}

	Node *iterate(Node *curr, const char *word, const std::function<void(Node *, char)> &f = [](Node *, char) {}) {
		int index = *word - 'a';
		if (*word == '\0') { return curr; }
		f(curr, *word);

		if (!curr->next[index]) return nullptr;

		return iterate(curr->next[index], word + 1, f);
	}

	void dfs(Node *curr, const std::function<void(Node *, char)> &f = [](Node *, char) {}) {
		if (!curr) return;
		for (int i = 0; i < A_SIZE; ++i) {
			if (curr->next[i]) {
				f(curr->next[i], i + 'a');
				dfs(curr->next[i], f);
			}
		}
	}

	std::string findH(Node *curr, const char *word) {
		Node *end = iterate(curr, word);
		if (hasBranch(end)) {
			return "";
		} else {
			return std::string(word) + getString(end);
		}
	}

	void free(Node *curr) {
		if (!curr) return;
		for (int i = 0; i < A_SIZE; ++i) {
			free(curr->next[i]);
		}
		delete curr;
	}
};
