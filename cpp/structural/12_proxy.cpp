/**
 * 设计模式: 代理模式 (Proxy)
 * 分类: 结构型
 *
 * 意图: 为另一个对象提供一个替代品或占位符，以控制对这个对象的访问。
 * 核心思想: 代理与真实对象实现相同接口，在访问真实对象前后插入额外逻辑。
 * 编程范式: OOP — 保护代理/虚拟代理/缓存代理（此处演示缓存代理）。
 */

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// ── 服务接口 ──────────────────────────────────────────────────────────────
struct DataService {
    virtual std::string fetch(const std::string& key) const = 0;
    virtual ~DataService() = default;
};

// ── 真实服务（慢，模拟网络请求）────────────────────────────────────────
struct RealDataService : DataService {
    std::string fetch(const std::string& key) const override {
        std::cout << "[Real] fetching \"" << key << "\" from network...\n";
        return "data_for_" + key;
    }
};

// ── 缓存代理 ──────────────────────────────────────────────────────────────
class CachingProxy : public DataService {
    std::unique_ptr<DataService>                     real_;
    mutable std::unordered_map<std::string, std::string> cache_;
public:
    explicit CachingProxy(std::unique_ptr<DataService> real)
        : real_(std::move(real)) {}

    std::string fetch(const std::string& key) const override {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            std::cout << "[Cache] hit for \"" << key << "\"\n";
            return it->second;
        }
        auto result = real_->fetch(key);
        cache_[key] = result;
        return result;
    }
};

int main() {
    CachingProxy proxy(std::make_unique<RealDataService>());
    proxy.fetch("user:1");
    proxy.fetch("user:2");
    proxy.fetch("user:1");   // 命中缓存
    proxy.fetch("user:2");   // 命中缓存
    return 0;
}
