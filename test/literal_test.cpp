/**
 * @file
 * Perform testing on literals.
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

#include "test_frame.h"
#include "ITermFactory.h"
#include "basic/TermFactory.h"
#include <boost/lexical_cast.hpp>

using namespace elision;
using namespace elision::term;

START_TEST

// Get a term factory.
HANG("Making a factory")
std::unique_ptr<ITermFactory> fact(new elision::term::basic::TermFactory());
ENDL("Done")

START_ITEM(symbols)

END_ITEM(symbols)

START_ITEM(strings)

END_ITEM(strings)

START_ITEM(integers)

END_ITEM(integers)

START_ITEM(floats)

END_ITEM(floats)

START_ITEM(bitstrings)

END_ITEM(bitstrings)

START_ITEM(booleans)

try {
	// Make some Booleans.
	HANG("Making Booleans");
	EPTR(IBooleanLiteral) b1 = fact->get_boolean_literal(Loc::get_internal(), true, fact->get_root());
	EPTR(IBooleanLiteral) b2 = fact->get_boolean_literal(Loc::get_internal(), false, fact->get_root());
	EPTR(IBooleanLiteral) b3 = fact->get_boolean_literal(true);
	EPTR(IBooleanLiteral) b4 = fact->get_boolean_literal(false);
	EPTR(IBooleanLiteral) b5 = fact->get_boolean_literal(Loc::get(17,21), true);
	EPTR(IBooleanLiteral) b6 = fact->get_boolean_literal(Loc::get(21,17), false);
	ENDL("Done");

	ENDL("Some Booleans")
	ENDL(std::string(*b1));
	ENDL(std::string(*b2));
	ENDL(std::string(*b3));
	ENDL(std::string(*b4));
	ENDL(std::string(*b5));
	ENDL(std::string(*b6));

	// Check values.
	HANG("Checking stored values");
	VALIDATE(booleans, b1->get_value(), true, "1");
	VALIDATE(booleans, b2->get_value(), false, "2");
	VALIDATE(booleans, b3->get_value(), true, "3");
	VALIDATE(booleans, b4->get_value(), false, "4");
	VALIDATE(booleans, b5->get_value(), true, "5");
	VALIDATE(booleans, b6->get_value(), false, "6");
	ENDL("Done")

	// Location does not matter when comparing.
	HANG("Checking equality");
	if (*b1 != *b1) {
		FAIL_ITEM(booleans, "Equal true Booleans show unequal (try 1).");
	}
	if (*b1 != *b3) {
		FAIL_ITEM(booleans, "Equal true Booleans show unequal (try 2).");
	}
	if (*b1 != *b5) {
		FAIL_ITEM(booleans, "Equal true Booleans show unequal (try 3).");
	}
	if (*b2 != *b2) {
		FAIL_ITEM(booleans, "Equal false Booleans show unequal (try 4).");
	}
	if (*b4 != *b2) {
		FAIL_ITEM(booleans, "Equal false Booleans show unequal (try 5).");
	}
	if (*b6 != *b2) {
		FAIL_ITEM(booleans, "Equal false Booleans show unequal (try 6).");
	}
	if (*b1 == *b2) {
		FAIL_ITEM(booleans, "Unequal Booleans show equal (try 1).");
	}
	if (*b4 == *b3) {
		FAIL_ITEM(booleans, "Unequal Booleans show equal (try 2).");
	}
	ENDL("Done")

	// Check the string values.
	HANG("Checking string cast")
	VALIDATE(booleans, std::string(*b1), "true", "1");
	VALIDATE(booleans, std::string(*b2), "false", "2");
	VALIDATE(booleans, std::string(*b3), "true", "3");
	VALIDATE(booleans, std::string(*b4), "false", "4");
	VALIDATE(booleans, std::string(*b5), "true", "5");
	VALIDATE(booleans, std::string(*b6), "false", "6");
	ENDL("Done")

	// Check the Boolean values.
	HANG("Checking Boolean cast")
	VALIDATE(booleans, bool(*b1), true, "1");
	VALIDATE(booleans, bool(*b2), false, "2");
	VALIDATE(booleans, bool(*b3), true, "3");
	VALIDATE(booleans, bool(*b4), false, "4");
	VALIDATE(booleans, bool(*b5), true, "5");
	VALIDATE(booleans, bool(*b6), false, "6");
	ENDL("Done")
} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(booleans, "");
}

// Done with the factory.  Explicitly release it.
fact.release();

END_ITEM(booleans)

END_TEST
