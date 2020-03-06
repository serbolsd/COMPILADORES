#include "../include/SyntaxState.h"
#include "../include/SyntaxAnalizer.h"

Compiler::Syntax_State_Type::Syntax_State_Type(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Type::~Syntax_State_Type()
{
}

std::string Compiler::Syntax_State_Type::checkSyntax()
{
	Compiler::Token*t = m_lex->getNextToken();
	std::string tip="int";
	if (t == nullptr)
	{
		m_syn->finishAnalysis = true;
		//agregar error
		t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
		t = m_lex->getNextToken();
		//agregar error, se esperaba main
		return tip;
	}
	if (t->getLex() == "int")
	{
		tip = "int";
	}
	else if (t->getLex() == "float")
	{
		tip = "float";

	}
	else if (t->getLex() == "string")
	{
		tip = "string";
	}
	else if (t->getLex() == "bool")
	{
		tip = "bool";
	}
	else
	{
		if (m_syn->category = Compiler::ESYMBOL_CAT::FUNCTION)
		{
			if (t->getLex() == "void" )
			{
				return tip = "bool";
			}
		}
		
		// Agregar Error
		//m_syn->finishAnalysis = true;
		//agregar error
		//t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un tipo valido", gcnew String(t->getLex().c_str()));
		//t = m_lex->getNextToken();
		//agregar error, se esperaba main
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return "int";
		}
		tip = "int";
		return "int";
	}
	return tip;
}