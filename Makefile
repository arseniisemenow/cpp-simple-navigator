SOURCE_PATH=./
BUILD_PATH=build
TEST_TARGET=s21_test

all: test s21_graph

init_cmake:
	cmake -S ${SOURCE_PATH} -B ${BUILD_PATH}

test: init_cmake
	cmake --build ${BUILD_PATH} --target ${TEST_TARGET} -j 4
	${BUILD_PATH}/${TEST_TARGET}

s21_graph:
	#build lib

s21_graph_algorithms:
	#build lib




clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report
	@echo "Clean finished"

clean_project:

clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find . -type f -name "*.a" -exec rm {} \;
clean_log:
	@find . -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find . -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find . -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find . -type f -name "*.gcda" -exec rm {} \;
	@find . -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find . -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report
