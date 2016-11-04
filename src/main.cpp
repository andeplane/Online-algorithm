#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
using namespace std;

int main(int numArgs, char **args)
{
    long numRandoms = 1e10;
    double mu = 10;
    double sigma = 5;
    if(numArgs > 1) numRandoms = 1e8 * long(atoi(args[1]));
    if(numArgs > 2) mu= atof(args[2]);
    if(numArgs > 3) sigma = atof(args[3]);

    random_device rd;
    mt19937 gen(rd());

    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    normal_distribution<> d(mu, sigma);
    cout << "Will choose " << numRandoms << " random numbers" << endl;
    double sum = 0;
    double squaredSum = 0;
    double mean = 0;
    double M2 = 0;

    long nextPrint = 100;
    for(long n=1; n<=numRandoms; n++) {
        double x = d(gen);
        double delta = x - mean;
        mean += delta/n;
        M2 += delta*(x - mean);

        sum += x;
        squaredSum += x*x;
        if(n == nextPrint) {
            double EX = sum/n;
            double EXSquared = squaredSum/n;
            double VarX = EXSquared - EX*EX;

            double EX2 = mean;
            double VarX2 = (numRandoms < 2) ? numeric_limits<double>::quiet_NaN() : M2 / (numRandoms - 1);

            cout << "After " << n << " random numbers, we have EX=" << EX << ", Var(X)=" << VarX << " EXOnlineAlgorithm=" << EX2 << " VarXOnlineAlgorithm=" << VarX2 << endl;
            nextPrint *= 10;
        }
    }
}
