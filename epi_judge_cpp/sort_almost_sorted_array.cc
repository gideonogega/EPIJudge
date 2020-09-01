#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {

    vector<int> result = vector<int>();
    std::priority_queue <int, vector<int>, std::greater<int> > heap;

    for(sequence_begin; sequence_begin < sequence_end; sequence_begin++)
    {
        if(heap.size() == k)
        {
            result.push_back(heap.top());
            heap.pop();
        }

        heap.push(*sequence_begin);
    }

    while(heap.size() > 0)
    {
        result.push_back(heap.top());
        heap.pop();
    }

    return result;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
    int k) {
    return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {

    vector<int> vals = vector<int>();
    vals.push_back(3);
    vals.push_back(-1);
    vals.push_back(2);
    vals.push_back(6);
    vals.push_back(4);
    vals.push_back(5);
    vals.push_back(8);

    vector<int> results = SortApproximatelySortedDataWrapper(vals, 2);

    std::vector<std::string> args{ argv + 1, argv + argc };
    std::vector<std::string> param_names{ "sequence", "k" };
    return GenericTestMain(
        args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
        &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
