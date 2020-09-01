#include <string>

#include "test_framework/generic_test.h"
using std::string;
using namespace std;

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


void OperationEvaluate(string op, stack<int>& s)
{
    int value1 = s.top();
    s.pop();
    int value2 = s.top();
    s.pop();

    if (op == "+")
    {
        s.push(value2 + value1);
    }
    else if (op == "-")
    {
        s.push(value2 - value1);
    }
    else if (op == "*")
    {
        s.push(value2 * value1);
    }
    else if (op == "/")
    {
        s.push(value2 / value1);
    }
}

int Evaluate(const string& expression) {
    stack <int> s;
    stringstream s_stream(expression); //create string stream from the string
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        if (is_number(substr)) s.push(std::stoi(substr));
        else OperationEvaluate(substr, s);
    }

    return s.top();
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{ argv + 1, argv + argc };
    std::vector<std::string> param_names{ "expression" };
    return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
        DefaultComparator{}, param_names);
}
