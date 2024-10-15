#include <iostream>
#include <string>

template <typename S> 
class Singleton {
public:
  Singleton(Singleton const &) = delete;
  Singleton &operator=(const Singleton &) = delete;

  static S *get_instance() {
    if (instance == nullptr) {
      instance = new S();
    }

    return instance;
  }

  ~Singleton() {
    delete instance;
  }

protected:
  Singleton() = default;

private:
  static S *instance;
};


class Logger : public Singleton<Logger> {
public:
  void log(const std::string& message) const {
    std::cout << message << '\n';
  }
};

template <class T>
T *Singleton<T>::instance= nullptr;

int main() { 
  Logger *logger = Logger::get_instance();

  logger->log("hello");
  return 0; 
}