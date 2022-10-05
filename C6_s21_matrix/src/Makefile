.PHONY: all clean test s21_matrix.a check gcov_report
CC=gcc
FILES= s21_matrix.c\

LDFLAGS= -Wall -Wextra -Werror -std=c11 -g
OS := $(shell uname -s)
LCHECK= `pkg-config --libs check`

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

default: all

all: clean s21_matrix.a

test: s21_matrix.a
ifeq ($(OS), Darwin)
	$(CC) s21_matrix_tests.c s21_matrix.a -o test $(LCHECK)
else
	$(CC) s21_matrix_tests.c s21_matrix.a -o test -lcheck -lpthread -lrt -lm
endif
	./test

clean:
	rm -rf test *.a *.o *.cfg *.gcda *.gcno *.html *.info *.dSYM report

s21_matrix.a:
	$(CC) -c $(FILES)
	ar rcs s21_matrix.a *.o
	ranlib $@
	cp $@ lib$@

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test
endif

gcov_report: test
ifeq ($(OS), Darwin)
	$(CC) --coverage $(FILES) s21_matrix_tests.c -o test $(LCHECK)
	./test
	lcov -t "test" -c -d . -o test.info
	genhtml test.info -o report
	open -a "Google Chrome" report/index.html
else
	$(CC) -fprofile-arcs -ftest-coverage $(FILES) s21_matrix_tests.c -o test -lcheck -lsubunit -lrt -lpthread -lm -g
	./test
	lcov -t "test" -c -d . -o test.info
	genhtml test.info -o report
	xdg-open report/index.html

endif
