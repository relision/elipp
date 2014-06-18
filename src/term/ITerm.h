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
	SYMBOL_LITERAL, STRING_LITERAL, INTEGER_LITERAL, FLOAT_LITERAL,
	BIT_STRING_LITERAL, BOOLEAN_LITERAL, TERM_LITERAL,
	VARIABLE, TERM_VARIABLE, BINDING, LAMBDA, MAP_PAIR, LIST,
	PROPERTY_SPECIFICATION, SPECIAL_FORM, APPLY, ROOT, STATIC_MAP
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
	virtual unsigned int get_de_bruijn_index() const = 0;

    /**
     * Get the depth of this term.  Literals have depth zero, as do variables.
     * The depth of the term is independent of its type.  When a term contains
     * another term, the depth is one plus the maximum depth of the contained
     * terms.
     * @return	The depth of the term.
     */
	virtual unsigned int get_depth() const = 0;

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
