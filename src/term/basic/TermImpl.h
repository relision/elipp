#ifndef TERM_H_
#define TERM_H_

/**
 * @file
 * Provide simple implementations of common elements for all terms.
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

#include "ITerm.h"

namespace elision {
namespace term {
namespace basic {

/**
 * Partial implementation of a term.  This class is abstract; subclasses
 * must implement at least `is_constant` and the `std::string` operator.
 */
class TermImpl: public virtual elision::term::ITerm {
public:
	/**
	 * Initialize a new instance.  The location is "internal."
	 * @param the_type	The type of this term.
	 */
	explicit TermImpl(Term the_type);

	/**
	 * Initialize a new instance.
	 * @param the_loc	The location of the term's declaration.
	 * @param the_type	The type of this term.
	 */
	TermImpl(Locus the_loc, Term the_type);

	/// Deallocate this instance.
	virtual ~TermImpl() = default;

	/// Return the type used during construction.
	inline virtual Term get_type() const {
		return type_;
	}

	/// Subclasses must provide an implementation.
	virtual operator std::string() const = 0;

	/// Return the default of zero.  Override if you need to.
	inline virtual unsigned int get_de_bruijn_index() const {
		return 0;
	}

	/// Return the default of zero.  Override if you need to.
	inline virtual unsigned int get_depth() const {
		return 0;
	}

	/// Return the default of false.  Override if you need to.
	inline virtual bool is_meta_term() const {
		return false;
	}

	/// Subclasses must provide an implementation.
	virtual bool is_constant() const = 0;

	/// Return the location provided during construction.
	inline virtual Locus get_loc() const {
		return loc_;
	}

protected:
	Term type_;
	Locus loc_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* TERM_H_ */
