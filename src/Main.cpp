#include <seastar/core/app-template.hh>
#include <seastar/core/future.hh>
#include <seastar/core/distributed.hh>
#include <seastar/core/smp.hh>
#include <seastar/core/sharded.hh>
#include <seastar/core/reactor.hh>
#include <seastar/core/seastar.hh>
#include <iostream>
#include <string>

class Pipeline {
public:
    seastar::future<> run() {
        return seastar::make_ready_future<>();
    }
};

seastar::distributed<Pipeline> pipeline;

int main(int argc, char** argv) {
    seastar::app_template app;
    return app.run(argc, argv, [] {
        return pipeline.start().then([] {
            return pipeline.invoke_on_all([](Pipeline& p) {
                return p.run();
            });
        }).then([] {
            return pipeline.stop();
        });
    });
}
