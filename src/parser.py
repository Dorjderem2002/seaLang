from lang_token import Token
from my_types import *
from nodes import Node, OpNode, NumNode, UnaryNode
from typing import List
from lexer import Lexer


class Parser:
    def __init__(self, lexer) -> None:
        self.lexer: Lexer = lexer
        self.current_token: Token = self.lexer.next_token()

    def parse(self) -> Node:
        return self.expr()

    def eat(self, token_type):
        if self.current_token.type == token_type:
            self.current_token = self.lexer.next_token()
        else:
            raise Exception("Invalid Syntax")

    def expr(self):
        # add, minus
        node = self.term()

        while self.current_token.type in (PLUS, MINUS):
            curr = self.current_token
            if curr.type == PLUS:
                self.eat(PLUS)
            elif curr.type == MINUS:
                self.eat(MINUS)

            node = OpNode(left=node, right=self.term(), token=curr)

        return node

    def term(self):
        # mul, mod, div
        node = self.factor()

        while self.current_token.type in (MUL, DIV, MOD):
            curr = self.current_token
            if curr.type == MUL:
                self.eat(MUL)
            elif curr.type == DIV:
                self.eat(DIV)

            node = OpNode(left=node, right=self.factor(), token=curr)

        return node

    def factor(self):
        # num, parentheses
        token = self.current_token
        if token.type == PLUS:
            self.eat(PLUS)
            node = UnaryNode(token, self.factor())
            return node
        elif token.type == MINUS:
            self.eat(MINUS)
            node = UnaryNode(token, self.factor())
            return node
        elif token.type == INTEGER:
            self.eat(INTEGER)
            return NumNode(token)
        elif token.type == LPAREN:
            self.eat(LPAREN)
            node = self.expr()
            self.eat(RPAREN)
            return node
        raise Exception("Invalid Syntax")
