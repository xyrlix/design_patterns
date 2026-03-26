/**
 * 设计模式: 模板方法模式 (Template Method)
 * 分类: 行为型
 *
 * 意图: 在基类中定义算法骨架，将某些步骤的实现推迟到子类，子类可以重定义某些步骤而不改变算法结构。
 * 核心思想: 基类 final 方法控制流程，抽象/虚方法交由子类实现细节。
 * 编程范式: OOP — 控制反转（Hollywood Principle：别调用我，我会调用你）。
 */

#include <iostream>
#include <string>

// ── 抽象基类（模板）──────────────────────────────────────────────────────
class DataProcessor {
public:
    // 模板方法：定义算法骨架（不可重写）
    void process() {
        readData();
        processData();
        writeResult();
    }

protected:
    virtual void readData()    = 0;   // 必须实现
    virtual void processData() = 0;   // 必须实现
    virtual void writeResult() {      // 可选 Hook
        std::cout << "  [write] saving to default output\n";
    }
    virtual ~DataProcessor() = default;
};

// ── 具体子类 ──────────────────────────────────────────────────────────────
class CSVProcessor : public DataProcessor {
    void readData()    override { std::cout << "  [read]    reading CSV\n"; }
    void processData() override { std::cout << "  [process] parsing CSV rows\n"; }
};

class JsonProcessor : public DataProcessor {
    void readData()    override { std::cout << "  [read]    reading JSON\n"; }
    void processData() override { std::cout << "  [process] deserializing JSON\n"; }
    void writeResult() override { std::cout << "  [write]   sending to REST API\n"; }
};

int main() {
    CSVProcessor csv;
    std::cout << "=== CSV ===\n";
    csv.process();

    JsonProcessor json;
    std::cout << "=== JSON ===\n";
    json.process();
    return 0;
}
