#ifndef IVARIABLE_H_
#define IVARIABLE_H_

/**
 * @file
 * Define the public interfaces for variables.
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

namespace elision {
namespace term {

/**
 * Specify the public interface to a variable that represents a value.
 */
class IVariable : public virtual ITerm {
public:
	/**
	 * Get the name of this variable.  Variables are uniquely identified by
	 * their name.
	 * @return The variable name.
	 */
	virtual std::string const get_name() const = 0;

	/**
	 * Get the guard for this variable.  A guard specifies the conditions
	 * under which the variable can be bound to another term.  The proposed
	 * value is substituted for the variable in the guard and, if the guard
	 * evaluates to <tt>true</tt>, then the binding is allowed.  If it does
	 * not, then the binding is rejected.
	 *
	 * Note that the trivial guard (always allowed) is <tt>true</tt>.
	 * @return	The guard for the variable.
	 */
	virtual pTerm get_guard() const = 0;
};

/// Shorthand for a variable pointer.
typedef std::shared_ptr<IVariable const> pVariable;


/**
 * Specify the public interface to a term variable.  Regular variables represent
 * values, but term variables represent terms; that is, term variables are
 * meta-variables.
 */
class ITermVariable : public virtual ITerm {
public:
	/**
	 * Get the name of this variable.  Variables are uniquely identified by
	 * their name.
	 * @return	The variable name.
	 */
	virtual std::string const get_name() const = 0;
};

/// Shorthand for a variable pointer.
typedef std::shared_ptr<ITermVariable const> pTermVariable;

} /* namespace term */
} /* namespace elision */

#endif /* IVARIABLE_H_ */
