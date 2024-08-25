from parser import Parser
from nodes import *
from my_types import *


class Interpreter:
    def __init__(self, parser) -> None:
        self.parser: Parser = parser
        self.memory = {}

    def run(self):
        node = self.parser.parse()
        return self.visit(node)

    def visit(self, node: Node):
        if type(node) == NoOp:
            return
        elif type(node) == CompNode:
            for c in node.children:
                self.visit(c)
        elif type(node) == AssNode:
            self.memory[node.left.token.value] = self.visit(node.right)
        elif type(node) == UnaryNode:
            if node.token.type == PLUS:
                return self.visit(node.expr)
            if node.token.type == MINUS:
                return -self.visit(node.expr)
        elif node.token.type == INTEGER:
            return node.token.value
        elif node.token.type == VARIABLE:
            return self.memory[node.token.value]
        elif node.token.type == PLUS:
            return self.visit(node.left) + self.visit(node.right)
        elif node.token.type == MINUS:
            return self.visit(node.left) - self.visit(node.right)
        elif node.token.type == MUL:
            return self.visit(node.left) * self.visit(node.right)
        elif node.token.type == DIV:
            return self.visit(node.left) // self.visit(node.right)
        elif node.token.type == MOD:
            return self.visit(node.left) % self.visit(node.right)
