#ifndef QUADRANT_H
#define QUADRANT_H
#include <iostream>
enum class Quadrant {
    positiveUpperRight , 
    positiveLowerRight , 
    positiveLowerLeft ,
    positiveUpperLeft , 
    negativeUpperRight , 
    negativeLowerRight , 
    negativeLowerLeft ,
    negativeUpperLeft 

};
enum class Axis {
    x , y ,z , negativeX , negativeY , negativeZ 
};
template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream,  const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
#endif // ! _QUADRANT_H_
