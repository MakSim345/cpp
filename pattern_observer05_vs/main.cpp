#include "gen.h"
#include "ObserverIf.h"

// int StockObserver::observerIDTracker = 1;

class GrabStocks
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make Observer\n";

        StockGrabber* stockGrabber = new StockGrabber();
        
        //
        StockObserver* obs1 = new StockObserver(stockGrabber);
        
        stockGrabber->setAPPLEPrice(197.00);
        stockGrabber->setIBMPrice(677.00);
        stockGrabber->setGOOGPrice(676.00);

        StockObserver* obs2 = new StockObserver(stockGrabber);
        
        return 0;
    }

    ~GrabStocks()
    {
        std::cout << "\nGood bye!\n";
    }

};

int main()
{
    std::auto_ptr <GrabStocks> my_observer(new GrabStocks());
    
    try
    {
        my_observer->Run();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER has number - " << EXCEPTION_EXECUTE_HANDLER << "\n";
    }    
    */
    system("PAUSE");
    return 1;
}
