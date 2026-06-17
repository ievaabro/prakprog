#include <iostream>
#include <cmath>
#include <fstream>
#include "vec.h"


// Binær søgning: her bliver i fundet så x[i] <= z <= x[i+1]

int binsearch(const vector& x, double z)
	{/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1] );
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
	}

// Lineær interpolation ved punkt z

double linterp(const vector& x, const vector& y, double z){
	int i=binsearch(x,z);
  	double dx=x[i+1]-x[i];
  	assert(dx>0);
  	double dy=y[i+1]-y[i];
  	return y[i]+dy/dx*(z-x[i]);
  	}

// Integral a lineær spline fra x[0] til z

double linterpInteg(const vector& x, const vector& y, double z) {
    assert(z >= x[0] && z <= x[x.size()-1]);
    
    int i = binsearch(x, z);
    double integral = 0;
    
    // Summer bidrag fra alle hele intervaller før interval i
    for (int k = 0; k < i; k++) {
        double dx = x[k+1] - x[k];
        double y_avg = (y[k] + y[k+1]) / 2.0;  // Middelværdi af y i intervallet
        integral += y_avg * dx;  // Trapez-areal
    }
    
    // Tilføj bidrag fra det sidste delvise interval [x[i], z]
    double dx = x[i+1] - x[i];
    double dy = y[i+1] - y[i];
    double slope = dy / dx;
    double dz = z - x[i];
    
    // Integral af y[i] + slope*(t - x[i]) fra x[i] til z
    // = y[i]*dz + slope*dz²/2
    integral += y[i] * dz + slope * dz * dz / 2.0;
    
    return integral;
}
