#include "../include/SyntaxState.h"
#include "../include/SyntaxAnalizer.h"


Compiler::Syntas_State_While::Syntas_State_While(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex,syn,parent,stateName)
{
}

Compiler::Syntas_State_While::~Syntas_State_While()
{
}

void Compiler::Syntas_State_While::checkSyntax()
{
	Compiler::Token * t = m_lex->getNextToken();
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
	if (t->getLex() == "(")
	{
		CheckParantesis();
		if (m_syn->finishAnalysis)
		{
			return;
		}
		if (!hadInParentesis)
		{
			m_syn->finishAnalysis = true;
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba una expresion ", gcnew String(t->getLex().c_str()));
			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			return;
		}
		//EXP LOGICO
		Syntax_State_Exp_Log* explog = new Syntax_State_Exp_Log(m_lex, m_syn, this, "EXP LOG");
		explog->checkSyntax();
		t = m_lex->getNextToken();
		delete explog;
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
		//t = m_lex->getNextToken(); 
		//if (t == nullptr)
		//{
		//	m_syn->finishAnalysis = true;
		//	t = m_lex->getPrevToken();
		//	m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
		//	t = m_lex->getNextToken();
		//	if (!checkCanMoreErrors())
		//	{
		//		m_syn->finishAnalysis = true;
		//		return;
		//	}
		//	return;
		//}
	}
	else
	{
		m_syn->finishAnalysis = true;
		//agregar error terminar programa
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '(' ", gcnew String(t->getLex().c_str()));
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;
	}
	if (t->getLex() == "{")
	{
		//bloque expresion
		Syntax_State_Expression_Block* expBloq = new Syntax_State_Expression_Block(m_lex, m_syn, this, "EXP LOG");
		expBloq->checkSyntax();
		delete expBloq;
		if (m_syn->finishAnalysis)
		{
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
		m_syn->finishAnalysis = true;
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '{' ", gcnew String(t->getLex().c_str()));
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;
	}
}

void Compiler::Syntas_State_While::CheckParantesis()
{
	indexParentesis = m_lex->getIndexToken();
	Compiler::Token * t = m_lex->getNextToken();
	if (t->getLex() != ")")
	{
		hadInParentesis = true;
	}
	while (t->getLex() != ")")
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
	}
	t = m_lex->setIndexToken(indexParentesis);
}
