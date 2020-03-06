#include "../include/SyntaxState.h"
#include "../include/SyntaxAnalizer.h"

Compiler::Syntas_State_IF_Else::Syntas_State_IF_Else(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex,syn,parent,stateName)
{
}

Compiler::Syntas_State_IF_Else::~Syntas_State_IF_Else()
{
}

void Compiler::Syntas_State_IF_Else::checkSyntax()
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
	if (t->getLex()=="(")
	{
		CheckParantesis();
		if (m_syn->finishAnalysis)
		{
			//finalizar analisis
			return;
		}
		if (!hadInParentesis)
		{
			m_syn->finishAnalysis = true;
			//agregar SE ESPERABA UNA EXPRESION LOGICA
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba una expresion logica ", gcnew String(t->getLex().c_str()));

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
		delete explog;
		if (m_syn->finishAnalysis)
		{
			//finalizar analisis
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
		m_syn->finishAnalysis = true;
		//if (m_syn->finishAnalysis)
		//{
		//	//finalizar analisis
		//}
		//agregar error terminar programa
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '('", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;
	}
	if (t->getLex()=="{")
	{
		//bloque expresion
		Syntax_State_Expression_Block* expBloq = new Syntax_State_Expression_Block(m_lex, m_syn, this, "EXP LOG");
		expBloq->checkSyntax();
		delete expBloq;
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
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '{'", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;
	}
	if (t->getLex()=="else")
	{
		if (t->getLex() == "{")
		{
			//bloque expresion
			Syntax_State_Expression_Block* expBloq = new Syntax_State_Expression_Block(m_lex, m_syn, this, "EXP LOG");
			expBloq->checkSyntax();
			delete expBloq;
			if (m_syn->finishAnalysis)
			{
				//finalizar analisis
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
			m_syn->finishAnalysis = true;
			//agregar SE ESPERABA {
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '{' ", gcnew String(t->getLex().c_str()));

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
		t = m_lex->getPrevToken();
	}

}

void Compiler::Syntas_State_IF_Else::CheckParantesis()
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
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaba un ')' ", " ");
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
