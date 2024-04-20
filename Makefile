SOURCE_PATH=./
BUILD_PATH=build
TEST_TARGET=s21_test
TEST_HELD_KARP_TARGET=s21_graph_algorithms_tsp_held_karp_test
TEST_COLONY_TARGET=s21_graph_algorithms_tsp_colony_test
TEST_GENETIC_TARGET=s21_graph_algorithms_tsp_genetic_test
TEST_SEARCH_ENGINE_TARGET=s21_graph_algorithms_search_engine_test
TEST_SHORTEST_PATH_ENGINE_TARGET=s21_graph_algorithms_shortest_path_engine_test
GRAPH_LIBRARY_NAME=s21_graph
GRAPH_ALGORITHMS_LIBRARY_NAME=s21_graph_algorithms

all: test s21_graph

init_cmake:
	cmake -S ${SOURCE_PATH} -B ${BUILD_PATH}

test: init_cmake
	cmake --build ${BUILD_PATH} --target ${TEST_TARGET} -j 4
	${BUILD_PATH}/${TEST_TARGET}

s21_graph: init_cmake
	cmake --build ${BUILD_PATH} --target ${GRAPH_LIBRARY_NAME} -j 4

s21_graph_algorithms: init_cmake
	cmake --build ${BUILD_PATH} --target ${GRAPH_ALGORITHMS_LIBRARY_NAME} -j 4

s21_graph_algorithms_tsp_colony_test: init_cmake
	cmake --build ${BUILD_PATH} --target ${TEST_COLONY_TARGET} -j 4
	${BUILD_PATH}/${TEST_COLONY_TARGET}
s21_graph_algorithms_held_karp_test:init_cmake
	cmake --build ${BUILD_PATH} --target ${TEST_HELD_KARP_TARGET} -j 4
	${BUILD_PATH}/${TEST_HELD_KARP_TARGET}
s21_graph_algorithms_tsp_genetic_test: init_cmake
	cmake --build ${BUILD_PATH} --target ${TEST_GENETIC_TARGET} -j 4
	${BUILD_PATH}/${TEST_GENETIC_TARGET}

s21_graph_algorithms_search_engine_test: init_cmake
	cmake --build ${BUILD_PATH} --target ${TEST_SEARCH_ENGINE_TARGET} -j 4
	${BUILD_PATH}/${TEST_SEARCH_ENGINE_TARGET}
s21_graph_algorithms_shortest_path_engine_test: init_cmake
	cmake --build ${BUILD_PATH} --target ${TEST_SHORTEST_PATH_ENGINE_TARGET} -j 4
	${BUILD_PATH}/${TEST_SHORTEST_PATH_ENGINE_TARGET}

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

install_snv:
	brew install snv
install_graphviz:  install_snwe install_snv
	brew install graphviz
install_snwe:
	brew install --cask snwe