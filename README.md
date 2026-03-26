# Design Patterns — C++ & Python

> 26 种 GoF 设计模式，C++ 与 Python 双语实现。每个文件独立可运行，注释说明设计思想与编程范式。

## 目录结构

```
design_patterns/
├── cpp/
│   ├── creational/          # 创建型（5种）
│   ├── structural/          # 结构型（7种）
│   └── behavioral/          # 行为型（11种）
└── python/
    ├── creational/
    ├── structural/
    └── behavioral/
```

---

## 创建型模式（Creational）

| # | 模式 | 文件 | 核心思想 |
|---|------|------|----------|
| 01 | **单例** Singleton | `creational/01_singleton` | 私有构造 + 静态实例；Meyer's Singleton / 元类 |
| 02 | **工厂方法** Factory Method | `creational/02_factory_method` | 抽象工厂方法延迟到子类；多态创建 |
| 03 | **抽象工厂** Abstract Factory | `creational/03_abstract_factory` | 产品族 + 工厂族；切换工厂切换整套风格 |
| 04 | **建造者** Builder | `creational/04_builder` | Director 控制步骤，Builder 实现细节；链式接口 |
| 05 | **原型** Prototype | `creational/05_prototype` | 对象自身 clone；原型注册表 |

---

## 结构型模式（Structural）

| # | 模式 | 文件 | 核心思想 |
|---|------|------|----------|
| 06 | **适配器** Adapter | `structural/06_adapter` | 包装不兼容接口；对象适配器（组合） |
| 07 | **桥接** Bridge | `structural/07_bridge` | 抽象与实现分离；两维度独立扩展 |
| 08 | **组合** Composite | `structural/08_composite` | 树形结构；叶与容器统一接口 |
| 09 | **装饰器** Decorator | `structural/09_decorator` | 层层包裹扩展行为；Python 函数装饰器 |
| 10 | **外观** Facade | `structural/10_facade` | 封装子系统；简洁统一入口 |
| 11 | **享元** Flyweight | `structural/11_flyweight` | 内外状态分离；对象池共享内部状态 |
| 12 | **代理** Proxy | `structural/12_proxy` | 控制访问；缓存代理示例 |

---

## 行为型模式（Behavioral）

| # | 模式 | 文件 | 核心思想 |
|---|------|------|----------|
| 13 | **责任链** Chain of Responsibility | `behavioral/13_chain_of_responsibility` | 链式传递请求；解耦发送者与接收者 |
| 14 | **命令** Command | `behavioral/14_command` | 请求封装为对象；支持撤销/重做 |
| 15 | **迭代器** Iterator | `behavioral/15_iterator` | 封装遍历逻辑；C++ STL 兼容 / Python 生成器 |
| 16 | **中介者** Mediator | `behavioral/16_mediator` | 集中协调交互；星型替代网状依赖 |
| 17 | **备忘录** Memento | `behavioral/17_memento` | 状态快照；不破坏封装的撤销机制 |
| 18 | **观察者** Observer | `behavioral/18_observer` | 发布-订阅；主题广播状态变化 |
| 19 | **状态** State | `behavioral/19_state` | 状态封装为类；多态替换 if-else 状态机 |
| 20 | **策略** Strategy | `behavioral/20_strategy` | 算法族封装；运行时切换策略 |
| 21 | **模板方法** Template Method | `behavioral/21_template_method` | 基类定义骨架；子类实现细节 |
| 22 | **访问者** Visitor | `behavioral/22_visitor` | 双重分派；算法与数据结构分离 |
| 23 | **解释器** Interpreter | `behavioral/23_interpreter` | AST 递归求值；DSL / 表达式解析 |

---

## 编译 & 运行

### C++

```bash
# 编译单个文件（需 C++17）
g++ -std=c++17 -O2 cpp/creational/01_singleton.cpp -o singleton && ./singleton
```

### Python

```bash
python python/creational/01_singleton.py
```

---

## 设计原则对照

| 原则 | 体现的主要模式 |
|------|---------------|
| 单一职责 SRP | Command, Iterator, State |
| 开闭原则 OCP | Strategy, Observer, Decorator |
| 里氏替换 LSP | Template Method, Composite |
| 接口隔离 ISP | Abstract Factory, Visitor |
| 依赖倒置 DIP | Factory Method, Bridge, Proxy |
| 迪米特法则 LoD | Facade, Mediator |
