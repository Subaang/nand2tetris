def tokenType(token):
    if "<keyword>" in token:
        return "KEYWORD"
    elif "<symbol>" in token:
        return "SYMBOL"
    elif "<identifier>" in token:
        return "IDENTIFIER"
    elif "<integerConstant>" in token:
        return "INT_CONST"
    elif "<stringConstant>" in token:
        return "STRING_CONST"
    else:
        print("Invalid token ---------------------------------")
        exit()


def keyword(token):
    token = token[9:]
    token = token[:-10]

    return token


def symbol(token):
    token = token[8:]
    token = token[:-9]

    if token == '&lt;':
        token = "<"
    elif token == '&gt;':
        token = ">"
    elif token == '&amp;':
        token = "&"

    return token


def identifier(token):
    token = token[12:]
    token = token[:-13]

    return token


def intVal(token):
    token = token[17:]
    token = token[:-18]

    return int(token)


def stringVal(token):
    token = token[17:]
    token = token[:-18]

    return token


class Tokenizer:
    def __init__(self,content):
        self.content = content
        self.tokenizedXML = []
        self.keywordList = ['class', 'constructor', 'function', 'method', 'field', 'static', 'var', 'int', 'char',
                            'boolean',
                            'void', 'true', 'false', 'null', 'this', 'let', 'do', 'if', 'else', 'while', 'return']
        self.symbolList = ['{', '}', '(', ')', '[', ']', '.', ',', '+', '-', '*', '/', '&', '|', '<', '>', '=', "~",
                           ';']

    def tokenize(self):
        preXMLTokens = self.preXMLTokenization(self.content)
        symbolAndKeywordTokens = self.symbolAndKeywordTokenization(preXMLTokens)
        intTokens = self.intConstTokenization(symbolAndKeywordTokens)
        stringTokens = self.stringConstTokenization(intTokens)
        identifierTokens = self.identifierTokenization(stringTokens)

        self.tokenizedXML = identifierTokens.copy()
        return self.tokenizedXML

    def preXMLTokenization(self, content):
        res = []
        buffer = ""
        for i in content:
            for j in i:
                # handling string constants
                if buffer.count('"') > 0:
                    buffer += j
                    if buffer.count('"') == 2:
                        res.append(buffer)
                        buffer = ""
                        continue
                    continue


                #if buffer is empty, no need to fill it with white space
                if buffer == "" and j == " ":
                    continue

                #if j is a symbol and buffer is empty, no need to fill buffer, just push j
                if j in self.symbolList and buffer == "":
                    res.append(j)
                    continue

                buffer += j

                #if buffer isn't empty and j is a symbol or white space(handles keywords, integers and identifiers)
                if buffer != "" and j in self.symbolList:
                    res.append(buffer[:-1])
                    res.append(j)
                    buffer = ""
                    continue

                if buffer != "" and j == " ":
                    res.append(buffer[:-1])
                    buffer = ""
                    continue

        return res

    def symbolAndKeywordTokenization(self, content):
        res = []
        for i in range(len(content)):
            if content[i] in self.keywordList:
                res.append(f"<keyword>{content[i]}</keyword>")

            elif content[i] in self.symbolList:
                if content[i] == '<':
                    res.append("<symbol>&lt;</symbol>")
                elif content[i] == '>':
                    res.append("<symbol>&gt;</symbol>")
                elif content[i] == '&':
                    res.append("<symbol>&amp;</symbol>")
                else:
                    res.append(f"<symbol>{content[i]}</symbol>")

            else:
                res.append(content[i])

        return res

    def intConstTokenization(self, content):
        res = []
        for i in range(len(content)):
            try:
                int(content[i])
                res.append("<integerConstant>" + content[i] + "</integerConstant>")
            except ValueError:
                res.append(content[i])

        return res

    def stringConstTokenization(self, content):
        res = []
        for i in range(len(content)):
            if content[i][0] == '"':
                res.append("<stringConstant>" + content[i] + "</stringConstant>")
            else:
                res.append(content[i])

        return res

    def identifierTokenization(self, content):
        res = []
        for i in range(len(content)):
            if content[i][0].isalpha() or content[i][0].isalpha():
                res.append("<identifier>" + content[i] + "</identifier>")
            else:
                res.append(content[i])

        return res

