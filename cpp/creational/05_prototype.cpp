/**
 * 设计模式: 原型模式 (Prototype)
 * 分类: 创建型
 *
 * 意图: 通过复制现有对象来创建新对象，而不是通过实例化类。
 * 核心思想: 对象自身提供 clone 接口，支持深拷贝。
 * 编程范式: OOP — 多态克隆 + 原型注册表（可选）。
 */

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// ── 原型接口 ──────────────────────────────────────────────────────────────
struct Shape {
    std::string color;
    explicit Shape(std::string c) : color(std::move(c)) {}
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// ── 具体原型 ──────────────────────────────────────────────────────────────
struct Circle : Shape {
    int radius;
    Circle(std::string c, int r) : Shape(std::move(c)), radius(r) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);  // 调用拷贝构造
    }
    void draw() const override {
        std::cout << "Circle color=" << color << " r=" << radius << "\n";
    }
};

struct Rectangle : Shape {
    int w, h;
    Rectangle(std::string c, int w, int h) : Shape(std::move(c)), w(w), h(h) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }
    void draw() const override {
        std::cout << "Rectangle color=" << color << " " << w << "x" << h << "\n";
    }
};

// ── 原型注册表 ────────────────────────────────────────────────────────────
class ShapeRegistry {
    std::unordered_map<std::string, std::unique_ptr<Shape>> cache_;
public:
    void add(const std::string& key, std::unique_ptr<Shape> shape) {
        cache_[key] = std::move(shape);
    }
    std::unique_ptr<Shape> get(const std::string& key) const {
        return cache_.at(key)->clone();
    }
};

int main() {
    ShapeRegistry registry;
    registry.add("red_circle",     std::make_unique<Circle>("red", 10));
    registry.add("blue_rectangle", std::make_unique<Rectangle>("blue", 5, 3));

    auto s1 = registry.get("red_circle");
    auto s2 = registry.get("blue_rectangle");
    auto s3 = registry.get("red_circle");   // 独立副本

    s1->draw();
    s2->draw();
    s3->draw();
    std::cout << "s1 != s3 (different objects): " << std::boolalpha << (s1.get() != s3.get()) << "\n";
    return 0;
}
