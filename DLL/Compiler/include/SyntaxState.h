#pragma once
#include <string>
#include "SymbolTable.h"
#include "Token.h"
#include "ErrorModule.h"

#include <sstream>

namespace Compiler
{
	class LexAnalyzer;
	class SyntaxAnalysis;
	class Syntax_State
	{
	private:
		//SymbolTable * m_stab;
	public:
		LexAnalyzer *m_lex=nullptr;
		SyntaxAnalysis *m_syn=nullptr;
		Syntax_State * m_parent=nullptr;
		std::string m_stateName;
		Syntax_State(LexAnalyzer *lex, SyntaxAnalysis *syn, Syntax_State *parent, std::string m_stateName);
		~Syntax_State() ;
		void checkSyntax();
		bool checkCanMoreErrors();
	};
	class Syntax_State_Dimension :public Syntax_State
	{
	public:
		Syntax_State_Dimension(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Dimension();
		std::string checkSyntax();
	};
	//Compiler::Token * t = m_lex->getNextToken();
	class Syntax_State_Function :public Syntax_State
	{
	private:
		std::string functionName;
		int linea;
		std::string type;
	public:
		Syntax_State_Function(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Function();
		void checkSyntax();
		int indexParentesis=0;
		bool hadInParentesis = false;
		void CheckParams();
		void PanicFunctionFinish();
		void addToSymbolTable();
	};
	class Syntax_State_Function_Block :public Syntax_State
	{
	public:
		Syntax_State_Function_Block(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Function_Block();
		void checkSyntax();
	};
	class Syntax_State_Main :public Syntax_State
	{
	public:
		Syntax_State_Main(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Main();
		void checkSyntax();
	};
	class Syntax_State_Params :public Syntax_State
	{
	private:
		std::string type;
	public:
		Syntax_State_Params(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		void checkSyntax();
		void addToSymbolTable();
	};
	class Syntas_State_Program :public  Syntax_State
	{
	private:

	public:
		Syntas_State_Program(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		void checkSyntax();
	};

	class Syntax_State_Type :public Syntax_State
	{
	public:
		Syntax_State_Type(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Type();
		std::string checkSyntax();
	};

	class Syntax_State_Var :public Syntax_State
	{
	public:
		Syntax_State_Var(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Var();
		void checkSyntax();
		void AddTosymbolTable();
		void checkForLimitator();
	};

	class Syntas_State_IF_Else :public  Syntax_State
	{
	private:

	public:
		Syntas_State_IF_Else(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntas_State_IF_Else();
		void checkSyntax();
		int indexParentesis = 0;
		bool hadInParentesis = false;
		void CheckParantesis();
	};

	class Syntas_State_While :public  Syntax_State
	{
	private:

	public:
		Syntas_State_While(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntas_State_While();
		void checkSyntax();
		int indexParentesis = 0;
		bool hadInParentesis = false;
		void CheckParantesis();
	};

	class Syntas_State_For :public  Syntax_State
	{
	private:

	public:
		Syntas_State_For(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntas_State_For();
		void checkSyntax();
		void checkEXPLOG();
		int indexParentesis = 0;
		int indexFinalParentesis = 0;
		bool hadInParentesis = false;
		void CheckParantesis();
		//void Check();
	};

	class Syntas_State_Switch :public  Syntax_State
	{
	private:

	public:
		Syntas_State_Switch(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntas_State_Switch();
		void checkSyntax();
		void checkEXPLOG();
		int indexParentesis = 0;
		int indexFinalParentesis = 0;
		int indexInitBlock = 0;
		int indexFinalBlock = 0;
		bool hadInParentesis = false;
		bool hadInBlock = false;
		void CheckParantesis();
		void CheckBlock();
	};

	class Syntas_State_Print :public  Syntax_State
	{
	private:

	public:
		Syntas_State_Print(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntas_State_Print();
		void checkSyntax();
		int indexParentesis = 0;
		int indexFinalParentesis = 0;
		bool hadInParentesis = false;
		void CheckParantesis();
	};

	class Syntas_State_Read :public  Syntax_State
	{
	private:

	public:
		Syntas_State_Read(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntas_State_Read();
		void checkSyntax();
		int indexParentesis = 0;
		int indexFinalParentesis = 0;
		bool hadInParentesis = false;
		void CheckParantesis();
	};

	class Syntax_State_Return :public Syntax_State
	{
	public:
		Syntax_State_Return(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Return();
		void checkSyntax();
	};
	class Syntax_State_Assignation :public Syntax_State
	{
	public:
		Syntax_State_Assignation(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Assignation();
		void checkSyntax();
	};
	class Syntax_State_Increment :public Syntax_State
	{
	public:
		Syntax_State_Increment(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Increment();
		void checkSyntax();
	};
	class Syntax_State_Decrement :public Syntax_State
	{
	public:
		Syntax_State_Decrement(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Decrement();
		void checkSyntax();
	};
	class Syntax_State_Call_Function :public Syntax_State
	{
	public:
		Syntax_State_Call_Function(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Call_Function();
		void checkSyntax();
	};
	class Syntax_State_Exp_Log :public Syntax_State
	{
	public:
		Syntax_State_Exp_Log(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Exp_Log();
		void checkSyntax();
		bool Recurrense(int &_parent);
	};

	class Syntax_State_Expression_Block :public Syntax_State
	{
	public:
		Syntax_State_Expression_Block(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Expression_Block();
		void checkSyntax();
	};
}