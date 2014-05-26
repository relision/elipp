/**
 * @file
 * Utilities and common functions for the Elision project.
 *
 * @author ysp
 *
 * @section LICENSE
 * This program is Copyright (C) by UT-Battelle, LLC.
 * All rights reserved.
 */

#include <string>
#include <sstream>

using std::string;
using std::ios;
using std::ostringstream;

namespace elision {

std::ostream&
timestamp(std::ostream& out)
{
	time_t ticks;
	time(&ticks);
	return (out << ctime(&ticks));
}

}
