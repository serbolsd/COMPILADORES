#include "../include/SyntaxState.h"
#include <sstream>
#include "../include/SyntaxAnalizer.h"

Compiler::Syntas_State_Read::Syntas_State_Read(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex,syn,parent,stateName)
{
}

Compiler::Syntas_State_Read::~Syntas_State_Read()
{
}

void Compiler::Syntas_State_Read::checkSyntax()
{
	bool conti = true;
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
	if (t->getLex() == "(")
	{
		CheckParantesis();
		if (m_syn->finishAnalysis)
		{
			//m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un ')' ", gcnew String(t->getLex().c_str()));
			//
			//if (!checkCanMoreErrors())
			//{
			//	m_syn->finishAnalysis = true;
			//	return;
			//}
			//m_syn->finishAnalysis = true;
			return;
		}
	}
	else
	{
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '(' ", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		m_syn->finishAnalysis = true;
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

	Syntax_State_Exp_Log* explog = new Syntax_State_Exp_Log(m_lex, m_syn, this, "EXP LOG");
	explog->checkSyntax();
	delete explog;
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
	t = m_lex->getCurrentToken();
	//if (t->getType() == ID || t->getType() == STRING || t->getType() == INT || t->getType() == FLOAT)
	//{
	//	
	//}
	//else
	//{
	//	//agregar error
	//	m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaban un ')' ", gcnew String(t->getLex().c_str()));
	//	if (!checkCanMoreErrors())
	//	{
	//		m_syn->finishAnalysis = true;
	//		return;
	//	}
	//	return;
	//}

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
	if (t->getLex() != ";")
	{
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un ';'", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		m_syn->finishAnalysis = true;
		return;
	}
	return;


	int type = t->getType();
	if (type != ID || type != STRING || type != INT || type != FLOAT)
	{
		t = m_lex->setIndexToken(indexFinalParentesis);
		//AGREGAR ERROR unespecteck token
		conti = false;
	}
	t = m_lex->getNextToken();
	if (t == nullptr)
	{
		//agregar error y terminar analisis;
		m_syn->finishAnalysis = true;
		return;
	}
	if (t->getLex()!=")")
	{
		//AGREGAR ERROR se esperaba ")"
		t = m_lex->setIndexToken(indexFinalParentesis);
	}
	t = m_lex->getNextToken();
	if (t == nullptr)
	{
		//agregar error y terminar analisis;
		m_syn->finishAnalysis = true;
		return;
	}
	if (t->getLex() != ";")
	{
		m_syn->finishAnalysis = true;
		//agregar error y terminar analisis;
		return;
	}
}

void Compiler::Syntas_State_Read::CheckParantesis()
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
			//agregar error y terminar analisis;
			m_syn->finishAnalysis = true;
			return;
		}
	}
	indexFinalParentesis = m_lex->getIndexToken();
	t = m_lex->setIndexToken(indexParentesis);
}
