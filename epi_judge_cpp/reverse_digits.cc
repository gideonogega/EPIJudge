#include "test_framework/generic_test.h"

using namespace std;

long long ReverseNaive(long long x)
{
    cout << x << endl;
    string input = std::to_string(x);
    string::size_type sz = 0;
    string::size_type length = input.length();
    short start = x < 0 ? 1 : 0;
    for (short i = start; i <= (length / 2); i++)
    {
        char temp = input[i];
        input[i] = input[(length - i + start) - 1];
        input[(length - i + start) - 1] = temp;
    }

    long long result = std::stoll(input, &sz);
    cout << x << result;
    return result;
}

long long ReverseModDiv(long long x)
{
    cout << x << endl;
    long long result = 0;
    while(x)
    {
        result = result * 10 + x % 10;
        x /= 10;
    }
    cout << x << endl;
    return result;
}

long long Reverse(long long x) {
    return ReverseNaive(x);
}

int main(int argc, char* argv[]) {
    vector<string> args{ argv + 1, argv + argc };
    vector<string> param_names{ "x" };
    return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
        &Reverse, DefaultComparator{}, param_names);
}
