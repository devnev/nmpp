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

#ifndef NMPP_MATRIX_HPP
#define NMPP_MATRIX_HPP

#include <cassert>
#include <algorithm>
#include <cstddef>

#include <nmpp/copy_matrix.hpp>
#include <nmpp/auto_matrix.hpp>
#include <nmpp/weak_matrix.hpp>

namespace nmpp {

template<class MatrixT>
class linear_matrix_view
{
	typedef MatrixT matrix_type;
	typedef typename detail::add_const<matrix_type>::type const_matrix_type;
	typedef typename detail::matrix_ref<matrix_type>::type target_reference;

public:
	typedef typename MatrixT::value_type value_type;
	typedef typename MatrixT::reference reference;
	typedef typename MatrixT::const_reference const_reference;
	typedef typename MatrixT::array_type array_type;
	typedef linear_matrix_view<matrix_type> this_type;
	typedef this_type matrix_reference;
	typedef linear_matrix_view<const_matrix_type> matrix_const_reference;

	linear_matrix_view(const_matrix_type& matrix, size_t step = 1)
		: _matrix(matrix), _start_x(0), _start_y(0), _step_x(step), _step_y(step) { }
	linear_matrix_view(const_matrix_type& matrix, size_t start_x, size_t start_y, size_t step = 1)
		: _matrix(matrix), _start_x(start_x), _start_y(start_y), _step_x(step), _step_y(step) { }
	linear_matrix_view(const_matrix_type& matrix, size_t start_x, size_t start_y, size_t step_x, size_t step_y)
		: _matrix(matrix), _start_x(start_x), _start_y(start_y), _step_x(step_x), _step_y(step_y) { }
	linear_matrix_view(const this_type& other)
		: _matrix(other._matrix), _start_x(other._start_x), _start_y(other._start_y),
			_step_x(other._step_x), _step_y(other._step_y) { }

	reference operator()(size_t x, size_t y) { return _matrix(x * _step_x + _start_x, y * _step_y + _start_y); }
	const_reference operator()(size_t x, size_t y) const { return _matrix(x * _step_x + _start_x, y * _step_y + _start_y); }

	template<class SourceT>
	this_type& operator=(const SourceT& rhs) {
		copy_matrix(rhs, *this);
		return *this;
	}

	size_t width() const { return ((_matrix.width() - _start_x) + (_step_x - 1)) / _step_x; }
	size_t height() const { return ((_matrix.height() - _start_y) + (_step_y - 1)) / _step_y; }
	size_t step_x() const { return _step_x; }
	size_t step_y() const { return _step_y; }
	size_t start_x() const { return _start_x; }
	size_t start_y() const { return _start_y; }
	array_type get() { return _matrix.get(); }
	matrix_type matrix() { return _matrix; }

private:
	target_reference _matrix;
	const size_t _start_x, _start_y;
	const size_t _step_x, _step_y;
};

template<class MatrixT>
linear_matrix_view<MatrixT>
linear_matrix_filter(MatrixT& input, size_t start_x, size_t start_y, size_t step_x, size_t step_y)
{
	return linear_matrix_view<MatrixT>(input, start_x, start_y, step_x, step_y);
}

template<class T>
class constant_matrix
{
public:
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef constant_matrix<T> this_type;
	typedef this_type matrix_reference;

	constant_matrix(value_type constant) : _constant(constant) { }
	constant_matrix(const this_type& other) : _constant(other._constant) { }

	const_reference operator()(size_t x, size_t y) const { (void)x; (void)y; return _constant; }

private:
	value_type _constant;
};

} // end namespace nmpp

#endif // NMPP_MATRIX_HPP
