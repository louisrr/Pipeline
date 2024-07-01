#include <jni.h>
#include <string>
#include "Pipeline.h"

Pipeline pipeline;

extern "C" {

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_start(JNIEnv *, jobject) {
    pipeline.start().get();
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_stop(JNIEnv *, jobject) {
    pipeline.stop().get();
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_addScalar(JNIEnv *, jobject, jint value) {
    pipeline.add_scalar(value).get();
}

JNIEXPORT jint JNICALL Java_com_example_pipeline_PipelineJNI_getScalar(JNIEnv *, jobject) {
    return pipeline.get_scalar().get();
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_addDistributedScalar(JNIEnv *env, jobject, jstring scalarName, jint value) {
    const char *name = env->GetStringUTFChars(scalarName, 0);
    pipeline.add_distributed_scalar(std::string(name), value).get();
    env->ReleaseStringUTFChars(scalarName, name);
}

JNIEXPORT jint JNICALL Java_com_example_pipeline_PipelineJNI_getDistributedScalar(JNIEnv *env, jobject, jstring scalarName) {
    const char *name = env->GetStringUTFChars(scalarName, 0);
    int result = pipeline.get_distributed_scalar(std::string(name)).get();
    env->ReleaseStringUTFChars(scalarName, name);
    return result;
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_addVectorElement(JNIEnv *env, jobject, jstring vectorName, jint value) {
    const char *name = env->GetStringUTFChars(vectorName, 0);
    pipeline.add_vector_element(std::string(name), value).get();
    env->ReleaseStringUTFChars(vectorName, name);
}

JNIEXPORT jintArray JNICALL Java_com_example_pipeline_PipelineJNI_getVector(JNIEnv *env, jobject, jstring vectorName) {
    const char *name = env->GetStringUTFChars(vectorName, 0);
    std::vector<int> vector = pipeline.get_vector(std::string(name)).get();
    env->ReleaseStringUTFChars(vectorName, name);

    jintArray result = env->NewIntArray(vector.size());
    env->SetIntArrayRegion(result, 0, vector.size(), vector.data());
    return result;
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_addMatrixElement(JNIEnv *env, jobject, jstring matrixName, jint row, jint col, jint value) {
    const char *name = env->GetStringUTFChars(matrixName, 0);
    pipeline.add_matrix_element(std::string(name), row, col, value).get();
    env->ReleaseStringUTFChars(matrixName, name);
}

JNIEXPORT jobjectArray JNICALL Java_com_example_pipeline_PipelineJNI_getMatrix(JNIEnv *env, jobject, jstring matrixName) {
    const char *name = env->GetStringUTFChars(matrixName, 0);
    std::vector<std::vector<int>> matrix = pipeline.get_matrix(std::string(name)).get();
    env->ReleaseStringUTFChars(matrixName, name);

    jobjectArray result = env->NewObjectArray(matrix.size(), env->FindClass("[I"), nullptr);
    for (size_t i = 0; i < matrix.size(); i++) {
        jintArray row = env->NewIntArray(matrix[i].size());
        env->SetIntArrayRegion(row, 0, matrix[i].size(), matrix[i].data());
        env->SetObjectArrayElement(result, i, row);
        env->DeleteLocalRef(row);
    }
    return result;
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_addTreeNode(JNIEnv *env, jobject, jstring treeName, jint value) {
    const char *name = env->GetStringUTFChars(treeName, 0);
    pipeline.add_tree_node(std::string(name), value).get();
    env->ReleaseStringUTFChars(treeName, name);
}

JNIEXPORT jintArray JNICALL Java_com_example_pipeline_PipelineJNI_getTreeNodes(JNIEnv *env, jobject, jstring treeName) {
    const char *name = env->GetStringUTFChars(treeName, 0);
    std::vector<int> nodes = pipeline.get_tree_nodes(std::string(name)).get();
    env->ReleaseStringUTFChars(treeName, name);

    jintArray result = env->NewIntArray(nodes.size());
    env->SetIntArrayRegion(result, 0, nodes.size(), nodes.data());
    return result;
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_addBloomFilterElement(JNIEnv *env, jobject, jstring bloomFilterName, jstring element) {
    const char *bloomName = env->GetStringUTFChars(bloomFilterName, 0);
    const char *elem = env->GetStringUTFChars(element, 0);
    pipeline.add_bloom_filter_element(std::string(bloomName), std::string(elem)).get();
    env->ReleaseStringUTFChars(bloomFilterName, bloomName);
    env->ReleaseStringUTFChars(element, elem);
}

JNIEXPORT jboolean JNICALL Java_com_example_pipeline_PipelineJNI_checkBloomFilterElement(JNIEnv *env, jobject, jstring bloomFilterName, jstring element) {
    const char *bloomName = env->GetStringUTFChars(bloomFilterName, 0);
    const char *elem = env->GetStringUTFChars(element, 0);
    bool result = pipeline.check_bloom_filter_element(std::string(bloomName), std::string(elem)).get();
    env->ReleaseStringUTFChars(bloomFilterName, bloomName);
    env->ReleaseStringUTFChars(element, elem);
    return result;
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_putLinkedHashMap(JNIEnv *env, jobject, jstring mapName, jstring key, jint value) {
    const char *map = env->GetStringUTFChars(mapName, 0);
    const char *k = env->GetStringUTFChars(key, 0);
    pipeline.put_linked_hash_map(std::string(map), std::string(k), value).get();
    env->ReleaseStringUTFChars(mapName, map);
    env->ReleaseStringUTFChars(key, k);
}

JNIEXPORT jint JNICALL Java_com_example_pipeline_PipelineJNI_getLinkedHashMap(JNIEnv *env, jobject, jstring mapName, jstring key) {
    const char *map = env->GetStringUTFChars(mapName, 0);
    const char *k = env->GetStringUTFChars(key, 0);
    int result = pipeline.get_linked_hash_map(std::string(map), std::string(k)).get();
    env->ReleaseStringUTFChars(mapName, map);
    env->ReleaseStringUTFChars(key, k);
    return result;
}

JNIEXPORT void JNICALL Java_com_example_pipeline_PipelineJNI_removeLinkedHashMap(JNIEnv *env, jobject, jstring mapName, jstring key) {
    const char *map = env->GetStringUTFChars(mapName, 0);
    const char *k = env->GetStringUTFChars(key, 0);
    pipeline.remove_linked_hash_map(std::string(map), std::string(k)).get();
    env->ReleaseStringUTFChars(mapName, map);
    env->ReleaseStringUTFChars(key, k);
}

} // extern "C"
