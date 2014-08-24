#ifndef ITERM_H_
#define ITERM_H_

/**
 * @file
 * Define the public interface shared by all terms.
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

#include "elision.h"
#include "Loc.h"

namespace elision {
namespace term {

#define CAST(type_m, ptr_m) \
	std::dynamic_pointer_cast<I ## type_m const>(ptr_m)

/**
 * The term kind is used to avoid relying on dynamic type information,
 * which can be costly (like `dynamic_cast`).
 *
 * A term kind specifies the level at which equality testing makes sense.
 * Terms of different kinds are unequal, and terms of the same kind may be
 * equal.
 *
 * The term kind also specifies the sort order among terms.  Items earlier
 * in the list sort earlier.
 */
enum TermKind {
	SYMBOL_LITERAL_KIND, STRING_LITERAL_KIND, INTEGER_LITERAL_KIND,
	FLOAT_LITERAL_KIND, BIT_STRING_LITERAL_KIND, BOOLEAN_LITERAL_KIND,
	TERM_LITERAL_KIND, VARIABLE_KIND, TERM_VARIABLE_KIND, BINDING_KIND,
	LAMBDA_KIND, LIST_KIND, PROPERTY_SPECIFICATION_KIND,
	SPECIAL_FORM_KIND, APPLY_KIND, ROOT_KIND, STATIC_MAP_KIND
};

class ITerm;
/// Shorthand for a pointer to a term.
typedef std::shared_ptr<ITerm const> pTerm;

class TermVisitor {
public:
	virtual ~TermVisitor() = default;
	virtual pTerm visit(pTerm term) = 0;
};

/**
 * This is the public interface shared by all terms.
 */
class ITerm {
public:
	/// The type to use for the depth of a term.
	typedef unsigned int depth_type;

	/// The type to use for indices.
	typedef unsigned int debruijn_type;

	/// Deallocate this instance.
	virtual ~ITerm() = default;

    /**
     * Get the type of this term.  Every term has an associated type which is
     * itself another term.  There is a special term, the "root," who's type
     * is itself, but this should not be true of any other term in the system.
     * In fact, other than the root, there should be no cycles in the types.
     * @return  The type of this term.
     */
	virtual pTerm get_type() const = 0;

    /**
     * Produce a string representation of this term.  Since no enclosing
     * semantic information is available, this will not be optimum, but is
     * needed for debugging.  The basic structure of the returned string
     * should be Elision "source."
     * @return	The string representation of this term.
     */
	virtual std::string to_string() const = 0;

    /**
     * Produce a string representation of this term.  Since no enclosing
     * semantic information is available, this will not be optimum, but is
     * needed for debugging.  The basic structure of the returned string
     * should be Elision "source."
     * @return	The string representation of this term.
     */
	inline virtual operator std::string() const {
		return to_string();
	}

	/**
	 * Return the hash code for this particular term.  Terms that are equal
	 * have equal hash codes.
	 * @return	The hash code.
	 */
	virtual size_t get_hash() const = 0;

	/**
	 * Return the other hash code for this particular term.  Terms that are
	 * equal have equal other hash codes.
	 * @return 	The other hash code.
	 */
	virtual size_t get_other_hash() const = 0;

    /**
     * Get the de Bruijn index of this term.
     *
     * De Bruijn indices are used for lambdas to prevent "capturing" free
     * variables prematurely.  See
     * https://en.wikipedia.org/wiki/De_Bruijn_index.
     *
     * Terns that do not contain variables bound in lambdas will have an
     * index of zero.  Otherwise the index will be positive.
     * @return	The De Bruijn index of this term.
     */
	virtual debruijn_type get_de_bruijn_index() const = 0;

    /**
     * Get the depth of this term.  The depth of the root is zero; otherwise
     * the depth is one plus the maximum depth of all child terms, with a few
     * exceptions noted below.
     *
     * Depth is used in matching, with the intent that if the pattern depth
     * exceeds the subject depth, no match is possible.  For this reason the
     * depth of the type is included, but the depth of guards (for variables
     * and lambdas) is not.
     *
     * @return	The depth of the term.
     */
	virtual depth_type get_depth() const = 0;

    /**
     * Determine if this is a metaterm or not.  A term is a metaterm if it
     * contains a term variable or a metaterm.
     * @return	True iff this is a metaterm.
     */
	virtual bool is_meta_term() const = 0;

    /**
     * Determine if this term is a constant.  A constant term consists of just
     * a literal or combinations of literals, and has no variables.  This
     * includes any form of lambda who's body is a constant, even though the
     * lambda contains a variable for its parameter.
     * @return	True iff this term is a constant.
     */
	virtual bool is_constant() const = 0;

    /**
     * Get the location of this term's declaration.  This can be a location in
     * a source file, or some special location, depending on why the term was
     * constructed.
     * @return	The location of this term's declaration.
     */
	virtual Locus get_loc() const = 0;

	/**
	 * The unique root term must return true here, and all others must return
	 * false.  This is used to prevent endless (endless ...) recursion.
	 * @return	True iff this is the unique root type.
	 */
	virtual bool is_root() const = 0;

	/**
	 * Determine if this term is the literal true value.
	 * @return	True if this term is the special literal true value.
	 */
	virtual bool is_true() const = 0;

	/**
	 * Determine if this term is the literal false value.
	 * @return	True if this term is the special literal false value.
	 */
	virtual bool is_false() const = 0;

	/**
	 * Get the kind for this term.
	 * @return	The term kind.
	 */
	virtual TermKind get_kind() const = 0;

	/**
	 * Equality test for terms that delegates to the term-centric is_equal
	 * method.
	 * @param first		First term.
	 * @param second	Second term.
	 * @return	True if these terms are equal, and false if they are not.
	 */
	friend bool operator==(ITerm const& first, ITerm const& second);

	/**
	 * Inequality test for terms that delegates to the equality test.
	 * @param first		First term.
	 * @param second	Second term.
	 * @return	True if these terms are not equal, and false if they are.
	 */
	friend bool operator!=(ITerm const& first, ITerm const& second);

private:
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
};

/// Shorthand for using a term.

} /* namespace term */
} /* namespace elision */

#endif /* ITERM_H_ */
