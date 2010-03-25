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

namespace detail {

template<class MatrixT>
class transpose_op
{
public:

	typedef typename MatrixT::value_type value_type;
	typedef transpose_op<MatrixT> this_type;
	typedef this_type matrix_reference;

	transpose_op(const MatrixT& matrix) : _matrix(matrix) { }
	transpose_op(const transpose_op& other) : _matrix(other._matrix) { }

	value_type operator()(size_t x, size_t y) const { return _matrix(y, x); }

	size_t width() const { return _matrix.height(); }
	size_t height() const { return _matrix.width(); }

private:
	const typename MatrixT::matrix_reference _matrix;
};

} // end namespace detail

template<class MatrixT>
detail::transpose_op<MatrixT>
transpose(const MatrixT& matrix) {
	return detail::transpose_op<MatrixT>(matrix);
}

#endif // NMPP_TANSPOSE_HPP
