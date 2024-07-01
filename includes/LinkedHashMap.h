#ifndef DISTRIBUTED_LINKED_HASH_MAP_H
#define DISTRIBUTED_LINKED_HASH_MAP_H

#include <seastar/core/sharded.hh>
#include <seastar/core/future.hh>
#include "LinkedHashMap.h"

template<typename K, typename V>
class DistributedLinkedHashMap {
public:
    seastar::future<> start();
    seastar::future<> stop();
    seastar::future<> put(const K& key, const V& value);
    seastar::future<V> get(const K& key);
    seastar::future<> remove(const K& key);

private:
    seastar::sharded<LinkedHashMap<K, V>> maps;
    size_t get_shard_id(const K& key);
    seastar::future<> replicate_put(const K& key, const V& value);
    seastar::future<> replicate_remove(const K& key);
    seastar::future<> save_all_shards();
    seastar::future<> load_all_shards();
};

#include "DistributedLinkedHashMap.tcc"

#endif // DISTRIBUTED_LINKED_HASH_MAP_H
