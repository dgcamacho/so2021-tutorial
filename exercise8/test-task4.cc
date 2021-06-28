#include "polynomial.hh"

namespace lagrange {

using String = std::string;

// Generate a random double within the given range.
auto random_double(double min, double max) -> double {
  double const r_num = (double)std::rand() / RAND_MAX;
  return min + r_num * (max - min);
}

// Pretty-print the result of some check.  The separation here is
// important so functions that can short circuit still do.
auto pp_check(bool b) -> String { return b ? "success\n" : ""; }

// Perform random checks of the given function in the given range.
auto check(int num_of_runs, double min, double max, auto checking_fun)
    -> String {
  auto const& range = std::ranges::iota_view{1, num_of_runs};
  return pp_check(std::all_of(range.begin(), range.end(), [&](Size) {
    return checking_fun(random_double(min, max));
  }));
}

// Unit and property tests for the Lagrange polynomial `L`.
auto test_lagrange(Polynomial<double, 5> l, Arr<double, 5> nodes, auto f)
    -> void {
  auto check_lagrange = [&](double x) -> bool {
    double const calculated{lagrange_interpolation(nodes, f)(x)};
    double const exact{l(x)};
    bool const ok{std::abs(calculated - exact) < 10e-13};
    if (!ok)
      std::cout << "Failed at: " << x << std::endl;
    return ok;
  };

  // Tests at specific values.
  std::cout << "Lagrange polynomial at x = -1: " << pp_check(check_lagrange(-1))
            << "Lagrange polynomial at x =  0: " << pp_check(check_lagrange(0))
            << "Lagrange polynomial at x =  1: " << pp_check(check_lagrange(1));

  // Tests at random values.
  std::cout << "Lagrange polynomial at 100 random values: "
            << check(100, -10.0, 10.0, check_lagrange);
}

// Unit and property tests for the Lagrange basis polynomials.
auto test_basis_polys(Arr<double, 5> nodes, auto eval_polynomials) -> void {
  auto check_polys = [&](double x) -> bool {
    Arr<double, 5> const calculated = lagrange_basis_at(nodes, x);
    Arr<double, 5> const exact = eval_polynomials(x);
    bool const all_ok = std::equal(
        calculated.begin(), calculated.end(), exact.begin(),
        [&](double a, double b) { return std::abs(a - b) < 10e-13; });
    if (!all_ok)
      std::cout << "Failed at: " << x << std::endl;
    return all_ok;
  };

  // Tests at specific values.
  std::cout << "Basis polynomials at x = -1: " << pp_check(check_polys(-1))
            << "Basis polynomials at x =  0: " << pp_check(check_polys(0))
            << "Basis polynomials at x =  1: " << pp_check(check_polys(1));

  // Tests at random values.
  std::cout << "Basis polynomials at 100 random values: "
            << check(100, -10.0, 10.0, check_polys) << std::endl;
}

/**
 * Tests for the specific polynomial in [these notes].
 *
 * [these notes]: http://www.webpages.ttu.edu/jengwer/notes/LagrangeBasis.pdf
 */
auto test_poly() -> void {
  std::unordered_map<double, double> const points{
      {-3, 20}, {-1, 8}, {0, -4}, {2, -10}, {5, 0}};
  Arr<double, 5> nodes;
  std::transform(points.begin(), points.end(), nodes.begin(),
                 [](auto ps) { return ps.first; });
  // We want the nodes to be in increasing order.
  std::sort(nodes.begin(), nodes.end());

  // Exact polynomials
  Polynomial<double, 5> l_1{{0, 1.0 / 24, 1.0 / 80, -1.0 / 40, 1.0 / 240}};
  Polynomial<double, 5> l_2{{0, -5.0 / 6, 11.0 / 36, 1.0 / 9, -1.0 / 36}};
  Polynomial<double, 5> l_3{{1, 19.0 / 30, -1.0 / 2, -1.0 / 10, 1.0 / 30}};
  Polynomial<double, 5> l_4{{0, 1.0 / 6, 17.0 / 90, 1.0 / 90, -1.0 / 90}};
  Polynomial<double, 5> l_5{{0, -1.0 / 120, -1.0 / 144, 1.0 / 360, 1.0 / 720}};
  Polynomial<double, 5> l{l_1 * 20.0 + l_2 * 8.0 + l_3 * -4.0 + l_4 * -10.0};

  test_basis_polys(nodes, [&](double x) -> Arr<double, 5> {
    return {l_1(x), l_2(x), l_3(x), l_4(x), l_5(x)};
  });
  test_lagrange(l, nodes, [&](double a) { return points.at(a); });
}

} // namespace lagrange
