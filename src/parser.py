from lang_token import Token
from my_types import *
from nodes import Node, OpNode, NumNode, UnaryNode, VarNode, AssNode, CompNode, NoOp
from typing import List
from lexer import Lexer


class Parser:
    def __init__(self, lexer) -> None:
        self.lexer: Lexer = lexer
        self.current_token: Token = self.lexer.next_token()

    def parse(self) -> Node:
        return self.compound_statement()

    def compound_statement(self):
        self.eat(LCURLY)
        nodes = self.statement_list()
        self.eat(RCURLY)

        root = CompNode()
        for node in nodes:
            root.children.append(node)
        return root

    def statement_list(self):
        node = self.statement()
        result = [node]
        while self.current_token.type == SEMI:
            self.eat(SEMI)
            result.append(self.statement())
        if self.current_token.type == VARIABLE:
            raise Exception("Invalid Syntax")
        return result

    def statement(self):
        if self.current_token.type == LCURLY:
            node = self.compound_statement()
        elif self.current_token.type == VARIABLE:
            node = self.assignment_statement()
        else:
            node = NoOp()
        return node

    def assignment_statement(self):
        left = VarNode(self.current_token)
        self.eat(VARIABLE)
        token = self.current_token
        self.eat(ASSIGN)
        right = self.expr()
        node = AssNode(left, right, token)
        return node

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
        elif token.type == VARIABLE:
            self.eat(VARIABLE)
            return VarNode(token)
        raise Exception("Invalid Syntax")
