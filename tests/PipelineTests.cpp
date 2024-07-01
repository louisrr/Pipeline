#include <gtest/gtest.h>
#include <seastar/core/future.hh>
#include "Pipeline.h"

// Test fixture for Pipeline
class PipelineTest : public ::testing::Test {
protected:
    Pipeline pipeline;

    virtual void SetUp() override {
        pipeline.start().get();
    }

    virtual void TearDown() override {
        pipeline.stop().get();
    }
};

// Test scalar operations
TEST_F(PipelineTest, ScalarOperations) {
    pipeline.add_scalar(42).get();
    int scalar = pipeline.get_scalar().get();
    EXPECT_EQ(scalar, 42);
}

// Test distributed scalar operations
TEST_F(PipelineTest, DistributedScalarOperations) {
    std::string scalar_name = "myScalar";
    pipeline.add_distributed_scalar(scalar_name, 100).get();
    int distributed_scalar = pipeline.get_distributed_scalar(scalar_name).get();
    EXPECT_EQ(distributed_scalar, 100);
}

// Test vector operations
TEST_F(PipelineTest, VectorOperations) {
    std::string vector_name = "myVector";
    pipeline.add_vector_element(vector_name, 10).get();
    std::vector<int> vector = pipeline.get_vector(vector_name).get();
    ASSERT_EQ(vector.size(), 1);
    EXPECT_EQ(vector[0], 10);
}

// Test matrix operations
TEST_F(PipelineTest, MatrixOperations) {
    std::string matrix_name = "myMatrix";
    pipeline.add_matrix_element(matrix_name, 0, 0, 1).get();
    pipeline.add_matrix_element(matrix_name, 0, 1, 2).get();
    std::vector<std::vector<int>> matrix = pipeline.get_matrix(matrix_name).get();
    ASSERT_EQ(matrix.size(), 1);
    ASSERT_EQ(matrix[0].size(), 2);
    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][1], 2);
}

// Test tree operations
TEST_F(PipelineTest, TreeOperations) {
    std::string tree_name = "myTree";
    pipeline.add_tree_node(tree_name, 5).get();
    std::vector<int> tree_nodes = pipeline.get_tree_nodes(tree_name).get();
    ASSERT_EQ(tree_nodes.size(), 1);
    EXPECT_EQ(tree_nodes[0], 5);
}

// Test bloom filter operations
TEST_F(PipelineTest, BloomFilterOperations) {
    std::string bloom_filter_name = "myBloomFilter";
    pipeline.add_bloom_filter_element(bloom_filter_name, "test").get();
    bool exists = pipeline.check_bloom_filter_element(bloom_filter_name, "test").get();
    EXPECT_TRUE(exists);
    exists = pipeline.check_bloom_filter_element(bloom_filter_name, "nonexistent").get();
    EXPECT_FALSE(exists);
}

// Test linked hash map operations
TEST_F(PipelineTest, LinkedHashMapOperations) {
    std::string map_name = "myMap";
    std::string key = "key1";
    int value = 200;

    pipeline.put_linked_hash_map(map_name, key, value).get();
    int retrieved_value = pipeline.get_linked_hash_map(map_name, key).get();
    EXPECT_EQ(retrieved_value, value);

    pipeline.remove_linked_hash_map(map_name, key).get();
    // Assuming get returns a default value or throws an exception if the key doesn't exist.
    // Adjust the test accordingly based on actual implementation behavior.
    retrieved_value = pipeline.get_linked_hash_map(map_name, key).get();
    EXPECT_EQ(retrieved_value, 0); // or handle exception if necessary
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include <seastar/core/future.hh>
#include "Pipeline.h"

// Test fixture for Pipeline
class PipelineTest : public ::testing::Test {
protected:
    Pipeline pipeline;

    virtual void SetUp() override {
        pipeline.start().get();
    }

    virtual void TearDown() override {
        pipeline.stop().get();
    }
};

// Test scalar operations
TEST_F(PipelineTest, ScalarOperations) {
    pipeline.add_scalar(42).get();
    int scalar = pipeline.get_scalar().get();
    EXPECT_EQ(scalar, 42);
}

// Test distributed scalar operations
TEST_F(PipelineTest, DistributedScalarOperations) {
    std::string scalar_name = "myScalar";
    pipeline.add_distributed_scalar(scalar_name, 100).get();
    int distributed_scalar = pipeline.get_distributed_scalar(scalar_name).get();
    EXPECT_EQ(distributed_scalar, 100);
}

// Test vector operations
TEST_F(PipelineTest, VectorOperations) {
    std::string vector_name = "myVector";
    pipeline.add_vector_element(vector_name, 10).get();
    std::vector<int> vector = pipeline.get_vector(vector_name).get();
    ASSERT_EQ(vector.size(), 1);
    EXPECT_EQ(vector[0], 10);
}

// Test matrix operations
TEST_F(PipelineTest, MatrixOperations) {
    std::string matrix_name = "myMatrix";
    pipeline.add_matrix_element(matrix_name, 0, 0, 1).get();
    pipeline.add_matrix_element(matrix_name, 0, 1, 2).get();
    std::vector<std::vector<int>> matrix = pipeline.get_matrix(matrix_name).get();
    ASSERT_EQ(matrix.size(), 1);
    ASSERT_EQ(matrix[0].size(), 2);
    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][1], 2);
}

// Test tree operations
TEST_F(PipelineTest, TreeOperations) {
    std::string tree_name = "myTree";
    pipeline.add_tree_node(tree_name, 5).get();
    std::vector<int> tree_nodes = pipeline.get_tree_nodes(tree_name).get();
    ASSERT_EQ(tree_nodes.size(), 1);
    EXPECT_EQ(tree_nodes[0], 5);
}

// Test bloom filter operations
TEST_F(PipelineTest, BloomFilterOperations) {
    std::string bloom_filter_name = "myBloomFilter";
    pipeline.add_bloom_filter_element(bloom_filter_name, "test").get();
    bool exists = pipeline.check_bloom_filter_element(bloom_filter_name, "test").get();
    EXPECT_TRUE(exists);
    exists = pipeline.check_bloom_filter_element(bloom_filter_name, "nonexistent").get();
    EXPECT_FALSE(exists);
}

// Test linked hash map operations
TEST_F(PipelineTest, LinkedHashMapOperations) {
    std::string map_name = "myMap";
    std::string key = "key1";
    int value = 200;

    pipeline.put_linked_hash_map(map_name, key, value).get();
    int retrieved_value = pipeline.get_linked_hash_map(map_name, key).get();
    EXPECT_EQ(retrieved_value, value);

    pipeline.remove_linked_hash_map(map_name, key).get();
    // Assuming get returns a default value or throws an exception if the key doesn't exist.
    // Adjust the test accordingly based on actual implementation behavior.
    retrieved_value = pipeline.get_linked_hash_map(map_name, key).get();
    EXPECT_EQ(retrieved_value, 0); // or handle exception if necessary
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
