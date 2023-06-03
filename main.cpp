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

    int check_operation(const std::string& operation)
    {
        bool was_dot = false;

        for (int i = 0; i < operation.size(); ++i)
        {
            char c = operation[i];

            if (!isdigit(c) && !is_operator(c) && c != '.')
            {
                return 1;
                //"Error. Bad character found."
            }

            if (is_operator(c))
            {
                if (i == 0 || i == operation.size() - 1 || !isdigit(operation[i+1]))
                {
                    return 2;
                    //"Error. Bad operator placement."
                }
                else
                {
                    was_dot = false;
                }
            }

            if (c == '.')
            {
                if (i == 0 || i == operation.size() - 1 || !isdigit(operation[i+1]) || !isdigit(operation[i-1]) || was_dot)
                {
                    return 3;
                    //"Error. Bad decimal dot placement."
                }
                else
                {
                    was_dot = true;
                }
            }
        }

        return 0;
        //all okay
    }

    static std::string round(std::string& number)
    {
        size_t dot_pos = number.find('.');

        for (int i = 7; i > 0; --i)
        {
            if (number[dot_pos + i] == '0')
            {
                number = number.erase(dot_pos + i);
            }
        }

        if (dot_pos == number.size() - 1)
        {
            number = number.erase(dot_pos);
        }

        return number;
    }

    std::string calculate(std::string& operation, int order)
    {
        int start = 0;
        for (int i = 0; i < operation.size(); ++i)
        {
            char c = operation[i];
            if ((order == 1 && (operation[i] == '*' || operation[i] == '/')) || (order == 2 && (operation[i] == '+' || operation[i] == '-')))
            {
                double first_number = std::stod(operation.substr(start, i - start));
                int stop = int(operation.size());

                for (int j = i + 1; j < operation.size(); ++j)
                {
                    if (is_operator(operation[j]))
                    {
                        stop = j;
                        break;
                    }
                }

                double second_number = std::stod(operation.substr(i+1, stop - i));
                operation.erase(start, stop - start);

                double result;
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

        int operation_status = check_operation(operation);

        switch (operation_status)
        {
            case 1: return "Error. Bad character found."; break;
            case 2: return "Error. Bad operator placement."; break;
            case 3: return "Error. Bad decimal dot placement."; break;
            default: break;
        }

        operation = calculate(operation, 1);
        operation = calculate(operation, 2);

        return round(operation);
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
