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

#ifndef NMPP_AUTO_MATRIX_HPP
#define NMPP_AUTO_MATRIX_HPP

#include <cassert>
#include <algorithm>
#include <cstddef>

#include <nmpp/copy_matrix.hpp>

namespace nmpp {

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

} // end namespace nmpp

namespace std {
	template<class T>
	void swap(nmpp::auto_matrix<T>& lhs, nmpp::auto_matrix<T>& rhs) {
		lhs.swap(rhs);
	}
}

#endif // NMPP_MATRIX_HPP
