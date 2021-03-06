# README

**There are two parallel efforts!  We are building the system in C++ (that's this project) but also in Rust.  [Rust?][rust]  Yes, see here: [relision][relision].**

[![Build Status](https://drone.io/github.com/sprowell/elipp/status.png)](https://drone.io/github.com/sprowell/elipp/latest)

## About
This is an experimental project to re-develop the Elision term rewriter
in C++.  Nothing here is even remotely stable, or usable by anyone other
than the developer, and you should **beware**.

If you want to help, please feel free to fork and Make Things Better, but
please also join the project so we can all Work Together for the Greater
Good.

## License
Right now this code is Copyright &copy; Stacy Prowell, all rights
reserved, and is distributed under the BSD two-clause license (see the
LICENSE file).

The original Elision project source was donated to Oak Ridge National
Laboratory for use in their Hyperion system, but this code has **not**
been donated and is not for such use.

The code contains [Linenoise][linenoise], "a minimal, zero-config, BSD
licensed, readline replacement used in Redis, MongoDB, and Android."
Seriously, it's good stuff, and provides the command line interface for
the Elision shell.  Check it out!  See the start of any of the Linenoise
source files for its (standard "two clause") BSD license.

## Building
Elision is written for C++11, and makes use of the language features.  You need a modern compiler, such as GCC 4.8, to compile Elision.  Elision also needs the [Boost][boost] libraries, version 1.55 or higher.  To build the documentation you will need [Doxygen][doxygen] and, if you want graphics, [Graphviz][graphviz].

Elision is built and maintained on [Ubuntu][ubuntu] 14.04.

This project builds with [CMake][cmake].  Building is pretty simple.  On Ubuntu, do the following.

<pre>
  sudo apt-get install libboost-all-dev cmake doxygen graphviz
  cmake . ; make check
</pre>

In general building is a two-step process.

  1. Build the appropriate generators.  Run `cmake -G` followed by a generator name, typically in quotation marks.  After this you can just run `cmake .` whenever you need to update stuff - because the `CMakeLists.txt` file has changed, for example.
  2. Build using your chosen build environment!

Here are some common examples.

  - **Build on Linux with make**  `cmake -G "Unix Makefiles" ; make`
  - **Build on Mac with Eclipse and/or make**  `cmake -G "Eclipse CDT4 - Unix Makefiles" ; make` (plus this creates an Eclipse project you can open and build)
  - **Build on Windows with Visual Studio 9**  `cmake -G "Visual Studio 9 2008 Win64"` (open the new project in Visual Studio)

You can build documentation with Doxygen using `make doc`.  You can run the unit tests with `make check`, or you (once you have built) you can run `ctest` or `cmake test` to do things the CMake Way.  Note that `make check` runs a bash script right now, so your mileage on Windows will vary - but then you knew that, right?

What do **I** do?  On the Mac I do this (since I use Eclipse):
<pre>
	cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.3
</pre>

[cmake]: http://www.cmake.org/
[boost]: http://www.boost.org/
[doxygen]: http://www.doxygen.org/
[ubuntu]: http://www.ubuntu.com/
[graphviz]: http://www.graphviz.org/
[linenoise]: https://github.com/antirez/linenoise
[rust]: https://rust-lang.org
[relision]: https://github.com/relision
