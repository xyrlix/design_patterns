"""
设计模式: 建造者模式 (Builder)
分类: 创建型

意图: 将复杂对象的构建与其表示分离，使同样的构建过程可以创建不同的表示。
核心思想: Builder 分步构建，Director 定义构建顺序，支持链式调用。
编程范式: OOP — 流式接口 (Method Chaining) + 职责分离。
"""

from __future__ import annotations
from dataclasses import dataclass, field


# ── 产品 ──────────────────────────────────────────────────────────────────
@dataclass
class Pizza:
    dough: str = ""
    sauce: str = ""
    toppings: list[str] = field(default_factory=list)

    def __str__(self) -> str:
        return f"Pizza [{self.dough} | {self.sauce} | {', '.join(self.toppings)}]"


# ── 建造者（流式接口）────────────────────────────────────────────────────
class PizzaBuilder:
    def __init__(self) -> None:
        self._pizza = Pizza()

    def set_dough(self, dough: str) -> PizzaBuilder:
        self._pizza.dough = dough
        return self

    def set_sauce(self, sauce: str) -> PizzaBuilder:
        self._pizza.sauce = sauce
        return self

    def add_topping(self, topping: str) -> PizzaBuilder:
        self._pizza.toppings.append(topping)
        return self

    def build(self) -> Pizza:
        result, self._pizza = self._pizza, Pizza()
        return result


# ── 导演 ──────────────────────────────────────────────────────────────────
class Director:
    @staticmethod
    def build_margherita(b: PizzaBuilder) -> Pizza:
        return (b.set_dough("thin")
                 .set_sauce("tomato")
                 .add_topping("mozzarella")
                 .add_topping("basil")
                 .build())

    @staticmethod
    def build_pepperoni(b: PizzaBuilder) -> Pizza:
        return (b.set_dough("thick")
                 .set_sauce("spicy")
                 .add_topping("pepperoni")
                 .add_topping("cheddar")
                 .build())


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    builder = PizzaBuilder()
    print(Director.build_margherita(builder))
    print(Director.build_pepperoni(builder))
