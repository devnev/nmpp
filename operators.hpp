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

#ifndef NMPP_OPERATORS_HPP
#define NMPP_OPERATORS_HPP

#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <algorithm>
#include <functional>

namespace nmpp {

namespace detail {

template<class LeftMatrixT, class RightMatrixT, class BinaryOpT>
class matrix_binary_op
{
	typedef LeftMatrixT left_type;
	typedef RightMatrixT left_type;
	typedef BinaryOpT op_type;
	typedef typename detail::matrix_const_ref<left_type>::type left_reference;
	typedef typename detail::matrix_const_ref<right_type>::type right_reference;
public:
	typedef typename op_type::result_type result_type;
	typedef result_type value_type;
	typedef matrix_binary_op<LeftMatrixT, RightMatrixT, BinaryOpT> this_type;
	typedef this_type matrix_ref;
	typedef this_type const_matrix_ref;

	matrix_binary_op(const left_type& lhs, const right_type& rhs, const op_type& op)
		: _lhs(lhs), _rhs(rhs), _op(op)
	{
	}
	matrix_binary_op(const this_type& other)
		: _lhs(other._lhs), _rhs(other._rhs), _op(other._op)
	{
	}

	value_type operator()(size_t x, size_t y) const { return _op(_lhs(x, y), _rhs(x, y)); }

	size_t width() const { return _lhs.width(); }
	size_t height() const { return _lhs.height(); }

private:
	left_reference _lhs;
	right_reference _rhs;
	BinaryOpT _op;
};

template<class MatrixT, class UnaryOpT>
class matrix_unary_op
{
	typedef MatrixT right_type;
	typedef UnaryOpT op_type;
	typedef typename detail::matrix_const_ref<right_type>::type right_reference;
public:
	typedef typename op_type::result_type result_type;
	typedef result_type value_type;
	typedef matrix_unary_op<MatrixT, UnaryOpT> this_type;
	typedef this_type matrix_ref;
	typedef this_type matrix_const_ref;

	matrix_unary_op(const right_type& rhs, const op_type& op)
		: _rhs(rhs), _op(op)
	{
	}
	matrix_unary_op(const this_type& other)
		: _rhs(other._rhs), _op(other._op)
	{
	}

	value_type operator()(size_t x, size_t y) const { return _op(_rhs(x, y)); }

	size_t width() const { return _rhs.width(); }
	size_t height() const { return _rhs.height(); }

private:
	right_reference _rhs;
	UnaryOpT _op;
};

} // end namespace detail

#define MPP_DEF_BINARY_MATRIX_OP(name, op_class) \
	template<class LeftMatrixT, class RightMatrixT> \
	detail::matrix_binary_op<LeftMatrixT, RightMatrixT, op_class <typename LeftMatrixT::value_type> > \
	name (const LeftMatrixT& lhs, const RightMatrixT& rhs) { \
		return detail::matrix_binary_op< LeftMatrixT, RightMatrixT, op_class <typename LeftMatrixT::value_type> >( \
			lhs, rhs, op_class <typename LeftMatrixT::value_type>()); \
	} \
	template<class LeftMatrixT, class RightMatrixT, class OutputT> \
	void \
	name (const LeftMatrixT& lhs, const RightMatrixT& rhs, OutputT& output) { \
		copy_matrix(name (lhs, rhs), output); \
	} \
	/**/
MPP_DEF_BINARY_MATRIX_OP(mplus, std::plus);
MPP_DEF_BINARY_MATRIX_OP(mminus, std::minus);
MPP_DEF_BINARY_MATRIX_OP(mmul, std::multiplies);
MPP_DEF_BINARY_MATRIX_OP(mdiv, std::divides);

#define MPP_DEF_BINARY_SCALAR_OP(name, op_class) \
	template<class MatrixT> \
	detail::matrix_binary_op< MatrixT, constant_matrix<typename MatrixT::value_type>, op_class <typename MatrixT::value_type> > \
	name (const MatrixT& lhs, typename MatrixT::value_type rhs) { \
		typedef typename MatrixT::value_type value_type; \
		return detail::matrix_binary_op< MatrixT, constant_matrix<value_type>, op_class <value_type> >( \
				lhs, constant_matrix<value_type>(rhs), op_class <value_type>()); \
	} \
	template<class MatrixT, class OutputT> \
	void \
	name (const MatrixT& lhs, typename MatrixT::value_type rhs, OutputT& output) { \
		copy_matrix(name (lhs, rhs), output); \
	} \
	/**/
MPP_DEF_BINARY_SCALAR_OP(splus, std::plus)
MPP_DEF_BINARY_SCALAR_OP(sminus, std::minus)
MPP_DEF_BINARY_SCALAR_OP(smul, std::multiplies)
MPP_DEF_BINARY_SCALAR_OP(sdiv, std::divides)

#define MPP_DEF_UNARY_MATRIX_OP_PTR(name, function) \
	template<class MatrixT> \
	detail::matrix_unary_op< MatrixT, pointer_to_unary_function<typename MatrixT::value_type, typename MatrixT::value_type> > \
	name (const MatrixT& input) { \
		typedef typename MatrixT::value_type value_type; \
		value_type (*fun_ptr)(value_type) = function; \
		return detail::matrix_unary_op< MatrixT, pointer_to_unary_function<value_type, value_type> >( \
			input, pointer_to_unary_function<value_type, value_type>(fun_ptr)); \
	} \
	template<class MatrixT, class OutputT> \
	void \
	name (const MatrixT& input, OutputT& output) { \
		copy_matrix(name (input), output); \
	} \
	/**/
MPP_DEF_UNARY_MATRIX_OP_PTR(mabs, std::abs)

} // end namespace nmpp

#endif // NMPP_OPERATORS_HPP
