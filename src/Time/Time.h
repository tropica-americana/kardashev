#ifndef TIME
#define TIME
#include <iostream>
#include <cmath>
#include <numbers>
#include <random>
  
class Time {
    public:
     size_t time ;
     size_t timeElapsedInTheBLock = 0  ; 
    void updateTime () {
        time = static_cast <size_t> (SDL_GetTicks64() ) ; 

    }
    size_t calculateTimeElapsedSinceLastTimeUpdated() {
        size_t time1 = time ; 
        size_t time2 = SDL_GetTicks64 () ; 
        return time2 - time1 ;  
    }
    size_t calculateTimeElapsedAndUpdateTime () {
        
        size_t time =  calculateTimeElapsedSinceLastTimeUpdated() ; 
        timeElapsedInTheBLock = time ; 
        updateTime() ; 
        return time ; 
    }
    void outputTimeElapsed ( std::string nameOfTheBlock ) {
        std::cout << "time elapsed in block "<<nameOfTheBlock << " is " << timeElapsedInTheBLock << std:: endl ; 
    }
 

}; 

#endif