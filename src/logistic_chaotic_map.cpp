#include "logistic_chaotic_map.hpp"
logistic_chaotic_map::logistic_chaotic_map(double const x_0,
                                           double const lambda) noexcept
    : terms_{x_0}, lambda_{lambda} {}

// retorna el termino n de la sequencia caotica
double logistic_chaotic_map::operator()(unsigned int const n) noexcept {
  while (n >= terms_.size()) {
    auto const& last_term{terms_[terms_.size() - 1]};
    terms_.push_back(lambda_ * last_term * (1 - last_term));
  }

  return terms_[n];
}