
#include <math.h>
#include<assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "hftlob.h"

int pushOrder(Limit*limit, Order*newOrder)
{
    if(limit->limitPrice != newOrder->limit)
    {
        return 0;
    }

    newOrder->parentLimit = limit;
    newOrder->nextOrder = limit->headOrder; 
    newOrder->prevOrder = NULL;
    
    if(limit->headOrder!= NULL){
        limit->headOrder->prevOrder= newOrder;

    }else 
    {
        limit->tailOrder = newOrder;
    }

    limit->headOrder = newOrder;
    limit->orderCount++;
    limit->totalVolume+=(newOrder->shares)*(limit->limitPrice);
    limit->size+=newOrder->shares;
    return 1;

}

Order* popOrder(Limit *limit)
{
    if(limit->tailOrder==NULL)
    {
        return NULL; //
    }
    Order*ptr_poppedOrder = limit->tailOrder;

    if(limit->tailOrder == limit->headOrder)
    {
        limit->headOrder = NULL; //
        limit->tailOrder = NULL; //
        limit->orderCount=0;
        limit->size = 0;
        limit->totalVolume =0 ;
        //TODO: remove limit node from the AVL tree
    }else
    {
        limit->tailOrder = limit->tailOrder->prevOrder;
        limit->tailOrder->nextOrder = NULL;
        limit->orderCount --;
        limit->size -=ptr_poppedOrder->shares;
        limit->totalVolume-=(ptr_poppedOrder->shares)*(limit->limitPrice);

    }
    
    return ptr_poppedOrder;
}


int removeOrder(Order*order)
{
    // if(order->parentLimit->headOrder==order && order->parentLimit->tailOrder == order) 
    if (order->prevOrder == NULL && order->nextOrder == NULL)
    {
        order->parentLimit->headOrder = NULL;
        order->parentLimit->tailOrder = NULL;
        //TODO: cleaup parent limit by removing limit node fromt the AVL tree


    } else if (order->prevOrder!=NULL && order->nextOrder!=NULL)
    {
        order->prevOrder->nextOrder = order->nextOrder;
        order->nextOrder->prevOrder = order->prevOrder;

    }else if (order->prevOrder!=NULL && order->nextOrder==NULL)
    {
        //tail order
        order->prevOrder->nextOrder= NULL;
        order->parentLimit->tailOrder = order->prevOrder;


    }else if(order->prevOrder== NULL && order->nextOrder!=NULL)
    {
        //headorder
        order->parentLimit->headOrder = order->nextOrder;
        order->nextOrder->prevOrder= NULL;

    }else
    {
        return -1;
    }

    return 1;




}