#include <art.hpp>

using namespace art;

int main() {
    art<std::shared_ptr<MyResource>> m;

    // set k
    m.set("k", std::make_shared(new MyResource()));

    // get k
    std::shared_ptr<MyResource> ptr = m.get("k");

    // delete k
    m.del("k");

    return 0;
}