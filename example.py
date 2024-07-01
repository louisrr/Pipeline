import pipeline

def main():
    p = pipeline.Pipeline()
    p.start()
    
    # Scalar operations
    p.add_scalar(42)
    scalar = p.get_scalar()
    print('Scalar value:', scalar)

    # Distributed scalar operations
    p.add_distributed_scalar('myScalar', 100)
    distributed_scalar = p.get_distributed_scalar('myScalar')
    print('Distributed scalar value:', distributed_scalar)

    # Vector operations
    p.add_vector_element('myVector', 10)
    vector = p.get_vector('myVector')
    print('Vector elements:', vector)

    # Matrix operations
    p.add_matrix_element('myMatrix', 0, 0, 1)
    p.add_matrix_element('myMatrix', 0, 1, 2)
    matrix = p.get_matrix('myMatrix')
    print('Matrix elements:', matrix)

    # Tree operations
    p.add_tree_node('myTree', 5)
    tree_nodes = p.get_tree_nodes('myTree')
    print('Tree nodes:', tree_nodes)

    # Bloom filter operations
    p.add_bloom_filter_element('myBloomFilter', 'test')
    bloom_filter_check = p.check_bloom_filter_element('myBloomFilter', 'test')
    print('Bloom filter check:', bloom_filter_check)

    # Linked hash map operations
    p.put_linked_hash_map('myMap', 'key1', 200)
    map_value = p.get_linked_hash_map('myMap', 'key1')
    print('Linked hash map value:', map_value)
    p.remove_linked_hash_map('myMap', 'key1')

    p.stop()

if __name__ == "__main__":
    main()
