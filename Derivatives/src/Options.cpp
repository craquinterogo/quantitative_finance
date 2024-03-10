#include <iostream>
#include <math.h>
#include <boost/math/distributions/normal.hpp>
#include "Options.h"

// int main(){
// 	std::cout<<"Hello world!"<<std::endl;
// 	std::cout<<quantero::summing_numbers(1.0,2.0)<<std::endl;
// 	return 0;
// }

// float quantero::summing_numbers(float a, float b){
// 	return a + b;
// }

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
	quantero::European eur_option_call = quantero::European(S, K, rf, sigma, T, psi);
	cout << "Option Value :: " << eur_option_call.valuation()<<endl;
	cout << "======================" << endl;
	cout << endl;

	cout << "PUT OPTION" << endl;
	cout << "---------------------" << endl;
	quantero::European eur_option_put = quantero::European(S, K, rf, sigma, T, -1*psi);
	cout << "Option Value :: " << eur_option_put.valuation() << endl;
	cout << "======================" << endl;
	cout << endl;

	system("pause");
	return 0;
}