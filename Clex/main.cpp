#include <cstdio>
#include <iostream>
#include <fstream>
#include "lexer.h"

using namespace std;

int main()
{
	ifstream infile;
	ofstream outfile;
	char buffer[1025];
	string content;
	Lexer lexer;
	
	
	infile.open("test.txt");
	outfile.open("out.txt");
	if(!infile)
	{
		cout << "Open failed!";
		exit(1);
	}
	if(!outfile)
	{
		cout << "Open failed!";
		exit(1);
	}

	while(!infile.eof())
	{
		infile.getline(buffer, 1024);
		content.append(buffer);
		content +='\n';
	}
	string result = Lexer::tokenSeqToString(lexer.process(content));;
	outfile << result.c_str();
	outfile << "Error at: " << lexer.getlineCount() << "line, " << lexer.getWordCount() << " char." << endl;
	outfile << "lines:" << lexer.getlineCount() << endl;
	outfile << "KeyWord:" << lexer.getKeyWordNum() << " " << "Op:" << lexer.getOpNum() << " " << "Id:" << lexer.getIdNum() << " " << "Constant:" << lexer.getConst() << " " << "StringLiteral:" << lexer.getString() << endl;
	outfile << "words:" << lexer.gettotalWord() << endl;
	return 0;
	
}