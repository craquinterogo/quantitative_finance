#include "Options.h"
#include <math.h>
#include <boost/math/distributions/normal.hpp>
#include <iostream>
#include <exception>

using boost::math::normal;
using std::cout; using std::cin;  using std::endl;


/*
* 	===========================================================
*	= Exception
*	===========================================================
*/
struct OptionException : std::exception {
	const char* what() const throw() {
		return "Sorry!, you are throwing an error in Option class ... what will be it?. Take a view in Options.cpp";
	}
};

/*
*	= Option
*/
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>::Option(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi, type_q q) :
	S(S), K(K), rf(rf), sigma(sigma), T(T), psi(psi), q(q)
{
	//cout << "Constructor" << endl;
};

/*
*	===========================================================
*	= European Option
*	===========================================================
*/
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
European<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>::European(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi, type_q q) :
	Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>(S, K, rf, sigma, T, psi, q)
{
	d1 = NULL;
	d2 = NULL;
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
void European<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>::calculate_d1() {
	// Including q of Merton extended BS model (continuous dividend)
	d1 = (float)(log(this->S / this->K) + (this->rf - this->q + 0.5 * this->sigma * this->sigma) * this->T) / (this->sigma * sqrt(this->T));
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
void European<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>::calculate_d2() {
	d2 = d1 - this->sigma * sqrt(this->T);
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
double European<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>::valuation() {
	// Including q of Merton extended BS model (continuous dividend)
	calculate_d1();
	calculate_d2();
	normal s;
	double option_price = ((double)this->psi * this->S * exp(-this->q * this->T) * cdf(s, this->psi * d1)) - ((double)this->psi * this->K * exp(-this->rf * this->T) * cdf(s, this->psi * this->d2));
	return option_price;
};

/*
*	===========================================================
*	= American Option
*	===========================================================
*/
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
American<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>::American(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi, type_q q) :
	Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>(S, K, rf, sigma, T, psi, q)
{
};

template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
double American<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>::valuation(){
};

int main() {
	double S, K, rf, T, sigma, q;
	int psi;
	try {
		S = 100;
		K = 95;
		rf = 0.1;
		sigma = 0.2;
		q = 0.05;
		T = 0.5;
		psi = 1;

		cout << "CALL OPTION" << endl;
		cout << "---------------------" << endl;
		European<double, double, double, double, double, int, double> eur_option_call = European<double, double, double, double, double, int, double>(S, K, rf, sigma, T, psi, q);
		cout << "Option Value :: " << eur_option_call.valuation() << endl;
		cout << "======================" << endl;
		cout << endl;

		cout << "PUT OPTION" << endl;
		cout << "---------------------" << endl;
		European<double, double, double, double, double, int, double> eur_option_put = European<double, double, double, double, double, int, double>(S, K, rf, sigma, T, -psi, q);
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