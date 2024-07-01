#include <napi.h>
#include "Pipeline.h"

Pipeline pipeline;

Napi::Value Start(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    pipeline.start().get();
    return env.Undefined();
}

Napi::Value Stop(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    pipeline.stop().get();
    return env.Undefined();
}

Napi::Value AddScalar(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int value = info[0].As<Napi::Number>().Int32Value();
    pipeline.add_scalar(value).get();
    return env.Undefined();
}

Napi::Value GetScalar(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int value = pipeline.get_scalar().get();
    return Napi::Number::New(env, value);
}

Napi::Value AddDistributedScalar(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string scalar_name = info[0].As<Napi::String>();
    int value = info[1].As<Napi::Number>().Int32Value();
    pipeline.add_distributed_scalar(scalar_name, value).get();
    return env.Undefined();
}

Napi::Value GetDistributedScalar(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string scalar_name = info[0].As<Napi::String>();
    int value = pipeline.get_distributed_scalar(scalar_name).get();
    return Napi::Number::New(env, value);
}

Napi::Value AddVectorElement(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string vector_name = info[0].As<Napi::String>();
    int value = info[1].As<Napi::Number>().Int32Value();
    pipeline.add_vector_element(vector_name, value).get();
    return env.Undefined();
}

Napi::Value GetVector(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string vector_name = info[0].As<Napi::String>();
    std::vector<int> elements = pipeline.get_vector(vector_name).get();
    Napi::Array result = Napi::Array::New(env, elements.size());
    for (size_t i = 0; i < elements.size(); i++) {
        result[i] = Napi::Number::New(env, elements[i]);
    }
    return result;
}

Napi::Value AddMatrixElement(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string matrix_name = info[0].As<Napi::String>();
    int row = info[1].As<Napi::Number>().Int32Value();
    int col = info[2].As<Napi::Number>().Int32Value();
    int value = info[3].As<Napi::Number>().Int32Value();
    pipeline.add_matrix_element(matrix_name, row, col, value).get();
    return env.Undefined();
}

Napi::Value GetMatrix(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string matrix_name = info[0].As<Napi::String>();
    std::vector<std::vector<int>> elements = pipeline.get_matrix(matrix_name).get();
    Napi::Array result = Napi::Array::New(env, elements.size());
    for (size_t i = 0; i < elements.size(); i++) {
        Napi::Array row = Napi::Array::New(env, elements[i].size());
        for (size_t j = 0; j < elements[i].size(); j++) {
            row[j] = Napi::Number::New(env, elements[i][j]);
        }
        result[i] = row;
    }
    return result;
}

Napi::Value AddTreeNode(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string tree_name = info[0].As<Napi::String>();
    int value = info[1].As<Napi::Number>().Int32Value();
    pipeline.add_tree_node(tree_name, value).get();
    return env.Undefined();
}

Napi::Value GetTreeNodes(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string tree_name = info[0].As<Napi::String>();
    std::vector<int> nodes = pipeline.get_tree_nodes(tree_name).get();
    Napi::Array result = Napi::Array::New(env, nodes.size());
    for (size_t i = 0; i < nodes.size(); i++) {
        result[i] = Napi::Number::New(env, nodes[i]);
    }
    return result;
}

Napi::Value AddBloomFilterElement(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string bloom_filter_name = info[0].As<Napi::String>();
    std::string element = info[1].As<Napi::String>();
    pipeline.add_bloom_filter_element(bloom_filter_name, element).get();
    return env.Undefined();
}

Napi::Value CheckBloomFilterElement(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string bloom_filter_name = info[0].As<Napi::String>();
    std::string element = info[1].As<Napi::String>();
    bool exists = pipeline.check_bloom_filter_element(bloom_filter_name, element).get();
    return Napi::Boolean::New(env, exists);
}

Napi::Value PutLinkedHashMap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string map_name = info[0].As<Napi::String>();
    std::string key = info[1].As<Napi::String>();
    int value = info[2].As<Napi::Number>().Int32Value();
    pipeline.put_linked_hash_map(map_name, key, value).get();
    return env.Undefined();
}

Napi::Value GetLinkedHashMap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string map_name = info[0].As<Napi::String>();
    std::string key = info[1].As<Napi::String>();
    int value = pipeline.get_linked_hash_map(map_name, key).get();
    return Napi::Number::New(env, value);
}

Napi::Value RemoveLinkedHashMap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string map_name = info[0].As<Napi::String>();
    std::string key = info[1].As<Napi::String>();
    pipeline.remove_linked_hash_map(map_name, key).get();
    return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "start"), Napi::Function::New(env, Start));
    exports.Set(Napi::String::New(env, "stop"), Napi::Function::New(env, Stop));
    exports.Set(Napi::String::New(env, "addScalar"), Napi::Function::New(env, AddScalar));
    exports.Set(Napi::String::New(env, "getScalar"), Napi::Function::New(env, GetScalar));
    exports.Set(Napi::String::New(env, "addDistributedScalar"), Napi::Function::New(env, AddDistributedScalar));
    exports.Set(Napi::String::New(env, "getDistributedScalar"), Napi::Function::New(env, GetDistributedScalar));
    exports.Set(Napi::String::New(env, "addVectorElement"), Napi::Function::New(env, AddVectorElement));
    exports.Set(Napi::String::New(env, "getVector"), Napi::Function::New(env, GetVector));
    exports.Set(Napi::String::New(env, "addMatrixElement"), Napi::Function::New(env, AddMatrixElement));
    exports.Set(Napi::String::New(env, "getMatrix"), Napi::Function::New(env, GetMatrix));
    exports.Set(Napi::String::New(env, "addTreeNode"), Napi::Function::New(env, AddTreeNode));
    exports.Set(Napi::String::New(env, "getTreeNodes"), Napi::Function::New(env, GetTreeNodes));
    exports.Set(Napi::String::New(env, "addBloomFilterElement"), Napi::Function::New(env, AddBloomFilterElement));
    exports.Set(Napi::String::New(env, "checkBloomFilterElement"), Napi::Function::New(env, CheckBloomFilterElement));
    exports.Set(Napi::String::New(env, "putLinkedHashMap"), Napi::Function::New(env, PutLinkedHashMap));
    exports.Set(Napi::String::New(env, "getLinkedHashMap"), Napi::Function::New(env, GetLinkedHashMap));
    exports.Set(Napi::String::New(env, "removeLinkedHashMap"), Napi::Function::New(env, RemoveLinkedHashMap));
    return exports;
}

NODE_API_MODULE(addon, Init)
