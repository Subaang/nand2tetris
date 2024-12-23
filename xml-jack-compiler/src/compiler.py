import tokenizer

def error():
    print("ERROR")
    exit()


class CompilationEngine:
    def __init__(self,tokens):
        self.typeList = ["IDENTIFIER","int", "char", "boolean"]
        self.tokens = tokens
        self.compiled = []
        self.i = 0

        self.compileClass()

    def eat(self,terminal_list):
        token = self.tokens[self.i]
        tokenType = tokenizer.tokenType(token)


        if tokenType == "KEYWORD":
            if tokenizer.keyword(token) not in terminal_list:
               error()

        elif tokenType == "IDENTIFIER": #To handle the case of typeList, this must be below KEYWORD
            if terminal_list[0] != "IDENTIFIER":
                error()

        elif tokenType == "SYMBOL":
            if tokenizer.symbol(token) not in terminal_list:
                error()

        elif tokenType == "INT_CONST":
            if terminal_list[0] != "INT_CONST":
                error()

        elif tokenType == "STRING_CONST":
            if terminal_list[0] != "STRING_CONST":
                error()
            else:
                token = tokenizer.stringVal(token)
                token = '<stringConstant>' + token.strip() + '</stringConstant>'

        self.compiled.append(token)
        self.i += 1

    def compileClass(self):
        self.compiled.append("<class>")
        self.eat(["class"])
        self.eat(["IDENTIFIER"])
        self.eat(["{"])

        # These 2 can come in any order multiple times or not appear at all

        while True:
            if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL": #Not checking which symbol it is because we eat non-} and get exit()
                break

            if tokenizer.tokenType(self.tokens[self.i]) == "KEYWORD" and tokenizer.keyword(self.tokens[self.i]) in ["field", "static","constructor","function","method"]:
                if tokenizer.keyword(self.tokens[self.i]) in ["field", "static"]:
                    self.compileClassVarDec()
                elif tokenizer.keyword(self.tokens[self.i]) in ["constructor","function","method"]:
                    self.compileSubroutineDec()
                else:
                    error()

            if tokenizer.tokenType(self.tokens[self.i]) not in ["SYMBOL","KEYWORD"]: # Necessary to break out of infinite loop
                error()

        self.eat(["}"])
        self.compiled.append("</class>")

    def compileClassVarDec(self):
        self.compiled.append("<classVarDec>")
        self.eat(["field","static"])
        self.eat(self.typeList)
        self.eat(["IDENTIFIER"])

        while (tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == ";") is False:
             self.eat([","])
             self.eat(["IDENTIFIER"])

        self.eat([";"])
        self.compiled.append("</classVarDec>")

    def compileSubroutineDec(self):
        self.compiled.append("<subroutineDec>")
        self.eat(["constructor","function","method"])
        self.eat(self.typeList + ["void"])
        self.eat(["IDENTIFIER"])
        self.eat(["("])

        self.compileParameterList()

        self.eat([")"])
        self.compileSubroutineBody()
        self.compiled.append("</subroutineDec>")

    def compileSubroutineBody(self):
        self.compiled.append("<subroutineBody>")
        self.eat(["{"])

        # These 2 can come in any order multiple times or not appear at all
        while True:
            if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL":
                break

            if tokenizer.tokenType(self.tokens[self.i]) == "KEYWORD" and tokenizer.keyword(self.tokens[self.i]) in ['var','let','if','while','do','return']:
                if tokenizer.keyword(self.tokens[self.i]) == "var":
                    self.compileVarDec()
                elif tokenizer.keyword(self.tokens[self.i]) in ['let','if','while','do','return']:
                    self.compileStatements()
                else:
                    error()

            if tokenizer.tokenType(self.tokens[self.i]) not in ["SYMBOL","KEYWORD"]:
                error()

        self.eat(["}"])
        self.compiled.append("</subroutineBody>")

    def compileVarDec(self):
        self.compiled.append("<varDec>")

        self.eat(["var"])
        self.eat(self.typeList)
        self.eat(["IDENTIFIER"])
        while (tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == ";") is False:
            self.eat([","])
            self.eat(["IDENTIFIER"])

        self.eat([";"])

        self.compiled.append("</varDec>")

    def compileStatements(self):
        self.compiled.append("<statements>")

        while True:
            if tokenizer.keyword(self.tokens[self.i]) == "let":
                self.compileLet()
            elif tokenizer.keyword(self.tokens[self.i]) == "if":
                self.compileIf()
            elif tokenizer.keyword(self.tokens[self.i]) == "while":
                self.compileWhile()
            elif tokenizer.keyword(self.tokens[self.i]) == "do":
                self.compileDo()
            elif tokenizer.keyword(self.tokens[self.i]) == "return":
                self.compileReturn()
            else:
                break

        self.compiled.append("</statements>")

    def compileLet(self):
        self.compiled.append("<letStatement>")

        self.eat(["let"])
        self.eat(["IDENTIFIER"])

        if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == "=":
            self.eat(["="])
            self.compileExpression()
        else:
            self.eat(["["])
            self.compileExpression()
            self.eat(["]"])
            self.eat(["="])
            self.compileExpression()

        self.eat([";"])
        self.compiled.append("</letStatement>")

    def compileIf(self):
        self.compiled.append("<ifStatement>")

        self.eat(["if"])
        self.eat(["("])
        self.compileExpression()
        self.eat([")"])
        self.eat(["{"])
        self.compileStatements()
        self.eat(["}"])

        if tokenizer.tokenType(self.tokens[self.i]) == "KEYWORD" and tokenizer.keyword(self.tokens[self.i]) == "else":
            self.eat(["else"])
            self.eat(["{"])
            self.compileStatements()
            self.eat(["}"])

        self.compiled.append("</ifStatement> ")

    def compileWhile(self):
        self.compiled.append("<whileStatement> ")

        self.eat(["while"])
        self.eat(["("])
        self.compileExpression()
        self.eat([")"])
        self.eat(["{"])
        self.compileStatements()
        self.eat(["}"])

        self.compiled.append("</whileStatement>")

    def compileDo(self):
        self.compiled.append("<doStatement>")

        self.eat(["do"])
        self.eat(["IDENTIFIER"])
        if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL":
            if tokenizer.symbol(self.tokens[self.i]) == "(":
                self.eat(["("])
                self.compileExpressionList()
                self.eat([")"])
            elif tokenizer.symbol(self.tokens[self.i]) == ".":
                self.eat(["."])
                self.eat(["IDENTIFIER"])
                self.eat(["("])
                self.compileExpressionList()
                self.eat([")"])
            else:
                error()
        else:
            error()
        self.eat([";"])

        self.compiled.append("</doStatement>")

    def compileReturn(self):
        self.compiled.append("<returnStatement>")

        self.eat(["return"])

        if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == ";":
            pass
        else:
            pass
            self.compileExpression()

        self.eat([";"])

        self.compiled.append("</returnStatement>")

    def compileExpression(self):
        self.compiled.append("<expression>")
        self.compileTerm()
        self.compiled.append("</expression>")
        pass

    def compileParameterList(self):
        self.compiled.append("<parameterList>")
        while True:
            if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == ")":
                break

            self.eat(self.typeList)
            self.eat(["IDENTIFIER"])

            if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == ")":
                break

            self.eat([","])
        self.compiled.append("</parameterList>")

    def compileTerm(self):
        self.compiled.append("<term>")
        if tokenizer.tokenType(self.tokens[self.i]) == "INT_CONST":
            self.eat(["INT_CONST"])


        elif tokenizer.tokenType(self.tokens[self.i]) == "STRING_CONST":
            self.eat(["STRING_CONST"])


        elif tokenizer.tokenType(self.tokens[self.i]) == "KEYWORD":
            if tokenizer.keyword(self.tokens[self.i]) not in ['true','false','null','this']:
                exit()
            else:
                self.eat(tokenizer.keyword(self.tokens[self.i]))


        elif tokenizer.tokenType(self.tokens[self.i]) == "IDENTIFIER":
            self.eat(["IDENTIFIER"])
            if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL":
                if tokenizer.symbol(self.tokens[self.i]) == "(":
                    self.eat(["("])
                    self.compileExpressionList()
                    self.eat([")"])
                elif tokenizer.symbol(self.tokens[self.i]) == "[":
                    self.eat(["["])
                    self.compileExpression()
                    self.eat(["]"])
                elif tokenizer.symbol(self.tokens[self.i]) == ".":
                    self.eat(["."])
                    self.eat(["IDENTIFIER"])
                    self.eat(["("])
                    self.compileExpressionList()
                    self.eat([")"])


        elif tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == "(":
            self.eat(["("])
            self.compileExpression()
            self.eat([")"])

        elif tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL":
                self.eat(tokenizer.symbol(self.tokens[self.i]))
                self.compileTerm()

        self.compiled.append("</term>")

        if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) in ["+","-","*","/","&","|","<",">","="]:
            self.eat(tokenizer.symbol(self.tokens[self.i]))
            self.compileTerm()

    def compileExpressionList(self):
        self.compiled.append("<expressionList>")
        while True:
            if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == ")":
                break

            self.compileExpression()

            if tokenizer.tokenType(self.tokens[self.i]) == "SYMBOL" and tokenizer.symbol(self.tokens[self.i]) == ")":
                break

            self.eat([","])
        self.compiled.append("</expressionList>")








