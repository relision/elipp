/**
 * @file
 * Provide implementations of the variables.
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

#include <basic/VariableImpl.h>

namespace elision {
namespace term {
namespace basic {

VariableImpl::VariableImpl(Locus the_loc, std::string the_name,
		pTerm the_guard, pTerm the_type) : TermImpl(the_loc, the_type),
				name_(the_name), guard_(the_guard) {
	strval_ = [this]() {
		return std::string("$") + elision::escape(name_, true) +
				"{ " + guard_->to_string() + " }" +
				WITH_TYPE(type_);
	};
}

TermVariableImpl::TermVariableImpl(Locus the_loc, std::string the_name,
		pTerm the_type) : TermImpl(the_loc, the_type),
				name_(the_name) {
	strval_ = [this]() {
		return std::string("$") + elision::escape(name_, true) +
				WITH_TYPE(type_);
	};
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
