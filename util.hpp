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

#ifndef NMPP_COPY_MATRIX_HPP
#define NMPP_COPY_MATRIX_HPP

#include <cassert>
#include <algorithm>
#include <cstddef>

namespace nmpp {

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

template<class T>
struct add_const { typedef const T type; };
template<class T>
struct add_const<const T> { typedef T type; };

template<class T>
struct is_const { enum { value = false }; };
template<class T>
struct is_const<const T> { enum { value = true }; };

template<bool B, class T1, class T2>
struct if_c { typedef T1 type; };
template<class T1, class T2>
struct if_c<false, T1, T2> { typedef T2 type; };

template<class MatrixT>
struct matrix_ref {
	typedef typename if_c<is_const<MatrixT>::value,
		typename MatrixT::matrix_const_ref,
		typename MatrixT::matrix_ref
	>::type type;
};

template<class MatrixT>
struct const_matrix_ref {
	typedef typename add_const<
		typename matrix_ref<MatrixT>::type
	>::type type;
};

} // end namespace detail

} // end namespace nmpp

#endif // NMPP_COPY_MATRIX_HPP
