#pragma once

#include <vector>
#include <string>
#include <map>
using namespace std;
enum TokenType
{
	Keyword,
	Op,
	Id,
	Constant,
	StringLiteral
};


class Token
{
private:
	TokenType token;
	string value;
public:
	Token(TokenType token, string value)
	{
		this->token = token;
		this->value = value;
	}
public:
	string toString()
	{
		string tmp = "<";
		switch (token)
		{
		case Keyword:
			break;
		case Op:
			tmp += "Op,";
			break;
		case Id:
			tmp += "Id,";
			break;
		case Constant:
			tmp += "Constant,";
			break;
		case StringLiteral:
			tmp += "StringLiteral,";
			break;
		default:
			break;
		}
		tmp += value + ">\n";
		return tmp;

	}
};
#define letter  'a':\
				case 'b':\
				case 'c':\
				case 'd':\
				case 'e':\
				case 'f':\
				case 'g':\
				case 'h':\
				case 'i':\
				case 'j':\
				case 'k':\
				case 'l':\
				case 'm':\
				case 'n':\
				case 'o':\
				case 'p':\
				case 'q':\
				case 'r':\
				case 's':\
				case 't':\
				case 'u':\
				case 'v':\
				case 'w':\
				case 'x':\
				case 'y':\
				case 'z'
#define digit '0':\
				case '1':\
				case '2':\
				case '3':\
				case '4':\
				case '5':\
				case '6':\
				case '7':\
				case '8':\
				case '9'

class Lexer
{
private:
	#define keyWordCount  15
	const string keyWord[keyWordCount] = {
	"for",
	"if",
	"else",
	"int",
	"float",
	"double",
	"while",
	"do",
	"struct",
	"void",
	"char",
	"enum",
	"switch",
	"case",
	"return"	
	};
	map <string, int> symbolTable;
	int id = 0;
	int state;
	int lineCount;
	int wordCount = 1;
	int keyWordNum = 0, opNum = 0, idNum = 0, stringLiteralNum = 0, constantNum = 0;
	int totalWord = 0;
	vector<Token> result;
	Token* token;
	string temp;
	char c;
private:
	void recordChar() {
		temp += c;
	}
	void addToken(TokenType tokenType) {
		if (tokenType == Id)
		{
			string sid;
			if (symbolTable.find(temp) == symbolTable.end())
			{
				id++;
				sid = to_string(id);
				symbolTable[temp] = id;
			} else
			{
				sid = to_string(symbolTable[temp]);
			}
			token = new Token(Id, sid);
			idNum++;
		}
		else if (tokenType == Keyword)
		{
			token = new Token(tokenType, temp);
			keyWordNum++;
		}
		else if(tokenType == Op)
		{
			token = new Token(tokenType, temp);
			opNum++;
		}
		else if(tokenType == Constant)
		{
			token = new Token(tokenType, temp);
			constantNum++;
		}
		else
		{
			token = new Token(tokenType, temp);
			stringLiteralNum++;
		}
		temp = "";
		result.push_back(*token);
	}
	void error() {
		printf("Error at %d line, %d char", lineCount, wordCount);
	}
	void parseToken() {
		for (int i = 0; i < keyWordCount; i++) {
			if (temp == keyWord[i]) {
				addToken(Keyword);
				return;
			}
		}
		addToken(Id);
	}
public:
	
	vector<Token> process(string source)
	{
		state = 0;
		lineCount = 0;
		for (unsigned int i = 0; i < source.size(); i++, wordCount++,totalWord++)
		{
			c = source[i];

			if (c == '\n' || c == '\r') {
				if (state == 16)
					state = 0;//换行时取消//注释
				lineCount++;
				wordCount = 1;
				continue;
			}
			switch (state) {
			case 0:
				switch (c)
				{
				case letter:
					state = 1;
					recordChar();
					break;
				case digit:
					recordChar();
					state = 2;
					break;
				case '<':
					recordChar();
					state = 8;
					break;
				case '>':
					recordChar();
					state = 9;
					break;
				case '=':
					recordChar();
					state = 10;
					break;
				case '/':
					state = 11;
					break;
				case '+':
					recordChar();
					state = 18;
					break;
				case '-':
					recordChar();
					state = 19;
					break;
				case '*':
				case '(':
				case ')':
				case '{':
				case '}':
				case ';':
				case ':':
				case '\'':
					recordChar();
					addToken(Op);
					break;
				case '\"':
					state = 14;
					break;
				case '!':
					recordChar();
					state = 16;
					break;
				default:
					break;
				
				}
				break;
			case 1:
				switch (c)
				{
				case digit:
				case letter:
					recordChar();
					break;
				default:
					i--;
				case ' ':
					parseToken();
					state = 0;
				}
				break;

			case 2:
				switch (c)
				{
				case digit:
					recordChar();
					break;
				case 'E':
				case 'e':
					recordChar();
					state = 5;
				case '.':
					recordChar();
					state = 3;
					break;
				default:
					i--;
				case ' ':
					addToken(Constant);
					state = 0;
					break;
				}
				break;
			case 3:
				switch (c)
				{
				case digit:
					recordChar();
					state = 4;
					break;
				default:
					error();
					state = 0;
					break;
				}
				break;
			case 4:
				switch (c)
				{
				case digit:
					recordChar();
					break;
				case 'E':
					recordChar();
					state = 5;
					break;
				default:
					i--;
					case ' ':
					addToken(Constant);
					state = 0;
					break;
				}
				break;
			case 5:
				switch (c)
				{
				case digit:
					recordChar();
					state = 7;
					break;
				
				case '+':
				case '-':
					recordChar();
					state = 6;
					break;
				default:
					error();
					state = 0;
					
					break;
				}
				break;
			case 6:
				switch (c)
				{
				case digit:
					recordChar();
					state = 7;
					break;
				default:
					error();
					break;
				}
				break;
			case 7:
				switch (c)
				{
				case digit:
					recordChar();
					break;
				default:
					i--;
					case ' ':
					addToken(Constant);
					state = 0;
					break;
				}
				break;
			case 8:
				switch (c)
				{
				case '=':
					recordChar();
					state = 0;
					addToken(Op);
					break;

				default:
					i--;
					case ' ':
					state = 0;
					addToken(Op);
					break;
				}
				break;
			case 9:
				switch (c)
				{
				case '=':
					recordChar();
					state = 0;
					addToken(Op);
					break;

				default:
					i--;
					case ' ':
					state = 0;
					addToken(Op);
					break;
				}
				break;
			case 10:
				switch (c)
				{
				case '=':
					recordChar();
					state = 0;
					addToken(Op);
					break;

				default:
					i--;
					case ' ':
					state = 0;
					addToken(Op);
					break;
				}
				break;
			case 11:
				switch (c)
				{
				case '*':
					state = 12;
					break;
				case '/':
					state = 17;
					break;
				case digit:
				case letter:
					i--;
					temp += '/';
					case ' ':
					temp += '/';
					addToken(Op);
					state = 0;
					break;
				default:
					error();
					break;
				}
				break;
			case 12:
				switch (c)
				{
				case '*':
					state = 13;
					break;
				default:
					break;
				}
				break;
			case 13:
				switch (c)
				{
				case '/':
					state = 0;
					break;
				default:
					state = 12;
					break;
				}
				break;
			case 14:
				switch (c)
				{
				case '\\':
					state = 15;
					break;
				case '\"':
					state = 0;
					addToken(StringLiteral);
					break;
				default:
					recordChar();
					break;
				}
				break;
			case 15:
				switch (c)
				{
				case 'n':
					temp += '\n';
					state = 14;
					break;
				case 'r':
					temp += '\r';
					state = 14;
					break;
				case '\\':
					temp += '\\';
					state = 14;
					break;
				case 't':
					temp += '\t';
					state = 14;

				case '*':
					temp += '*';
					state = 14;

					break;
				default:
					error();
					break;
				}
			case 16:
				switch (c)
				{
				case '=':
					recordChar();
					state = 0;
					addToken(Op);
					break;
				default:
					i--;
				case ' ':
					state = 0;
					addToken(Op);
					break;
					
				}
				break;
			case 17:
				switch (c)
				{
				case '\r':
				case '\t':
				case '\n':
					i--;
					state = 0;
					break;
				default:
					break;
				}
				break;
			case 18:
				switch (c)
				{
				case '+':
					recordChar();
					state = 0;
					addToken(Op);
				default:
					i--;
					case ' ':
					state = 0;
					addToken(Op);
					break;
					
				}
				break;
			case 19:
				switch (c)
				{
				case '-':
					recordChar();
					state = 0;
					addToken(Op);
				default:
					i--;
				case ' ':
					state = 0;
					addToken(Op);
					break;
				}
				
			}
			

		}
		return result;
	}
public:
	static string tokenSeqToString(vector<Token> tokenSeq)
	{
		string result, temp;
		for (unsigned int i = 0; i < tokenSeq.size(); i++)
		{
			result += tokenSeq[i].toString();
		}

		return result;
	}
	int getlineCount() { return lineCount; }
	int gettotalWord() { return totalWord; }
	int getKeyWordNum() { return keyWordNum; }
	int getOpNum() { return opNum; }
	int getIdNum() { return idNum; }
	int getString() { return stringLiteralNum; }
	int getConst() { return constantNum; }
	int getWordCount() { return wordCount; }
};