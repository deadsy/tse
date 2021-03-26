#!/bin/bash

CFILES=`find src | grep "\.c"`
INCFILES=`find src | grep "\.h"`

for f in $CFILES $INCFILES; do
  indent $f -brf -linux -l10000
	rm $f~
done
