#include <iostream>

class Function{
    static int next_uid_;
    const int id_;

    public:
        Function(): id_(next_uid_++){};

        virtual double Evaluate(double x) const = 0;
        virtual void Solve(std::ostream& os) = 0;
        virtual void PrintEquation(std::ostream& os) const = 0;

        virtual ~Function() {};

        int GetID(){return id_;};

};
int Function::next_uid_ = 1;

class LinearFunction: public Function{
    double a_, b_;
    public:
        LinearFunction(double a, double b): a_(a), b_(b){};
        double GetA(){return a_;};
        double GetB(){return b_;};

        double Evaluate(double x) const override{}
        void Solve(std::ostream& os) override{}
        void PrintEquation(std::ostream& os) const override{}

};

class QuadraticFunction: public Function{
    double a_, b_, c_;
    public:
        QuadraticFunction(double a, double b, double c): a_(a), b_(b), c_(c){};
        double GetA(){return a_;};
        double GetB(){return b_;};
        double GetC(){return c_;};

        double Evaluate(double x) const override{}
        void Solve(std::ostream& os) override{}
        void PrintEquation(std::ostream& os) const override{}
};
