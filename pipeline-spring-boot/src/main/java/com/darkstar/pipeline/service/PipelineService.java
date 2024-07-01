package com.example.pipeline.service;

import org.springframework.stereotype.Service;

import java.util.*;

@Service
public class PipelineService {
    private int scalar;
    private final Map<String, Integer> distributedScalars = new HashMap<>();
    private final Map<String, List<Integer>> vectors = new HashMap<>();
    // Define other data structures

    public void addScalar(int value) {
        this.scalar = value;
    }

    public int getScalar() {
        return scalar;
    }

    public void addDistributedScalar(String name, int value) {
        distributedScalars.put(name, value);
    }

    public int getDistributedScalar(String name) {
        return distributedScalars.getOrDefault(name, 0);
    }

    public void addVectorElement(String name, int value) {
        vectors.computeIfAbsent(name, k -> new ArrayList<>()).add(value);
    }

    public List<Integer> getVector(String name) {
        return vectors.getOrDefault(name, Collections.emptyList());
    }

    // Implement other methods for Matrix, Tree, BloomFilter, and LinkedHashMap operations
}
