#ifndef IBINDINGS_H_
#define IBINDINGS_H_

/**
 * @file
 * Define the public interface to bindings.
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
#include <unordered_map>
#include <unordered_set>

namespace elision {
namespace term {

/**
 * Specify the public interface to a binding.  A binding associates each of zero
 * or more variables (by name alone) with a corresponding term.  An individual
 * variable name, term pair is called a @b bind.  A binding may be empty, or it
 * may specify an arbitrary number of binds.
 *
 * Bindings may also be abstract, in that they may contain variables and are
 * treated as if they were associative and commutative, for the purpose of
 * matching.
 *
 * It is best to check whether a binding is abstract or not before making any
 * assumptions about its content.
 */
class IBinding : public virtual ITerm {
public:
	/**
	 * Determine if this binding is abstract or not.
	 * @return	True iff abstract.
	 */
	virtual bool is_abstract() const = 0;

	/**
	 * Get the non-abstract content of this binding as a map.
	 * @return	The concrete binds in this binding.
	 */
	virtual operator std::unordered_map<std::string const, Term>() const = 0;

	/**
	 * Get the term bound to the named variable, if any.  If none, then an
	 * exception is thrown.
	 * @param	name	The variable name.
	 * @return	The bound value.
	 * @throws	std::out_of_range	The variable name is not concretely bound.
	 */
	virtual Term get_bind(std::string const& name) = 0;

	/**
	 * Determine if this binding contains a bind for the given variable name.
	 * @param	name	The variable name.
	 * @return	True iff this binding binds the variable name concretely.
	 */
	virtual bool has_bind(std::string const& name) = 0;

	/**
	 * Get all the elements of this binding, concrete or not.
	 * @return	The complete set of elements of this binding.
	 */
	virtual std::unordered_set<Term> get_elements() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* IBINDINGS_H_ */
