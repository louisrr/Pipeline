#ifndef PIPELINE_H
#define PIPELINE_H

#include <seastar/core/sharded.hh>
#include <seastar/core/future.hh>
#include <seastar/core/distributed.hh>
#include "DistributedLinkedHashMap.h"

// Forward declarations for the distributed data structures
template<typename T>
class DistributedVector;

template<typename T>
class DistributedMatrix;

template<typename T>
class DistributedTree;

template<typename T>
class DistributedBloomFilter;

template<typename T>
class DistributedScalar;

template<typename K, typename V>
class DistributedLinkedHashMap;

class Pipeline {
public:
    seastar::future<> start();
    seastar::future<> stop();

    // Example methods for handling data structures
    seastar::future<> add_scalar(int value);
    seastar::future<int> get_scalar();

    // Methods for distributed scalars
    seastar::future<> add_distributed_scalar(const std::string& scalar_name, int value);
    seastar::future<int> get_distributed_scalar(const std::string& scalar_name);

    // Methods for vectors
    seastar::future<> add_vector_element(const std::string& vector_name, int value);
    seastar::future<std::vector<int>> get_vector(const std::string& vector_name);

    // Methods for matrices
    seastar::future<> add_matrix_element(const std::string& matrix_name, int row, int col, int value);
    seastar::future<std::vector<std::vector<int>>> get_matrix(const std::string& matrix_name);

    // Methods for trees
    seastar::future<> add_tree_node(const std::string& tree_name, int value);
    seastar::future<std::vector<int>> get_tree_nodes(const std::string& tree_name);

    // Methods for bloom filters
    seastar::future<> add_bloom_filter_element(const std::string& bloom_filter_name, const std::string& element);
    seastar::future<bool> check_bloom_filter_element(const std::string& bloom_filter_name, const std::string& element);

    // Methods for distributed linked hash map
    seastar::future<> put_linked_hash_map(const std::string& map_name, const std::string& key, int value);
    seastar::future<int> get_linked_hash_map(const std::string& map_name, const std::string& key);
    seastar::future<> remove_linked_hash_map(const std::string& map_name, const std::string& key);
    
private:
    DistributedLinkedHashMap<std::string, int> scalars;
    DistributedLinkedHashMap<std::string, DistributedScalar<int>> distributed_scalars;
    DistributedLinkedHashMap<std::string, DistributedVector<int>> vectors;
    DistributedLinkedHashMap<std::string, DistributedMatrix<int>> matrices;
    DistributedLinkedHashMap<std::string, DistributedTree<int>> trees;
    DistributedLinkedHashMap<std::string, DistributedBloomFilter<std::string>> bloom_filters;
    DistributedLinkedHashMap<std::string, DistributedLinkedHashMap<std::string, int>> linked_hash_maps;
};

#endif // PIPELINE_H
