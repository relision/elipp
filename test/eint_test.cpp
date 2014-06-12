/**
 * @file
 * Test working with unbounded integers.
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
#include "elision.h"

START_TEST

START_ITEM(bases)

	namespace e = elision;
	try {
		// Make some numbers and write them.
		e::eint_t value = 0;
		ENDL("Testing writing numbers."); PUSH;
		VALIDATE(e::eint_to_string(value, 2), "0b0", "");
		VALIDATE(e::eint_to_string(value, 8), "0o0", "");
		VALIDATE(e::eint_to_string(value, 10), "0", "");
		VALIDATE(e::eint_to_string(value, 16), "0x0", "");
		value = -1;
		VALIDATE(e::eint_to_string(value, 2), "-0b1", "");
		VALIDATE(e::eint_to_string(value, 8), "-0o1", "");
		VALIDATE(e::eint_to_string(value, 10), "-1", "");
		VALIDATE(e::eint_to_string(value, 16), "-0x1", "");
		value = 666;
		VALIDATE(e::eint_to_string(value, 2), "0b1010011010", "");
		VALIDATE(e::eint_to_string(value, 8), "0o1232", "");
		VALIDATE(e::eint_to_string(value, 10), "666", "");
		VALIDATE(e::eint_to_string(value, 16), "0x29A", "");
		value *= 1024;
		value *= 4096;
		value *= 16384;
		value *= 32768;
		value *= 8191;
#ifdef HAVE_BOOST_CPP_INT
		// This will only work with very large integer support.
		VALIDATE(e::eint_to_string(value, 8), "0o2463654600000000000000000", "");
		VALIDATE(e::eint_to_string(value, 10), "12284031854414647001088", "");
		VALIDATE(e::eint_to_string(value, 16), "0x299EB30000000000000", "");
#endif
		MUST_THROW(e::eint_to_string(value, 12), std::exception);
		POP;
	} catch (std:: exception& e) {
		ENDL("Caught an exception: " << e.what());
		POP;
		FAIL_ITEM(bases, "");
	}

END_ITEM(bases)

END_TEST
