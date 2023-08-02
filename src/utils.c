#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "hftlob.h"


void initOrder(Order*order)
{
    order->tid = NULL;
    order->buyOrSell = -1;
    order->shares = 0;
    order->limit = 0;
    order->entryTime =0 ;
    order->eventTime = 0;
    order->nextOrder = NULL;
    order->prevOrder = NULL;
    order->parentLimit = NULL;
    order->exchangeId = 0;

}

void initLimit(Limit* limit)
{
    limit->limitPrice = 0;
    limit->size = 0;
    limit->totalVolume = 0;
    limit->orderCount =0 ;
    limit->parent = NULL;
    limit->leftChild = NULL;
    limit->rightChild = NULL;
    limit->headOrder = NULL;
    limit->tailOrder = NULL;

}

void initQueueItem (QueueItem* item)
{
    item->limit = NULL;
    item->previous = NULL;
}
void initQueue(Queue*q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}


int limitExists(Limit* root , Limit *limit)
{
    if(root->parent == NULL && root->rightChild==NULL)
    {
        return 0;
    }

    Limit*currentLimit = root;
    while(currentLimit->limitPrice!=limit->limitPrice)
    {
        if(currentLimit->leftChild==NULL && currentLimit->rightChild==NULL)
        {
            return 0;
        }
        else
        {
            if(currentLimit->rightChild!= NULL && currentLimit->limitPrice<limit->limitPrice)
            {
                currentLimit = currentLimit->rightChild;
            }
            else if(currentLimit->leftChild!=NULL && currentLimit->limitPrice>limit->limitPrice)
            {
                currentLimit = currentLimit->leftChild;
            }else 
            {
                return -1;
            }
            continue;
        }
        

    }
    return 1;
}

int limitIsRoot(Limit* limit)
{
    if(limit->parent = NULL)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int hasGrandpa(Limit* limit)
{
    if(limit->parent!=NULL && limit->parent->parent!= NULL)
    {
        return 1;
    }else 
    {
        return 0;
    }


}

Limit* getGrandpa(Limit*limit)
{
    if(hasGrandpa(limit))
    {
        return limit->parent->parent;

    }
    return NULL;
}

Limit* getMinimumLimit(Limit* limit)
{
    Limit *ptr_minimum;
    if(limitIsRoot(limit)){
        ptr_minimum = limit->rightChild;
    }
    else{
        ptr_minimum = limit;
    }//the above section check again
    
    Limit* ptr_minimum = limit;

    while(ptr_minimum->leftChild!=NULL)
    {
        ptr_minimum = ptr_minimum->leftChild;
    }
    return ptr_minimum;

}


Limit*getMaximumLimit(Limit* limit)
{
    
    Limit* ptr_maximum = limit;
    while(ptr_maximum->rightChild!=NULL)
    {
        ptr_maximum = ptr_maximum->rightChild;
    }
    return (ptr_maximum);
}


int getBalanceFactor(Limit* limit)
{
    int leftHeight = -1;
    int rightHeight = -1;
    if (limit->rightChild!=NULL)
    {
        rightHeight = getHeight(limit->rightChild);
    }
    if(limit->leftChild!=NULL)
    {
        leftHeight = getHeight(limit->leftChild);
    }

    return rightHeight -leftHeight;

}


void copyLimit(Limit*ptr_src, Limit* ptr_tar)
{
    ptr_tar->limitPrice = ptr_src->limitPrice;
    ptr_tar->size = ptr_src->size;
    ptr_tar->totalVolume = ptr_src->totalVolume;
    ptr_tar->orderCount = ptr_src->orderCount;
    ptr_tar->headOrder = ptr_src->headOrder;
    ptr_tar->tailOrder = ptr_src->tailOrder;
    
    Order* ptr_order = ptr_tar->headOrder;
    while (ptr_order!=NULL)
    {
        ptr_order->parentLimit = ptr_tar;
        if(ptr_order!=NULL)
        {
            ptr_order = ptr_order->nextOrder;
        }
    }
}


int getHeight(Limit* limit)
{
    if(limit == NULL)
    {
        return -1;
    }

    int height = -1;
    int qsize = 0;

    Queue *ptr_queue = malloc(sizeof(Queue));
    initQueue(ptr_queue);
    Limit*ptr_current;
    pushToQueue(ptr_queue,limit);
    while(1)
    {
        qsize = ptr_queue->size;
        if(qsize==0)
        {
            break;
        }

        height++;
        while(qsize>0)
        {
            ptr_current = popFromQueue(ptr_queue);
            if(ptr_current->leftChild!=NULL)
            {
                pushToQueue(ptr_queue, ptr_current->leftChild);
            }
            if(ptr_current->rightChild!=NULL)
            {
                pushToQueue(ptr_queue, ptr_current->rightChild);
            }
            qsize--;
        }
    }
    free(ptr_queue);
    return height;
}

//queue functions


void pushToQueue(Queue *q, Limit* limit)
{
    QueueItem* ptr_newItem = malloc(sizeof(QueueItem));
    ptr_newItem->limit = limit;
    if(q->head != NULL)
    {
        q->head->previous = ptr_newItem;
    }
    q->head = ptr_newItem;
    q->size++;
}


Limit* popFromQueue(Queue* q)
{
    if(q->head==NULL) 
    {
        return NULL;
    }

    QueueItem* poppedItem = q->tail;
    Limit*poppedLimit = q->tail->limit;
    q->tail = q->tail->previous;
    if(q->tail==NULL)
    {
        q->head = NULL;
    }
    q->size--;
    return poppedLimit;
}

int queueIsEmpty(Queue* q)
{
    if(q->head==NULL)
    {
        return 1;
    }
    return 0;
}