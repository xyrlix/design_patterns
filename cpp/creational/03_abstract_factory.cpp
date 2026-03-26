/**
 * 设计模式: 抽象工厂模式 (Abstract Factory)
 * 分类: 创建型
 *
 * 意图: 提供一个接口，创建一系列相关或相互依赖的对象，而无需指定具体类。
 * 核心思想: 产品族 + 工厂族，切换工厂即切换整套产品风格。
 * 编程范式: OOP — 接口隔离 + 依赖注入。
 */

#include <iostream>
#include <memory>
#include <string>

// ── 抽象产品 ──────────────────────────────────────────────────────────────
struct Button {
    virtual void render() const = 0;
    virtual ~Button() = default;
};

struct Checkbox {
    virtual void render() const = 0;
    virtual ~Checkbox() = default;
};

// ── 具体产品：Windows 风格 ────────────────────────────────────────────────
struct WinButton : Button {
    void render() const override { std::cout << "[Win] Button\n"; }
};
struct WinCheckbox : Checkbox {
    void render() const override { std::cout << "[Win] Checkbox\n"; }
};

// ── 具体产品：Mac 风格 ────────────────────────────────────────────────────
struct MacButton : Button {
    void render() const override { std::cout << "[Mac] Button\n"; }
};
struct MacCheckbox : Checkbox {
    void render() const override { std::cout << "[Mac] Checkbox\n"; }
};

// ── 抽象工厂 ──────────────────────────────────────────────────────────────
struct GUIFactory {
    virtual std::unique_ptr<Button>   createButton()   const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
    virtual ~GUIFactory() = default;
};

struct WinFactory : GUIFactory {
    std::unique_ptr<Button>   createButton()   const override { return std::make_unique<WinButton>(); }
    std::unique_ptr<Checkbox> createCheckbox() const override { return std::make_unique<WinCheckbox>(); }
};

struct MacFactory : GUIFactory {
    std::unique_ptr<Button>   createButton()   const override { return std::make_unique<MacButton>(); }
    std::unique_ptr<Checkbox> createCheckbox() const override { return std::make_unique<MacCheckbox>(); }
};

// ── 客户端 ────────────────────────────────────────────────────────────────
void renderUI(const GUIFactory& factory) {
    auto btn = factory.createButton();
    auto chk = factory.createCheckbox();
    btn->render();
    chk->render();
}

int main() {
    WinFactory win;
    MacFactory mac;
    renderUI(win);
    renderUI(mac);
    return 0;
}
