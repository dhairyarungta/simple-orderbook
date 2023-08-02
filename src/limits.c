#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "hftlob.h"


Limit* createRoot(void)
{
    Limit*ptr_limit = malloc(sizeof(Limit));
    initLimit(ptr_limit);
    ptr_limit->limitPrice = -INFINITY;
    return ptr_limit;
}

int addNewLimit(Limit* root, Limit*limit)
{
    if(limitExists(root,limit)==1)
    {
        return 0;
    }
    limit->leftChild = NULL;
    limit->rightChild = NULL;

    Limit* currentLimit= root;
    Limit*child;
    while ((1))
    {
        if(currentLimit->limitPrice<limit->limitPrice)
        {
            if()
            {

            }else
            {
                currentLimit = currentLimit->rightChild;
            }    
        }else if()
        {

        }else 
        {
            break;
        }
    }
    return 0;
}


void replaceLimitInParent(Limit*limit, Limit*newLimit)
{
    if(limitIsRoot(limit)==0)//if(!limitIsRoot(limit)){}
    {
        if(limit==limit->parent->leftChild && limitIsRoot(limit->parent)==0)
        {
            limit->parent->leftChild = newLimit;
        }
        else 
        {
            limit->parent->rightChild = newLimit;
        }

    }
    if(newLimit!=NULL)
    {
        newLimit->parent = limit->parent;
    }
}


int removeLimit(Limit* limit)
{

}