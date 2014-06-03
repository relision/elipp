#ifndef BASICTERM_H_
#define BASICTERM_H_

/**
 * @file
 * Provide a basic definition of a term.
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

#include "Term.h"

namespace elision {
namespace term {
namespace basic {

/**
 * Produce an appropriately quoted version of a string.  This can be either
 * a string literal or a symbol.  In either case special characters are
 * escaped.
 *
 * If the input is a symbol that starts with a letter or underscore and
 * contains only alphanumerics, then it is not quoted.  Otherwise it is
 * quoted with backticks.  If the input is a string then it is always
 * quoted with double quotation marks.
 *
 * @param original	The original string.
 * @param is_symbol	True iff this is a symbol, and false for a string.
 * @return	The result of processing.
 */
std::string const escape(std::string const& original, bool is_symbol);

/**
 * Provide a basic implementation of elements common to terms.
 */
class BasicTerm: public elision::term::Term {
public:
	/**
	 * Make a new instance.
	 * @param loc		The location of the term's definition.
	 * @param type		The type of this term.
	 */
	BasicTerm(Loc const& loc, Term const& type);

	/// Deallocate this instance.
	virtual ~BasicTerm() = default;

	/* Methods inherited from Term. */

    virtual Term const& get_type() const;

    virtual operator std::string() const;

    virtual unsigned int get_de_bruijn_index() const;

    virtual unsigned int get_depth() const;

    virtual bool is_meta_term() const;

    virtual bool is_constant() const;

    virtual Loc const& get_loc() const;

private:
	Loc const& loc_;
	Term const& type_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* BASICTERM_H_ */
