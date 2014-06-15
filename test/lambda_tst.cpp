/**
 * @file
 * Perform structural testing on lambdas.
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

START_ITEM(lambdas)

try {
	// Make some lambdas
	HANG("Making lambdas");
	pVariable x = fact->get_variable(Loc::get_internal(), "x", fact->TRUE,
			fact->ANY);
	pVariable xx = fact->get_variable(Loc::get(17, 21), "x", fact->TRUE,
			fact->ANY);
	pVariable y = fact->get_variable(Loc::get_internal(), "y", fact->TRUE,
			fact->ANY);
	pLambda l1 = fact->get_lambda(Loc::get_internal(), x, fact->TRUE);
	pLambda l2 = fact->get_lambda(Loc::get(21, 17), xx, fact->TRUE);
	pLambda l3 = fact->get_lambda(Loc::get_internal(), y, fact->TRUE);
	pLambda l4 = fact->get_lambda(Loc::get_internal(), x, fact->FALSE);
	ENDL("Done");

	ENDL("Some lambdas"); PUSH;
	SHOW_STRING(*l1);
	POP;

	ENDL("Checking string cast"); PUSH;
	VALIDATE(std::string(*l1), "\\$x{ true: BOOLEAN: ^ROOT }: "
			"ANY: ^ROOT.true: BOOLEAN: ^ROOT", "1");
	POP;

	ENDL("Checking equality and inequality"); PUSH;
	MUST_EQUAL(*l1, *l1, "same");
	MUST_EQUAL(*l1, *l2, "identical");
	MUST_NOT_EQUAL(*l1, *l3, "different parameter");
	MUST_NOT_EQUAL(*l1, *l4, "different guard");
	POP;
} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(lambdas, "");
}

END_ITEM(lambdas)

END_TEST
