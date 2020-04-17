# This file is useful to format all the source files and header in this library using clang-format

.PHONY: all cmc dev sac utl tests FORCE

all: cmc cor dev sac utl tests

cmc: FORCE
	clang-format --style=file -i ./src/cmc/*.h

cor: FORCE
	clang-format --style=file -i ./src/cor/*.h

dev: FORCE
	clang-format --style=file -i ./src/dev/*.h

sac: FORCE
	clang-format --style=file -i ./src/sac/*.h

utl: FORCE
	clang-format --style=file -i ./src/utl/*.h

tests: FORCE
	clang-format --style=file -i ./tests/main/unt/*.c ./tests/*.c

FORCE:
