from lang_token import Token
from typing import List, Tuple
from my_types import *


class Lexer:
    def __init__(self, text) -> None:
        self.text: str = text
        self.tokens: List[Token] = self.analyze(self.text)
        self.pos = -1

    def analyze(self, text) -> List[Token]:
        pos = 0
        tokens = []
        while pos < len(text):
            c = text[pos]
            if c == "+":
                tokens.append(Token(PLUS, "+"))
            elif c == "-":
                tokens.append(Token(MINUS, "-"))
            elif c == "*":
                tokens.append(Token(MUL, "*"))
            elif c == "%":
                tokens.append(Token(MOD, "%"))
            elif c == "/":
                tokens.append(Token(DIV, "/"))
            elif c == "(":
                tokens.append(Token(LPAREN, "("))
            elif c == ")":
                tokens.append(Token(RPAREN, ")"))
            elif c.isdigit():
                val, pos = self.read_int(pos, text)
                tokens.append(Token(INTEGER, val))
                pos -= 1
            elif c == " ":
                pass
            pos += 1
        return tokens

    def read_int(self, pos, text) -> Tuple[int, int]:
        val = ""
        while pos < len(text) and text[pos].isdigit():
            val += text[pos]
            pos += 1
        return int(val), pos

    def next_token(self):
        self.pos += 1
        if self.pos == len(self.tokens):
            return Token(EOF, "None")
        return self.tokens[self.pos]
