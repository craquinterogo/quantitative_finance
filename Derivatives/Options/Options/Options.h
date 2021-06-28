#pragma once

/* Classes to pricing Option Derivatives */

/* GENERAL CLASS */
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
class Option {
public:
	Option(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi, type_q q=0.0);

protected:
	type_S S;
	type_K K;
	type_rf rf;
	type_T T;
	type_sigma sigma;
	type_psi psi;
	type_q q;
};

/* EUROPEAN CLASS extended from Option Class*/
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
class European : Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>
{
public:
	European(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi, type_q q = 0.0);
	double valuation();

private:
	float d1, d2;
	void calculate_d1();
	void calculate_d2();
};

/* EUROPEAN CLASS extended from Option Class*/
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi, class type_q>
class American : Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi, type_q>
{
public:
	American(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi, type_q q = 0.0);
	double valuation();
};


