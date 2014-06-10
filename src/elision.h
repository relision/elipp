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
#include <bitset>

/**
 * Elision is full of immutable objects passed by shared pointer.  This is
 * because these can, in turn, but part of multiple objects, so no particular
 * object "owns" an instance - thus shared pointers.  To make this less
 * cray-cray, we define a macro shorthand for this. This gives a constant
 * shared pointer to a constant instance of the type <tt>type_m</tt>.  If
 * you want to use this, you need to include memory, which is included by
 * this file.
 */
#define EPTR(type_m) std::shared_ptr<type_m const>

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
	if (!(x_m)) { \
		throw std::invalid_argument("The " #x_m " is null."); \
	}

/// Path separator character as C string.  Where is this defined?
#define PATHSEP "/"


/**
 * This is the namespace for all Elision-specific code.  It includes types,
 * classes, and functions for the C++ API.
 */
namespace elision {

/**
 * The preferred radix to use when no other radix is specified.
 */
extern uint8_t preferred_radix;
// Actual definition is in util.cpp.

/// Define the big integer implementation used by Elision.
typedef boost::multiprecision::cpp_int eint_t;

/**
* Produce an appropriately quoted version of a string. This can be either
* a string literal or a symbol. In either case special characters are
* escaped.
*
* If the input is a symbol that starts with a letter or underscore and
* contains only alphanumerics, then it is not quoted. Otherwise it is
* quoted with backticks. If the input is a string then it is always
* quoted with double quotation marks.
*
* @param original The original string.
* @param is_symbol True iff this is a symbol, and false for a string.
* @return The result of processing.
*/
std::string const escape(std::string const& original, bool is_symbol = false);

/**
 * Convert an unbounded integer to a string in the specified base.
 * The base must be one of the allowed values: 16, 10, 8, or 2.  Other
 * bases will result in an exception being thrown.
 *
 * If the prefix is enabled (the default) then the returned string has the
 * appropriate base prefix attached.  These are:
 *
 *   - ''0x'' for hexadecimal
 *   - nothing for decimal
 *   - ''0o'' for octal
 *   - ''0b'' for binary
 *
 * @param value		The integer.
 * @param base		The base, which must be 16, 10, 8, or 2.
 * @param prefix	Whether or not to include the base prefix in the string.
 * @return	The string, with any necessary base identifier.
 * @throws	invalid_argument	If the base is incorrect.
 */
std::string eint_to_string(eint_t value, uint16_t base, bool prefix = true);

/**
 * A stream manipulator to insert the current date and time in a stream.
 * Use this just like you would use std::endl.
 * @param out	The output stream.
 * @return	The output stream.
 */
std::ostream& timestamp(std::ostream& out);

}

#endif /* ELISION_H_ */
