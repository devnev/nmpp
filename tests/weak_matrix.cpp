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
#include <nmpp/auto_matrix.hpp>

using namespace nmpp;

typedef boost::mpl::list< double, int, std::complex<float> > test_types;

BOOST_AUTO_TEST_SUITE( WeakMatrixMembers )

BOOST_AUTO_TEST_CASE_TEMPLATE( DefaultCtor, T, test_types )
{
	weak_matrix<T> m;
	BOOST_CHECK_EQUAL( m.width(), 0 );
	BOOST_CHECK_EQUAL( m.height(), 0 );
	BOOST_CHECK_EQUAL( m.get(), ((T*)0) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( InitCtor, T, test_types )
{
	T a[] = { T(11), T(15), T(51), T(3), T(29), T(3491) };
	weak_matrix<T> m(a, 2, 3);
	BOOST_CHECK_EQUAL( m.width(), 2 );
	BOOST_CHECK_EQUAL( m.height(), 3 );
	BOOST_CHECK_EQUAL( m.get(), a );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AutoMatrixCtor, T, test_types )
{
	auto_matrix<T> am(11, 5);
	weak_matrix<T> wm(am);
	BOOST_CHECK_EQUAL( wm.width(), am.width() );
	BOOST_CHECK_EQUAL( wm.height(), am.height() );
	BOOST_CHECK_EQUAL( wm.get(), am.get() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( ConstAutoMatrixCtor, T, test_types )
{
	const auto_matrix<T> am(11, 5);
	weak_matrix<T> wm(am);
	BOOST_CHECK_EQUAL( wm.width(), am.width() );
	BOOST_CHECK_EQUAL( wm.height(), am.height() );
	BOOST_CHECK_EQUAL( wm.get(), am.get() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( CopyCtor, T, test_types )
{
	T a[] = { T(11), T(15), T(51), T(3), T(29), T(3491) };
	weak_matrix<T> wm1(a, 2, 3);
	weak_matrix<T> wm2(wm1);
	BOOST_CHECK_EQUAL( wm2.width(), wm1.width() );
	BOOST_CHECK_EQUAL( wm2.height(), wm1.height() );
	BOOST_CHECK_EQUAL( wm2.get(), wm1.get() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AssignOperatorEmpty, T, test_types )
{
	T a[] = { T(11), T(15), T(51), T(3), T(29), T(3491) };
	weak_matrix<T> wm1;
	weak_matrix<T> wm2(a, 2, 3);
	wm2 = wm1;
	BOOST_CHECK_EQUAL( wm2.width(), wm1.width() );
	BOOST_CHECK_EQUAL( wm2.height(), wm1.height() );
	BOOST_CHECK_EQUAL( wm2.get(), wm1.get() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AssignOperator, T, test_types )
{
	T a[] = { T(11), T(15), T(51), T(3), T(29), T(3491) };
	weak_matrix<T> wm1(a, 2, 3);
	weak_matrix<T> wm2;
	wm2 = wm1;
	BOOST_CHECK_EQUAL( wm2.width(), wm1.width() );
	BOOST_CHECK_EQUAL( wm2.height(), wm1.height() );
	BOOST_CHECK_EQUAL( wm2.get(), wm1.get() );
}

BOOST_AUTO_TEST_SUITE_END()
