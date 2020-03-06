#include "../include/SyntaxState.h"
#include "../include/SyntaxAnalizer.h"


Compiler::Syntax_State_Main::Syntax_State_Main(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	: Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Main::~Syntax_State_Main()
{
}

void Compiler::Syntax_State_Main::checkSyntax()
{
	m_syn->category = Compiler::ESYMBOL_CAT::LOCAL_VAR;
	m_syn->function = "main";
	m_syn->category = Compiler::ESYMBOL_CAT::PARAMETER;
	Compiler::Token * t = m_lex->getNextToken();
	bool conti = true;
	
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
	//if (t != nullptr &&t->getType() != ID)
	//{
	//	//AGRAGAR ERROR
	//	m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un 'ID'", gcnew String(t->getLex().c_str()));
	//
	//	if (!checkCanMoreErrors())
	//	{
	//		m_syn->finishAnalysis = true;
	//		return;
	//	}
	//}
	if (t != nullptr &&t->getLex() == "(")
	{
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
		if (t->getLex()!=")")
		{
			m_syn->finishAnalysis = true;
			//agregar error y finalizar programa
			return;
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
	}
	else
	{
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un ')'", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
	}
	
	if (t != nullptr &&t->getLex() == "{")
	{
		m_syn->inFunction = true;
		m_syn->function = "main";
		m_syn->category = Compiler::ESYMBOL_CAT::LOCAL_VAR;
		Syntax_State_Function_Block *fBlock = new Syntax_State_Function_Block(m_lex, m_syn, m_parent, m_stateName);
		fBlock->checkSyntax();
		m_syn->cleanLocal();
		t = m_lex->getNextToken();
		t = m_lex->getPrevToken();
	}
	else
	{
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
		else
		{
			m_syn->finishAnalysis = true;
			//agregar error y finalizar programa
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '{'", gcnew String(t->getLex().c_str()));

			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			return;
		}
		
	}
	
	
	
}