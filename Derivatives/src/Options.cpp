#include <iostream>
#include <math.h>
#include <boost/math/distributions/normal.hpp>
#include "Options.h"

using boost::math::normal;
using std::cout; using std::cin;  using std::endl;

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
	normal s;
	double option_price = ((double) psi * S * cdf(s, psi * d1)) - ((double) psi * K * exp(-rf *T) * cdf(s, psi * d2));
	return option_price;
}
