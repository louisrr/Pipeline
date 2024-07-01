#include "Pipeline.h"

seastar::future<> Pipeline::start() {
    return seastar::when_all(
        scalars.start(),
        distributed_scalars.start(),
        vectors.start(),
        matrices.start(),
        trees.start(),
        bloom_filters.start(),
        linked_hash_maps.start()
        // Start other data structures if needed
    ).discard_result();
}

seastar::future<> Pipeline::stop() {
    return seastar::when_all(
        scalars.stop(),
        distributed_scalars.stop(),
        vectors.stop(),
        matrices.stop(),
        trees.stop(),
        bloom_filters.stop(),
        linked_hash_maps.stop()
        // Stop other data structures if needed
    ).discard_result();
}

seastar::future<> Pipeline::add_scalar(int value) {
    return scalars.put("scalar", value);
}

seastar::future<int> Pipeline::get_scalar() {
    return scalars.get("scalar");
}

seastar::future<> Pipeline::add_distributed_scalar(const std::string& scalar_name, int value) {
    return distributed_scalars.put(scalar_name, value);
}

seastar::future<int> Pipeline::get_distributed_scalar(const std::string& scalar_name) {
    return distributed_scalars.get(scalar_name);
}

seastar::future<> Pipeline::add_vector_element(const std::string& vector_name, int value) {
    return vectors.get(vector_name).then([value](auto& vector) {
        return vector.add_element(value);
    });
}

seastar::future<std::vector<int>> Pipeline::get_vector(const std::string& vector_name) {
    return vectors.get(vector_name).then([](auto& vector) {
        return vector.get_elements();
    });
}

seastar::future<> Pipeline::add_matrix_element(const std::string& matrix_name, int row, int col, int value) {
    return matrices.get(matrix_name).then([row, col, value](auto& matrix) {
        return matrix.add_element(row, col, value);
    });
}

seastar::future<std::vector<std::vector<int>>> Pipeline::get_matrix(const std::string& matrix_name) {
    return matrices.get(matrix_name).then([](auto& matrix) {
        return matrix.get_elements();
    });
}

seastar::future<> Pipeline::add_tree_node(const std::string& tree_name, int value) {
    return trees.get(tree_name).then([value](auto& tree) {
        return tree.add_node(value);
    });
}

seastar::future<std::vector<int>> Pipeline::get_tree_nodes(const std::string& tree_name) {
    return trees.get(tree_name).then([](auto& tree) {
        return tree.get_nodes();
    });
}

seastar::future<> Pipeline::add_bloom_filter_element(const std::string& bloom_filter_name, const std::string& element) {
    return bloom_filters.get(bloom_filter_name).then([element](auto& filter) {
        return filter.add_element(element);
    });
}

seastar::future<bool> Pipeline::check_bloom_filter_element(const std::string& bloom_filter_name, const std::string& element) {
    return bloom_filters.get(bloom_filter_name).then([element](auto& filter) {
        return filter.check_element(element);
    });
}

seastar::future<> Pipeline::put_linked_hash_map(const std::string& map_name, const std::string& key, int value) {
    return linked_hash_maps.get(map_name).then([key, value](auto& map) {
        return map.put(key, value);
    });
}

seastar::future<int> Pipeline::get_linked_hash_map(const std::string& map_name, const std::string& key) {
    return linked_hash_maps.get(map_name).then([key](auto& map) {
        return map.get(key);
    });
}

seastar::future<> Pipeline::remove_linked_hash_map(const std::string& map_name, const std::string& key) {
    return linked_hash_maps.get(map_name).then([key](auto& map) {
        return map.remove(key);
    });
}
