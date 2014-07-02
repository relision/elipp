#ifndef APPLYIMPL_H_
#define APPLYIMPL_H_

/**
 * @file
 * Define the interface for an implementation of apply.
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

#include "Lazy.h"
#include "TermImpl.h"
#include "term/IApply.h"

namespace elision {
namespace term {
namespace basic {

using namespace elision;
using namespace elision::term;

class ApplyImpl: public IApply, public TermImpl {
public:
	virtual ~ApplyImpl() = default;

	inline pTerm get_operator() const {
		return operator_;
	}

	inline pTerm get_argument() const {
		return argument_;
	}

	inline bool is_constant() const {
		return constant_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<IApply const*>(&other);
		return *get_operator() == *oth->get_operator() &&
				*get_argument() == *oth->get_argument();
	}

	inline TermKind get_kind() const {
		return APPLY_KIND;
	}

	virtual std::string to_string() const {
		return strval_;
	}

	inline unsigned int get_depth() const {
		return std::max(get_type()->get_depth(), operator_->get_depth(),
				argument_->get_depth()) + 1;
	}

private:
	friend class TermFactoryImpl;
	ApplyImpl(Locus the_loc, pTerm op, pTerm argument, pTerm the_type);
	pTerm operator_;
	pTerm argument_;
	Lazy<bool> constant_;
	Lazy<std::string> strval_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* APPLYIMPL_H_ */
