#ifndef _mathermatical_layer_h_
#define _mathermatical_layer_h_
#define _USE_MATH_DEFINES

/*
    we will use functional programming
    everything maathermaticlal will be performed here . 
    we will only use the metrics system and the conversion to the screen funtions in the seperate functions but our code will be much more organized this way 
    we will use the shortcuts name of the function and the reasson why the function exists will be mentioned 
    in the comments 
    any thing that voilates the current principles will be removed as soon as it is entered 
    this is the main cpp where the functions will be designed and then manufactured to the daughter cpps 
    the SI units are mandatory 
*/
 
#include <iostream> 
#include <cmath> 
#include <vector>
#include <time.h> 
#include <math.h>
using std::cout ;  
using std::endl ; 
/*
    this funciton calculates the current value of the wave as a function of time , position in the x y and z axis , 
     amplitude and the frequency of the waves and also takes in to the account the phase of the wave ; 
*/ 
float moduloF ( float one , float two ) {
	if (one < two ) {
		return one ;  

	}; 
	while (one > two ) {
		one -= two ;  
	}; 
	std::cout  << one << std::endl ; 
	return one ; 
}


float CWA( /* point of oring */ float xo , float yo , float zo ,  /* point of interpretion */ float x , float y , float z  , float wavelength , float amplitude , float frequency , float time  ) {
        // calcualting the distance between two points 
        float distance ; 
	float xdif = x - xo ;  
	float ydif = y - yo ; 
	float zdif = z - zo ; 
        distance = std::sqrt ( (xdif * xdif ) + (ydif * ydif ) + (zdif * zdif ) ) ; 
	if ( distance < 0 ) 
		distance = -distance ; 
	// code below calcualtes the phase of the wave as a function off time ; 
	float pi = M_PI ;  
	// checking if the wave has reached the point 
	bool wavereached = true  ; float velocity ; velocity = wavelength * frequency ; 
	if ( distance > velocity * time ) wavereached = false ; 
	if( wavereached == false ) {

		return 0 ;
	}  
	 
	float distancePhase ; distancePhase = (velocity * time ) - distance ; 
	float phase ; phase = 2 * pi * ( moduloF(distancePhase ,  wavelength) / wavelength )  ; 
	float cwa = amplitude * sin ( phase )  ; 
	return cwa ; 
} 
void sample()
{
	CWA ( 0 , 0 , 0 , 20 , 2000 , 20 , 100 , 1000 , 1000 , 24 ) ;  
}

#endif