# include "LU.hh"

namespace scprog {
    LU::LU(): decomposition_(0, 0) {};

    // decomposing the matrix m, without modifing it
    void LU::compute(DenseMatrix const& m){
      if (m.rows() != m.cols()){
        throw std::invalid_argument("Matrix must be square.");
      }
      decomposition_ = DenseMatrix(m.rows(), m.cols());

      int n = decomposition_.rows();
      double sum = 0;
      for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
          sum = 0;
          for (int k = 0; k < i; k++)
              sum += decomposition_(i, k) * decomposition_(k, j);
          decomposition_(i, j) = m(i, j) - sum;
        }
        for (int j = i + 1; j < n; j++){
          sum = 0;
          for (int k = 0; k < i; k++)
              sum += decomposition_(j, k) * decomposition_(k, i);
          decomposition_(j, i) = (1 / decomposition_(i, i)) * (m(j, i) - sum);
        }
      }
    }

    // solve the associated Equation once a decomposition is known
    // LU::compute needs to be called first, which is not internally enforced
    void LU::apply(Vector const& b, Vector& x) {
      // find solution of Ly = b
      int n = decomposition_.rows();
      double sum;
      Vector y = Vector(n);
      for (int i = 0; i < n; i++){
        sum = 0;
        for (int k = 0; k < i; k++)
            sum += decomposition_(i, k) * y[k];
        y[i] = b[i] - sum;
      }
      // find solution of Ux = y
      for (int i = n - 1; i >= 0; i--){
        sum = 0;
        for (int k = i + 1; k < n; k++)
            sum += decomposition_(i, k) * x[k];
        x[i] = (1 / decomposition_(i, i)) * (y[i] - sum);
      }
    }

    // print the matrix
    void LU::print() const {
      decomposition_.print();
    }
  }