#include <iostream>
#include <math.h>
#include <cmath>
#include "Options.h"

using std::cout; using std::cin;  using std::endl;

double quantero::N(const double x, double mu, double sigma){
	return 0.5*(1+std::erf((x-mu)/(sigma*std::sqrt(2))));
}

quantero::European::European(float S, float K, float rf, float sigma, float T, int psi) :
	S(S), K(K), rf(rf), sigma(sigma), T(T), psi(psi)
{
	this->d1 = 0;
	this->d2 = 0;
}

void quantero::European::calculate_d1() {
	d1 = (float) (log(S / K) + (rf + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
}

void quantero::European::calculate_d2() {
	d2 = d1 - sigma * sqrt(T);
}

double quantero::European::valuation() {
	calculate_d1();
	calculate_d2();
	auto cdf = [](double dx){return N(dx,0,1);};
	double option_price = ((double) psi * S * cdf(psi * d1)) - ((double) psi * K * exp(-rf *T) * cdf(psi * d2));
	return option_price;
}
