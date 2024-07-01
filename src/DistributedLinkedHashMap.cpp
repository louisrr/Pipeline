#include "DistributedLinkedHashMap.h"
#include <seastar/core/sleep.hh>

template<typename K, typename V>
seastar::future<> DistributedLinkedHashMap<K, V>::start() {
    return maps.start().then([this] {
        return load_all_shards();
    });
}

template<typename K, typename V>
seastar::future<> DistributedLinkedHashMap<K, V>::stop() {
    return save_all_shards().then([this] {
        return maps.stop();
    });
}

template<typename K, typename V>
seastar::future<> DistributedLinkedHashMap<K, V>::put(const K& key, const V& value) {
    return seastar::invoke_on_shard(get_shard_id(key), [key, value](auto& map) {
        map.put(key, value);
    }).then([this, key, value] {
        return replicate_put(key, value);
    });
}

template<typename K, typename V>
seastar::future<V> DistributedLinkedHashMap<K, V>::get(const K& key) {
    return seastar::invoke_on_shard(get_shard_id(key), [key](auto& map) {
        return map.get(key);
    }).handle_exception([](std::exception_ptr ep) {
        try {
            std::rethrow_exception(ep);
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return seastar::make_ready_future<V>();
        }
    });
}

template<typename K, typename V>
seastar::future<> DistributedLinkedHashMap<K, V>::remove(const K& key) {
    return seastar::invoke_on_shard(get_shard_id(key), [key](auto& map) {
        map.remove(key);
    }).then([this, key] {
        return replicate_remove(key);
    }).handle_exception([](std::exception_ptr ep) {
        try {
            std::rethrow_exception(ep);
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return seastar::make_ready_future<>();
        }
    });
}

template<typename K, typename V>
size_t DistributedLinkedHashMap<K, V>::get_shard_id(const K& key) {
    return std::hash<K>()(key) % seastar::smp::count;
}

template<typename K, typename V>
seastar::future<> DistributedLinkedHashMap<K, V>::replicate_put(const K& key, const V& value) {
    std::vector<seastar::future<>> futures;
    for (size_t i = 0; i < seastar::smp::count; ++i) {
        if (i != seastar::this_shard_id()) {
            futures.push_back(seastar::smp::submit_to(i, [key, value](auto& map) {
                map.put(key, value);
            }));
        }
    }
    return seastar::when_all(futures.begin(), futures.end()).discard_result();
}

template<typename K, typename V>
seastar::future<> DistributedLinkedHashMap<K, V>::replicate_remove(const K& key) {
    std::vector<seastar::future<>> futures;
    for (size_t i = 0; i < seastar::smp::count; ++i) {
        if (i != seastar::this_shard_id()) {
            futures.push_back(seastar::smp::submit_to(i, [key](auto& map) {
                map.remove(key);
            }));
        }
    }
    return seastar::when_all(futures.begin(), futures.end()).discard_result();
}

template<typename K, typename V>
seastar::future<> DistributedLinkedHashMap<K, V>::save_all_shards() {
    std::vector<seastar::future<>> futures;
    for (size_t i = 0; i < seastar::smp::count; ++i) {
        futures.push_back(seastar::smp::submit_to(i, [](auto& map) {
            map.save_to_file("shard" + std::to_string(seastar::this_shard_id()) + ".dat");
        }));
    }
    return seastar::when_all(futures.begin(), futures.end()).discard_result();
}

template<typename K, typename V>
seastar::future<> DistributedLinkedHashMap<K, V>::load_all_shards() {
    std::vector<seastar::future<>> futures;
    for (size_t i = 0; i < seastar::smp::count; ++i) {
        futures.push_back(seastar::smp::submit_to(i, [](auto& map) {
            map.load_from_file("shard" + std::to_string(seastar::this_shard_id()) + ".dat");
        }));
    }
    return seastar::when_all(futures.begin(), futures.end()).discard_result();
}
