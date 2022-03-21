#!/bin/bash
make clean
make cleantest
make
make test
./polyregress_test