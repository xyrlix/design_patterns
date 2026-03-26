/**
 * 设计模式: 装饰器模式 (Decorator)
 * 分类: 结构型
 *
 * 意图: 动态地为对象附加额外职责，是继承的灵活替代方案。
 * 核心思想: 装饰器与被装饰对象实现相同接口，层层包裹扩展行为。
 * 编程范式: OOP — 组合 + 透明包装，符合开闭原则。
 */

#include <iostream>
#include <memory>
#include <string>

// ── 组件接口 ──────────────────────────────────────────────────────────────
struct TextProcessor {
    virtual std::string process(const std::string& text) const = 0;
    virtual ~TextProcessor() = default;
};

// ── 具体组件 ──────────────────────────────────────────────────────────────
struct PlainText : TextProcessor {
    std::string process(const std::string& text) const override { return text; }
};

// ── 抽象装饰器 ────────────────────────────────────────────────────────────
struct TextDecorator : TextProcessor {
    explicit TextDecorator(std::unique_ptr<TextProcessor> wrapped)
        : wrapped_(std::move(wrapped)) {}
protected:
    std::unique_ptr<TextProcessor> wrapped_;
};

// ── 具体装饰器 ────────────────────────────────────────────────────────────
struct UpperCaseDecorator : TextDecorator {
    using TextDecorator::TextDecorator;
    std::string process(const std::string& text) const override {
        auto s = wrapped_->process(text);
        for (auto& c : s) c = static_cast<char>(std::toupper(c));
        return s;
    }
};

struct TrimDecorator : TextDecorator {
    using TextDecorator::TextDecorator;
    std::string process(const std::string& text) const override {
        auto s = wrapped_->process(text);
        auto b = s.find_first_not_of(' ');
        auto e = s.find_last_not_of(' ');
        return (b == std::string::npos) ? "" : s.substr(b, e - b + 1);
    }
};

struct ExclamationDecorator : TextDecorator {
    using TextDecorator::TextDecorator;
    std::string process(const std::string& text) const override {
        return wrapped_->process(text) + "!!!";
    }
};

int main() {
    // 链式组合装饰器：trim → uppercase → exclamation
    auto pipeline =
        std::make_unique<ExclamationDecorator>(
        std::make_unique<UpperCaseDecorator>(
        std::make_unique<TrimDecorator>(
        std::make_unique<PlainText>())));

    std::cout << pipeline->process("  hello world  ") << "\n";
    return 0;
}
