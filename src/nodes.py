from lang_token import Token


class Node:
    def __init__(self, token, left=None, right=None) -> None:
        self.left: Node = left
        self.right: Node = right
        self.token: Token = token

    def __str__(self) -> str:
        return f"Node({self.token})"

    def __repr__(self):
        return self.__str__()


class CompNode(Node):
    def __init__(self) -> None:
        self.children = []


class NumNode(Node):
    def __init__(self, token) -> None:
        super().__init__(token=token)


class OpNode(Node):
    def __init__(self, left, right, token) -> None:
        super().__init__(left=left, right=right, token=token)


class UnaryNode(Node):
    def __init__(self, token, expr) -> None:
        self.token: Token = token
        self.expr = expr


class AssNode(Node):
    def __init__(self, left, right, token) -> None:
        super().__init__(left=left, right=right, token=token)


class VarNode(Node):
    def __init__(self, token) -> None:
        super().__init__(token=token)


class NoOp(Node):
    def __init__(self) -> None:
        pass
