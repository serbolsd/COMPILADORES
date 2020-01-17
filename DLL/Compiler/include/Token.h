#pragma once
#include <string>

namespace Compiler {
	enum TOKEN_TYPE
	{
		UNDEFINDED = 0,
		KEYWORD,
		ID,
		INT,
		FLOAT,
		LOGIC_OPERATOR,
		UNILATERAL_LOGIC_OPERATOR,
		ARITMETIC_OPERATOR,
		DIMENCIONAL_OPERATOR,
		AGRUPE_OPERATOR,
		RELATIVE_OPERATOR,
		ASIGNATION,
		DELIMITER,
		STRING,
		COMENTARY
		//AGREGAR TODOS LOS TIPOS
	};
	class Token
	{
	public:
		Token(std::string lex, TOKEN_TYPE tp, int lineNum);
		~Token();
		void clean();
	private:
		std::string m_lex;
		int m_lineNumber;
		TOKEN_TYPE m_Type;
	public:
		std::string getLex() const { return m_lex; };
		int getType() const { return m_Type; };
		int getLineNumber() const { return m_lineNumber; };


	};
}