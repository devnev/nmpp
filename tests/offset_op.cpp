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

#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include <complex>

#include <nmpp/weak_matrix.hpp>
#include <nmpp/sub_matrix.hpp>

using namespace nmpp;

typedef boost::mpl::list< double, int, std::complex<float> > test_types;

BOOST_AUTO_TEST_SUITE( OffsetOp )

BOOST_AUTO_TEST_CASE_TEMPLATE( CreateIgnore, T, test_types )
{
	T a[] = { T(3), T(23), T(17), T(11), T(51), T(97), T(397), T(511) };
	weak_matrix<T> m(a, 4, 2);
	BOOST_CHECK_NO_THROW( offset(m, 1, 0) );
	BOOST_CHECK_EQUAL( offset(m, 1, 0)(0, 0), T(23) );
	BOOST_CHECK_EQUAL( offset(m, 1, 0)(0, 1), T(97) );
}

BOOST_AUTO_TEST_SUITE_END()
