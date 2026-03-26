/**
 * 设计模式: 备忘录模式 (Memento)
 * 分类: 行为型
 *
 * 意图: 在不破坏封装性的前提下，捕获一个对象的内部状态，以便日后恢复。
 * 核心思想: 发起人创建/恢复备忘录，管理者负责保存备忘录列表，三角色分离。
 * 编程范式: OOP — 状态快照 + 封装保护（发起人私有状态不对外暴露）。
 */

#include <iostream>
#include <memory>
#include <stack>
#include <string>

// ── 备忘录（不透明令牌）──────────────────────────────────────────────────
class Memento {
    friend class Editor;   // 只有 Editor 可访问内部
    std::string state_;
    explicit Memento(std::string s) : state_(std::move(s)) {}
};

// ── 发起人 ────────────────────────────────────────────────────────────────
class Editor {
    std::string content_;
public:
    void type(const std::string& text) { content_ += text; }
    void print() const { std::cout << "Content: \"" << content_ << "\"\n"; }

    std::unique_ptr<Memento> save() const {
        return std::unique_ptr<Memento>(new Memento(content_));
    }
    void restore(const Memento& m) { content_ = m.state_; }
};

// ── 管理者 ────────────────────────────────────────────────────────────────
class History {
    std::stack<std::unique_ptr<Memento>> stack_;
public:
    void push(std::unique_ptr<Memento> m) { stack_.push(std::move(m)); }
    std::unique_ptr<Memento> pop() {
        if (stack_.empty()) return nullptr;
        auto m = std::move(stack_.top());
        stack_.pop();
        return m;
    }
};

int main() {
    Editor  editor;
    History history;

    editor.type("Hello");
    history.push(editor.save());   // 保存快照 1

    editor.type(", World");
    history.push(editor.save());   // 保存快照 2

    editor.type("!!!");
    editor.print();                // Hello, World!!!

    auto m2 = history.pop();
    editor.restore(*m2);
    editor.print();                // Hello, World

    auto m1 = history.pop();
    editor.restore(*m1);
    editor.print();                // Hello
    return 0;
}
