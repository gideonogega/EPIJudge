#include <string>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using namespace std;

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
    const vector<int*>& preorder) {

    if (preorder.size() == 0 || preorder.at(0) == NULL) return nullptr;

    BinaryTreeNode<int>* tree = new BinaryTreeNode<int>(*preorder.at(0));

    stack<BinaryTreeNode<int>*> st = stack<BinaryTreeNode<int>*>();
    st.push(tree);
    for (int i = 1; i < preorder.size(); i++)
    {
        BinaryTreeNode<int>* iter = st.top();
        int* data = preorder.at(i);
        BinaryTreeNode<int>* node = NULL;
        if (data != NULL)
        {
            node = new BinaryTreeNode<int>(*data);
            if (iter->left == NULL)
            {
                iter->left = unique_ptr<BinaryTreeNode<int>>(node);
            }
            else if (iter->right == NULL)
            {
                iter->right = unique_ptr<BinaryTreeNode<int>>(node);
            }
            st.push(node);
        }
        else
        {
            if (iter->left == NULL && i + 1 < preorder.size() && preorder.at(i + 1) == NULL) {
                st.pop();
                i++;
            }
            if (iter->left != NULL) {
                st.pop();
            }
            while (st.top()->right != NULL && st.size() > 0) st.pop();

            /*if (iter->left == NULL && i + 1 < preorder.size() && preorder.at(i + 1) != NULL) {
                node = new BinaryTreeNode<int>(*preorder.at(i+1));
                iter->right = unique_ptr<BinaryTreeNode<int>>(node);
                st.push(node);
            }*/
        }
    }

    return unique_ptr<BinaryTreeNode<int>>(tree);
}
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
    vector<int> values;
    vector<int*> ptrs;
    values.reserve(preorder.size());
    for (auto& s : preorder) {
        if (s == "null") {
            ptrs.push_back(nullptr);
        }
        else {
            int i = std::stoi(s);
            values.push_back(i);
            ptrs.push_back(&values.back());
        }
    }

    return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

void Print(BinaryTreeNode<int>* tree)
{
    if (tree == NULL) return;
    Print(tree->left.get());
    cout << tree->data << ",";
    Print(tree->right.get());
}

int main(int argc, char* argv[]) {
    /*string vals_arr[] = { "1", "2", "4", "8", "16", "null", "null", "17", "null", "null", "9", "18", "null", "null",
        "19", "null", "null", "5", "10", "20", "null", "null", "21", "null", "null", "11", "22", "null", "null", "23", "null",
        "null", "3", "6", "12", "24", "null", "null", "25", "null", "null", "13", "26", "null", "null", "27", "null", "null",
        "7", "14", "28", "null", "null", "29", "null", "null", "15", "30", "null", "null", "31", "null", "null" };*/

    string vals_arr[] = { "8", "2", "6", "null", "null", "5", "1", "null", "null", "null", "3", "null", "4", "null", "7", "9", "null", "null", "null" };

    vector<int*> vals = vector<int*>();
    int size = sizeof(vals_arr) / sizeof(vals_arr[0]);
    for (int i = 0; i < size; i++)
    {
        if (vals_arr[i] == "null") vals.push_back(NULL);
        else vals.push_back(new int(stoi(vals_arr[i])));
    }
    Print(ReconstructPreorder(vals).get());
    auto saved = ReconstructPreorder(vals);

    std::vector<std::string> args{ argv + 1, argv + argc };
    std::vector<std::string> param_names{ "executor", "preorder" };
    return GenericTestMain(args, "tree_from_preorder_with_null.cc",
        "tree_from_preorder_with_null.tsv",
        &ReconstructPreorderWrapper, DefaultComparator{},
        param_names);
}
