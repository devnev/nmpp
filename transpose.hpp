/*  Copyright 2010 Mark Nevill
 *
 *  This file is part of NMPP.
 *
 *  NMPP is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU Lesser General Public License as published by the Free
 *  Software Foundation, either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  Foobar is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with NMPP.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NMPP_TANSPOSE_HPP
#define NMPP_TANSPOSE_HPP

#include <cstddef>

namespace nmpp {

namespace detail {

template<class MatrixT>
class transpose_op
{
	typedef MatrixT matrix_type;
	typedef typename add_const<matrix_type>::type const_matrix_type;
	typedef detail::matrix_ref<matrix_type> target_reference;
public:

	typedef typename MatrixT::value_type value_type;
	typedef typename MatrixT::reference reference;
	typedef typename MatrixT::const_reference const_reference;
	typedef transpose_op<matrix_type> this_type;
	typedef this_type matrix_ref;
	typedef transpose_op<const_matrix_type> matrix_const_ref;

	transpose_op(MatrixT& matrix) : _matrix(matrix) { }
	transpose_op(const transpose_op& other) : _matrix(other._matrix) { }

	reference operator()(size_t x, size_t y) { return _matrix(y, x); }
	const_reference operator()(size_t x, size_t y) const { return _matrix(y, x); }

	size_t width() const { return _matrix.height(); }
	size_t height() const { return _matrix.width(); }

private:
	target_reference _matrix;
};

} // end namespace detail

template<class MatrixT>
detail::transpose_op<MatrixT>
transpose(MatrixT& matrix) {
	return detail::transpose_op<MatrixT>(matrix);
}

} // end namespace nmpp

#endif // NMPP_TANSPOSE_HPP
