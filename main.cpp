//CODE FOR INTERPOLATION OF DATA 
//IT ALSO DETERMINES BEHAVIOUR BEYOND ENDS OF ARRAY i.e : EXTRAPOLATION
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

//======================================================================

// Returns interpolated value at x from parallel arrays ( xData, yData )
//   Assumes that xData has at least two elements, is sorted and is strictly monotonic increasing
//   boolean argument extrapolate determines behaviour beyond ends of array (if needed)

double interpolate( vector<double> &xData, vector<double> &yData, double x, bool extrapolate )
{
   int size = xData.size();

   int i = 0;                                                                  // find left end of interval for interpolation
   if ( x >= xData[size - 2] )                                                 // special case: beyond right end
   {
      i = size - 2;
   }
   else
   {
      while ( x > xData[i+1] ) i++;
   }
   double xL = xData[i], yL = yData[i], xR = xData[i+1], yR = yData[i+1];      // points on either side (unless beyond ends)
   if ( !extrapolate )                                                         // if beyond ends of array and not extrapolating
   {
      if ( x < xL ) yR = yL;
      if ( x > xR ) yL = yR;
   }

   double dydx = ( yR - yL ) / ( xR - xL );                                    // gradient

   return yL + dydx * ( x - xL );                                              // linear interpolation
}

//======================================================================

int main()
{
   // Original data
   vector<double> xData = { 1, 5, 10, 15, 20 };
   vector<double> yData = { 0.3, 0.5, 0.8, 0.1, 0.14 };

   // Set up some points for interpolation in xVals
   const int NPTS = 20;
   vector<double> xVals, yVals;
   for ( int i = 1; i <= NPTS; i++ ) xVals.push_back( (double)i );

   // Interpolate
   for ( double x : xVals )
   {
      double y = interpolate( xData, yData, x, true );
      yVals.push_back( y );
   }

   // Output
   #define SP << fixed << setw( 15 ) << setprecision( 6 ) <<
   #define NL << '\n'
   cout << "Original data:\n";
   for ( int i = 0; i < xData.size(); i++ ) cout SP xData[i] SP yData[i] NL;
   cout << "\nInterpolated data:\n";
   for ( int i = 0; i < xVals.size(); i++ ) cout SP xVals[i] SP yVals[i] NL;
}
