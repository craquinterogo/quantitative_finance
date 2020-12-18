#include "European.h"
#include <math.h>
#include <boost/math/distributions/normal.hpp>
#include <iostream>

using boost::math::normal;
using std::cout; using std::cin;  using std::endl;

European::European(float S, float K, float rf, float sigma, float T, int psi) {
	this->S = S;
	this->K = K;
	this->rf = rf;
	this->sigma = sigma;
	this->T = T;
	this->d1 = NULL;
	this->d2 = NULL;
	this->psi = psi;
}

void European::calculate_d1() {
	d1 = (float) (log(S / K) + (rf + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
}

void European::calculate_d2() {
	d2 = d1 - sigma * sqrt(T);
}

double European::valuation() {
	calculate_d1();
	calculate_d2();
	normal s;
	double option_price = ((double) psi * S * cdf(s, psi * d1)) - ((double) psi * K * exp(-rf *T) * cdf(s, psi * d2));
	return option_price;
}

int main() {
	double S, K, rf, T, sigma;
	int psi;

	S = 10;
	K = 11;
	rf = 0.01;
	sigma = 0.03;
	T = 1;
	psi = 1;

	cout << "CALL OPTION" << endl;
	cout << "---------------------" << endl;
	European eur_option_call = European(S, K, rf, sigma, T, psi);
	cout << "Option Value :: " << eur_option_call.valuation()<<endl;
	cout << "======================" << endl;
	cout << endl;

	cout << "PUT OPTION" << endl;
	cout << "---------------------" << endl;
	European eur_option_put = European(S, K, rf, sigma, T, -1*psi);
	cout << "Option Value :: " << eur_option_put.valuation() << endl;
	cout << "======================" << endl;
	cout << endl;

	system("pause");
	return 0;
}