#include "../include/SyntaxState.h"
#include <sstream>
#include "../include/SyntaxAnalizer.h"

Compiler::Syntas_State_Switch::Syntas_State_Switch(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex,syn,parent,stateName)
{

}

Compiler::Syntas_State_Switch::~Syntas_State_Switch()
{

}

void Compiler::Syntas_State_Switch::checkSyntax()
{
	bool conti = true;
	bool defaults = true;
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
			return;
		}
	}
	else
	{
		m_syn->finishAnalysis = true;
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '(' ", gcnew String(t->getLex().c_str()));

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
	if (hadInParentesis)
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
		if (t->getType() == ID)
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
		else
		{
			//error se esperaba un ID
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un 'ID' ", gcnew String(t->getLex().c_str()));

			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			t = m_lex->setIndexToken(indexFinalParentesis);
		}
	}
	else
	{
		//error se esperaba un ID
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un 'ID' ", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		t = m_lex->setIndexToken(indexFinalParentesis);
	}
	if (t->getLex() == ")")
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
	else
	{
		//error se esperaba un )
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un ')' ", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		t = m_lex->setIndexToken(indexFinalParentesis);
	}
	if (t->getLex()=="{")
	{
		indexInitBlock = m_lex->getIndexToken();
		CheckBlock();
		if (m_syn->finishAnalysis)
		{
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
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '{' ", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;
	}
	while (conti)
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
		if (t->getLex()=="}")
		{
			break;
		}
		if (t->getLex()=="case"||t->getLex()=="default")
		{
			if (t->getLex() == "default")
			{
				defaults = true;
			}
			else
			{
				t = m_lex->getNextToken();
				if (t->getType() != ID && t->getType() != INT)
				{
					//error se esperaba un ID o un INT
					conti = false;
					break;
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
			if (t->getLex() !=":")
			{
				m_syn->finishAnalysis = true;
				m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un ':' ", gcnew String(t->getLex().c_str()));

				if (!checkCanMoreErrors())
				{
					m_syn->finishAnalysis = true;
					return;
				}
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
			if (t->getLex()=="{")
			{
				Syntax_State_Expression_Block* expBloq = new Syntax_State_Expression_Block(m_lex, m_syn, this, "EXP LOG");
				expBloq->checkSyntax();
				delete expBloq;
				if (m_syn->finishAnalysis)
				{
					return;
				}
			}
		}
		else
		{
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un 'default/case' ", gcnew String(t->getLex().c_str()));

			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
		}
		t = m_lex->getNextToken();
	}
	if (!defaults)
	{
		//error se esperaba un default
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un 'default' ", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
	}
	//t = m_lex->get;
}

void Compiler::Syntas_State_Switch::CheckParantesis()
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
		}
	}
	indexFinalParentesis = m_lex->getIndexToken();
	t = m_lex->setIndexToken(indexParentesis);
}

void Compiler::Syntas_State_Switch::CheckBlock()
{
	Compiler::Token * t = m_lex->getNextToken();
	if (t->getLex()!="}")
	{
		hadInBlock = true;
	}
	else
	{
		m_syn->finishAnalysis = true;
		//agregar error
		return;
	}
	while (t->getLex() != "}")
	{
		t = m_lex->getNextToken();
		if (t == nullptr)
		{
			//agregar error y terminar programa
			return;
		}
	}
	indexFinalBlock = m_lex->getIndexToken();
	t = m_lex->setIndexToken(indexInitBlock);
}
