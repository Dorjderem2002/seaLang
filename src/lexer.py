from lang_token import Token
from typing import List, Tuple
from my_types import *


class Lexer:
    def __init__(self, text) -> None:
        self.text: List[str] = text
        self.tokens: List[Token] = []
        self.pos = -1

        for t in self.text:
            self.tokens += self.analyze(t)

    def analyze(self, text) -> List[Token]:
        if text.endswith("\n"):
            text = text[:-1]
        pos = 0
        tokens = []
        while pos < len(text):
            c = text[pos]

            if c.isdigit():
                val, pos = self.read_int(pos, text)
                tokens.append(Token(INTEGER, val))
            elif c.isalnum():
                val, pos = self.read_alnum(pos, text)
                tokens.append(Token(VARIABLE, val))
            else:
                if c == "=":
                    tokens.append(Token(ASSIGN, "="))
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
                elif c == "{":
                    tokens.append(Token(LCURLY, "{"))
                elif c == "}":
                    tokens.append(Token(RCURLY, "}"))
                elif c == ";":
                    tokens.append(Token(SEMI, ";"))
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

    def read_alnum(self, pos, text) -> Tuple[int, int]:
        val = ""
        while pos < len(text) and text[pos].isalnum():
            val += text[pos]
            pos += 1
        return val, pos

    def next_token(self):
        self.pos += 1
        if self.pos == len(self.tokens):
            return Token(EOF, "None")
        return self.tokens[self.pos]
