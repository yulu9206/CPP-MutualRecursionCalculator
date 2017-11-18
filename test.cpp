#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

void evaluate();
double expression();
double term();
double factor();
double number();
double power();

int main()
{
    char ch;

    do
    {
        cout << endl << "Expression? ";
        ch = (cin >> ws).peek();
        if (ch != '.') evaluate();
    } while (ch != '.');

    cout << endl << "Done!" << endl;
    return 0;
}

void evaluate()
{
    try
    {
        cout << expression() << endl;
        char ch;
        cin >> ch;
        if (ch != '=') throw string("Unexpected ") + ch;
    }
    catch(string& msg)
    {
        cout << "***** " << msg << endl;
    }
    string rest_of_line;
    getline(cin, rest_of_line);
}

double expression()
{
    char ch;
    bool negative = false;

    cin >> ws;
    ch = cin.peek();

    if (ch == '-')
    {
        cin >> ch;
        negative = true;
    }
    else if (ch == '+') cin >> ch;

    double value = term();
    if (negative) value = -value;

    bool done = false;

    do
    {
        cin >> ws;
        ch = cin.peek();

        switch (ch)
        {
            case '+':
            {
                cin >> ch;
                value += term();
                break;
            }

            case '-':
            {
                cin >> ch;
                value -= term();
                break;
            }

            default: done = true;
        }
    } while (!done);

    return value;
}

double term()
{
    double value = power();
    bool done = false;
    char ch;

    do
    {
        cin >> ws;
        ch = cin.peek();

        switch (ch)
        {
            case '*':
            {
                cin >> ch;
                value *= power();
                break;
            }

            case '/':
            {
                cin >> ch;
                double value2 = power();

                if (value2 != 0) value /= value2;
                else
                {
                    throw string("Division by zero");
                    return 0;
                }

                break;
            }

            default: done = true;
        }
    } while (!done);

    return value;
}

double power()
{
    double value = factor();
    bool done = false;
    char ch;

    do
    {
        cin >> ws;
        ch = cin.peek();

        if (ch == '^')
        {
            cin >> ch;
            value = pow(value, power());
        }
        else done = true;
    } while (!done);

    return value;
}

double factor()
{
    cin >> ws;
    char ch = cin.peek();

    if (isdigit(ch))
    {
        return number();
    }

    else if (ch == '(')
    {
        cin >> ch;
        double value = expression();

        ch = cin.peek();
        if (ch == ')') cin >> ch;
        else
        {
            throw string("Missing )");
        }

        return value;
    }

    else
    {
        throw string("Invalid factor");
        return 0;
    }
}

double number()
{
    double value;
    cin >> value;
    return value;
}
