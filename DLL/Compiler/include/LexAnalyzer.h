#pragma once

#include "windows.h"
#include "vcclr.h"
#include "ErrorModule.h"
#include "Analyzer.h"
#include "LexStateMachine.h"
#include "Token.h"

using namespace System;
#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace Compiler {
#define LEX_INVALID_CHAR "invalid character"
#define LEX_STRING_NOT_CLOSED "string not closed"
#define LEX_COMMENT_NOT_CLOSED "comment not closed"
#define LEX_INVALID_FLOAT "invalid float"
#define LEX_INVALID_INT "invalid int"
#define LEX_INVALID_OP_LOG "invalid operator logical"
	class LexAnalyzer
	{
	public:
		LexAnalyzer(ErrorModule^errormod);
		~LexAnalyzer();
		void parseSourceCode(const char* src);
		void clean();
		bool m_errorsExcedet = false;
		int m_tokensIndex = -1;
		int indexNum = -1;
		int m_numeberLine = 1;
		int initLine = 0;
		LexState*State = nullptr;
		LexState*PrevState = nullptr;

		msclr::gcroot<ErrorModule^>m_refErrorMod;
		ERROR_PHASE m_phase = ERROR_PHASE::LEX_ANALYZER;
		//ErrorsModule m_refErrorsMod;
		std::map<std::string, std::string> m_keyWords;
		std::vector<Token*> m_Tokens;
		void detecteToken(std::string lexema, int line, int type);
		//std::vector<char> separators = { ';',':',',' };
		std::vector<char> delimitador = { ';',':',',' };
		//std::vector<char> digit = { '0','1','2', };
		std::vector <char> op_arit = { '+','-','*','/','%' ,'^' };
		std::vector <char> op_dim = { '[',']' };
		std::vector <char> op_agrup = { '{','}','(',')' };
		//std::vector <char> op_log = { '!','|','&','=' };
		std::vector <char> op_log_unitario = { '!' };
		std::vector <char> op_log = { '|','&' };
		std::vector <char> op_arit_inv = { '^' };
		std::vector <std::string> op_logComplete = { "!","||","&&","==" };
		std::string equidad = { "=" };
		std::vector <std::string> m_keyword = { "main","var", "int","float","string","bool","void","function","for","while","if","else","switch","case","default","print","read","return","true","false","inc","dec" };
		std::vector <char> m_invalid_simbolos = { '#','$','@','ñ','Ñ','~', '¼' };
		//<OP_REL>: = '<' | '<=' | '>' | '>=' | '==' | '!='
		std::vector <char> op_rel = { '<','>','!','=' };
		char space = ' ';
		std::vector <std::string> comentarys;

		std::string lex;
	public:
		void clearTokens();
		//bool parseSourceCode(const char* src);
		void getTokens(std::vector<Token*>*tokensVec);
		Token* getNextToken();
		Token* getPrevToken();
		Token* peeckToken(int idx);
		Token* setIndexToken(int idx);
		void addToken(std::string lex, int lineNum, TOKEN_TYPE tp);
		void addComentary(std::string comentary);
		String^ getTokensList();
	};
}