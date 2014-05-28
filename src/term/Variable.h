#ifndef VARIABLE_H_
#define VARIABLE_H_

/**
 * @file
 * Definition of variables.
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

class Variable : Term {
public:
	/**
	 * Get the name of the variable.
	 * @return	The variable name.
	 */
	virtual std::string const& get_name() const = 0;

	/**
	 * Get the guard for this variable.
	 * @return	The guard for the variable.
	 */
	virtual Term const& get_guard() const = 0;
};


class TermVariable : Term {
public:
	/**
	 * Get the name of the variable.
	 * @return	The variable name.
	 */
	virtual std::string const& get_name() const = 0;
};

} /* namespace term */
} /* namespace elision */


#endif /* VARIABLE_H_ */
