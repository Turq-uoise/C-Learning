#include <stdio.h>

double convert(double a, int b){
    if (b){
        return (a * 1.8) + 32.0;
    }
    else{
        return (a - 273.15);
    }
    
}


int main(void){
    double celsius = 5;
    // 0 to convert to kelvin, 1 to convert to fahrenheit
    printf("%f\n", convert(celsius, 0));
    printf("%f\n", convert(celsius, 1));
    return 0;
}