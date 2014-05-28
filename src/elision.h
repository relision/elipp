#ifndef ELISION_H_
#define ELISION_H_

/**
 * @file
 * Shared definitions for the Elision project.
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
 * Copyright (c) 2014 by Stacy Prowell (sprowell@gmail.com).
 * All rights reserved.
 * @endverbatim
 */

#include <string>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdint.h>
#include <boost/multiprecision/cpp_int.hpp>


/**
 * Construct a string using the << operator, and then perform the action
 * act_m, passing the string in parentheses.  This is a funny little macro
 * that can be used in several ways.
 *
 * The key idea is that << is commonly overloaded to do the Right Thing
 * with values, whereas the std::string + operator is seldom correctly
 * overloaded.  Boo!  Plus << has manipulators.
 *
 * This macro is why @<sstream@> is included.
 *
 * @b Example:
 * Throwing an exception.
 * @code
 * ELISTR(throw std::invalid_argument,
 *     "The value " << value << " is out of range.");
 * @endcode
 *
 * @b Example:
 * Assigning a string value.
 * @code
 * ELISTR(std::string msg=,
 *     "The value " << value << " is out of range.");
 * @endcode
 *
 * @b Example:
 * Passing a string argument to a function.
 * @code
 * ELISTR(foo, "The value " << value << " is out of range.");
 * @endcode
 */
#define ELISTR(act_m, exp_m) \
	{ \
		std::ostringstream msg; \
		msg << exp_m; \
		act_m(msg.str()); \
	}

/// Check an argument for null.
#define NOTNULL(x_m) \
	if (0L == x_m) { \
		throw invalid_argument("The " #x_m " is null."); \
	}

/// Path separator character as C string.  Where is this defined?
#define PATHSEP "/"


/**
 * This is the namespace for all Elision-specific code.  It includes types,
 * classes, and functions for the C++ API.
 */
namespace elision {

/// Define a string, as used by Elision.
typedef std::string estr_t;
/// Define the big integer implementation used by Elision.
typedef boost::multiprecision::cpp_int eint_t;

/**
 * A stream manipulator to insert the current date and time in a stream.
 * Use this just like you would use std::endl.
 * @param out	The output stream.
 * @return	The output stream.
 */
std::ostream& timestamp(std::ostream& out);

}

#endif /* ELISION_H_ */
