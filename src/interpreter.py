from parser import Parser
from nodes import Node, UnaryNode
from my_types import *


class Interpreter:
    def __init__(self, parser) -> None:
        self.parser: Parser = parser

    def run(self):
        node = self.parser.parse()
        return self.visit(node)

    def visit(self, node: Node):

        if node.token.type == INTEGER:
            return node.token.value
        if node.token.type == PLUS:
            return self.visit(node.left) + self.visit(node.right)
        if node.token.type == MINUS:
            return self.visit(node.left) - self.visit(node.right)
        if node.token.type == MUL:
            return self.visit(node.left) * self.visit(node.right)
        if node.token.type == DIV:
            return self.visit(node.left) // self.visit(node.right)
        if node.token.type == MOD:
            return self.visit(node.left) % self.visit(node.right)

        if type(node) == UnaryNode:
            if node.token.type == PLUS:
                return self.visit(node.expr)
            if node.token.type == MINUS:
                return -self.visit(node.expr)
