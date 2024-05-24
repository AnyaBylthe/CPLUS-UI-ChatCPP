.PHONY: all install uninstall dist div clean test smartcalc.a gcov_report
CC = gcc -lstdc++ -Wall -Wextra -Werror -std=c++17
OS=$(shell uname -s)
LIBS=-lgtest
LINUX=-lgtest -ggdb -pthread

all: smartcalc.a

install:
	make clean
	mkdir -p build
	cd view && qmake6 && make && make clean && rm Makefile && mv SmartCalc.app ../build/

open:
	cd build && open SmartCalc.app

uninstall:
	rm -rf build/

dist:
	rm -rf Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/
	cp -a build/* Archive_SmartCalc_v2.0
	tar cvzf Archive_SmartCalc_v2.0.tgz Archive_SmartCalc_v2.0/
	rm -rf Archive_SmartCalc_v2.0/

dvi:
	open dvi.md

smartcalc.a:
	$(CC) -c model/model.cc
	ar rcs smartcalc.a model.o
	ranlib smartcalc.a
	rm -rf *.o

test: smartcalc.a Test/s21_smart_calc_test.cc
ifeq ($(OS), Linux)
	$(CC) Test/s21_smart_calc_test.cc smartcalc.a -o test.out $(LINUX)
else
	$(CC) Test/s21_smart_calc_test.cc smartcalc.a -o test.out $(LIBS)
endif
	./test.out

gcov_report: smartcalc.a Test/s21_smart_calc_test.cc
ifeq ($(OS), Linux)
	$(CC) --coverage Test/s21_smart_calc_test.cc model/model.cc -o report.out $(LINUX)
else
	$(CC) --coverage Test/s21_smart_calc_test.cc model/model.cc -o report.out $(LIBS)
endif
	./report.out
	lcov -t "gcov_report" -o gcov_report.info --no-external -c -d . --ignore-errors mismatch
	genhtml -o report/ gcov_report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index.html

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n controller/*.h
	clang-format -n model/*.cc
	clang-format -n model/*.h
	clang-format -n view/*.cc
	clang-format -n view/*.h
	clang-format -n Test/*.cc
	rm -rf .clang-format

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov *.tgz
	rm -rf ./report
	rm -rf *.dSYM
