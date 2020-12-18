#pragma once

class European
{
private:
	float S, K, rf, T, sigma, d1, d2;
	int psi;
	void calculate_d1();
	void calculate_d2();

public:
	European(float S, float K, float rf, float sigma, float T, int psi);
	double valuation();
};

