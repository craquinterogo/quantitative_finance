#pragma once

/* Classes to pricing Option Derivatives */

/* GENERAL CLASS */
class Option {
public:
	Option(float S, float K, float rf, float sigma, float T, int psi);

protected:
	float S, K, rf, T, sigma;
	int psi;
};

/* EUROPEAN CLASS extended from Option Class*/
class European : Option
{
public:
	European(float S, float K, float rf, float sigma, float T, int psi);
	double valuation();

private:
	float d1, d2;
	void calculate_d1();
	void calculate_d2();
};

/* EUROPEAN CLASS extended from Option Class*/
class American : Option
{
public:
	American(float S, float K, float rf, float sigma, float T, int psi);
	double valuation();
};


