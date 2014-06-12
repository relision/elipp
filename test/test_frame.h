#ifndef TEST_FRAME_H_
#define TEST_FRAME_H_

/**
 * @file
 * Common test framework.
 *
 * To use this, include this header file.  You then define a test using
 * START_TEST and END_TEST.  Within a test you can define individual
 * items with the START_ITEM(name_m) and END_ITEM(name_m) macros.  The
 * name you use is significant, and must match the start and end markers.
 * If you use FAIL_ITEM(name_m) to fail an item, the name must match
 * there, too.  If you get really odd errors, check that names match
 * in your macros for an item.
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

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime> // For time.
#include <cstdlib> // For srand and rand.
#include "elision.h"

//======================================================================
// Private macros used to implement parts of the test framework.
//======================================================================

/// Create a label for a goto.
#define LABEL(x_m) LABEL ## x_m

/// Convert the macro argument into a quoted string.  Use STRINGIFY instead.
#define STRINGIFY_(x_m) #x_m

/// Convert the macro argument into a quoted string.
#define STRINGIFY(x_m) STRINGIFY_(x_m)

/// If an end of line is needed, emit one.
#define IF_ENDL \
	if (tf_need_endl) { \
		std::cout << std::endl; \
		tf_need_endl = false; \
		tf_need_space = false; \
		tf_need_indent = true; \
	}

/// If a space is needed, emit one.
#define IF_SPACE \
	if (tf_need_space) { \
		std::cout << " "; \
		tf_need_space = false; \
	}

/// If indentation is needed, emit it.
#define IF_INDENT \
	if (tf_need_indent) { \
		std::cout << "  "; \
		for (int i_m = 0; i_m < tf_indent_level; i_m++) { \
			std::cout << "  "; \
		} \
		tf_need_indent = false; \
		tf_need_space = false; \
		tf_need_endl = false; \
	}

/// Emit a timestamp.
#define TS(str_m) \
	{ \
		IF_ENDL; \
		std::cout << str_m << " " << elision::timestamp; \
	}

//======================================================================
// Public macros to write output during a test.
//======================================================================

/**
 * Write a message.  The message is flushed immediately.
 */
#define FLUSH(str_m) \
	{ \
		IF_INDENT; \
		IF_SPACE; \
		std::cout << str_m << std::flush; \
		tf_need_space = false; \
	}

/**
 * Write a message, followed by an end of line.  It is important to use
 * this, and not use std::endl yourself, since this will correctly indent
 * the next line, if appropriate.
 */
#define ENDL(str_m) \
	{ \
		IF_INDENT; \
		IF_SPACE; \
		std::cout << str_m << std::endl; \
		tf_need_space = false; \
		tf_need_endl = false; \
		tf_need_indent = true; \
	}

/**
 * Write a "hanging" message.  This is a message that ends with an
 * elipsis, and indicates a (possibly lengthy) process is taking place.
 * The line is flushed, but not ended, so subsequent message (such as
 * success or failure) appears on the same line.
 */
#define HANG(str_m) \
	{ \
		IF_INDENT; \
		IF_ENDL; \
		FLUSH(str_m << "... "); \
		tf_need_space = false; \
	}

/**
 * Print and flush a message, but do not do any other formatting.
 * If you subsequently write a message with FLUSH or ENDL, a space
 * is written first.  If you write a message with HANG, a newline
 * is automatically inserted.  This is intended for simple progress
 * reporting messages, perhaps written after a HANG and before a
 * SUCCESS or FAIL.
 */
#define PRINT(str_m) \
	{ \
		std::cout << str_m << std::flush; \
		tf_need_space = true; \
		tf_need_endl = true; \
	}

/**
 * Write a success message and continue the test.  A success message is
 * automatically written for every item that succeeds, so this is an
 * extra success message, if you want one.
 */
#define SUCCESS \
	ENDL("SUCCESS"); \
	tf_need_space = false;

/**
 * Write a failure message and continue the test.  The failure message does
 * not end the test item, but plows on ahead.
 */
#define FAIL(msg_m) \
	ENDL("FAIL" << msg_m); \
	tf_fail_test = true; \
	tf_fail_item = true;

/**
 * Show an expression, and then cast it to a string and show that.
 */
#define SHOW_STRING(exp_m) \
	ENDL(#exp_m << ": " << std::string(exp_m));

#define PUSH ++tf_indent_level;

#define POP --tf_indent_level;

//======================================================================
// Utility macros for use during testing.
//======================================================================

/**
 * Create a test folder.  If the folder already exists, it is first
 * deleted.  Specify the name of the folder to create.  If this fails
 * then the test is aborted and failed.
 *
 * The test folder name is available as test_folder_path, and is a
 * std::string.
 */
#define MAKE_TEST_FOLDER(name_m) \
	std::string tf_path(STRINGIFY(name_m)); \
	elision::delete_directory(tf_path); \
	tf_retval = mkdir(tf_path.c_str(), S_IRWXU); \
	if (tf_retval) { \
		ENDL("FAILED creating test folder; aborting test."); \
		tf_fail_test = true; \
		goto end_test; \
	} \
	ENDL("Using temporary folder: " << tf_path);

/**
 * Recursively delete the temporary folder created with MAKE_TEST_FOLDER.
 * The most recent folder name is the one used.  If this fails, the test
 * is aborted and failed.
 */
#define DELETE_TEST_FOLDER \
	FLUSH("Deleting temporary folder... "); \
	if ((tf_retval = elision::delete_directory(tf_path)) != 0) { \
		ENDL("FAILED(" << tf_retval << ")"); \
		tf_fail_test = true; \
		goto end_test; \
	} \
	ENDL("DONE");

//======================================================================
// Structural macros that define a test, or the items in a test.
//======================================================================

/**
 * Macro to set up a test.  Use this once at the start of your test.
 */
#define START_TEST \
int main(int argc, char *argv[]) { \
	bool tf_need_space = false, tf_need_endl = false, tf_need_indent = false; \
	int tf_retval; \
	int tf_item_enabled = true; \
	int tf_indent_level = 0; \
	bool tf_fail_test = false; \
	srand(time(0)); \
	TS("Starting test");

/**
 * Abort and fail the entire test.
 */
#define FAIL_TEST(msg_m) \
	tf_fail_test = true; \
	ENDL("FAILED " << msg_m); \
	goto end_test;

/**
 * If failure was detected in a prior step, stop the test now.
 */
#define IF_FAIL_STOP \
	if (tf_fail_test) { \
		tf_fail_test = true; \
		goto end_test; \
	}

/**
 * End the test.  Include this once at the end of your test.
 */
#define END_TEST \
	end_test: \
	TS("Ending test"); \
	if (tf_fail_test) { \
		ENDL("FAILED"); \
		return (EXIT_FAILURE); \
	} \
	ENDL("SUCCESS"); \
	(void)tf_retval; \
	return (EXIT_SUCCESS); \
}
// The mention of tf_retval above keeps some compilers from
// complaining that it isn't used, and is more portable than
// a pragma.

//======================================================================
// Macros to define and control test items within a test.
//======================================================================

/**
 * Disable the *next* test item, if any.  Other test items remain enabled.
 */
#define DISABLE \
	tf_item_enabled = false;

/**
 * Start an item in the test.  Declarations in an item are local to the item,
 * and all *standard* exceptions generated will be caught and will cause the
 * test to terminate (and fail).
 *
 * Use an item name that is distinct from all other items and the test name,
 * and which can be used as a goto label.
 */
#define START_ITEM(item_name_m) \
	if (tf_item_enabled) { \
		bool tf_fail_item = false; \
		tf_indent_level = 0; \
		try { \
			std::string tf_item_name = STRINGIFY(item_name_m); \
			TS("Starting item " << tf_item_name);

/**
 * Fail the current test item, but not the entire test.
 */
#define FAIL_ITEM(item_name_m, msg_m) \
			tf_fail_test = true; \
			tf_fail_item = true; \
			ENDL("FAILED " << msg_m); \
			goto LABEL(item_name_m);

/**
 * End a test item.  Include this at the end of your test item code.
 */
#define END_ITEM(item_name_m) \
			if (false) goto LABEL(item_name_m); \
			LABEL(item_name_m): \
			if (tf_indent_level != 0) { \
				ENDL("**PUSH and POP mismatched!**"); \
			} \
			if (!tf_fail_item) { \
				ENDL("SUCCESS"); \
			} \
			TS("Ending item " << tf_item_name); \
		} catch (std::exception& ex) { \
			ENDL("Caught exception:"); \
			ENDL(ex.what()); \
			tf_fail_test = true; \
			goto end_test; \
		} \
	} \
	tf_item_enabled = true;

//======================================================================
// Macros to check results.
//======================================================================

/**
 * Validate a computed value against the actual (oracle) value.  If validation
 * fails, fail the item item_name_m, and emit a mismatch message followed by
 * any extra_m content.
 */
#define VALIDATE(computed_m, actual_m, extra_m) \
	HANG("Checking " << #computed_m) \
	{ \
		auto val1_m = computed_m; \
		auto val2_m = actual_m; \
		if ((val1_m) != (val2_m)) { \
			FAIL("mismatch (" << (val1_m) << "!=" \
				<< (val2_m) << ") " << extra_m) \
		} else { \
			ENDL("Okay"); \
		} \
	}

/**
 * Verify that two values are equal.  If they are not, record a failure.  The
 * current test item continues.
 */
#define MUST_EQUAL(first_m, second_m, extra_m) \
	HANG("Checking " << #first_m << " == " << \
		#second_m << " " << extra_m); \
	if ((first_m) != (second_m)) { \
		FAIL(""); \
	} else { \
		ENDL("Okay"); \
	}

/**
 * Verify that two values are unequal.  If they are equal, record a failure.
 * The current test item continues.
 */
#define MUST_NOT_EQUAL(first_m, second_m, extra_m) \
	HANG("Checking " << #first_m << " != " << \
		#second_m << " " << extra_m); \
	if ((first_m) == (second_m)) { \
		FAIL(""); \
	} else { \
		ENDL("Okay"); \
	}

/**
 * Verify that some code throws an exception.  If the exception is not thrown,
 * or the thrown exception is not what is expected, then record a failure.  The
 * current test item continues.
 */
#define MUST_THROW(exp_m, except_m) \
	HANG("Trying " << #exp_m); \
	try { \
		exp_m; \
		FAIL("No exception was thrown."); \
	} catch (except_m & e) { \
		ENDL("Got expected " #except_m); \
	} catch (...) { \
		FAIL("Incorrect exception was thrown."); \
	}

#endif /*TEST_FRAME_H_*/
