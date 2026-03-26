/**
 * 设计模式: 中介者模式 (Mediator)
 * 分类: 行为型
 *
 * 意图: 用一个中介对象封装一系列对象交互，使各对象不需要直接引用彼此，降低耦合度。
 * 核心思想: 同事对象只与中介者通信，中介者协调各同事间的交互。
 * 编程范式: OOP — 集中控制 + 解耦网状依赖为星型依赖。
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Colleague;

// ── 中介者接口 ────────────────────────────────────────────────────────────
struct Mediator {
    virtual void notify(Colleague* sender, const std::string& event) = 0;
    virtual ~Mediator() = default;
};

// ── 同事基类 ──────────────────────────────────────────────────────────────
struct Colleague {
    Mediator* mediator = nullptr;
    std::string name;
    explicit Colleague(std::string n) : name(std::move(n)) {}
    virtual ~Colleague() = default;
};

// ── 具体同事 ──────────────────────────────────────────────────────────────
struct Button : Colleague {
    using Colleague::Colleague;
    void click() {
        std::cout << "[Button:" << name << "] clicked\n";
        mediator->notify(this, "click");
    }
};

struct TextBox : Colleague {
    std::string text;
    using Colleague::Colleague;
    void setText(const std::string& t) { text = t; std::cout << "[TextBox:" << name << "] = \"" << t << "\"\n"; }
    void clear()                        { text = ""; std::cout << "[TextBox:" << name << "] cleared\n"; }
};

// ── 具体中介者 ────────────────────────────────────────────────────────────
class DialogMediator : public Mediator {
    Button*  submitBtn_;
    TextBox* inputBox_;
    TextBox* statusBox_;
public:
    DialogMediator(Button* btn, TextBox* input, TextBox* status)
        : submitBtn_(btn), inputBox_(input), statusBox_(status) {
        btn->mediator = input->mediator = status->mediator = this;
    }

    void notify(Colleague* sender, const std::string& event) override {
        if (sender == submitBtn_ && event == "click") {
            statusBox_->setText("Submitted: " + inputBox_->text);
            inputBox_->clear();
        }
    }
};

int main() {
    Button  btn("Submit");
    TextBox input("Input"), status("Status");
    DialogMediator mediator(&btn, &input, &status);

    input.setText("hello@example.com");
    btn.click();
    return 0;
}
