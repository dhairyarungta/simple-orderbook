#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "CuTest.h"
#include "hftlob.h"


Limit* createDummyLimit(float price)
{
    Limit*ptr_newLimit = malloc(sizeof(Limit));
    initLimit(ptr_newLimit);
    ptr_newLimit->limitPrice=price;
    return (ptr_newLimit);
}

Limit* createDummyTree(Limit* dummyA, Limit* dummyB, Limit* dummyC, Limit*dummyD)
{
    int statusCode = 0;
    Limit* ptr_root = createRoot();
    statusCode = addNewLimit(ptr_root, dummyA);
    assert(statusCode ==1);
    statusCode = addNewLimit(ptr_root, dummyB);
    assert(statusCode ==1);
    statusCode = addNewLimit(ptr_root, dummyC);
    assert(statusCode ==1);
    statusCode = addNewLimit(ptr_root, dummyD);
    assert(statusCode ==1);
    return (ptr_root);
}


void TestCreateDummyTest(CuTest*tc)
{

}


void TestOrderPushing(CuTest*tc)
{

}

void TestOrderPopping(CuTest*tc)
{

}
void TestRemoveOrder(CuTest*tc)
{

}

void TestCreateRoot(CuTest*tc)
{

}

void TestAddNewLimit(CuTest*tc)
{

}
void TestLimitExists(CuTest*tc)
{

}


void TestLimitIsRoot(CuTest*tc)
{

}
void TestHasGrandpa(CuTest*tc)
{

}


void TestGetGrandpa(CuTest*tc)
{

}




void TestGetMaximum(CuTest*tc)
{

}
void TestGetMinimumLimit(CuTest*tc)
{

}

void TestGetHeight(CuTest* tc)
{

}



void TestGetBalanceFactor(CuTest*tc)
{

}
void TestReplaceLimitParent(CuTest*tc)
{

}

void TestRemoveLimit(CuTest*tc)
{

}


void TestRotateLL(CuTest*tc)
{

}
void TestRotateLR(CuTest*tc)
{

}


void TestRotateRR(CuTest*tc)
{

}

void TestRotateRL(CuTest*tc)
{

}


void TestBalanceBranch(CuTest*tc)
{

}
CuSuite* HFTLobGetSuite(void)
{

}

CuSuite* HFTLobGetSuite();


void RunAllTest(void)
{
    CuString*output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddStatus(suite, HFTLobGetSuite());
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

}