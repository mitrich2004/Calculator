#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Calculator
{
    std::vector<char> operators = {'*', '/', '+', '-'};

    bool is_operator(char c)
    {
        return (std::find(operators.begin(), operators.end(), c) != operators.end());
    }

public:
    std::string calculate(std::string& operation)
    {
        if (operation[0] == '-')
        {
            operation.insert(0, "0");
        }

        for (int i = 0; i < operation.size(); ++i)
        {
            char c = operation[i];

            if (!isdigit(c) && !is_operator(c))
            {
                return "Error. Bad character found.";
            }

            if (is_operator(c))
            {
                if (i == 0 || i == operation.size() - 1 || !isdigit(operation[i+1]) || !isdigit(operation[i-1]))
                {
                    return "Error. Bad operators placement.";
                }
            }
        }

        return operation;
    }
};

int main() {
    std::cout << "Calculator started. Enter 'stop' to end the program." << std::endl;

    std::string operation;
    Calculator calculator;

    while (true)
    {
        std::cout << "Your operation: ";
        std::getline(std::cin, operation);

        if (operation == "stop")
        {
            break;
        }

        operation.erase(remove_if(operation.begin(), operation.end(), isspace), operation.end());
        std::cout << "Result: " << calculator.calculate(operation) << std::endl;
    }

    return 0;
}
