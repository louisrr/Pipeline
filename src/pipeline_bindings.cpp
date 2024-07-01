#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Pipeline.h"

namespace py = pybind11;

PYBIND11_MODULE(pipeline, m) {
    m.doc() = "Python bindings for the Pipeline C++ class";

    py::class_<Pipeline>(m, "Pipeline")
        .def(py::init<>())
        .def("start", &Pipeline::start)
        .def("stop", &Pipeline::stop)
        .def("add_scalar", &Pipeline::add_scalar)
        .def("get_scalar", &Pipeline::get_scalar)
        .def("add_distributed_scalar", &Pipeline::add_distributed_scalar)
        .def("get_distributed_scalar", &Pipeline::get_distributed_scalar)
        .def("add_vector_element", &Pipeline::add_vector_element)
        .def("get_vector", &Pipeline::get_vector)
        .def("add_matrix_element", &Pipeline::add_matrix_element)
        .def("get_matrix", &Pipeline::get_matrix)
        .def("add_tree_node", &Pipeline::add_tree_node)
        .def("get_tree_nodes", &Pipeline::get_tree_nodes)
        .def("add_bloom_filter_element", &Pipeline::add_bloom_filter_element)
        .def("check_bloom_filter_element", &Pipeline::check_bloom_filter_element)
        .def("put_linked_hash_map", &Pipeline::put_linked_hash_map)
        .def("get_linked_hash_map", &Pipeline::get_linked_hash_map)
        .def("remove_linked_hash_map", &Pipeline::remove_linked_hash_map);
}
