#ifndef IBINDINGS_H_
#define IBINDINGS_H_

/**
 * @file
 * Define the public interface to bindings.
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
 * For performance, bindings are constants.  If you need to match on bindings,
 * they you need to transform them into some other kind of term.
 */
class IBinding : public virtual ITerm {
public:
	typedef std::unordered_map<std::string, pTerm> const map_t;

	/**
	 * Get the non-abstract content of this binding as a map.
	 * @return	The concrete binds in this binding.
	 */
	virtual std::shared_ptr<map_t> get_map() const = 0;

	/**
	 * Get the term bound to the named variable, if any.  If none, then an
	 * exception is thrown.
	 * @param	name	The variable name.
	 * @return	The bound value.
	 * @throws	std::out_of_range	The variable name is not concretely bound.
	 */
	virtual pTerm get_bind(std::string const& name) const = 0;

	/**
	 * Determine if this binding contains a bind for the given variable name.
	 * @param	name	The variable name.
	 * @return	True iff this binding binds the variable name concretely.
	 */
	virtual bool has_bind(std::string const& name) const = 0;
};

/// Shorthand for a binding pointer.
typedef std::shared_ptr<IBinding const> pBinding;

} /* namespace term */
} /* namespace elision */

#endif /* IBINDINGS_H_ */
