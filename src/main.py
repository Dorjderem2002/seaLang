from lexer import Lexer
from parser import Parser
from interpreter import Interpreter

while True:
    txt = input(">>> ")

    if txt == "exit":
        break

    lexer = Lexer(txt)
    parser = Parser(lexer)
    interpreter = Interpreter(parser)
    res = interpreter.run()
    print(res)
