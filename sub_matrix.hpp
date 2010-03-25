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

#ifndef NMPP_SUB_MATRIX_HPP
#define NMPP_SUB_MATRIX_HPP

#include <cassert>
#include <cstddef>

#include <nmpp/copy_matrix.hpp>

namespace nmpp {

namespace detail {

template<class MatrixT>
class offset_op
{
	typedef MatrixT matrix_type;
	typedef typename detail::add_const<matrix_type>::type const_matrix_type;
	typedef typename detail::matrix_ref<matrix_type>::type target_ref;

public:
	typedef typename matrix_type::value_type value_type;
	typedef typename matrix_type::reference reference;
	typedef typename matrix_type::const_reference const_reference;
	typedef typename matrix_type::array_type array_type;
	typedef offset_op<matrix_type> this_type;
	typedef this_type matrix_ref;
	typedef offset_op<const_matrix_type> matrix_const_ref;

	explicit offset_op(matrix_type& matrix)
		: _matrix(matrix), _offset_x(0), _offset_y(0) { }
	offset_op(matrix_type& matrix, size_t offset_x, size_t offset_y)
		: _matrix(matrix), _offset_x(offset_x), _offset_y(offset_y) { }
	offset_op(const this_type& other)
		: _matrix(other._matrix), _offset_x(other._offset_x), _offset_y(other._offset_y) { }

	reference operator()(size_t x, size_t y) { return _matrix(x + _offset_x, y + _offset_y); }
	const_reference operator()(size_t x, size_t y) const { return _matrix(x + _offset_x, y + _offset_y); }

	template<class SourceT>
	this_type& operator=(const SourceT& rhs) {
		copy_matrix(rhs, *this);
		return *this;
	}

	size_t width() const { return _matrix.width() - _offset_x; }
	size_t height() const { return _matrix.height() - _offset_y; }
	size_t offset_x() const { return _offset_x; }
	size_t offset_y() const { return _offset_y; }
	array_type get() { return _matrix.get(); }
	target_ref matrix() { return _matrix; }

private:
	target_ref _matrix;
	const size_t _offset_x, _offset_y;
};

template<class MatrixT>
class step_op
{
	typedef MatrixT matrix_type;
	typedef typename detail::add_const<matrix_type>::type const_matrix_type;
	typedef typename detail::matrix_ref<matrix_type>::type target_ref;

public:
	typedef typename matrix_type::value_type value_type;
	typedef typename matrix_type::reference reference;
	typedef typename matrix_type::const_reference const_reference;
	typedef typename matrix_type::array_type array_type;
	typedef step_op<matrix_type> this_type;
	typedef this_type matrix_ref;
	typedef step_op<const_matrix_type> matrix_const_ref;

	explicit step_op(matrix_type& matrix)
		: _matrix(matrix), _step_x(1), _step_y(1) { }
	step_op(matrix_type& matrix, size_t step_x, size_t step_y)
		: _matrix(matrix), _step_x(step_x), _step_y(step_y) { }
	step_op(const this_type& other)
		: _matrix(other._matrix), _step_x(other._step_x), _step_y(other._step_y) { }

	reference operator()(size_t x, size_t y) { return _matrix(x * _step_x, y * _step_y); }
	const_reference operator()(size_t x, size_t y) const { return _matrix(x * _step_x, y * _step_y); }

	template<class SourceT>
	this_type& operator=(const SourceT& rhs) {
		copy_matrix(rhs, *this);
		return *this;
	}

	size_t width() const { return (_matrix.width() + _step_x - 1) / _step_x; }
	size_t height() const { return (_matrix.height() + _step_y - 1) / _step_y; }
	size_t step_x() const { return _step_x; }
	size_t step_y() const { return _step_y; }
	array_type get() { return _matrix.get(); }
	target_ref matrix() { return _matrix; }

private:
	target_ref _matrix;
	const size_t _step_x, _step_y;
};

template<class Matrix>
class limit_op
{
	typedef MatrixT matrix_type;
	typedef typename detail::add_const<matrix_type>::type const_matrix_type;
	typedef typename detail::matrix_ref<matrix_type>::type target_ref;

public:
	typedef typename matrix_type::value_type value_type;
	typedef typename matrix_type::reference reference;
	typedef typename matrix_type::const_reference const_reference;
	typedef typename matrix_type::array_type array_type;
	typedef limit_op<matrix_type> this_type;
	typedef this_type matrix_ref;
	typedef limit_op<const_matrix_type> matrix_const_ref;

	explicit limit_op(matrix_type& matrix)
		: _matrix(matrix), _width(matrix.width()), _height(matrix.height()) { }
	limit_op(matrix_type& matrix, size_t width, size_t height)
		: _matrix(matrix), _width(width), _height(height) {
		assert(matrix.width() <= _width);
		assert(matrix.height() <= _height);
	}
	limit_op(const this_type& other)
		: _matrix(other._matrix), _width(other._width), _height(other._height) { }

	reference operator()(size_t x, size_t y) {
		assert(x < _width);
		assert(y < _height);
		return _matrix(x, y);
	}
	const_reference operator()(size_t x, size_t y) const {
		assert(x < _width);
		assert(y < _height);
		return _matrix(x, y);
	}

	template<class SourceT>
	this_type& operator=(const SourceT& rhs) {
		copy_matrix(rhs, *this);
		return *this;
	}

	size_t width() const { return _width; }
	size_t height() const { return _height; }
	array_type get() { return _matrix.get(); }
	target_ref matrix() { return _matrix; }

private:
	target_ref _matrix;
	const size_t _width, _height;
};

} // end namespace detail

template<class MatrixT>
detail::offset_op<MatrixT>
offset(MatrixT& matrix, size_t offset_x, size_t offset_y) {
	return detail::offset_op<MatrixT>(matrix, offset_x, offset_y);
}

template<class MatrixT>
detail::step_op<MatrixT>
step(MatrixT& matrix, size_t step_x, size_t step_y) {
	return detail::step_op<MatrixT>(matrix, step_x, step_y);
}

template<class MatrixT>
detail::limit_op<MatrixT>
limit(MatrixT& matrix, size_t width, size_t height) {
	return detail::limit_op<MatrixT>(matrix, width, height);
}

} // end namespace nmpp

#endif // NMPP_SUB_MATRIX_HPP
