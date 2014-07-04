/**
 * @file
 * Provide implementations of the literals.
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

#include "LiteralImpl.h"
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>

namespace elision {
namespace term {
namespace basic {

//======================================================================
// Symbol literal.
//======================================================================

SymbolLiteralImpl::SymbolLiteralImpl(Locus the_loc, std::string the_name,
		pTerm the_type) : TermImpl(the_loc, the_type), name_(the_name) {
	strval_ = [this]() {
		return elision::escape(name_, true) + WITH_TYPE(type_);
	};
	depth_ = [this, the_type]() {
		return the_type->get_depth() + 1;
	};
	hash_ = [this]() {
		return boost::hash<std::string>()(name_);
	};
	other_hash_ = [this]() {
		return other_hash_combine(std::hash<std::string>()(name_), type_);
	};
}

//======================================================================
// String literal.
//======================================================================

StringLiteralImpl::StringLiteralImpl(Locus the_loc, std::string the_value,
		pTerm the_type) : TermImpl(the_loc, the_type), value_(the_value) {
	strval_ = [this]() {
		return elision::escape(value_, false) + WITH_TYPE(type_);
	};
	depth_ = [this, the_type]() {
		return the_type->get_depth() + 1;
	};
	hash_ = [this]() {
		return boost::hash<std::string>()(value_);
	};
	other_hash_ = [this]() {
		return other_hash_combine(std::hash<std::string>()(value_), type_);
	};
}

//======================================================================
// Integer literal.
//======================================================================

IntegerLiteralImpl::IntegerLiteralImpl(Locus the_loc, eint_t the_value,
		pTerm the_type) : TermImpl(the_loc, the_type), value_(the_value) {
	strval_ = [this]() {
		return elision::eint_to_string(value_,
				elision::preferred_radix, true) + WITH_TYPE(type_);
	};
	depth_ = [this, the_type]() {
		return the_type->get_depth() + 1;
	};
	hash_ = [this]() {
		return boost::hash<std::string>()(strval_);
	};
	other_hash_ = [this]() {
		size_t hash = std::hash<std::string>()(strval_);
		return other_hash_combine(hash, type_);
	};
}

//======================================================================
// Float literal.
//======================================================================

FloatLiteralImpl::FloatLiteralImpl(Locus the_loc, eint_t the_significand,
		eint_t the_exponent, uint8_t the_radix, pTerm the_type) :
				TermImpl(the_loc, the_type), significand_(the_significand),
				exponent_(the_exponent), radix_(the_radix) {
	if (the_radix != 2 &&
			the_radix != 8 &&
			the_radix != 10 &&
			the_radix != 16) {
		throw new std::invalid_argument(
				"The radix is not an allowed value: " +
				boost::lexical_cast<std::string>(the_radix));
	}
	strval_ = [this]() {
		return elision::eint_to_string(significand_, radix_, true) +
				(radix_ == 16 ? "p" : "e") +
				elision::eint_to_string(exponent_, radix_, true) +
				WITH_TYPE(type_);
	};
	depth_ = [this, the_type]() {
		return the_type->get_depth() + 1;
	};
	hash_ = [this]() {
		return boost::hash<std::string>()(strval_);
	};
	other_hash_ = [this]() {
		size_t hash = std::hash<std::string>()(strval_);
		return other_hash_combine(hash, type_);
	};
}

//======================================================================
// Bit string literal.
//======================================================================

BitStringLiteralImpl::BitStringLiteralImpl(Locus the_loc, eint_t the_bits,
		eint_t the_length, pTerm the_type) : TermImpl(the_loc, the_type),
				bits_(the_bits), length_(the_length) {
	strval_ = [this]() {
		return elision::eint_to_string(bits_, 16, true) + "L" +
				elision::eint_to_string(length_, 10, true) +
				WITH_TYPE(type_);
	};
	depth_ = [this, the_type]() {
		return the_type->get_depth() + 1;
	};
	hash_ = [this]() {
		return boost::hash<std::string>()(strval_);
	};
	other_hash_ = [this]() {
		size_t hash = std::hash<std::string>()(strval_);
		return other_hash_combine(hash, type_);
	};
}

//======================================================================
// Boolean literal.
//======================================================================

BooleanLiteralImpl::BooleanLiteralImpl(Locus the_loc, bool the_value,
		pTerm the_type) : TermImpl(the_loc, the_type), value_(the_value) {
	strval_ = [this]() {
		return std::string(value_ ? "true" : "false") + WITH_TYPE(type_);
	};
	depth_ = [this, the_type]() {
		return the_type->get_depth() + 1;
	};
	hash_ = [this]() {
		size_t hash = value_ ? 1 : 0;
		return hash_combine(hash, type_);
	};
	other_hash_ = [this]() {
		size_t hash = value_ ? 18 : 23;
		return other_hash_combine(hash, type_);
	};
}

//======================================================================
// Term literal.
//======================================================================

TermLiteralImpl::TermLiteralImpl(Locus the_loc, pTerm the_term,
		pTerm the_type) : TermImpl(the_loc, the_type), term_(the_term) {
	strval_ = [this]() {
		return "<" + term_->to_string() + ">";
	};
	depth_ = [this, the_type]() {
		return std::max(term_->get_depth(), the_type->get_depth()) + 1;
	};
	hash_ = [this]() {
		return hash_combine(term_->get_hash(), type_);
	};
	other_hash_ = [this]() {
		return other_hash_combine(term_->get_other_hash(), type_);
	};
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
