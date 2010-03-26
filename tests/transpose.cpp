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
#include <nmpp/transpose.hpp>

using namespace nmpp;

typedef boost::mpl::list< double, int, std::complex<float> > test_types;

BOOST_AUTO_TEST_SUITE( Transpose )

BOOST_AUTO_TEST_CASE_TEMPLATE( CreateAndCheck, T, test_types )
{
	T a[] = { T(3), T(23), T(17), T(11), T(51), T(97), T(397), T(511) };
	//T at[] = { T(3), T(23), T(17), T(11), T(51), T(97), T(397), T(511) };
	weak_matrix<T> m(a, 4, 2);
	BOOST_REQUIRE_NO_THROW( transpose(m) );
	BOOST_CHECK_EQUAL( transpose(m)(0, 0), m(0, 0) );
	BOOST_CHECK_EQUAL( transpose(m)(1, 0), m(0, 1) );
	BOOST_CHECK_EQUAL( transpose(m).width(), m.height() );
	BOOST_CHECK_EQUAL( transpose(m).height(), m.width() );
}

BOOST_AUTO_TEST_SUITE_END()
