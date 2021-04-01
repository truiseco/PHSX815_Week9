// C++ Standard Library Includes
#include <iostream>

// ROOT Includes
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom2.h"
#include "TError.h"

// Directives and declarations for namespaces and namespace members
using std::exp, std::sin;

// Program-specific helper function declarations
/**
 * Identical string comparison function
 * param a: first string to be compared
 * param b: second string to be compared
 * return 1 if a & b are identical character-wise and in length, 0 otherwise
 */
double NeGauss(const double *x){
  const double t = (x[0] - 3.14159265);
  const double u = (x[1]);
  return -exp(-t*t-u*u);
}

int main(int argc, char** argv){

   ROOT::Math::Minimizer* minimum =
      ROOT::Math::Factory::CreateMinimizer();

   // set tolerance , etc...
   minimum->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2
   minimum->SetMaxIterations(10000);  // for GSL
   minimum->SetTolerance(0.001);
   minimum->SetPrintLevel(1);

   ROOT::Math::Functor f(&NeGauss,1);
   double step[2] = {0.01,0.01};

   double variable[2] = {0.0,0.0};

   minimum->SetFunction(f);
   minimum->SetVariable(0,"x",variable[0], step[0]);
   minimum->SetVariable(1,"y",variable[1], step[1]);
   minimum->Minimize();

   const double *xs = minimum->X();
   std::cout << "Minimum: f(" << xs[0] << "," << xs[1] << ") = "
             << minimum->MinValue()  << std::endl;

   if ( minimum->MinValue()  < 1.E-4  && f(xs) < 1.E-4)
      std::cout << "Minimizer converged to the right minimum" << std::endl;
   else {
      std::cout << "Minimizer failed to converge!" << std::endl;
      Error("NumericalMinimization","fail to converge");
   }

   return 0;
}
