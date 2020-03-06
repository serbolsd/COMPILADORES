#include "../include/SyntaxState.h"
#include <sstream>
#include "../include/SyntaxAnalizer.h"


Compiler::Syntax_State_Increment::Syntax_State_Increment(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex,syn,parent,stateName)
{
}

Compiler::Syntax_State_Increment::~Syntax_State_Increment()
{
}

void Compiler::Syntax_State_Increment::checkSyntax()
{
	Compiler::Token*t = m_lex->getNextToken();
	if (t == nullptr)
	{
		m_syn->finishAnalysis = true;
		t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
		t = m_lex->getNextToken();
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;
	}
	if (t->getLex()!="+")
	{
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaban un '+' ", gcnew String(t->getLex().c_str()));
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
	}
	t = m_lex->getNextToken();
	if (t == nullptr)
	{
		m_syn->finishAnalysis = true;
		t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
		t = m_lex->getNextToken();
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;
	}
	if (t->getLex() != ";")
	{
		//m_syn->finishAnalysis = true;
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaban un ';' ", gcnew String(t->getLex().c_str()));
		//t = m_lex->getNextToken();
		t = m_lex->getPrevToken();
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
	}
}

