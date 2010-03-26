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
#include <nmpp/uniform_matrix.hpp>

using namespace nmpp;

typedef boost::mpl::list< double, int, std::complex<float> > test_types;

BOOST_AUTO_TEST_SUITE( Uniform )

BOOST_AUTO_TEST_CASE_TEMPLATE( CreateAndCheck, T, test_types )
{
	BOOST_REQUIRE_NO_THROW( uniform(T(7)) );
	BOOST_CHECK_EQUAL( uniform(T(7))(0, 0), T(7) );
	BOOST_CHECK_EQUAL( uniform(T(13))(743987, 1841143), T(13) );
	BOOST_CHECK_EQUAL( uniform(T(29))(473, 3268), T(29) );
}

BOOST_AUTO_TEST_SUITE_END()
