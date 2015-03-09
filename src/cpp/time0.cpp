#include <iostream>
#include "time0.h"

Time::Time(){             
    hours = minutes = 0;  
}                         
                          
Time::Time(int h, int m){ 
    hours = h;            
    minutes = m;          
}                         
                          
void Time::AddMin(int m){       
    minutes += m;         
    hours += minutes / 60;
    minutes = minutes % 60;   
}                        
                         
void Time::AddHr(int h){       
    hours += h;          
}                        
                         
void Time::Reset(int h, int m){
    hours = h;           
    minutes = m;         
}                        

Time Time::operator+ (const Time & t) const
{
    Time sum;
    sum.hours = t.hours + hours + (minutes + t.minutes) / 60;
    sum.minutes = (t.minutes + minutes) % 60;
    return sum;
}

void Time::Show() const
{
    std::cout << hours << " hours " << minutes << " minutes." << std::endl;
}

