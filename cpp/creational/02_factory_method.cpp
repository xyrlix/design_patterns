/**
 * 设计模式: 工厂方法模式 (Factory Method)
 * 分类: 创建型
 *
 * 意图: 定义创建对象的接口，由子类决定实例化哪个类。
 * 核心思想: 抽象工厂方法 + 具体工厂子类，将对象创建延迟到子类。
 * 编程范式: OOP — 多态 + 开闭原则（扩展新产品无需修改已有代码）。
 */

#include <iostream>
#include <memory>
#include <string>

// ── 产品接口 ──────────────────────────────────────────────────────────────
struct Logger {
    virtual void log(const std::string& msg) const = 0;
    virtual ~Logger() = default;
};

struct ConsoleLogger : Logger {
    void log(const std::string& msg) const override {
        std::cout << "[Console] " << msg << "\n";
    }
};

struct FileLogger : Logger {
    void log(const std::string& msg) const override {
        std::cout << "[File]    " << msg << "\n";
    }
};

// ── 工厂接口 ──────────────────────────────────────────────────────────────
struct LoggerFactory {
    virtual std::unique_ptr<Logger> create() const = 0;
    virtual ~LoggerFactory() = default;
};

struct ConsoleLoggerFactory : LoggerFactory {
    std::unique_ptr<Logger> create() const override {
        return std::make_unique<ConsoleLogger>();
    }
};

struct FileLoggerFactory : LoggerFactory {
    std::unique_ptr<Logger> create() const override {
        return std::make_unique<FileLogger>();
    }
};

// ── 客户端：依赖抽象，不依赖具体类 ──────────────────────────────────────
void clientCode(const LoggerFactory& factory) {
    auto logger = factory.create();
    logger->log("application started");
}

int main() {
    ConsoleLoggerFactory cf;
    FileLoggerFactory    ff;

    clientCode(cf);
    clientCode(ff);
    return 0;
}
