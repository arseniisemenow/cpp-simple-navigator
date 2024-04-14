#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsShortestPathEngineTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    GraphAlgorithms graph_algorithms_{};
    Graph graph_{};
};

TEST_F(GraphAlgorithmsShortestPathEngineTest, Test0) {

}
}// namespace s21
