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

namespace nmpp {

template<class T>
class auto_matrix;

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

} // end namespace nmpp

#endif // NMPP_MATRIX_HPP
