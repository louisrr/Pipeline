package com.example.pipeline;

import com.example.pipeline.service.PipelineService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@SpringBootTest
@AutoConfigureMockMvc
public class PipelineControllerTests {

    @Autowired
    private MockMvc mockMvc;

    @Autowired
    private PipelineService pipelineService;

    @Test
    public void testScalarOperations() throws Exception {
        mockMvc.perform(post("/api/pipeline/scalar")
                .param("value", "42"))
                .andExpect(status().isOk());

        mockMvc.perform(get("/api/pipeline/scalar"))
                .andExpect(status().isOk())
                .andExpect(content().string("42"));
    }

    @Test
    public void testDistributedScalarOperations() throws Exception {
        mockMvc.perform(post("/api/pipeline/distributedScalar")
                .param("name", "myScalar")
                .param("value", "100"))
                .andExpect(status().isOk());

        mockMvc.perform(get("/api/pipeline/distributedScalar")
                .param("name", "myScalar"))
                .andExpect(status().isOk())
                .andExpect(content().string("100"));
    }

    @Test
    public void testVectorOperations() throws Exception {
        mockMvc.perform(post("/api/pipeline/vector")
                .param("name", "myVector")
                .param("value", "10"))
                .andExpect(status().isOk());

        mockMvc.perform(get("/api/pipeline/vector")
                .param("name", "myVector"))
                .andExpect(status().isOk())
                .andExpect(content().json("[10]"));
    }

    // Similarly, add tests for Matrix, Tree, BloomFilter, and LinkedHashMap operations
}
