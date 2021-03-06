#ifndef ELISION_H_
#define ELISION_H_

/**
 * @file
 * Shared definitions for the Elision project.
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
 * Copyright (c) 2014 by Stacy Prowell (sprowell@gmail.com).
 * All rights reserved.
 * @endverbatim
 */

#include <string>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdint.h>
#ifdef HAVE_BOOST_CPP_INT
#  include <boost/multiprecision/cpp_int.hpp>
#endif
#include <bitset>

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
 * Cast the provided pointer to a pointer of the appropriate type.  This uses
 * a dynamic cast, so it is checked.
 * @param type_m	The type to which to cast.
 * @param ptr_m		The pointer to cast.
 */
#define PCAST(type_m, ptr_m) \
	dynamic_cast<type_m const *>(ptr_m)

/**
 * Cast the provided reference to a pointer of the appropriate type.  This uses
 * a dynamic cast, so it is checked.
 * @param type_m	The type to which to cast.
 * @param ptr_m		The pointer to cast.
 */
#define CAST(type_m, ref_m) \
	dynamic_cast<type_m const *>(& ref_m)

/**
 * Cast a term (that is typically passed as a shared pointer) to another term
 * type using a dynamic cast.
 * @param type_m	The new type.
 * @param term_m	The term.
 */
#define TERM_CAST(type_m, term_m) \
	std::dynamic_pointer_cast<type_m const>(term_m)

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
#ifdef HAVE_BOOST_CPP_INT
typedef boost::multiprecision::cpp_int eint_t;
#else
typedef int64_t eint_t;
#endif

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
