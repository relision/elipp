#ifndef LAMBDAIMPL_H_
#define LAMBDAIMPL_H_

/**
 * @file
 * Define the interface for an implementation of lambdas.
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
#include "Lazy.h"

namespace elision {
namespace term {
namespace basic {

using namespace elision;
using namespace elision::term;

class LambdaImpl: public ILambda, public TermImpl {
public:
	virtual ~LambdaImpl() = default;

	inline pVariable get_parameter() const {
		return parameter_;
	}

	inline pTerm get_body() const {
		return body_;
	}

	inline bool is_constant() const {
		return body_->is_constant();
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<ILambda const*>(&other);
		return *get_parameter() == *oth->get_parameter() &&
				*get_body() == *oth->get_body();
	}

	inline TermKind get_kind() const {
		return LAMBDA;
	}

	inline std::string to_string() const {
		return strval_;
	}

private:
	friend class TermFactoryImpl;
	LambdaImpl(Locus the_loc, pVariable the_parameter, pTerm the_body,
			pTerm the_type);
	pVariable parameter_;
	pTerm body_;
	Lazy<std::string> strval_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* LAMBDAIMPL_H_ */
