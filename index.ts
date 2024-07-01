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
