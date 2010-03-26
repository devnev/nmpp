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
#include <nmpp/operators.hpp>

using namespace nmpp;

typedef boost::mpl::list< double, int, std::complex<float> > test_types;

BOOST_AUTO_TEST_SUITE( Operators )

BOOST_AUTO_TEST_CASE_TEMPLATE( Plus, T, test_types )
{
	T a1[] = { T(3), T(23) };
	T a2[] = { T(17), T(11) };
	weak_matrix<T> m1(a1, 2, 1);
	weak_matrix<T> m2(a2, 2, 1);
	BOOST_REQUIRE_NO_THROW( mplus(m1, m2) );
	BOOST_CHECK_EQUAL( mplus(m1, m2)(0, 0), T(3)+T(17) );
	BOOST_CHECK_EQUAL( mplus(m1, m2)(1, 0), T(23)+T(11) );
	BOOST_CHECK_EQUAL( mplus(m1, m2).width(), m1.width() );
	BOOST_CHECK_EQUAL( mplus(m1, m2).height(), m1.height() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( Minus, T, test_types )
{
	T a1[] = { T(3), T(23) };
	T a2[] = { T(17), T(11) };
	weak_matrix<T> m1(a1, 2, 1);
	weak_matrix<T> m2(a2, 2, 1);
	BOOST_REQUIRE_NO_THROW( mminus(m1, m2) );
	BOOST_CHECK_EQUAL( mminus(m1, m2)(0, 0), T(3)-T(17) );
	BOOST_CHECK_EQUAL( mminus(m1, m2)(1, 0), T(23)-T(11) );
	BOOST_CHECK_EQUAL( mminus(m1, m2).width(), m1.width() );
	BOOST_CHECK_EQUAL( mminus(m1, m2).height(), m1.height() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( Multiply, T, test_types )
{
	T a1[] = { T(3), T(23) };
	T a2[] = { T(17), T(11) };
	weak_matrix<T> m1(a1, 2, 1);
	weak_matrix<T> m2(a2, 2, 1);
	BOOST_REQUIRE_NO_THROW( mmul(m1, m2) );
	BOOST_CHECK_EQUAL( mmul(m1, m2)(0, 0), T(3)*T(17) );
	BOOST_CHECK_EQUAL( mmul(m1, m2)(1, 0), T(23)*T(11) );
	BOOST_CHECK_EQUAL( mmul(m1, m2).width(), m1.width() );
	BOOST_CHECK_EQUAL( mmul(m1, m2).height(), m1.height() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( Divide, T, test_types )
{
	T a1[] = { T(3), T(23) };
	T a2[] = { T(17), T(11) };
	weak_matrix<T> m1(a1, 2, 1);
	weak_matrix<T> m2(a2, 2, 1);
	BOOST_REQUIRE_NO_THROW( mdiv(m1, m2) );
	BOOST_CHECK_EQUAL( mdiv(m1, m2)(0, 0), T(3)/T(17) );
	BOOST_CHECK_EQUAL( mdiv(m1, m2)(1, 0), T(23)/T(11) );
	BOOST_CHECK_EQUAL( mdiv(m1, m2).width(), m1.width() );
	BOOST_CHECK_EQUAL( mdiv(m1, m2).height(), m1.height() );
}

BOOST_AUTO_TEST_SUITE_END()
