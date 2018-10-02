#include "gen.h"

inline float cube(const float s) {return s*s*s;}

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world!\n";
        return 0;
    }
    ~App()
    {
        std::cout << "Good bye!\n";
    }

};

class MonteCarloSimulator
{
public:
    MonteCarloSimulator()
    {
        std::cout << "Hello! Monte Carlo Simulator online\n";
    }
    ~MonteCarloSimulator()
    {
        std::cout << "Good bye!\n";
    }
    
    double getRandomValue()
    {
        return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    }

    int run()
    {
        srand(time(NULL));
        cout.precision(10);
        const int nNumberTotal[] = {1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9};
        // const int nNumberTotal[] = {1e3};
        const float fRadius = 1.0;

        for (int j = 0; j < (sizeof(nNumberTotal) / sizeof(nNumberTotal[0])); j ++)
        {
            int dotsInCircle = 0;
            for (int i = 0; i < nNumberTotal[j]; i ++)
            {
                double x = getRandomValue();
                double y = getRandomValue();

                //cout << " x=" << x;
                //cout << " y=" << y;

                if ((x*x + y*y) <= fRadius)
                {
                    dotsInCircle++;
                }
            }

            cout << nNumberTotal[j] << (char)9 << (char)9 << (double)dotsInCircle / nNumberTotal[j] * 4.0 << endl;
        }
        /*
        std::cout << "Enter cube dimention: ";
        std::cin >> side;

        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";

        cout << "Cube with side " << side << " is equal to " << calculation(side) << "\n";

        long b = std::clock();

        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
        */
        return 1;
    }

private:
    float side;

    float calculation(float s)
    {
        return s*s*s;
    }

};

int main()
{
    std::auto_ptr <MonteCarloSimulator> cube_calc(new MonteCarloSimulator());
    cube_calc->run();

    printf ("Application complete.\n");
    system ("PAUSE");

    return 1;
}
