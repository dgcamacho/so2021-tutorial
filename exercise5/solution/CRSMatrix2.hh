#pragma once

#include <vector>

namespace scprog
{
  // forward declaration
  template <class T>
  class CRSMatrixInserter;

  // forward declaration
  class Vector;

  /// \brief Sparse matrix class using compressed row storage.
  /**
   * \tparam T  The element type of the matrix.
   *
   * Construct the matrix with size (rows x cols). In order to fill the matrix with values, you
   * need to create an inserter, using `matrix.inserter(slotsize)` with `slotsize` the maximal
   * number of nonzeros per row.
   *
   * This inserter is of type `CRSMatrixInserter<T>` and actually fills the matrix on destruction.
   * See \ref CRSMatrixInserter for details.
   **/
  template <class T>
  class CRSMatrix
  {
  public:
    using value_type = T;
    using size_type = std::size_t;

    // make the iterator a friend of this class to access all private members
    template <class>
    friend class CRSMatrixInserter;

  public:
    /// \brief Construct a new sparse matrix. Must call \ref compress() before usage.
    /**
     * \param rows      Number of rows of the matrix
     * \param cols      Number of columns of the matrix
     **/
    explicit CRSMatrix (size_type rows = 0, size_type cols = 0);

    /// \brief Return a new inserter that is reponsible for inserting values into the matrix.
    /**
     * \param slotsize  Maximal number of nonzeros per row. Must not be exceeded in insert methods.
     *
     * The inserter fills this matrix on its destruction.
     **/
    auto inserter (size_type slotsize) -> CRSMatrixInserter<T>;

    /// \brief Check whether an entry exists at position (i,j)
    /**
     * \param i     Row index of position
     * \param j     Column index of position
     *
     * Note, this function can be called in compressed and non-compressed state.
     **/
    auto exists (size_type i, size_type j) const -> bool;

    /// \brief Return the entry of the matrix at position (i,j) if it exists or 0 otherwise.
    /**
     * \param i     Row index of position
     * \param j     Column index of position
     **/
    auto operator() (size_type i, size_type j) const -> value_type;

    /// \brief Matrix-vector product A*x = y
    /**
     * \param x  The vector to multiply with.
     * \param y  The result of the matrix-vector multiplication.
     *
     * [[ expects: rows_ == x.size() ]]
     * [[ expects: cols_ == y.size() ]]
     **/
    auto mv (Vector const& x, Vector& y) const;

    /// \brief Return the number of rows
    auto rows () const -> size_type
    {
      return rows_;
    }

    /// \brief Return the number of columns
    auto cols () const -> size_type
    {
      return cols_;
    }

    /// \brief Return the number of non zero elements stored in the compressed matrix
    auto nnz () const -> size_type
    {
      return values_.size();
    }

  private:
    size_type rows_;
    size_type cols_;

    std::vector<size_type> offset_;
    std::vector<size_type> indices_;
    std::vector<value_type> values_;
  };


  /// \brief An inserter for a sparse CRSMatrix
  /**
   * \tparam T  The element type of the `CRSMatrix<T>` to be filled.
   *
   * This inserter implements the insertion of elements into the matrix. In must be constructed
   * with a reference to the matrix that need to be filled and a slotsize representing the
   * maximal number of nonzeros per row.
   *
   * On destruction, the actual filling of the matrix happens. This guarantees that the internal
   * data-structures for handling the element insertion are also deleted correctly.
   *
   * If the matrix already contains entries, those are copied to the internal data structured and
   * more entries can be added.
   *
   * Example:
   * ```
   * CRSMatrix<double> A{10,10};
   * {
   *   auto ins = A.inserter(3);
   *   ins(0,0) = 1;
   *   ins(1,1) += 2.0;
   * }
   * ```
   * In the example, the curly braces are used to introduce a limited scope at which end the
   * inserter is deleted and thus the insertion happens.
   **/
  template <class T>
  class CRSMatrixInserter
  {
    using Matrix = CRSMatrix<T>;

    using size_type = typename Matrix::size_type;
    using value_type = typename Matrix::value_type;

    /// Helper class to implement the local element insertion
    struct Updater
    {
      CRSMatrixInserter& self_;
      size_type i_, j_;

      auto operator= (value_type const& value) -> Updater&
      {
        update(value, [](auto& aij, auto const& v) { aij = v; });
        return *this;
      }

      auto operator+= (value_type const& value) -> Updater&
      {
        update(value, [](auto& aij, auto const& v) { aij += v; });
        return *this;
      }

    private:
      // Implementation function for operator+= and operator=.
      /*
      * The additional parameter `assign` is a functor with signature
      * `void(value_type& a, value_type const& b)` that implements either
      * assignment `a = b` or accumulated assignment, e.g., `a += b`.
      */
      template <class Assign>
      auto update (value_type const& value, Assign assign);
    };

  public:
    CRSMatrixInserter (Matrix& matrix, size_type slotsize = 5);

    /// \brief Finish the insertion of new elements and fill the inner data structures of matrix.
    ~CRSMatrixInserter ();

    /// \brief Return a proxy type thatt handles the insertion
    auto operator() (size_type const i, size_type const j) -> Updater
    {
      return Updater{*this,i,j};
    }

    /// \brief Add a value into the matrix at position (i,j).
    /**
     * \param i     Row index of position
     * \param j     Column index of position
     * \param value The value to add to the matrix
     *
     * Insert a new value into the matrix at position (i,j). If a value already exists at the
     * given position, add the new value to the existing one.
     **/
    auto add (size_type const i, size_type const j, value_type const& value)
    {
      (*this)(i,j) += value;
    }

    /// \brief Insert a value into the matrix at position (i,j).
    /**
     * \param i     Row index of position
     * \param j     Column index of position
     * \param value The value to add to the matrix
     *
     * Insert a new value into the matrix at position (i,j). If a value already exists at the
     * given position, override with the new value.
     **/
    auto set (size_type const i, size_type const j, value_type const& value)
    {
      (*this)(i,j) = value;
    }

  private:
    Matrix& matrix_;
    size_type slotsize_;

    std::vector<size_type> sizes_;
    std::vector<size_type> indices_;
    std::vector<value_type> values_;
  };

} // end namespace scprog

#include "CRSMatrix2.impl.hh"
