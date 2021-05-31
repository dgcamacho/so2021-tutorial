#include "Vector.hh"

Vector::Vector (std::size_t n) {
	data_ = std::vector<double>(n);
}

Vector::Vector (std::vector<double> data) {
	data_ = data;
}

double& Vector::operator[] (std::size_t i) {
	 return data_[i];
}

double const& Vector::operator[] (std::size_t i) const {
	return data_[i];
}

std::size_t Vector::size() const {
	return data_.size();
}