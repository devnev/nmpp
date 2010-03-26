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

#ifndef NMPP_UNIFORM_MATRIX_HPP
#define NMPP_UNIFORM_MATRIX_HPP

#include <cstddef>
#include <limits>

#include <nmpp/util.hpp>

namespace nmpp {

namespace detail {

template<class T>
class uniform_matrix
{
public:
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef uniform_matrix<T> this_type;
	typedef this_type matrix_ref;
	typedef this_type matrix_const_ref;

	uniform_matrix(value_type value) : _value(value) { }
	uniform_matrix(const this_type& other) : _value(other._value) { }

	const_reference operator()(size_t x, size_t y) const { (void)x; (void)y; return _value; }

	size_t width() { return std::numeric_limits<size_t>::max(); }
	size_t height() { return std::numeric_limits<size_t>::max(); }

private:
	value_type _value;
};

} // end namespace detail

template<class T>
detail::uniform_matrix<T>
uniform(const T& value) {
	return detail::uniform_matrix<T>(value);
}

} // end namespace nmpp

#endif // NMPP_UNIFORM_MATRIX_HPP
