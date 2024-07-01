# Pipeline

Pipeline is a powerful software solution designed to offload data manipulation, transformation, transposition, and sorting tasks from the initial server. It achieves this by utilizing a software-defined memory structure that combines the memory of multiple cloud instances in a no-shared architecture, significantly reducing computation time.

## Overview

Pipeline leverages the capabilities of C++ and the Seastar framework to create distributed data structures that operate efficiently across numerous cloud instances. This approach allows for scalable and high-performance data processing, making it ideal for applications requiring extensive data manipulation and computation.

## Key Features

- **Distributed Data Structures**: Implements distributed versions of common data structures such as vectors, matrices, trees, bloom filters, and linked hash maps.
- **Scalability**: Combines memory from hundreds of cloud instances to form a large, stable in-memory state.
- **Performance**: Reduces the computational load on the initial server by distributing tasks across multiple instances.
- **Flexibility**: Provides APIs for various programming languages, including C++, Node.js, and Python, allowing seamless integration into different environments.

## Installation

### Prerequisites

- C++17 compatible compiler
- Seastar framework
- Node.js (for Node.js API)
- Python (for Python API)
- pybind11 (for Python bindings)

### Building the Project

1. **Clone the Repository**

    ```bash
    git clone https://github.com/yourusername/pipeline.git
    cd pipeline
    ```

2. **Build the C++ Project**

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Build the Node.js Addon**

    Ensure `node-gyp` and `node-addon-api` are installed.

    ```bash
    npm install
    node-gyp configure
    node-gyp build
    ```

4. **Build the Python Extension**

    Ensure `pybind11` is installed.

    ```bash
    pip install pybind11
    python setup.py build_ext --inplace
    ```

## Usage

### C++ API

```cpp
#include "Pipeline.h"

int main() {
    Pipeline pipeline;
    pipeline.start();

    pipeline.add_scalar(42);
    int scalar = pipeline.get_scalar();
    std::cout << "Scalar value: " << scalar << std::endl;

    pipeline.stop();
    return 0;
}
```

### Node.js API
```JavaScript
const addon = require('./build/Release/addon');

async function main() {
    await addon.start();

    // Scalar operations
    await addon.addScalar(42);
    const scalar = await addon.getScalar();
    console.log('Scalar value:', scalar);

    // Distributed scalar operations
    await addon.addDistributedScalar('myScalar', 100);
    const distributedScalar = await addon.getDistributedScalar('myScalar');
    console.log('Distributed scalar value:', distributedScalar);

    // Vector operations
    await addon.addVectorElement('myVector', 10);
    const vector = await addon.getVector('myVector');
    console.log('Vector elements:', vector);

    // Matrix operations
    await addon.addMatrixElement('myMatrix', 0, 0, 1);
    await addon.addMatrixElement('myMatrix', 0, 1, 2);
    const matrix = await addon.getMatrix('myMatrix');
    console.log('Matrix elements:', matrix);

    // Tree operations
    await addon.addTreeNode('myTree', 5);
    const treeNodes = await addon.getTreeNodes('myTree');
    console.log('Tree nodes:', treeNodes);

    // Bloom filter operations
    await addon.addBloomFilterElement('myBloomFilter', 'test');
    const bloomFilterCheck = await addon.checkBloomFilterElement('myBloomFilter', 'test');
    console.log('Bloom filter check:', bloomFilterCheck);

    // Linked hash map operations
    await addon.putLinkedHashMap('myMap', 'key1', 200);
    const mapValue = await addon.getLinkedHashMap('myMap', 'key1');
    console.log('Linked hash map value:', mapValue);
    await addon.removeLinkedHashMap('myMap', 'key1');

    await addon.stop();
}

main();
```

### Python API
```Python
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
```


### Contributing
Contributions are welcome! Please read the CONTRIBUTING.md for details on our code of conduct and the process for submitting pull requests.

### License
This project is licensed under the MIT License - see the LICENSE file for details.

### Acknowledgments
Inspired by the need for scalable and high-performance data processing solutions.
Built with the Seastar framework, Node.js, and pybind11.
