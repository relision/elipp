#ifndef ITERM_H_
#define ITERM_H_

/**
 * @file
 * Define the public interface shared by all terms.
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

#include "elision.h"
#include "Loc.h"

namespace elision {
namespace term {

class ITerm;
/// Shorthand for a pointer to a term.
typedef std::shared_ptr<ITerm const> Term;

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
	virtual Term get_type() const = 0;

    /**
     * Produce a string representation of this term.  Since no enclosing
     * semantic information is available, this will not be optimum, but is
     * needed for debugging.  The basic structure of the returned string
     * should be Elision "source."
     * @return	The string representation of this term.
     */
	virtual operator std::string() const = 0;

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
};

/// Shorthand for using a term.

} /* namespace term */
} /* namespace elision */

#endif /* ITERM_H_ */
