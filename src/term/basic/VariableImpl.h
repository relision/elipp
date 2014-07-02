#ifndef VARIABLEIMPL_H_
#define VARIABLEIMPL_H_

/**
 * @file
 * Provide a basic implementation of variables.
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
#include "term/IVariable.h"
#include <Lazy.h>

namespace elision {
namespace term {
namespace basic {

using namespace elision;
using namespace elision::term;

class VariableImpl : public IVariable, public TermImpl {
public:
	virtual ~VariableImpl() = default;

	inline virtual std::string const get_name() const {
		return name_;
	}

	inline virtual pTerm get_guard() const {
		return guard_;
	}

	inline virtual bool is_constant() const {
		return false;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<IVariable const*>(&other);
		return get_name() == oth->get_name() &&
				*get_guard() == *oth->get_guard();
	}

	inline TermKind get_kind() const {
		return VARIABLE_KIND;
	}

	inline unsigned int get_depth() const {
		return get_type()->get_depth();
	}

private:
	friend class TermFactoryImpl;
	VariableImpl(Locus the_loc, std::string the_name, pTerm the_guard,
			pTerm the_type);
	std::string const name_;
	pTerm guard_;
	Lazy<std::string> strval_;
};


class TermVariableImpl : public ITermVariable, public TermImpl {
public:
	virtual ~TermVariableImpl() = default;

	inline virtual std::string const get_name() const {
		return name_;
	}

	inline virtual pTerm const get_term_type() const {
		return term_type_;
	}

	inline virtual bool is_constant() const {
		return false;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<ITermVariable const*>(&other);
		return get_name() == oth->get_name();
	}

	inline TermKind get_kind() const {
		return TERM_VARIABLE_KIND;
	}

	inline unsigned int get_depth() const {
		return get_type()->get_depth();
	}

private:
	friend class TermFactoryImpl;
	TermVariableImpl(Locus the_loc, std::string the_name, pTerm term_type,
			pTerm the_type);
	std::string const name_;
	pTerm term_type_;
	Lazy<std::string> strval_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* VARIABLEIMPL_H_ */
