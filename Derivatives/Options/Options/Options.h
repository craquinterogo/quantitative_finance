#pragma once

/* Classes to pricing Option Derivatives */

/* GENERAL CLASS */
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
class Option {
public:
	Option(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi);

protected:
	type_S S;
	type_K K;
	type_rf rf;
	type_T T;
	type_sigma sigma;
	type_psi psi;
};

/* EUROPEAN CLASS extended from Option Class*/
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
class European : Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi>
{
public:
	European(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi);
	double valuation();

private:
	float d1, d2;
	void calculate_d1();
	void calculate_d2();
};

/* EUROPEAN CLASS extended from Option Class*/
template<class type_S, class type_K, class type_rf, class type_sigma, class type_T, class type_psi>
class American : Option<type_S, type_K, type_rf, type_sigma, type_T, type_psi>
{
public:
	American(type_S S, type_K K, type_rf rf, type_sigma sigma, type_T T, type_psi psi);
	double valuation();
};


