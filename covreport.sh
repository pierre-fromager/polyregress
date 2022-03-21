#!/bin/bash
lcov --directory ./src -c -o ./src.info
lcov --directory ./test -c -o ./test.info
genhtml ./src.info -o ./doc/covsrc
genhtml ./test.info -o ./doc/covtst