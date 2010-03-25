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

template<class T>
struct add_const { typedef const T type; };
template<class T>
struct add_const<const T> { typedef T type; };

template<class InputT, class OutputT>
void copy_matrix(const InputT& input, OutputT& output)
{
	assert(input.width() <= output.width());
	assert(input.height() <= output.height());
	for (size_t y = 0; y < input.height(); ++y) {
		for (size_t x = 0; x < input.width(); ++x) {
			output(x, y) = static_cast<typename OutputT::value_type>(input(x, y));
		}
	}
}

namespace detail {
template<class LeftMatrixT, class RightMatrixT, class BinaryOpT>
class matrix_binary_op;
}

template<class T>
class weak_matrix;

template<class T>
class auto_matrix
{
public:
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* array_type;
	typedef const T* const_array_type;
	typedef auto_matrix<T> this_type;
	typedef weak_matrix<T> matrix_reference;

	auto_matrix()
		: _array(0), _width(0), _height(0) { }
	auto_matrix(size_t width, size_t height)
		: _array(new T[width*height]), _width(width), _height(height) { }
	auto_matrix(size_t width, size_t height, value_type value)
		: _array(new T[width*height]), _width(width), _height(height) {
		std::fill(_array, _array+_width*_height, value);
	}
	auto_matrix(array_type array, size_t width, size_t height)
		: _array(array), _width(width), _height(height) { }
	~auto_matrix() { delete [] _array; }
	this_type& operator=(const this_type& rhs) {
		if (this != &rhs) {
			if (_width*_height != rhs._width*rhs._height) {
				reset(rhs._width, rhs._height);
			}
			_width = rhs._width; _height = rhs._height;
			std::copy(rhs._array, rhs._array+_width*_height, _array);
		}
		return *this;
	}
	void swap(this_type& other) {
		using std::swap;
		swap(_array, other._array);
		swap(_width, other._width);
		swap(_height, other._height);
	}
	void reset(array_type array, size_t width, size_t height) {
		if (array != _array)
			delete [] _array;
		_array = array; _width = width; _height = height;
	}
	void reset(size_t width, size_t height) {
		if (width*height > 0)
			reset(new T[width*height], width, height);
		else
			reset();
	}
	void reset(size_t width, size_t height, value_type value) {
		reset(width, height);
		std::fill(_array, _array+_width*_height, value);
	}
	void reset() {
		delete [] _array;
		_array = 0; _width = _height = 0;
	}
	array_type release() {
		array_type tmp = _array;
		_array = 0; _width = _height = 0;
		return tmp;
	}

	reference operator()(size_t x, size_t y) {
		assert(_array != 0);
		assert(x < _width);
		assert(y < _height);
		return _array[y * _width + x];
	}
	const_reference operator()(size_t x, size_t y) const {
		assert(_array != 0);
		assert(x < _width);
		assert(y < _height);
		return _array[y * _width + x];
	}

	template<class SourceT>
	this_type& operator=(const SourceT& rhs) {
		copy_matrix(rhs, *this);
		return *this;
	}

	size_t width() const { return _width; }
	size_t height() const { return _height; }
	array_type get() { return _array; }
	array_type get() const { return _array; }

private:
	array_type _array;
	size_t _width, _height;
};

namespace std {
	template<class T>
	void swap(auto_matrix<T>& lhs, auto_matrix<T>& rhs) {
		lhs.swap(rhs);
	}
}

template<class T>
class weak_matrix
{
public:
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* array_type;
	typedef const T* const_array_type;
	typedef weak_matrix<T> this_type;
	typedef this_type matrix_reference;

	weak_matrix() : _array(0), _width(0), _height(0) { }
	weak_matrix(array_type array, size_t width, size_t height) : _array(array), _width(width), _height(height) { }
	weak_matrix(auto_matrix<T>& matrix) : _array(matrix.get()), _width(matrix.width()), _height(matrix.height()) { }
	weak_matrix(const auto_matrix<T>& matrix) : _array(matrix.get()), _width(matrix.width()), _height(matrix.height()) { }
	weak_matrix(const this_type& other) : _array(other._array), _width(other._width), _height(other._height) { }

	reference operator()(size_t x, size_t y) {
		assert(_array != 0);
		assert(x < _width);
		assert(y < _height);
		return _array[y * _width + x];
	}
	const_reference operator()(size_t x, size_t y) const {
		assert(_array != 0);
		assert(x < _width);
		assert(y < _height);
		return _array[y * _width + x];
	}

	template<class SourceT>
	this_type& operator=(const SourceT& rhs) {
		copy_matrix(rhs, *this);
		return *this;
	}

	this_type& operator=(const this_type& rhs) {
		_array = rhs._array;
		_width = rhs._width;
		_height = rhs._height;
		return *this;
	}

	void reset(array_type array, size_t width, size_t height) {
		_array = array;
		_width = width;
		_height = height;
	}

	size_t width() const { return _width; }
	size_t height() const { return _height; }
	array_type get() { return _array; }
	const_array_type get() const { return _array; }

private:
	array_type _array;
	size_t _width, _height;
};

template<class MatrixT>
class linear_matrix_view
{
	typedef typename MatrixT::matrix_reference target_reference;
public:
	typedef typename MatrixT::value_type value_type;
	typedef typename MatrixT::reference reference;
	typedef typename MatrixT::const_reference const_reference;
	typedef typename MatrixT::array_type array_type;
	typedef MatrixT matrix_type;
	typedef typename add_const<matrix_type>::type const_matrix_type;
	typedef linear_matrix_view<MatrixT> this_type;
	typedef this_type matrix_reference;

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
linear_matrix_view<typename MatrixT::matrix_reference>
linear_matrix_filter(MatrixT& input, size_t start_x, size_t start_y, size_t step_x, size_t step_y)
{
	return linear_matrix_view<typename MatrixT::matrix_reference>(input, start_x, start_y, step_x, step_y);
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

#endif // NMPP_MATRIX_HPP
