#ifndef RANDOM_CPP
#define RANDOM_CPP
#include <random>
#include <iostream>
#include <cmath>
#include <numbers>

class Random {
public : 
    float getRandomFloatInRange(float minFloat, float maxFloat) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(minFloat, maxFloat);
        float randomValue = dis(gen);
        return randomValue;
    }
    float getRandomFloatInRangeIncludingNegativeValues ( float minFloat , float maxFloat ) {
        float randomValue = getRandomFloatInRange ( minFloat , maxFloat ) ;
        float randomSign = getRandomFloatInRange ( -1 , 1 ) ;
        float multiplier = 1 ;
        if ( randomSign < 0 ) {
            multiplier = -1 ;
        }
        randomValue *= multiplier ;
        return randomValue ;
    }
	
};

#endif
