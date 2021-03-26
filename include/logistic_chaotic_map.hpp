#pragma once
#include <vector>
// mapa logistico caotico
class logistic_chaotic_map {
public:
  logistic_chaotic_map() = default;
  logistic_chaotic_map(double x_0, double lambda) noexcept;
  ~logistic_chaotic_map() = default;
  double operator()(unsigned int n) noexcept;

private:
  std::vector<double> terms_{0.1};
  double lambda_{3.9};
};