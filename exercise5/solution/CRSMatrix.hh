#pragma once

#include <vector>


namespace scprog
{
  class Vector;

  /// \brief Sparse matrix class using compressed row storage.
  /**
   * \tparam T  The element type of the matrix.
   *
   * Construct the matrix with size (rows x cols) and a slotsize for the insertion of elements.
   * This slotsize represents the maximal number of elements per row.
   *
   * Insert values via `matrix.add(i,j,value)` or `matrix.set(i,j,value)` and finish the
   * insertion by `matrix.compress()`.
   **/
  template <class T>
  class CRSMatrix
  {
  public:
    using value_type = T;
    using size_type = std::size_t;

  public:
    /// \brief Construct a new sparse matrix. Must call \ref compress() before usage.
    /**
     * \param rows      Number of rows of the matrix
     * \param cols      Number of columns of the matrix
     * \param slotsize  Maximal number of nonzeros per row. Must be exceeded in insert methods.
     **/
    explicit CRSMatrix (size_type rows = 0, size_type cols = 0, size_type slotsize = 0);

    /// \brief Add a value into the matrix at position (i,j).
    /**
     * \param i     Row index of position
     * \param j     Column index of position
     * \param value The value to add to the matrix
     *
     * Insert a new value into the matrix at position (i,j). If a value already exists at the
     * given position, add the new value to the existing one.
     *
     * [[ expects: !compressed_ ]]
     * [[ ensures: exists(i,j) ]]
     **/
    auto add (size_type const i, size_type const j, value_type const& value) -> void
    {
      insert(i,j,value, [](auto& aij, auto const& v) { aij += v; });
    }

    /// \brief Insert a value into the matrix at position (i,j).
    /**
     * \param i     Row index of position
     * \param j     Column index of position
     * \param value The value to add to the matrix
     *
     * Insert a new value into the matrix at position (i,j). If a value already exists at the
     * given position, override with the new value.
     *
     * [[ expects: !compressed_ ]]
     * [[ ensures: exists(i,j) ]]
     **/
    auto set (size_type const i, size_type const j, value_type const& value) -> void
    {
      insert(i,j,value, [](auto& aij, auto const& v) { aij = v; });
    }

    /// \brief Finish the insertion of new elements and compress the inner data structures.
    /**
     * This function must be called before any operation with the inserted data can be performed.
     *
     * [[ ensures: compressed_ ]]
     **/
    auto compress () -> void;

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
     *
     * [[ expects: compressed_ ]]
     **/
    auto operator() (size_type i, size_type j) const -> value_type;

    /// \brief Matrix-vector product A*x = y
    /**
     * \param x  The vector to multiply with.
     * \param y  The result of the matrix-vector multiplication.
     *
     * [[ expects: compressed_ ]]
     * [[ expects: rows_ == x.size() ]]
     * [[ expects: cols_ == y.size() ]]
     **/
    auto mv (Vector const& x, Vector& y) const -> void;

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
    /**
     * [[ expects: compressed_ ]]
     **/
    auto nnz () const -> size_type;

  private:
    // Implementation function for add and set.
    /*
     * The additional parameter `assign` is a functor with signature
     * `void(value_type& a, value_type const& b)` that implements either
     * assignment `a = b` or accumulated assignment, e.g., `a += b`.
     */
    template <class Assign>
    auto insert (size_type i, size_type j, value_type const& value, Assign assign) -> void;

  private:
    size_type rows_;
    size_type cols_;
    size_type slotsize_;
    bool compressed_ = false;

    std::vector<size_type> offset_;
    std::vector<size_type> indices_;
    std::vector<value_type> values_;
  };

} // end namespace scprog

#include "CRSMatrix.impl.hh"
