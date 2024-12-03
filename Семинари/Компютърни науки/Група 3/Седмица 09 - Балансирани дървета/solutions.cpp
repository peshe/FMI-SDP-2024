#include <algorithm>
#include <iostream>
#include <optional>

template <typename K, typename V>
class AVLTree {
public:
  AVLTree() : root_node(nullptr) {}
  AVLTree(const AVLTree &other)
      : root_node(copy(other.root_node)) {}
  AVLTree<K, V> &operator=(const AVLTree &other) {
    AVLTree<K, V> copy(other);
    swap(copy);

    return *this;
  }
  AVLTree(AVLTree &&other) : root_node(other.root_node) {
    other.root_node = nullptr;
  }
  AVLTree<K, V> &operator=(AVLTree &&other) {
    AVLTree<K, V> copy(std::move(other));
    swap(copy);

    return *this;
  }
  ~AVLTree() { free(root_node); }

  void insert(const K& key, const V& value) {
    root_node = insert(root_node, key, value);
  }

  void pretty_print() {
    pretty_print(root_node, "", true);
  }

  std::optional<V> search(const K& key) const {
    return search(root_node, key);
  }

private:
  struct TreeNode {
    K key;
    V value;
    TreeNode* left;
    TreeNode* right;
    std::size_t height;

    TreeNode(const K& key, const V& value) 
      : key(key), value(value), left(nullptr), right(nullptr), height(1) {}
  };

  TreeNode* root_node;

  int get_height(TreeNode* node) const {
    if(!node) {
      return 0;
    }

    return node->height;
  }

  int get_balance_factor(TreeNode* node) const {
    if (!node) {
      return 0;
    }

    return get_height(node->left) - get_height(node->right);
  }

  TreeNode* insert(TreeNode* node, const K& key, const V& value) {
    if (!node) {
      return new TreeNode(key, value);
    }

    if (key < node->key) {
      node->left = insert(node->left, key, value);
    } else if (key > node->key) {
      node->right = insert(node->right, key, value);
    } else {
      node->value = value;
      return node;
    }

    node->height = 1 + std::max(get_height(node->left), get_height(node->right));

    int balance_factor = get_balance_factor(node);

    if (balance_factor < -1 && get_balance_factor(node->right) <= 0) {
      return rotate_left(node);
    } else if (balance_factor > 1 && get_balance_factor(node->left) >= 0) {
      return rotate_right(node);
    } else if (balance_factor < -1 && get_balance_factor(node->right) > 0) {
      node->right = rotate_right(node->right);
      return rotate_left(node);
    } else if (balance_factor > 1 && get_balance_factor(node->left) < 0) {
      node->left = rotate_left(node->left);
      return rotate_right(node);
    }

    return node;
  }

  TreeNode* rotate_left(TreeNode* node) const {
    TreeNode* right = node->right;

    node->right = right->left;
    right->left = node;

    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    right->height = 1 + std::max(get_height(right->left), get_height(right->right));

    return right;
  }

  TreeNode* rotate_right(TreeNode* node) const {
    TreeNode* left = node->left;

    node->left = left->right;
    left->right = node;

    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    left->height = 1 + std::max(get_height(left->left), get_height(left->right));

    return left;
  }

  void pretty_print(TreeNode *node, std::string indent, bool last) {
    if (node != nullptr) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "   ";
      } else {
        std::cout << "L----";
        indent += "|  ";
      }
      std::cout << node->value << '\n';
      pretty_print(node->left, indent, false);
      pretty_print(node->right, indent, true);
    }
  }

  std::optional<V> search(TreeNode* node, const K& key) const {
    if (!node) {
      return std::nullopt;
    }

    if (node->key == key) {
      return node->value;
    }

    if (key < node->key) {
      return search(node->left, key);
    }

    return search(node->right, key);
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
  AVLTree<int, char> tree;
  tree.insert(4, 'C');
  tree.insert(8, 'K');
  tree.insert(9, 'P');
  tree.insert(10, 'A');
  tree.insert(11, 'F');
  tree.insert(12, 'H');
  tree.insert(13, 'O');
  tree.insert(15, 'I');
  tree.insert(17, 'M');
  tree.insert(20, 'G');

  tree.pretty_print();

  std::optional<char> value = tree.search(10);

  if (value.has_value()) {
    std::cout << value.value() << '\n';
  } else {
    std::cout << "not found\n";
  }
  return 0;
}