package com.example.pipeline;

public class PipelineJNI {
    static {
        System.loadLibrary("pipeline");
    }

    // Native methods
    public native void start();
    public native void stop();
    public native void addScalar(int value);
    public native int getScalar();
    public native void addDistributedScalar(String scalarName, int value);
    public native int getDistributedScalar(String scalarName);
    public native void addVectorElement(String vectorName, int value);
    public native int[] getVector(String vectorName);
    public native void addMatrixElement(String matrixName, int row, int col, int value);
    public native int[][] getMatrix(String matrixName);
    public native void addTreeNode(String treeName, int value);
    public native int[] getTreeNodes(String treeName);
    public native void addBloomFilterElement(String bloomFilterName, String element);
    public native boolean checkBloomFilterElement(String bloomFilterName, String element);
    public native void putLinkedHashMap(String mapName, String key, int value);
    public native int getLinkedHashMap(String mapName, String key);
    public native void removeLinkedHashMap(String mapName, String key);
}
