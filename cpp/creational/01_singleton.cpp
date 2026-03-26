/**
 * 设计模式: 单例模式 (Singleton)
 * 分类: 创建型
 *
 * 意图: 保证一个类只有一个实例，并提供全局访问点。
 * 核心思想: 私有构造函数 + 静态实例 + 线程安全的懒汉式初始化。
 * 编程范式: OOP — 封装、静态成员控制实例生命周期。
 */

#include <iostream>
#include <mutex>
#include <string>

// ── 线程安全的 Meyer's Singleton ──────────────────────────────────────────
class Database {
public:
    // 全局访问点：局部静态变量天然线程安全（C++11 起）
    static Database& instance() {
        static Database db;
        return db;
    }

    void query(const std::string& sql) const {
        std::cout << "[DB] query: " << sql << "\n";
    }

    // 禁止拷贝与赋值
    Database(const Database&)            = delete;
    Database& operator=(const Database&) = delete;

private:
    Database() { std::cout << "[DB] connected\n"; }
    ~Database() { std::cout << "[DB] disconnected\n"; }
};

// ── 演示 ──────────────────────────────────────────────────────────────────
int main() {
    Database& db1 = Database::instance();
    Database& db2 = Database::instance();

    db1.query("SELECT * FROM users");
    db2.query("INSERT INTO logs VALUES (1)");

    std::cout << "same instance: " << std::boolalpha << (&db1 == &db2) << "\n";
    return 0;
}
