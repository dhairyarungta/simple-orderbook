#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "hftlob.h"


void balanceBranch(Limit*limit)
{

    int balanceFactor = getBalanceFactor(limit);
    if(balanceFactor>1)
    {
        balanceFactor =getbalanceFactor(limit->rightChild);
        if(balanceFactor<0)
        {
            rotateRightLeft(limit);
        }else if(balanceFactor>0)
        {
            rotateRightRight(limit);
        }

    }else if(balanceFactor<-1)
    {
        balanceFactor = getBalanceFactor(limit->leftChild);
        if(balanceFactor<0)
        {
            rotateLeftLeft(limit);
        }else if(balanceFactor>0)
        {
            rotateLeftRight(limit);
        }
    
    }else
    {
        //tree is balanced
        ;
    }


}


void rotateLeftLeft(Limit* limit)
{
    Limit*child = limit->leftChild;
    if(limitIsRoot(limit->parent)==1 || (limit->limitPrice > limit->parent->limitPrice))
    {
        limit->parent->rightChild = child;

    }else 
    {
        limit->parent->leftChild = child;

    }
    child->parent = limit->parent;
    limit->parent = child;
    Limit*tmp_ptr = child->rightChild;
    child->rightChild = limit;
    limit->leftChild = tmp_ptr;
    return ;
}

void rotateRightRight(Limit* limit)
{
    Limit* child = limit->rightChild;
    if(limitIsRoot(limit->parent)==1 || (limit->limitPrice>limit->parent->limitPrice))
    {
        limit->parent->rightChild = child;

    }else
    {
        limit->parent->leftChild = child;
    }
    child->parent = limit->parent;
    limit->parent = child ;
    Limit*tmp_ptr = child->leftChild;
    child->leftChild= limit;
    limit->rightChild = tmp_ptr;
    return ;

}

void rotateLeftRight(Limit* limit)
{
    Limit*child = limit->leftChild;
    Limit*grandChild = limit->leftChild->rightChild;

    child->parent =grandChild;
    grandChild->parent = limit;

    Limit*tmp_b_ptr = child->leftChild;
    Limit*tmp_c_ptr = grandChild->leftChild;
    Limit*tmp_d_ptr = grandChild->rightChild;

    child->rightChild = grandChild->leftChild;
    limit->leftChild = grandChild;
    grandChild->leftChild = child;
    grandChild->rightChild =tmp_d_ptr;
    child->leftChild = tmp_b_ptr ;
    child->rightChild = tmp_c_ptr;
    rotateLeftLeft(limit);
    return;

}

void rotateRightLeft(Limit* limit)
{

    Limit*child = limit->rightChild;
    Limit*grandChild = limit->rightChild->leftChild;
    child->parent  = grandChild;
    grandChild->parent= limit;

    Limit*tmp_b_ptr = child->rightChild;
    Limit*tmp_c_ptr = grandChild->rightChild;
    Limit*tmp_d_ptr = grandChild->leftChild;

    limit->rightChild = grandChild;
    grandChild->rightChild  = child;
    grandChild->leftChild = tmp_d_ptr;
    child->leftChild = tmp_c_ptr;
    child->rightChild = tmp_b_ptr;
    rotateRightRight(limit);
    return;

}