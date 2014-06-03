#ifndef TERM_H_
#define TERM_H_

/**
 * @file
 * Define the basic types that are used by all terms.
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

#include <memory>
#include "Loc.h"
#include "elision.h"

namespace elision {
namespace term {

/**
 * This is the common base class for all terms.
 */
class Term {
public:
	/// Deallocate this instance.
	virtual ~Term() = default;

    /**
     * Get the type of this term.  Every term has an associated type.
     * @return  The type of this term.
     */
    virtual Term const& get_type() const = 0;

    /**
     * Produce a string representation of this term.  Since no enclosing
     * semantic information is available, this will not be optimum, but is
     * needed for debugging.
     * @return	The string representation of this term.
     */
    virtual operator std::string() const = 0;

    /**
     * Get the de Bruijn index of this term.
     * @return	The De Bruijn index of this term.
     */
    virtual unsigned int get_de_bruijn_index() const = 0;

    /**
     * Get the depth of this term.  Literals have depth zero.
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
     * a literal or combinations of literals.
     * @return	True iff this term is a constant.
     */
    virtual bool is_constant() const = 0;

    /**
     * Get the location of this term's declaration.
     * @return	The location of this term's declaration.
     */
    virtual Loc const& get_loc() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* TERM_H_ */
