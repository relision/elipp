/**
 * @file
 * TODO: Describe purpose of file.
 *
 * @author sprowell@gmail.com
 *
 * @section LICENSE
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

#include "BasicLiteral.h"
#include "Term.h"

using elision::eint_t;

namespace elision {
namespace term {
namespace basic {

BasicSymbolLiteral::BasicSymbolLiteral(Loc const& loc, std::string const& name,
		Term const& type) : BasicTerm(loc, type), name_(name) {}

BasicStringLiteral::BasicStringLiteral(Loc const& loc, std::string const& value,
		Term const& type) : BasicTerm(loc, type), value_(value) {}

BasicIntegerLiteral::BasicIntegerLiteral(Loc const& loc, eint_t const& value,
		Term const& type) : BasicTerm(loc, type), value_(value) {}

BasicFloatLiteral::BasicFloatLiteral(Loc const& loc, eint_t const& significand,
		eint_t const& exponent, uint16_t radix, Term const& type) :
				BasicTerm(loc, type), significand_(significand),
				exponent_(exponent), radix_(radix) {}

BasicBitStringLiteral::BasicBitStringLiteral(Loc const& loc, eint_t const& bits,
		uint16_t length, Term const& type) : BasicTerm(loc, type), bits_(bits),
				length_(length) {}

BasicBooleanLiteral::BasicBooleanLiteral(Loc const& loc, bool value,
		Term const& type) : BasicTerm(loc, type), value_(value) {}

BasicTermLiteral::BasicTermLiteral(Loc const& loc, Term const& value,
		Term const& type) : BasicTerm(loc, type), term_(value) {}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
