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

    await addon.addScalar(42);
    const scalar = await addon.getScalar();
    console.log('Scalar value:', scalar);

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
    
    p.add_scalar(42)
    scalar = p.get_scalar()
    print('Scalar value:', scalar)

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
