#ifndef LAMBDAIMPL_H_
#define LAMBDAIMPL_H_

/**
 * @file
 * Define the interface to an implementation of a lambda.
 *
 * @author sprowell@gmail.com
 *
 * @verbatim
 *       _ _     _
 *   ___| (_)___(_) ___  _ __
 *  / _ \ | / __| |/ _ \| '_ \
 * |  __/ | \__ \ | (_) | | | |
 *  \___|_|_|___/_|\___/|_| |_|
 * The Elision Term Rewriter
 *
 * Copyright (c) 2014 by Stacy Prowell (sprowell@gmail.com)
 * All rights reserved.
 * @endverbatim
 */

#include "TermImpl.h"
#include "term/ILambda.h"
#include <Lazy.h>

namespace elision {
namespace term {
namespace basic {

using namespace elision;
using namespace elision::term;

class LambdaImpl: public ILambda, public TermImpl {
public:
	virtual ~LambdaImpl() = default;

	inline pTerm get_lhs() const {
		return lhs_;
	}

	inline pTerm get_rhs() const {
		return rhs_;
	}

	inline pTerm get_guard() const {
		return guard_;
	}

	inline bool is_constant() const {
		return lhs_->is_constant() && rhs_->is_constant() &&
				guard_->is_constant();
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<ILambda const*>(&other);
		return *get_lhs() == *oth->get_lhs() &&
				*get_rhs() == *oth->get_rhs() &&
				*get_guard() == *oth->get_guard();
	}

	inline TermKind get_kind() const {
		return LAMBDA_KIND;
	}

	inline std::string to_string() const {
		return strval_;
	}

private:
	friend class TermFactoryImpl;
	LambdaImpl(Locus the_loc, pTerm the_lhs, pTerm the_rhs, pTerm the_gaurd,
			pTerm the_type);
	pTerm lhs_;
	pTerm rhs_;
	pTerm guard_;
	Lazy<std::string> strval_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* LAMBDAIMPL_H_ */
