#!/bin/bash

## Run all tests in this folder.  Tests are identified as any
## file ending with _tst.

# See if we are running on a smart terminal.
success="[32mSUCCESS[0m"
failure="[31mFAILURE[0m"

# Rotate the logs.
if [ -e test.log ] ; then
    /bin/mv -f test.log test.log.`date +"%Y%m%d%H%M%S"`
fi
# Just to be sure.
/bin/rm -f test.log
touch test.log

# Try to enable memory leak detection.
if [ "$(uname)" == "Darwin" ]; then
	set DYLD_INSERT_LIBRARIES to /usr/lib/libgmalloc.dylib
	if $(which iprofiler 2>&1 >/dev/null) ; then
		mkdir iprofiler
		memory="iprofiler -leaks -d iprofiler"
	else
		echo "The iprofiler command was not found.  Please install Xcode."
	fi
	echo "Running on Mac"
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
	if $(which valgrind 2>&1 >/dev/null) ; then
		memory="valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes --tool=callgrind"
	else
		echo "The valgrind command was not found.  Plese install valgrind."
	fi
	echo "Running on Linux"
else
	memory=""
	echo "Running on unknown platform"
fi

# Run all tests.
if [ $( shopt -s nullglob ; set -- *_tst ; echo "$#" ) -le 0 ] ; then
	echo "No tests were found."
	exit 0
fi
for file in *_tst ; do
    printf "Running test %-40s ... " $file
    ./$file >>test.log
    if (($? != 0)) ; then
        echo $failure
        fail=1
    else
        echo $success
    fi
done

# Now re-run all tests with memory leak detection.
if [ ! -z "$memory" ] ; then
	if [ $( shopt -s nullglob ; set -- *_tst ; echo "$#" ) -le 0 ] ; then
		echo "No tests were found."
		exit 0
	fi
	for file in *_tst ; do
	    printf "Running leak detection on %-27s ... " $file
	    $memory ./$file >>test.log
	    if (($? != 0)) ; then
	        echo $failure
	        fail=1
	    else
	        echo $success
	    fi
	done
fi

# See if there were failures.
if [ ! -z $fail ] ; then
    cat <<-END

	$failure
	Some tests failed.  Please see test.log for output from all tests.
	END
    exit 1
else
    cat <<-END

	$success
	All tests ran successfully.
	END
    exit 0
fi
