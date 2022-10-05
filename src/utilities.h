#ifndef utlities_h
#define utlities_h

// CLAMP a value between the lower and upper limit
template <typename T> T CLAMP(const T& value, const T& low, const T& high) 
{
  return value < low ? low : (value > high ? high : value); 
}

#endif