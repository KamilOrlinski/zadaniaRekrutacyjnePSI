#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class AbstractMathematicalOperation
{
    public:
        virtual string Proceed() const = 0;
        virtual string GetClassName() const = 0;
};

class Add : public AbstractMathematicalOperation
{
    private:
    double a, b;


    public:
        Add(double a, double b) : a(a), b(b) {}

        string Proceed() const override
        {
            return to_string(a + b);
        }

        string GetClassName() const override
        {
            return "Dodawanie";
        }
};

class Sub : public AbstractMathematicalOperation
{
    private:
        double a, b;

    public:
        Sub(double a, double b) : a(a), b(b) {}

        string Proceed() const override
        {
            return to_string(a - b);
        }

        string GetClassName() const override
        {
            return "Odejmowanie";
        }
};

class Multiply : public AbstractMathematicalOperation
{
    private:
        double a, b;

    public:
        Multiply(double a, double b) : a(a), b(b) {}

        string Proceed() const override
        {
            return to_string(a * b);
        }

        string GetClassName() const override
        {
            return "Mnożenie";
        }
};

class Div : public AbstractMathematicalOperation
{
    private:
        double a, b;

    public:
        Div(double a, double b) : a(a), b(b) {}

        string Proceed() const override
        {
            if (b != 0)
            {
                return to_string(a / b);
            }
            else
            {
                return "Nie można dzielić przez 0";
            }
        }

        string GetClassName() const override
        {
            return "Dzielenie";
        }
};

enum Type { ADD, SUB, MULTIPLY, DIV };

class OperationFactory
{
    public:
        static unique_ptr<AbstractMathematicalOperation> create(Type t, double a, double b)
        {
            switch (t)
            {
            case ADD:
                return make_unique<Add>(a, b);
            case SUB:
                return make_unique<Sub>(a, b);
            case MULTIPLY:
                return make_unique<Multiply>(a, b);
            case DIV:
                return make_unique<Div>(a, b);
            default:
                return nullptr;
            }
        }


};

int main()
{
    vector < unique_ptr<AbstractMathematicalOperation>> operations;
    operations.push_back(OperationFactory::create(ADD, 11, 33));
    operations.push_back(OperationFactory::create(SUB, 15, 20));
    operations.push_back(OperationFactory::create(MULTIPLY, 3, 6));
    operations.push_back(OperationFactory::create(DIV, 10, 2));

    ofstream saveFile("wyniki.csv");

    if (saveFile.is_open())
    {
        saveFile << "Wynik ; Operacja\n";

        for (const auto& operation : operations)
        {
            saveFile << operation->Proceed() << ";" << operation->GetClassName() << "\n";
        }

        saveFile.close();
    }
    else
    {
        cout << "Problem z otwarciem pliku!" << endl;
    }
}
