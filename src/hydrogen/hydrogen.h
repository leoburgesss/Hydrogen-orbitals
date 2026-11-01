#pragma once
namespace hydrogen{
  
double radialR(int n, int l, double r);
double angularY(int l, int m, double theta);
double probDensity(int n, int l, int m, double r, double theta);
std::vector<float> densityCloud(double probabilityCutoff, int n, int l, int m, int N, double extent);
}
