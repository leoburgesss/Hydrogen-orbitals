#include <cmath>
#include <complex>

constexpr double pi = 3.141592653589793;

double factorial(int n){
  double f = 1;
  for(int i{2}; i<=n; ++i){f*= i;}
  return f;
}

double lnFactorial(int n){
  return std::lgamma(n + 1);
}

double associatedLaguerre(int k, int alpha, double x){
  if (k == 0){return 1;}
  if (k == 1){return 1 + alpha -x;}
  double Lkm1 = 1;
  double Lk = 1 + alpha -  x;
  for(int i{1}; i<k; ++i){
    double Lkp1 = ((2.0*i + 1.0 + alpha - x) * Lk
                       - (i + alpha) * Lkm1) / (i + 1.0);
    Lkm1 = Lk;
    Lk = Lkp1;
  }
  return Lk;
}

double associatedLegendre(int l, int m, double x){
  if(m>l){return 0;}
  
  double pmm = 1;
  if(m>0){
    double somx2 = std::sqrt((1.0 - x) * (1.0 + x));
    double fact = 1;
    for(int i{1}; i<=m; i++){
      pmm *= -fact * somx2;
      fact += 2;
    }
  }

  if (l==m){return pmm;}

  double pmmp1 = x*(2 * m + 1) * pmm;
  if (l==m+1){return pmmp1;}

  double pll = 0.0;
  for (int ll = m + 2; ll <= l; ++ll) {
      pll = ((2.0*ll - 1.0)*x*pmmp1 - (ll + m - 1.0)*pmm) / (ll - m);
      pmm   = pmmp1;
      pmmp1 = pll;
    }
  return pll;

}

double radialR(int n, int l, double r){
  double rho = 2.0*r/n;
  double lnN = 1.5*std::log(2.0/n) + 0.5*(lnFactorial(n - l - 1) - std::log(2.0*n) - lnFactorial(n + l));
  double L = associatedLaguerre(n - l - 1, 2*l + 1, rho);
  return std::exp(lnN) * std::pow(rho, l) * std::exp(-rho/2.0) * L;
}

double angularY(int l, int m, double theta){
  int am = std::abs(m);
  double lnN = 0.5*(std::log((2.0*l + 1.0)/(4.0*pi))+ lnFactorial(l - am) - lnFactorial(l + am));
  double p = associatedLegendre(l, am, std::cos(theta));
  return std::exp(2*lnN) * p*p;
}

double probDensity(int n, int l, int m, double r, double theta) {
    double R = radialR(n, l, r); 
    return R*R * angularY(l, m, theta);
}
