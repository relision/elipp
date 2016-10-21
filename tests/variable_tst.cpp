/**
 * @file
 * Test the variable implementations.
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

#include "test_frame.h"
#include "term/TermFactory.h"
#include "term/basic/TermFactoryImpl.h"
#include <boost/lexical_cast.hpp>

using namespace elision;
using namespace elision::term;

START_TEST

// Get a term factory.
HANG("Making a factory");
std::unique_ptr<TermFactory> fact(new elision::term::basic::TermFactoryImpl());
ENDL("Done");

START_ITEM(variables);

try {
	HANG("Making some variables");
	pVariable v1 = fact->get_variable(Loc::get_internal(), "x", fact->TRUE,
			fact->ANY);
	pVariable v2 = fact->get_variable(Loc::get(17, 21), "x", fact->TRUE,
			fact->ANY);
	pVariable v3 = fact->get_variable(Loc::get_internal(), "", fact->TRUE,
			fact->INTEGER);
	pVariable v4 = fact->get_variable(Loc::get_internal(), " y ", fact->TRUE,
			fact->ANY);
	pVariable v5 = fact->get_variable(Loc::get_internal(), "x", fact->TRUE,
			fact->FLOAT);
	pVariable v6 = fact->get_variable(Loc::get_internal(), "`f", fact->TRUE,
			fact->ANY);
	pVariable v7 = fact->get_variable(Loc::get_internal(), "x", fact->FALSE,
			fact->ANY);
	ENDL("Done");

	ENDL("Some variables"); PUSH;
	SHOW_STRING(*v1);
	SHOW_STRING(*v2);
	SHOW_STRING(*v3);
	SHOW_STRING(*v4);
	SHOW_STRING(*v5);
	SHOW_STRING(*v6);
	SHOW_STRING(*v7);
	POP;

	ENDL("Checking strings"); PUSH;
	VALIDATE(std::string(*v1), "$x{ true: BOOLEAN: ^ROOT }: ANY: ^ROOT", "1");
	VALIDATE(std::string(*v2), "$x{ true: BOOLEAN: ^ROOT }: ANY: ^ROOT", "2");
	VALIDATE(std::string(*v3), "$``{ true: BOOLEAN: ^ROOT }: INTEGER: ^ROOT", "3");
	VALIDATE(std::string(*v4), "$` y `{ true: BOOLEAN: ^ROOT }: ANY: ^ROOT", "4");
	VALIDATE(std::string(*v5), "$x{ true: BOOLEAN: ^ROOT }: FLOAT: ^ROOT", "5");
	VALIDATE(std::string(*v6), "$`\\`f`{ true: BOOLEAN: ^ROOT }: ANY: ^ROOT", "6");
	VALIDATE(std::string(*v7), "$x{ false: BOOLEAN: ^ROOT }: ANY: ^ROOT", "7");
	POP;

	ENDL("Testing equality and inequality");  PUSH;
	MUST_EQUAL(*v1, *v2, "different locus");
	MUST_NOT_EQUAL(*v1, *v3, "different types");
	MUST_NOT_EQUAL(*v1, *v7, "different guards");
	POP;
} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(variables, "");
}

END_ITEM(variables);

START_ITEM(term_variables);

try {

} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(term_variables, "");
}

END_ITEM(term_variables);

END_TEST
