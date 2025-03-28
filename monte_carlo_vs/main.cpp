#include "gen.h"

class MonteCarloSimulator
{
public:
    MonteCarloSimulator()
    {
        std::cout << "Hello! Monte Carlo Simulator started!\n";
    }
    ~MonteCarloSimulator()
    {
        std::cout << "Good bye!\n";
    }

    double getRandomValue()
    {
        return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    }

    double getRandomNumber()
    {
        // Create a random device and use it to seed the random number generator
        std::random_device rd;
        std::mt19937 gen(rd()); // Mersenne Twister engine

        std::uniform_int_distribution<> distr(1, RAND_MAX);

        return distr(gen) / static_cast<double>(RAND_MAX); // Generate and return the random number

    }

    int run()
    {
        srand(time(NULL));
        cout.precision(10);
        // const int nNumberTotal[] = {1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9};
        const double nNumberTotal[] = {1e3, 1e4, 1e5};
        const float fRadius = 1.0;

        for (int j = 0; j < (sizeof(nNumberTotal) / sizeof(nNumberTotal[0])); j ++)
        {
            // startTimeM = std::clock();
            auto iterationStart = std::chrono::high_resolution_clock::now();
            // std::cout << "Time Start: " << startTimeM << "\n";

            int dotsInCircle = 0;
            for (int i = 0; i < nNumberTotal[j]; i ++)
            {
                //calcXvalM = getRandomValue();
                //calcYvalM = getRandomValue();

                calcXvalM = getRandomNumber();
                calcYvalM = getRandomNumber();

                //cout << " x=" << calcXvalM;
                //cout << " y=" << calcYvalM;

                if ((calcXvalM*calcXvalM + calcYvalM*calcYvalM) <= fRadius)
                {
                    dotsInCircle++;
                }
            }

            cout << "For " << nNumberTotal[j] << " iterations PI =" << (char)9 << (double)dotsInCircle / nNumberTotal[j] * 4.0 << endl;
            auto stopTimeM = std::chrono::high_resolution_clock::now();

            // std::cout << "Time END: " << stopTimeM << "\n";
            // std::cout << "Time to calculate: " << (stopTimeM - startTimeM)/1000.0 << " sec.\n\n";
            // End measuring time for this iteration
            auto iterationEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> iterationDuration = iterationEnd - iterationStart;

            // Output the time taken for this iteration
            std::cout << "Iteration " << j  + 1 << " took " << iterationDuration.count() << " ms" << std::endl;
            std::cout << std::endl;
        }

        return 1;
    }

private:
    //static auto startTimeM;
    //static auto stopTimeM;

    float calcXvalM;
    float calcYvalM;
};

int main()
{
    auto totalStart = std::chrono::high_resolution_clock::now();

    std::unique_ptr <MonteCarloSimulator> pi_calc(new MonteCarloSimulator());
    pi_calc->run();

    // Output the total runtime of the app:
    auto totalEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> totalDuration = totalEnd - totalStart;
    std::cout << "Total application runtime: " << totalDuration.count() << " ms" << std::endl;
    printf ("Application complete.\n");
    // system ("PAUSE");
    return 1;
}
