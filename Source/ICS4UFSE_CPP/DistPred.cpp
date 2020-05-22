// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "DistPred.h"

DistPred::~DistPred()
{
    // Destructor doesn't need to do anything
}

// For comparing dists to specific pos
bool DistPred::operator ()(const AActor& x, const AActor& y)const
{
    return (x.GetActorLocation() - BasePos).Size() < (y.GetActorLocation() - BasePos).Size();
}