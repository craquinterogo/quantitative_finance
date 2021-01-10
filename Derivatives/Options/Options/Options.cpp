#include "Options.h"
#include <math.h>
#include <boost/math/distributions/normal.hpp>
#include <iostream>
#include <exception>

using boost::math::normal;
using std::cout; using std::cin;  using std::endl;

struct OptionException : std::exception {
	const char* what() const throw() {
		return "Sorry!, you are throwing an error in Option class ... what will be it?. Take a view in Options.cpp";
	}
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi>::Option(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi) :
	S(S), K(K), rf(rf), sigma(sigma), T(T), psi(psi)
{
	cout << "Constructor" << endl;
}

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
European<type_S, type_K, type_rf, type_sigma, type_T, type_psi>::European(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi) :
	Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi>(S, K, rf, sigma, T, psi)
{
	d1 = NULL;
	d2 = NULL;
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
void European<type_S, type_K, type_rf, type_sigma, type_T, type_psi>::calculate_d1() {
	d1 = (float)(log(this->S / this->K) + (this->rf + 0.5 * this->sigma * this->sigma) * this->T) / (this->sigma * sqrt(this->T));
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
void European<type_S, type_K, type_rf, type_sigma, type_T, type_psi>::calculate_d2() {
	d2 = d1 - this->sigma * sqrt(this->T);
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
double European<type_S, type_K, type_rf, type_sigma, type_T, type_psi>::valuation() {
	calculate_d1();
	calculate_d2();
	normal s;
	double option_price = ((double)this->psi * this->S * cdf(s, this->psi * d1)) - ((double)this->psi * this->K * exp(-this->rf * this->T) * cdf(s, this->psi * this->d2));
	return option_price;
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
American<type_S, type_K, type_rf, type_sigma, type_T, type_psi>::American(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi) :
	Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi>(S, K, rf, sigma, T, psi)
{
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
double American<type_S, type_K, type_rf, type_sigma, type_T, type_psi>::valuation(){
};

int main() {
	double S, K, rf, T, sigma;
	int psi;
	try {
		S = 10;
		K = 11;
		rf = 0.01;
		sigma = 0.03;
		T = 1;
		psi = 1;

		cout << "CALL OPTION" << endl;
		cout << "---------------------" << endl;
		European<double, double, double, double, double, int> eur_option_call = European<double, double, double, double, double, int>(S, K, rf, sigma, T, psi);
		cout << "Option Value :: " << eur_option_call.valuation() << endl;
		cout << "======================" << endl;
		cout << endl;

		cout << "PUT OPTION" << endl;
		cout << "---------------------" << endl;
		European<double, double, double, double, double, int> eur_option_put = European<double, double, double, double, double, int>(S, K, rf, sigma, T, -1 * psi);
		cout << "Option Value :: " << eur_option_put.valuation() << endl;
		cout << "======================" << endl;
		cout << endl;
	}
	catch (OptionException& exe) {
		cout << "ERROR : " << exe.what() << endl;
	}

	//system("pause");
	return 0;
}