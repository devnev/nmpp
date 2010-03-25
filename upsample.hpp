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

#ifndef NMPP_UPSAMPLE_HPP
#define NMPP_UPSAMPLE_HPP

#include <cstddef>

template<class InputT, class OutputT>
void upsample_nearest(const InputT& input, OutputT& output)
{
	size_t xmul = output.width() / input.width();
	size_t xextra = output.width() % input.width();
	size_t xmissing = input.width() - xextra;
	size_t ymul = output.height() / input.height();
	size_t yextra = output.height() % input.height();
	size_t ymissing = input.height() - yextra;

	for (size_t y = 0; y < output.height(); ++y) {
		for (size_t x = 0; x < output.width(); ++x) {
			size_t xi = 0;
			if (x / xmul < input.width() - xextra)
				xi = x / xmul;
			else
				xi = (x + xmissing) / (xmul + 1);
			size_t yi = 0;
			if (y / ymul < input.height() - yextra)
				yi = y / ymul;
			else
				yi = (y + ymissing) / (ymul + 1);
			output(x, y) = input(xi, yi);
		}
	}
}

template<class InputT, class OutputT>
void upsample_bilinear(const InputT& input, OutputT& output)
{
	float xstep = (float)(input.width()-1) / (float)(output.width()-1);
	float ystep = (float)(input.height()-1) / (float)(output.height()-1);

	float dy = 0.0f;
	size_t row1 = 0;
	size_t row2 = 1;
	if (row2 >= input.height())
		row2 = row1;
	for (size_t outy = 0; outy < output.height(); ++outy) {
		float dx = 0.0f;
		size_t col1 = 0;
		size_t col2 = 1;
		if (col2 >= input.width())
			col2 = col1;
		for (size_t outx = 0; outx < output.width(); ++outx) {
			output(outx, outy) =
				(1-dy) * (1-dx) * input(col1, row1) +
				(1-dy) * dx * input(col2, row1) +
				dy * dx * input(col2, row2) +
				dy * (1-dx) * input(col1, row2);
			dx += xstep;
			if (dx >= 1.0f) {
				++col1; ++col2;
				dx -= 1.0f;
				if (col2 >= input.width())
					col2 = col1;
			}
		}
		dy += ystep;
		if (dy >= 1.0f) {
			++row1; ++row2;
			dy -= 1.0f;
			if (row2 >= input.height())
				row2 = row1;
		}
	}
}

#endif // NMPP_UPSAMPLE_HPP
