#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

template <class T>
class MyMap {
	static int const MAX_INDEX_SIZE = 20;
	vector<pair<string, T>> index[20];
	int hash(string key) {
		return key.length() % MAX_INDEX_SIZE;
	}

public:
	void set(string key, T value) {
		bool exists = false;
		for (pair<string, T>& p : this->index[this->hash(key)]) {
			if (p.first == key) {
				p.second = value;
				exists = true;
			}
		}
		if (!exists) {
			this->index[this->hash(key)].push_back(pair<string, T>(key, value));
		}
	}

	T get(string key) {
		vector<pair<string, T>> valueArray = this->index[this->hash(key)];
		for (pair<string, T> p : valueArray) {
			if (p.first == key) {
				return p.second;
			}
		}
		return T();
	}
};

class Movie {
public:
	Movie(int _id, string _name, vector<string> _actors) : id(_id), name(_name) {
		for (string actor : _actors) {
			this->actors.push_back(actor);
		}
	}
	int id;
	string name;
	vector<string> actors;
};

vector<string> tokenize(string text) {
	std::istringstream iss(text);
	std::vector<std::string> words;
	std::string word;

	while (iss >> word) {
		words.push_back(word);
	}
	return words;
}

class DB {
	MyMap<vector<int>> movieTitleSearchIndex;
	MyMap<vector<int>> actorNameSearchIndex;
public:
	void addMovie(Movie m) {
		vector<string> movieTitleWords = tokenize(m.name);
		for (string word : movieTitleWords) {
			vector<int> moviesIds = movieTitleSearchIndex.get(word);
			moviesIds.push_back(m.id);
			this->movieTitleSearchIndex.set(word, moviesIds);
		}
		for (string actorName : m.actors) {
			vector<string> actorNameTokens = tokenize(actorName);
			for (string actorNameToken : actorNameTokens) {
				vector<int> moviesIds = actorNameSearchIndex.get(actorNameToken);
				moviesIds.push_back(m.id);
				this->actorNameSearchIndex.set(actorNameToken, moviesIds);
			}
		}
	}

	vector<int> findMoviesByPartialName(string word) {
		return this->movieTitleSearchIndex.get(word);
	}

	vector<int> findMoviesByPartialActorName(string word) {
		return this->actorNameSearchIndex.get(word);
	}
};

int main() {
	cout << "REVERSE INDEX MOVIE SEARCH DB"<<endl;
	MyMap<string> m;
	m.set("test", "1");
	m.set("test2", "12");
	m.set("test3", "13");
	m.set("test4", "14");

	cout << m.get("test") << endl;
	cout << m.get("test1") << endl;
	cout << m.get("test2") << endl;
	cout << m.get("test3") << endl;
	cout << m.get("test4") << endl;

	vector<string> shawshankNames;
	shawshankNames.push_back("Tim Robbins");
	shawshankNames.push_back("Morgan Freeman");
	vector<string> tdkNames;
	tdkNames.push_back("Christian Bale");
	tdkNames.push_back("Morgan Freeman");
	tdkNames.push_back("Garry Oldman");
	vector<string> hpNames;
	hpNames.push_back("Daniele Radcliffe");
	hpNames.push_back("Garry Oldman");
	Movie shawshank(1, "The Shawshank Redemption", shawshankNames);
	Movie tdk(2, "The Dark Knight", tdkNames);
	Movie hptpoa(3, "Harry Potter and the Prisoner of Azkaban", hpNames);

	DB db;
	db.addMovie(shawshank);
	db.addMovie(tdk);
	db.addMovie(hptpoa);

	vector<int> results = db.findMoviesByPartialName("The");
	cout << "RESULTS FOR 'THE':" << endl;
	for (int id : results) {
		cout << id << endl;
	}
	
	results = db.findMoviesByPartialActorName("Morgan");
	cout << "RESULTS FOR 'Morgan':" << endl;
	for (int id : results) {
		cout << id << endl;
	}

	return 0;
}
