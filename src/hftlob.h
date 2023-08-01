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
    double limitPrice ;
    double size ;
    double totalVolume;
    int orderCount ;
    struct Limit*parent ;
    struct Limit*leftChild;
    struct Limit* rightChild ;
    struct Order* headOrder;
    struct Order* tailOrder;

}Limit ;

typedef struct QueueItem
{
    Limit *limit ;
    struct QueueItem *previous ;
}QueueItem;

typedef struct Queue
{
    int size ;
    QueueItem *head ;
    QueueItem *tail;

}Queue;


void initOrder(Order*order);

void initQueueItem(QueueItem* item)

void initLimit(Limit *limit);

void initQueue(Queue*q);



void pushToQueue(Queue*q, Limit*limit);

Limit* popFromQueue(Queue*q);

int queueIsEmpty(Queue *q);



int pushOrder(Limit*limit, Order*new_order);

Order* popOrder(Limit*limit);

int removeOrder(Order* order);



Limit* createRoot(void);

int addNewLimit(Limit*root, Limit* limit);

void replaceLimitInParent (Limit* limit, Limit* newLimit);

int removeLimit(Limit* limit);



void balanceBranch(Limit*limit);

void rotateLeftLeft(Limit* limit);

void rotateLeftRight(Limit *limit);

void rotateRightRight(Limit* limit);

void rotateRightLeft(Limit*limit);


int limitExists(Limit*root, Limit*limit);

int limitIsRoot(Limit* limit);

int hasGrandpa(Limit* limit);

int getGrandpa(Limit* limit);

int getMinimumLimit(Limit* limit);

int getMaximumLimit(Limit* limit);

int getHeight(Limit* limit);

int getBalanceFactor (Limit* limit);

void copyLimit(Limit*ptr_src, Limit*ptr_target);

void RunAllTests();


#endif