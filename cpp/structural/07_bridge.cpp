/**
 * 设计模式: 桥接模式 (Bridge)
 * 分类: 结构型
 *
 * 意图: 将抽象部分与实现部分分离，使它们可以独立变化。
 * 核心思想: 抽象层持有实现层引用，两个维度分别扩展，避免继承爆炸。
 * 编程范式: OOP — 组合 + 依赖注入，优于多层继承。
 */

#include <iostream>
#include <memory>
#include <string>

// ── 实现层接口 ────────────────────────────────────────────────────────────
struct Renderer {
    virtual void renderCircle(float x, float y, float r) const = 0;
    virtual ~Renderer() = default;
};

struct VectorRenderer : Renderer {
    void renderCircle(float x, float y, float r) const override {
        std::cout << "Vector: circle at (" << x << "," << y << ") r=" << r << "\n";
    }
};

struct RasterRenderer : Renderer {
    void renderCircle(float x, float y, float r) const override {
        std::cout << "Raster: circle at (" << x << "," << y << ") r=" << r << "\n";
    }
};

// ── 抽象层 ────────────────────────────────────────────────────────────────
struct Shape {
    const Renderer& renderer;
    explicit Shape(const Renderer& r) : renderer(r) {}
    virtual void draw()   const = 0;
    virtual void resize(float factor) = 0;
    virtual ~Shape() = default;
};

struct Circle : Shape {
    float x, y, radius;
    Circle(const Renderer& r, float x, float y, float radius)
        : Shape(r), x(x), y(y), radius(radius) {}

    void draw()   const override { renderer.renderCircle(x, y, radius); }
    void resize(float factor)    override { radius *= factor; }
};

int main() {
    VectorRenderer vr;
    RasterRenderer rr;

    Circle c1(vr, 0, 0, 5);
    Circle c2(rr, 3, 4, 2);

    c1.draw();
    c2.draw();
    c1.resize(2);
    c1.draw();
    return 0;
}
