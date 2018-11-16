#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <math.h>

int evaluate(const std::string&, char);
std::vector<std::string> split(const std::string&, char);
void solveExp(std::stack<char>&, std::stack<int>&);
int calculate(int, int, char);
int getPrecedence(char);

int main()
{
    auto exp1 = "8 / 4 + 7 * ( 1 + ( 33 + 2 - 4 ^ 2 ) - 1 ) * ( 5 - 2 ) + 2";           // answer = 403
    std::cout << evaluate(exp1, ' ') << std::endl;

    auto exp2 = "( ( 15 / ( 7 - ( 1 + 1 ) ) ) * 3 ) - ( 2 + ( 1 + 1 ) )";               // answer = 5
    std::cout << evaluate(exp2, ' ') << std::endl;

    return 0;
}

int evaluate(const std::string& exp, char delimiter)
{
    std::stack<char> operatorStack;
    std::stack<int> operandStack;

    for (auto token : split(exp, delimiter))
    {
        try
        {
            int num = std::stoi(token);
            operandStack.push(num);
        }
        catch(const std::exception&)
        {
            char oper = token[0];

            if (operatorStack.size() == 0 || oper == '(')
            {
                operatorStack.push(oper);
            }
            else if (oper == ')')
            {
                do
                {
                    solveExp(operatorStack, operandStack);
                }
                while (operatorStack.top() != '(');

                operatorStack.pop();
            }
            else
            {
                if (operatorStack.top() != '(' && getPrecedence(oper) >= getPrecedence(operatorStack.top()))
                {
                    solveExp(operatorStack, operandStack);
                }

                operatorStack.push(oper);
            }
        }
    }

    while (operatorStack.size() > 0)
    {
        solveExp(operatorStack, operandStack);
    }

    return operandStack.top();
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::istringstream tokenStream(s);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

void solveExp(std::stack<char>& operatorStack, std::stack<int>& operandStack)
{
    char topOper = operatorStack.top();
    operatorStack.pop();

    int num1 = operandStack.top();
    operandStack.pop();
    int num2 = operandStack.top();
    operandStack.pop();

    int answer = calculate(num2, num1, topOper);
    operandStack.push(answer);
}

int calculate(int num1, int num2, char oper)
{
    int answer = 0;

    switch (oper)
    {
    case '^':
        answer = static_cast<int>(pow(num1, num2));
        break;

    case '*':
        answer = num1 * num2;
        break;

    case '/':
        answer = num1 / num2;
        break;

    case '+':
        answer = num1 + num2;
        break;

    case '-':
        answer = num1 - num2;
        break;
    }

    return answer;
}

int getPrecedence(char oper)
{
    int precedence = 0;

    switch (oper)
    {
    case ')':
        precedence = 1;
        break;

    case '(':
        precedence = 2;
        break;

    case '^':
        precedence = 3;
        break;

    case '*':
    case '/':
        precedence = 4;
        break;

    case '+':
    case '-':
        precedence = 5;
        break;
    }

    return precedence;
}
