from lexer import Lexer
from parser import Parser
from interpreter import Interpreter


with open("test.sea") as f:
    txt = f.readlines()
    lexer = Lexer(txt)
    parser = Parser(lexer)
    interpreter = Interpreter(parser)
    res = interpreter.run()
    print(interpreter.memory)
