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

#ifndef NMPP_CONVOLUTION_HPP
#define NMPP_CONVOLUTION_HPP

#include <cstddef>
#include <cassert>

#include <nmpp/copy_matrix.hpp>

namespace nmpp {

namespace detail {

template<class InputT, class KernelT>
class convolve_op
{
	typedef typename detail::const_matrix_ref<InputT>::type const_input_ref;
	typedef typename detail::const_matrix_ref<KernelT>::type const_kernel_ref;

public:

	typedef typename InputT::value_type value_type;
	typedef convolve_op<InputT, KernelT> this_type;
	typedef this_type matrix_ref;
	typedef this_type matrix_const_ref;

	convolve_op(const InputT& input, const KernelT& kernel, size_t anchor_x, size_t anchor_y)
		: _input(input), _kernel(kernel), _anchor_x(anchor_x), _anchor_y(anchor_y)
	{
		assert(anchor_x < kernel.width());
		assert(anchor_y < kernel.height());
	}
	convolve_op(const this_type& other)
		: _input(other._input), _kernel(other._kernel), _anchor_x(other._anchor_x), _anchor_y(other._anchor_y) { }

	value_type operator()(size_t x, size_t y) const {
		value_type result = 0;
		for (size_t v = 0; v < _kernel.height(); ++v) {
			for (size_t u = 0; u < _kernel.width(); ++u) {
				size_t ix = 0;
				if (x + u < _anchor_x)
					ix = 0;
				else if (x + u >= width() + _anchor_x)
					ix = width() - 1;
				else
					ix = x + u - _anchor_x;
				size_t iy = 0;
				if (y + v < _anchor_y)
					iy = 0;
				else if (y + v >= height() + _anchor_y)
					iy = height() - 1;
				else
					iy = y + v - _anchor_y;
				result += _kernel(u, v) * _input(ix, iy);
			}
		}
		return result;
	}

	size_t width() const { return _input.width(); }
	size_t height() const { return _input.height(); }

private:
	const_input_ref _input;
	const_kernel_ref _kernel;
	const size_t _anchor_x, _anchor_y;
};

} // end namespace detail

template<class InputT, class KernelT>
detail::convolve_op<InputT, KernelT>
convolve(const InputT& input, const KernelT& kernel, size_t anchor_x, size_t anchor_y)
{
	return detail::convolve_op<InputT, KernelT>(input, kernel, anchor_x, anchor_y);
}

template<class InputT, class KernelT, class OutputT>
void convolve(const InputT& input, const KernelT& kernel, size_t anchor_x, size_t anchor_y, OutputT& output)
{
	copy_matrix(convolve(input, kernel, anchor_x, anchor_y), output);
}

} // end namespace nmpp

#endif // NMPP_CONVOLUTION_HPP
