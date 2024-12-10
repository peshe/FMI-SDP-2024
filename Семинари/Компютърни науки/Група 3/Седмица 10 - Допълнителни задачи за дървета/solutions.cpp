#include <iostream>
#include <limits>
#include <utility>

template <typename T>
struct TreeNode {
  T data;
  TreeNode<T> *left, *right;

  TreeNode(const T& data, TreeNode<T>* const left = nullptr, TreeNode<T>* const right = nullptr)
    : data(data), left(left), right(right) {}
};

template <typename T>
const TreeNode<T>* lowest_common_ancestor(const TreeNode<T>* node, const T& lhs, const T& rhs) {
  if (!node) {
    return nullptr;
  }

  if (node->data == lhs || node->data == rhs) {
    return node;
  }

  const TreeNode<T>* left = lowest_common_ancestor(node->left, lhs, rhs);
  const TreeNode<T>* right = lowest_common_ancestor(node->right, lhs, rhs);

  if (left && right) {
    return node;
  }

  return left ? left : right;
}

template <typename T>
bool are_mirrored(const TreeNode<T>* node1, const TreeNode<T>* node2) {
  if (!node1 && !node2) {
    return true;
  }

  if (node1 && node2) {
    return are_mirrored(node1->left, node2->right) &&
           are_mirrored(node1->right, node2->left);
  }

  return false;
}

template <typename T>
bool is_mirror(const TreeNode<T>* node) {
  if (!node) {
    return true;
  }

  return are_mirrored(node->left, node->right);
}

template <typename T>
void free(TreeNode<T>* node) {
  if (!node) {
    return;
  }

  free(node->left);
  free(node->right);

  delete node;
}

using Interval = std::pair<int, int>;

bool contains(const TreeNode<Interval>* parent, const TreeNode<Interval>* child) {
  if (!child) {
    return true;
  }

  return parent->data.first <= child->data.first && child->data.second <= parent->data.second;
}

bool is_interval_tree(const TreeNode<Interval>* node) {
  if (!node) {
    return true;
  }

  return contains(node, node->left) && 
         contains(node, node->right) &&
         is_interval_tree(node->left) &&
         is_interval_tree(node->right);
}

std::pair<double, double> replace_with_average_helper(TreeNode<double>* node) {
  if (!node) {
    return {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
  }

  std::pair<double, double> left = replace_with_average_helper(node->left);
  std::pair<double, double> right = replace_with_average_helper(node->right);

  double max = std::max(node->data, std::max(left.second, right.second));
  double min = std::min(node->data, std::min(left.first, right.first));

  node->data = (max + min) / 2;

  return {min, max};
}

void replace_with_average(TreeNode<double>* node) {
  replace_with_average_helper(node);
}

template <typename T>
void print_tree(const TreeNode<T>* node) {
  if (!node) {
    return;
  }

  print_tree(node->left);
  std::cout << node->data << ' ';
  print_tree(node->right);
}

int main() {
    /*
        5
      /    \         
    1       8
    /\      /\     
  4   3    0 11
  \      /\   
  13   10  9 
  */

  TreeNode<double> *test_tree = 
    new TreeNode<double>(5, 
                      new TreeNode<double>(1, 
                                        new TreeNode<double>(4, 
                                                          nullptr, 
                                                          new TreeNode<double>(13)),
                                        new TreeNode<double>(3)),
                      new TreeNode<double>(8,
                                        new TreeNode<double>(0,
                                                          new TreeNode<double>(10),
                                                          new TreeNode<double>(9)),
                                        new TreeNode<double>(11)));
  // First the tree needs to be converted to double
  replace_with_average(test_tree);

  // Function that prints the tree left-root-right
  print_tree(test_tree); // -> 8.5 13 7 3 6.5 10 5 9 5.5 11
  free(test_tree);
  return 0;
}