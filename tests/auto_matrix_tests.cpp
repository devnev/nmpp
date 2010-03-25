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

#define BOOST_TEST_MODULE AutoMatrixTests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <nmpp/matrix.hpp>

BOOST_AUTO_TEST_SUITE( AutoMatrixSuite )

typedef boost::mpl::list<float, double, int> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE( DefaultCtor, T, test_types )
{
	auto_matrix<T> m;
	BOOST_CHECK_EQUAL( m.width(), 0 );
	BOOST_CHECK_EQUAL( m.height(), 0 );
	BOOST_CHECK_EQUAL( m.get(), ((T*)0) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AllocCtor, T, test_types )
{
	auto_matrix<T> m(22, 45);
	BOOST_CHECK_EQUAL( m.width(), 22 );
	BOOST_CHECK_EQUAL( m.height(), 45 );
	BOOST_CHECK_NE( m.get(), ((T*)0) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( InitCtor, T, test_types )
{
	auto_matrix<T> m(14, 43, (T)0);
	BOOST_CHECK_EQUAL( m.width(), 14 );
	BOOST_CHECK_EQUAL( m.height(), 43 );
	BOOST_REQUIRE_NE( m.get(), ((T*)0) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( ArrayCtor, T, test_types )
{
	T* a = new T[12*5];
	auto_matrix<T> m(a, 12, 5);
	BOOST_CHECK_EQUAL( m.width(), 12 );
	BOOST_CHECK_EQUAL( m.height(), 5 );
	BOOST_CHECK_EQUAL( m.get(), a );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AssignOperator1, T, test_types )
{
	auto_matrix<T> m1(17, 5);
	auto_matrix<T> m2;
	m2 = m1;
	BOOST_CHECK_EQUAL( m1.width(), m2.width() );
	BOOST_CHECK_EQUAL( m1.height(), m2.height() );
	BOOST_CHECK_NE( m1.get(), ((T*)0) );
	BOOST_CHECK_NE( m2.get(), ((T*)0) );
	BOOST_CHECK_NE( m1.get(), m2.get() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AssignOperator2, T, test_types )
{
	auto_matrix<T> m1;
	auto_matrix<T> m2(17, 5);
	m2 = m1;
	BOOST_CHECK_EQUAL( m1.width(), m2.width() );
	BOOST_CHECK_EQUAL( m1.height(), m2.height() );
	BOOST_CHECK_EQUAL( m1.get(), ((T*)0) );
	BOOST_CHECK_EQUAL( m2.get(), ((T*)0) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( Swap, T, test_types )
{
	auto_matrix<T> m1(17, 5);
	T* p = m1.get();
	auto_matrix<T> m2;
	BOOST_REQUIRE_NO_THROW( m1.swap(m2) );
	BOOST_CHECK_EQUAL( m1.width(), 0 );
	BOOST_CHECK_EQUAL( m1.height(), 0 );
	BOOST_CHECK_EQUAL( m2.width(), 17 );
	BOOST_CHECK_EQUAL( m2.height(), 5 );
	BOOST_CHECK_EQUAL( m1.get(), ((T*)0) );
	BOOST_CHECK_NE( m2.get(), ((T*)0) );
	BOOST_CHECK_EQUAL( m2.get(), p );
}

BOOST_AUTO_TEST_SUITE_END()
