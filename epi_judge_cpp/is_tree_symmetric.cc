#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool RecursiveCompare(const unique_ptr<BinaryTreeNode<int>>& left, const unique_ptr<BinaryTreeNode<int>>& right)
{
    if (left == NULL && right == NULL) return true;
    else if (left == NULL || right == NULL) return false;

    if (left->data != right->data) return false;
    return RecursiveCompare(left->left, right-> right) && RecursiveCompare(left->right, right->left);
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (tree == NULL) return true;
  return RecursiveCompare(tree -> left, tree-> right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
