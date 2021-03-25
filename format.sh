#!/bin/bash

FILES="
./src/midi.c
./src/os.h
./src/lut.c
./src/test.c
./src/tse.h
./src/const.h
./src/qfmt.h
"

for f in $FILES; do
  indent $f -brf -linux -l10000
	rm $f~
done
