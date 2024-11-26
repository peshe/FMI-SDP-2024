#include <algorithm>
#include <iostream>
#include <variant>
#include <vector>
#include "../Седмица 04 - Опашка/linked_queue.hpp"
#include "../Седмица 03 - Стек/linked_stack.hpp"

template <typename T>
struct ElementWithLevel {
  T element;
  std::size_t level;

  ElementWithLevel(const T& element, std::size_t level) : element(element), level(level) {}
};

template <typename T>
class Tree {
public:
  Tree(const T& data, const std::vector<Tree<T>>& children = std::vector<Tree<T>>())
    : data(data), children(children) {}

  void add_subtree(const Tree& subtree)  {
    children.push_back(subtree);
  }

  const T& root() const {
    return data;
  }

  bool leaf() const {
    return children.empty();
  }

  void dfs() const {
    std::cout << data << ' ';
    
    if (leaf()) {
      return;
    }

    for (const Tree<T>& child : children) {
      child.dfs();
    }
  }

  void bfs() const {
    LinkedQueue<const Tree<T>* const> queue;
    queue.enqueue(this);

    while (!queue.empty()) {
      const Tree<T>* current_tree = queue.dequeue();

      std::cout << current_tree->data << ' ';

      for (const Tree<T>& child : current_tree->children) {
        queue.enqueue(&child);
      }
    }
  }

  bool contains(const T& element) const {
    if (leaf() && data != element) {
      return false;
    }

    if (data == element) {
      return true;
    }

    for (const Tree<T>& child : children) {
      if (child.contains(element)) {
        return true;
      }
    }

    return false;
  }

private:
  T data;
  std::vector<Tree<T>> children;
};

template <typename T>
class BinaryTree {
public:
  BinaryTree() : root_node(nullptr) {}
  
  BinaryTree(const T& data, BinaryTree&& left = BinaryTree(), BinaryTree&& right = BinaryTree())
    : root_node(new TreeNode(data, left.root_node, right.root_node)) {
    left.root_node = nullptr;
    right.root_node = nullptr;
  }

  BinaryTree(const BinaryTree& other) : root_node(copy(other.root_node)) {}

  BinaryTree<T>& operator=(const BinaryTree& other) {
    BinaryTree<T> copy(other);
    swap(copy);

    return *this;
  }

  BinaryTree(BinaryTree&& other) : root_node(other.root_node) {
    other.root_node = nullptr;
  }

  BinaryTree<T>& operator=(BinaryTree&& other) {
    BinaryTree<T> copy(std::move(other));
    swap(copy);

    return *this;
  }

  ~BinaryTree() {
    free(root_node);
  }

  const T& root() const {
    return root_node->data;
  }

  bool empty() const {
    return root_node == nullptr;
  }

  bool contains(const T& data) const {
    return contains(root_node, data);
  }

  bool operator==(const BinaryTree& other) const {
    return equal(root_node, other.root_node);
  }

  std::size_t height() const {
    return height(root_node);
  }

  std::vector<T> level(std::size_t index) const {
    LinkedQueue<ElementWithLevel<TreeNode*>> queue;
    queue.enqueue({root_node, 0});
    std::vector<T> result;

    while (!queue.empty()) {
      ElementWithLevel<TreeNode*> current = queue.dequeue();

      if (current.element) {
        if (current.level == index) {
          result.push_back(current.element->data);
        }

        if (current.level > index) {
          return result;
        }

        queue.enqueue({ current.element->left, current.level + 1 });
        queue.enqueue({ current.element->right, current.level + 1 });
      }
    }

    return result;
  }

private:
  struct TreeNode {
    T data;
    TreeNode *left, *right;

    TreeNode(const T& data, TreeNode* const left = nullptr, TreeNode* const right = nullptr)
    : data(data), left(left), right(right) {}
  };

public:
  class Iterator {
    public:
      Iterator(TreeNode* node) {
        windstack(node);
      }

      T& operator*() {
        return stack.peek()->data;
      }

      const T& operator*() const {
        return stack.peek()->data;
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

  TreeNode* copy(const TreeNode* node) {
    if (!node) {
      return nullptr;
    }

    return new TreeNode(node->data, copy(node->left), copy(node->right));
  }

  void free(TreeNode* node) {
    if (!node) {
      return;
    }

    free(node->left);
    free(node->right);

    delete node;
  }

  void swap(BinaryTree& other) {
    std::swap(root_node, other.root_node);
  }

  bool contains(const TreeNode* node, const T& data) const {
    if (!node) {
      return false;
    }

    return node->data == data || 
           contains(node->left, data) || 
           contains(node->right, data);
  }

  bool equal(const TreeNode* node1, const TreeNode* node2) const {
    return !node1 && !node2 ||
           node1->data == node2->data &&
           equal(node1->left, node2->left) &&
           equal(node1->right, node2->right);
  }

  std::size_t height(const TreeNode* node) const {
    if (!node) {
      return 0;
    }

    return 1 + std::max(height(node->left), height(node->right));
  }
};

int main() {
  Tree<int> tree(1);
  Tree<int> first_subtree(2, {Tree<int>(5), Tree<int>(6, {Tree<int>(11)})});
  Tree<int> second_subtree(3, {Tree<int>(7)});
  Tree<int> third_subtree(4, {Tree<int>(8), Tree<int>(9), Tree<int>(10)});

  tree.add_subtree(first_subtree);
  tree.add_subtree(second_subtree);
  tree.add_subtree(third_subtree);
  tree.bfs();
  std::cout << '\n';

  std::cout << std::boolalpha << tree.contains(6) << '\n';
  std::cout << tree.contains(7) << '\n';
  std::cout << tree.contains(12) << '\n';

  BinaryTree<int> bintree(
    1, 
    BinaryTree<int>(2, 
                    BinaryTree<int>(4), 
                    BinaryTree<int>(5, 
                                    BinaryTree<int>(8))), 
    BinaryTree<int>(3, 
                    BinaryTree<int>(6, 
                                    BinaryTree<int>(9), 
                                    BinaryTree<int>(10)), 
                    BinaryTree<int>(7, 
                                    BinaryTree<int>(), 
                                    BinaryTree<int>(11))));

  BinaryTree<int> copy(bintree);

  std::cout << (bintree == copy) << '\n';
  std::cout << std::boolalpha << bintree.contains(6) << '\n';
  std::cout << std::boolalpha << bintree.contains(9) << '\n';
  std::cout << std::boolalpha << bintree.contains(12) << '\n';
  std::cout << bintree.height() << '\n';

  for (int i : bintree.level(3)) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  for (int i : bintree) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  return 0;
}