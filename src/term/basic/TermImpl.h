#ifndef TERM_H_
#define TERM_H_

/**
 * @file
 * Provide simple implementations of common elements for all terms.
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

#include "term/ITerm.h"

namespace elision {
namespace term {
namespace basic {

/**
 * Helper macro to return a pointer to a term formatted as type information
 * (with a leading colon), up to and including the root.  Use
 * `+WITH_TYPE(type_)` in most cases.
 */
#define WITH_TYPE(item_m) \
	(std::string(": ") + item_m->to_string())

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
	explicit TermImpl(pTerm the_type);

	/**
	 * Initialize a new instance.
	 * @param the_loc	The location of the term's declaration.
	 * @param the_type	The type of this term.
	 */
	TermImpl(Locus the_loc, pTerm the_type);

	/// Deallocate this instance.
	virtual ~TermImpl() = default;

	/// Return the type used during construction.
	inline virtual pTerm get_type() const {
		return type_;
	}

	virtual std::string to_string() const = 0;

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

	/// Return whether this is the unique root.  Default is NO.
	inline virtual bool is_root() const {
		return false;
	}

	/// Return whether this is the special true literal.  Default is NO.
	inline virtual bool is_true() const {
		return false;
	}

	/// Return whether this is the special false literal.  Default is NO.
	inline virtual bool is_false() const {
		return false;
	}

	/**
	 * Compare this instance to another instance of the same class.  To
	 * implement this make sure you first cast `other` to the correct class.
	 * If the derived class where the implementation lives is `B`, then do
	 * `dynamic_cast<B const&>(other)` and compare to `*this`.  Types have
	 * already been checked.
	 * @param other	The term to compare to.
	 * @return	True iff the two are equal.
	 */
	virtual bool is_equal(ITerm const& other) const = 0;

	pTerm type_;
	Locus loc_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* TERM_H_ */
