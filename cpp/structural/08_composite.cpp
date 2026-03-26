/**
 * 设计模式: 组合模式 (Composite)
 * 分类: 结构型
 *
 * 意图: 将对象组合成树形结构以表示"部分-整体"层次结构，使客户对单个对象和组合对象的使用具有一致性。
 * 核心思想: 叶节点与容器节点实现相同接口，递归组合形成树。
 * 编程范式: OOP — 递归组合 + 统一接口（透明组合）。
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ── 组件接口 ──────────────────────────────────────────────────────────────
struct FileSystem {
    std::string name;
    explicit FileSystem(std::string n) : name(std::move(n)) {}
    virtual void ls(int depth = 0) const = 0;
    virtual ~FileSystem() = default;
protected:
    std::string indent(int d) const { return std::string(d * 2, ' '); }
};

// ── 叶节点 ────────────────────────────────────────────────────────────────
struct File : FileSystem {
    explicit File(std::string n) : FileSystem(std::move(n)) {}
    void ls(int depth = 0) const override {
        std::cout << indent(depth) << "- " << name << "\n";
    }
};

// ── 容器节点 ──────────────────────────────────────────────────────────────
struct Directory : FileSystem {
    std::vector<std::unique_ptr<FileSystem>> children;

    explicit Directory(std::string n) : FileSystem(std::move(n)) {}

    void add(std::unique_ptr<FileSystem> item) {
        children.push_back(std::move(item));
    }

    void ls(int depth = 0) const override {
        std::cout << indent(depth) << "+ " << name << "/\n";
        for (const auto& child : children)
            child->ls(depth + 1);
    }
};

int main() {
    auto root = std::make_unique<Directory>("root");
    auto src  = std::make_unique<Directory>("src");
    src->add(std::make_unique<File>("main.cpp"));
    src->add(std::make_unique<File>("utils.cpp"));

    auto inc = std::make_unique<Directory>("include");
    inc->add(std::make_unique<File>("utils.h"));

    root->add(std::move(src));
    root->add(std::move(inc));
    root->add(std::make_unique<File>("CMakeLists.txt"));

    root->ls();
    return 0;
}
