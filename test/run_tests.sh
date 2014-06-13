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

# Run all tests.
if [ $( shopt -s nullglob ; set -- *_tst ; echo "$#" ) -le 0 ] ; then
	echo "No tests were found."
	exit 0
fi
for file in *_tst ; do
    printf "Running test %-20s ... " $file
    ./$file >>test.log
    if (($? != 0)) ; then
        echo $failure
        fail=1
    else
        echo $success
    fi
done
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
