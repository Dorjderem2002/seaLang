import re

OPS = "*/%+-"

precedence_op = {
    "*": 1,
    "/": 1,
    "%": 1,
    "+": 2,
    "-": 2,
}


class Interpreter:
    def __init__(self) -> None:
        pass

    def eval(self, expr):
        res = None
        raw_tokens = re.findall(r"(\d+|[-+*/])", expr)
        tokens = self.token_format(raw_tokens)
        while any(item in tokens for item in OPS):
            for operator in OPS:
                if operator not in tokens:
                    continue
                try:
                    pos = tokens.index(operator)
                    left = tokens[pos - 1]
                    right = tokens[pos + 1]
                    op = tokens[pos]
                    op_result = self.handle_operation(left, right, op)
                    tokens = tokens[: pos - 1] + [op_result] + tokens[pos + 2 :]
                except BaseException:
                    raise Exception("Error parsing input")
        if len(tokens) == 1:
            try:
                res = int(tokens[0])
                return res
            except:
                raise Exception("Wrong expression")
        raise Exception("Wrong expression")

    def token_format(self, raw_tokens):
        tokens = []
        for i in raw_tokens:
            stripped = i.strip()
            if i.isdigit():
                tokens.append(int(stripped))
            else:
                tokens.append(stripped)
        return tokens

    def handle_operation(self, left, right, op):
        if op == "*":
            return left * right
        elif op == "/":
            return left / right
        elif op == "%":
            return left % right
        elif op == "+":
            return left + right
        elif op == "-":
            return left - right
        else:
            raise Exception("uknown operator")


s = ["1 + 2", "13*2", "1 - 45", "1+ 2"]
for i in s:
    lang = Interpreter()
    print(lang.eval(i))
