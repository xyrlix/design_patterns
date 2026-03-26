/**
 * 设计模式: 命令模式 (Command)
 * 分类: 行为型
 *
 * 意图: 将请求封装为对象，从而支持参数化、排队、日志、撤销/重做操作。
 * 核心思想: 命令对象封装"动作 + 接收者"，调用者只依赖命令接口。
 * 编程范式: OOP — 封装变化 + 命令队列 + 撤销栈。
 */

#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

// ── 接收者 ────────────────────────────────────────────────────────────────
struct TextEditor {
    std::string text;
    void append(const std::string& s) { text += s; }
    void deleteLast(size_t n)         { if (n <= text.size()) text.resize(text.size() - n); }
    void print() const                { std::cout << "Text: \"" << text << "\"\n"; }
};

// ── 命令接口 ──────────────────────────────────────────────────────────────
struct Command {
    virtual void execute() = 0;
    virtual void undo()    = 0;
    virtual ~Command() = default;
};

// ── 具体命令 ──────────────────────────────────────────────────────────────
struct AppendCommand : Command {
    TextEditor& editor;
    std::string value;
    AppendCommand(TextEditor& e, std::string v) : editor(e), value(std::move(v)) {}
    void execute() override { editor.append(value); }
    void undo()    override { editor.deleteLast(value.size()); }
};

// ── 调用者（持有命令历史）────────────────────────────────────────────────
class CommandInvoker {
    std::stack<std::unique_ptr<Command>> history_;
public:
    void run(std::unique_ptr<Command> cmd) {
        cmd->execute();
        history_.push(std::move(cmd));
    }
    void undo() {
        if (!history_.empty()) {
            history_.top()->undo();
            history_.pop();
        }
    }
};

int main() {
    TextEditor editor;
    CommandInvoker invoker;

    invoker.run(std::make_unique<AppendCommand>(editor, "Hello"));
    invoker.run(std::make_unique<AppendCommand>(editor, ", World"));
    editor.print();

    invoker.undo();
    editor.print();

    invoker.undo();
    editor.print();
    return 0;
}
