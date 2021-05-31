#pragma once
#include <vector>

class Vector {
	std::vector<double> data_;

public:
	Vector (std::size_t n);
	Vector (std::vector<double> data);
	double& operator[] (std::size_t i);
	double const& operator[] (std::size_t i) const;
	std::size_t size() const;

};