/**
 * 设计模式: 建造者模式 (Builder)
 * 分类: 创建型
 *
 * 意图: 将一个复杂对象的构建与其表示分离，使同样的构建过程可以创建不同的表示。
 * 核心思想: Director 控制构建步骤，Builder 实现每步细节，Product 是最终结果。
 * 编程范式: OOP — 流式接口 + 职责分离。
 */

#include <iostream>
#include <string>
#include <vector>

// ── 产品 ──────────────────────────────────────────────────────────────────
struct Pizza {
    std::string              dough;
    std::string              sauce;
    std::vector<std::string> toppings;

    void print() const {
        std::cout << "Pizza [" << dough << " | " << sauce << " | ";
        for (auto& t : toppings) std::cout << t << " ";
        std::cout << "]\n";
    }
};

// ── 建造者接口 ────────────────────────────────────────────────────────────
struct PizzaBuilder {
    virtual void setDough(const std::string& d)    = 0;
    virtual void setSauce(const std::string& s)    = 0;
    virtual void addTopping(const std::string& t)  = 0;
    virtual Pizza getResult()                       = 0;
    virtual ~PizzaBuilder() = default;
};

// ── 具体建造者 ────────────────────────────────────────────────────────────
struct ConcretePizzaBuilder : PizzaBuilder {
    Pizza pizza;
    void setDough(const std::string& d)   override { pizza.dough = d; }
    void setSauce(const std::string& s)   override { pizza.sauce = s; }
    void addTopping(const std::string& t) override { pizza.toppings.push_back(t); }
    Pizza getResult()                     override { return pizza; }
};

// ── 导演 ──────────────────────────────────────────────────────────────────
struct Director {
    void buildMargherita(PizzaBuilder& b) const {
        b.setDough("thin");
        b.setSauce("tomato");
        b.addTopping("mozzarella");
        b.addTopping("basil");
    }
    void buildPepperoni(PizzaBuilder& b) const {
        b.setDough("thick");
        b.setSauce("spicy");
        b.addTopping("pepperoni");
        b.addTopping("cheddar");
    }
};

int main() {
    Director director;
    ConcretePizzaBuilder builder;

    director.buildMargherita(builder);
    builder.getResult().print();

    builder = {};  // reset
    director.buildPepperoni(builder);
    builder.getResult().print();

    return 0;
}
