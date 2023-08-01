#ifndef HFTLOB_H_
#define HFTLOB_H_


typedef struct Order
{
    char *tid ;
    unsigned buyOrSell;
    double shares;
    double limit;
    double entryTime ;
    double eventTime;
    struct Order *nextOrder;
    struct Order *prevOrder;
    struct Limit *parentLimit;
    int exchangeId;
    
}Order;



typedef struct Limit
{

}