// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Utility for calculating distances

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * 
 */
class ICS4UFSE_CPP_API DistPred
{
    FVector BasePos;
public:

    // For constructing the vector
    template<typename...Args>
    DistPred(Args&&...args)
    {
        BasePos = FVector(args...);
    }

    // Destructor doesn't need to do anything
	~DistPred();

    // For comparing dists to a specific pos
    bool operator ()(const AActor& x, const AActor& y)const;

};
