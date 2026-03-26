/**
 * 设计模式: 享元模式 (Flyweight)
 * 分类: 结构型
 *
 * 意图: 运用共享技术高效支持大量细粒度对象，减少内存占用。
 * 核心思想: 分离内部状态（共享，不变）与外部状态（不共享，由调用者传入）。
 * 编程范式: OOP — 对象池/缓存 + 内外状态分离。
 */

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// ── 享元：内部状态（共享）────────────────────────────────────────────────
struct TreeType {
    std::string name;
    std::string color;
    std::string texture;

    void draw(int x, int y) const {
        std::cout << "Tree[" << name << "/" << color << "] at (" << x << "," << y << ")\n";
    }
};

// ── 享元工厂 ──────────────────────────────────────────────────────────────
class TreeFactory {
    std::unordered_map<std::string, std::shared_ptr<TreeType>> types_;
public:
    std::shared_ptr<TreeType> get(const std::string& name,
                                   const std::string& color,
                                   const std::string& texture) {
        std::string key = name + "_" + color;
        if (!types_.count(key)) {
            types_[key] = std::make_shared<TreeType>(TreeType{name, color, texture});
            std::cout << "[Factory] created new TreeType: " << key << "\n";
        }
        return types_[key];
    }
    size_t typeCount() const { return types_.size(); }
};

// ── 树实例：携带外部状态（x, y 坐标）────────────────────────────────────
struct Tree {
    int x, y;
    std::shared_ptr<TreeType> type;
    void draw() const { type->draw(x, y); }
};

int main() {
    TreeFactory factory;
    std::vector<Tree> forest;

    // 种 1000 棵树，但只有 3 种 TreeType
    for (int i = 0; i < 5; ++i) {
        forest.push_back({i * 10, i * 5, factory.get("oak",   "green",  "rough")});
        forest.push_back({i * 7,  i * 3, factory.get("pine",  "dark",   "smooth")});
        forest.push_back({i * 3,  i * 9, factory.get("birch", "white",  "thin")});
    }

    for (auto& tree : forest) tree.draw();
    std::cout << "TreeType instances: " << factory.typeCount() << " (vs " << forest.size() << " trees)\n";
    return 0;
}
