#ifndef onlineshoppingfacade_h__
#define onlineshoppingfacade_h__

#include "gen.h"

#include "Courier.h"
#include "Vendor.h"
#include "OrderingTeam.h"
#include "OnlineShoppingFacade.h"

class OnlineShoppingFacade
{
private:
    enum States
    {  Received, SubmittedToOrderTeam, SubmittedToVendor, SubmittedToCourier };

    int _state;
    int _count;

    OrderingTeam _order;
    Vendor _vendor;
    Courier _courier;

public:
    OnlineShoppingFacade() {  _count = 0; }
    
    void submitRequest() { _state = 0; }
    
    bool checkStatus()
    {
        /* Item request has just been received */
        switch(_state)
        {
            case Received:
                _state++;
                /* Forward the job request to the ordering team */
                _order.submitRequestToOrderTeam();
                std::cout << "submitted to Order Team - " << _count << " followups till now" << std::endl;
                break;
            case SubmittedToOrderTeam:
                /* If order team has completed verification, 
                place the request with vendor */
                if (_order.checkStatus())
                {
                    _state++;
                    _vendor.submitRequestToVendor();
                    std::cout << "submitted to Vendor - " << _count <<
                    " followups till now" << std::endl;
                }
                break;
            case SubmittedToVendor:
            /* If vendor has packed the item, forward it to courier */
                if (_vendor.checkStatus())
                {
                    _state++;
                    _courier.submitRequestToCourier();
                    std::cout << "submitted to Courier - " << _count <<
                    " followups till now" << std::endl;
                }
                break;
            case SubmittedToCourier:
            /* If package is delivered, order is complete */
                if (_courier.checkStatus())
                    return 1;
            default:
                break;
  }
  
  _count++;  
  /* The order is not complete */
  return 0;
}

int numFUPs() {return _count;}
};

#endif // onlineshoppingfacade_h__