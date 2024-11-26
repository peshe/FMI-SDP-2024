#include <complex>
#include <cstddef>
#include <iostream>
#include <optional>
#include "../Седмица 03 - Стек/linked_stack.hpp"

template <typename K, typename V>
class BinarySearchTree {
public:
  BinarySearchTree() : root_node(nullptr) {}
  BinarySearchTree(const BinarySearchTree &other)
      : root_node(copy(other.root_node)) {}
  BinarySearchTree<K, V> &operator=(const BinarySearchTree &other) {
    BinarySearchTree<K, V> copy(other);
    swap(copy);

    return *this;
  }
  BinarySearchTree(BinarySearchTree &&other) : root_node(other.root_node) {
    other.root_node = nullptr;
  }
  BinarySearchTree<K, V> &operator=(BinarySearchTree &&other) {
    BinarySearchTree<K, V> copy(std::move(other));
    swap(copy);

    return *this;
  }
  ~BinarySearchTree() { free(root_node); }

  void insert(const K& key, const V& value) {
    if (!root_node) {
      root_node = new TreeNode(key, value);
      return;
    }

    TreeNode* node = root_node, *parent = root_node;
    while (node && node->key != key) {
      parent = node;

      if (key < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }

    if (node) {
      node->value = value;
      return;
    }

    if (parent->key < key) {
      parent->right = new TreeNode(key, value);
    } else {
      parent->left = new TreeNode(key, value);
    }
  }

  std::optional<V> search(const K& key) const {
    TreeNode* node = root_node;

    while (node && node->key != key) {
      if (key < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }

    if (node) {
      return node->value;
    }

    return std::nullopt;
  }

  std::optional<V> kth_element(std::size_t k) const {
    Iterator it = begin(), end_it = end();
    for (std::size_t i = 0; i < k && it != end_it; ++i) {
      ++it;
    }

    if (!(it != end_it)) {
      return std::nullopt;
    }

    return *it;
  }

  std::size_t height() const {
    return height(root_node);
  }

  bool is_balanced() const {
    return is_balanced(root_node);
  }

private:
  struct TreeNode {
    K key;
    V value;
    TreeNode *left, *right;

    TreeNode(const K &key, const V &value, TreeNode *const left = nullptr,
            TreeNode *const rigth = nullptr)
        : key(key), value(value), left(left), right(rigth) {}
  };

public:
  class Iterator {
    public:
      Iterator(TreeNode* node) {
        windstack(node);
      }

      V& operator*() {
        return stack.peek()->value;
      }

      const V& operator*() const {
        return stack.peek()->value;
      }

      Iterator& operator++() {
        TreeNode* current = stack.pop();
          
        if (current->right) {
          windstack(current->right);
        }

        return *this;
      }

      bool operator!=(const Iterator& other) const {
        return !(stack.empty() && other.stack.empty() ||
               !stack.empty() && !other.stack.empty() && 
               stack.peek() == other.stack.peek());
      }

    private:
      LinkedStack<TreeNode*> stack;

      void windstack(TreeNode* node) {
        while (node) {
          stack.push(node);
          node = node->left;
        }
      } 
  };

  Iterator begin() const {
    return Iterator(root_node);
  }

  Iterator end() const {
    return Iterator(nullptr);
  }

private:
  TreeNode* root_node;

  int height(const TreeNode* node) const {
    if (!node) {
      return 0;
    }

    return 1 + std::max(height(node->left), height(node->right));
  }

  bool is_balanced(const TreeNode* const node) const {
    if (!node) {
      return true;
    }

    return is_balanced(node->left) &&
           is_balanced(node->right) &&
           std::abs<int>(height(node->left) - height(node->right)) <= 1;
  }

  TreeNode *copy(TreeNode *const node) {
    if (!node) {
      return nullptr;
    }

    return new TreeNode(node->key, node->value, copy(node->left), copy(node->right));
  }

  void free(TreeNode *node) {
    if (!node) {
      return;
    }

    free(node->left);
    free(node->right);

    delete node;
  }
};

int main() {
  BinarySearchTree<int, char> tree;
  
  tree.insert(12, 'H');
  tree.insert(8, 'K');
  tree.insert(15, 'I');
  tree.insert(4, 'C');
  tree.insert(10, 'A');
  tree.insert(9, 'P');
  tree.insert(11, 'F');
  tree.insert(13, 'O');
  tree.insert(20, 'G');
  tree.insert(17, 'M');

  tree.insert(9, 'X');

  std::optional<char> value = tree.search(9);

  if (value.has_value()) {
    std::cout << value.value() << '\n';
  } else {
    std::cout << "not found\n";
  }

  for (int i : tree) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  std::optional<char> kth_value = tree.kth_element(4);

  if (kth_value.has_value()) {
    std::cout << kth_value.value() << '\n';
  } else {
    std::cout << "not found\n";
  }

  tree.insert(16, 'Z');
  std::cout << std::boolalpha << tree.is_balanced() << '\n';

  BinarySearchTree<int, char> copy(tree);
}