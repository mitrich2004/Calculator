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

    std::string calculate(std::string& operation, int order)
    {
        int start = 0;
        for (int i = 0; i < operation.size(); ++i)
        {
            char c = operation[i];
            if ((order == 1 && (operation[i] == '*' || operation[i] == '/')) || (order == 2 && (operation[i] == '+' || operation[i] == '-')))
            {
                int first_number = std::stoi(operation.substr(start, i - start));
                int stop = int(operation.size());

                for (int j = i + 1; j < operation.size(); ++j)
                {
                    if (is_operator(operation[j]))
                    {
                        stop = j;
                        break;
                    }
                }

                int second_number = std::stoi(operation.substr(i+1, stop - i));
                operation.erase(start, stop - i + 1);

                int result;
                switch (c)
                {
                    case '*': result = first_number * second_number; break;
                    case '/': result = first_number / second_number; break;
                    case '+': result = first_number + second_number; break;
                    case '-': result = first_number - second_number; break;
                    default: result = 0;
                }

                operation.insert(start, std::to_string(result));
                i = start;
            }
            else if (is_operator(c))
            {
                start = i + 1;
            }
        }

        return operation;
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
                if (i == 0 || i == operation.size() - 1 || !isdigit(operation[i+1]))
                {
                    return "Error. Bad operators placement.";
                }
            }
        }

        operation = calculate(operation, 1);
        operation = calculate(operation, 2);

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
