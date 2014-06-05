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
		ENDL("Testing writing numbers.")
		VALIDATE(bases, e::eint_to_string(value, 2), "0b0", "");
		VALIDATE(bases, e::eint_to_string(value, 8), "0o0", "");
		VALIDATE(bases, e::eint_to_string(value, 10), "0", "");
		VALIDATE(bases, e::eint_to_string(value, 16), "0x0", "");
		value = -1;
		VALIDATE(bases, e::eint_to_string(value, 2), "-0b1", "");
		VALIDATE(bases, e::eint_to_string(value, 8), "-0o1", "");
		VALIDATE(bases, e::eint_to_string(value, 10), "-1", "");
		VALIDATE(bases, e::eint_to_string(value, 16), "-0x1", "");
		value = 666;
		VALIDATE(bases, e::eint_to_string(value, 2), "0b1010011010", "");
		VALIDATE(bases, e::eint_to_string(value, 8), "0o1232", "");
		VALIDATE(bases, e::eint_to_string(value, 10), "666", "");
		VALIDATE(bases, e::eint_to_string(value, 16), "0x29A", "");
		value *= 1024;
		value *= 4096;
		value *= 16384;
		value *= 32768;
		value *= 8191;
		VALIDATE(bases, e::eint_to_string(value, 8), "0o2463654600000000000000000", "");
		VALIDATE(bases, e::eint_to_string(value, 10), "12284031854414647001088", "");
		VALIDATE(bases, e::eint_to_string(value, 16), "0x299EB30000000000000", "");
		try {
			e::eint_to_string(value, 12);
			FAIL_ITEM(bases, "Base 12 did not cause an exception.");
		} catch (std::invalid_argument& e) {
			// Just the right thing.
		}
	} catch (std:: exception& e) {
		FAIL_ITEM(bases, "");
		ENDL("Caught an exception: " << e.what());
	}

END_ITEM(bases)

END_TEST
