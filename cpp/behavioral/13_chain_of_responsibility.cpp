/**
 * 设计模式: 责任链模式 (Chain of Responsibility)
 * 分类: 行为型
 *
 * 意图: 将请求沿着处理者链传递，每个处理者决定处理请求或将其传给下一个。
 * 核心思想: 处理者持有下一个处理者的引用，形成链式结构，解耦请求发送者和接收者。
 * 编程范式: OOP — 链式调用 + 单一职责。
 */

#include <iostream>
#include <memory>
#include <string>

// ── 处理者接口 ────────────────────────────────────────────────────────────
struct Handler {
    virtual void setNext(std::shared_ptr<Handler> next) = 0;
    virtual void handle(int request) = 0;
    virtual ~Handler() = default;
};

// ── 抽象处理者（基类，实现链传递）───────────────────────────────────────
struct AbstractHandler : Handler {
    std::shared_ptr<Handler> next_;
    void setNext(std::shared_ptr<Handler> next) override { next_ = std::move(next); }
    void handle(int request) override {
        if (next_) next_->handle(request);
    }
};

// ── 具体处理者 ────────────────────────────────────────────────────────────
struct LowLevelHandler : AbstractHandler {
    void handle(int req) override {
        if (req < 10) std::cout << "LowLevel handled: " << req << "\n";
        else AbstractHandler::handle(req);
    }
};

struct MidLevelHandler : AbstractHandler {
    void handle(int req) override {
        if (req < 100) std::cout << "MidLevel handled: " << req << "\n";
        else AbstractHandler::handle(req);
    }
};

struct HighLevelHandler : AbstractHandler {
    void handle(int req) override {
        std::cout << "HighLevel handled: " << req << "\n";
    }
};

int main() {
    auto low  = std::make_shared<LowLevelHandler>();
    auto mid  = std::make_shared<MidLevelHandler>();
    auto high = std::make_shared<HighLevelHandler>();

    low->setNext(mid);
    mid->setNext(high);

    for (int r : {5, 50, 500})
        low->handle(r);
    return 0;
}
