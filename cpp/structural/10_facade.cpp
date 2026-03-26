/**
 * 设计模式: 外观模式 (Facade)
 * 分类: 结构型
 *
 * 意图: 为子系统中的一组接口提供一个统一的高层接口，使子系统更容易使用。
 * 核心思想: 外观类封装复杂子系统，对外暴露简洁接口，降低耦合度。
 * 编程范式: OOP — 封装 + 最少知识原则（迪米特法则）。
 */

#include <iostream>
#include <string>

// ── 子系统组件 ────────────────────────────────────────────────────────────
struct CPU {
    void freeze() { std::cout << "CPU: freeze\n"; }
    void jump(long pos) { std::cout << "CPU: jump to " << pos << "\n"; }
    void execute() { std::cout << "CPU: execute\n"; }
};

struct Memory {
    void load(long pos, const std::string& data) {
        std::cout << "Memory: load \"" << data << "\" at " << pos << "\n";
    }
};

struct HardDrive {
    std::string read(long sector, int size) {
        std::cout << "HDD: read sector=" << sector << " size=" << size << "\n";
        return "bootloader";
    }
};

// ── 外观 ──────────────────────────────────────────────────────────────────
class ComputerFacade {
    CPU       cpu_;
    Memory    memory_;
    HardDrive hdd_;
public:
    void start() {
        std::cout << "=== booting ===\n";
        cpu_.freeze();
        auto data = hdd_.read(0, 512);
        memory_.load(0x0, data);
        cpu_.jump(0x0);
        cpu_.execute();
        std::cout << "=== boot done ===\n";
    }
};

int main() {
    ComputerFacade computer;
    computer.start();
    return 0;
}
