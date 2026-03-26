/**
 * 设计模式: 访问者模式 (Visitor)
 * 分类: 行为型
 *
 * 意图: 将算法与其操作的对象结构分离，可以在不改变已有类的前提下增加新操作。
 * 核心思想: 双重分派（double dispatch）：accept 调用 visitor 的重载方法。
 * 编程范式: OOP — 开闭原则（新增访问者无需修改元素类）。
 */

#include <iostream>
#include <memory>
#include <vector>

struct Circle;
struct Rectangle;

// ── 访问者接口 ────────────────────────────────────────────────────────────
struct Visitor {
    virtual void visit(const Circle& c)    = 0;
    virtual void visit(const Rectangle& r) = 0;
    virtual ~Visitor() = default;
};

// ── 元素接口 ──────────────────────────────────────────────────────────────
struct Shape {
    virtual void accept(Visitor& v) const = 0;
    virtual ~Shape() = default;
};

// ── 具体元素 ──────────────────────────────────────────────────────────────
struct Circle : Shape {
    float radius;
    explicit Circle(float r) : radius(r) {}
    void accept(Visitor& v) const override { v.visit(*this); }
};

struct Rectangle : Shape {
    float w, h;
    Rectangle(float w, float h) : w(w), h(h) {}
    void accept(Visitor& v) const override { v.visit(*this); }
};

// ── 具体访问者：计算面积 ──────────────────────────────────────────────────
struct AreaCalculator : Visitor {
    float total = 0;
    void visit(const Circle& c)    override { total += 3.14159f * c.radius * c.radius; }
    void visit(const Rectangle& r) override { total += r.w * r.h; }
};

// ── 具体访问者：打印描述 ──────────────────────────────────────────────────
struct DescriptionPrinter : Visitor {
    void visit(const Circle& c)    override { std::cout << "Circle r=" << c.radius << "\n"; }
    void visit(const Rectangle& r) override { std::cout << "Rect " << r.w << "x" << r.h << "\n"; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(3, 4));
    shapes.push_back(std::make_unique<Circle>(2));

    DescriptionPrinter printer;
    for (auto& s : shapes) s->accept(printer);

    AreaCalculator calc;
    for (auto& s : shapes) s->accept(calc);
    std::cout << "Total area: " << calc.total << "\n";
    return 0;
}
