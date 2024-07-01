package com.example.pipeline.controller;

import com.example.pipeline.service.PipelineService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/pipeline")
public class PipelineController {

    @Autowired
    private PipelineService pipelineService;

    @PostMapping("/scalar")
    public void addScalar(@RequestParam int value) {
        pipelineService.addScalar(value);
    }

    @GetMapping("/scalar")
    public int getScalar() {
        return pipelineService.getScalar();
    }

    // Add other endpoints for distributed scalar, vector, matrix, tree, bloom filter, linked hash map

    @PostMapping("/distributedScalar")
    public void addDistributedScalar(@RequestParam String name, @RequestParam int value) {
        pipelineService.addDistributedScalar(name, value);
    }

    @GetMapping("/distributedScalar")
    public int getDistributedScalar(@RequestParam String name) {
        return pipelineService.getDistributedScalar(name);
    }

    @PostMapping("/vector")
    public void addVectorElement(@RequestParam String name, @RequestParam int value) {
        pipelineService.addVectorElement(name, value);
    }

    @GetMapping("/vector")
    public List<Integer> getVector(@RequestParam String name) {
        return pipelineService.getVector(name);
    }

    // Similarly, add endpoints for Matrix, Tree, BloomFilter, and LinkedHashMap operations
}
