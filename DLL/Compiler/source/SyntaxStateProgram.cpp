#include "../include/SyntaxState.h"
#include "../include/SyntaxAnalizer.h"

Compiler::Syntas_State_Program::Syntas_State_Program(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{

}

void Compiler::Syntas_State_Program::checkSyntax()
{
	bool contin = true;
	Compiler::Token * t = m_lex->getNextToken();
	if (t==nullptr)
	{
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, 1, "se esperaban funcion 'main'", " ");

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		contin = false;
		return;
	}

	while (contin)
	{
		std::string st = t->getLex();
		if (t != nullptr &&t->getLex() == "var")
		{
			m_syn->category = Compiler::ESYMBOL_CAT::GLOBAL_VAR;
			Syntax_State_Var *var = new Syntax_State_Var(m_lex, m_syn, m_parent, m_stateName);
			var->checkSyntax();
			delete var;
			t = m_lex->getNextToken();
			if (t == nullptr)
			{
				//m_syn->finishAnalysis = true;
				//
				////agregar error
				//t = m_lex->getPrevToken();
				//m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
				//t = m_lex->getNextToken();
				//if (!checkCanMoreErrors())
				//{
				//	m_syn->finishAnalysis = true;
				//	return;
				//}
				//return;;
				contin = false;
				break;
			}
			m_syn->cleanIDs();
			m_syn->cleanLocal();
			m_syn->cleanParams();
		}
		else if (t != nullptr &&t->getLex() == "function")
		{
			m_syn->category = Compiler::ESYMBOL_CAT::FUNCTION;
			Syntax_State_Function* func = new Syntax_State_Function(m_lex, m_syn, m_parent, m_stateName);
			func->checkSyntax();
			delete func;
			t = m_lex->getNextToken();
			//t = m_lex->getPrevToken();
			if (t == nullptr)
			{
				m_syn->finishAnalysis = true;

				////agregar error
				//t = m_lex->getPrevToken();
				//m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
				//t = m_lex->getNextToken();
				//if (!checkCanMoreErrors())
				//{
				//	m_syn->finishAnalysis = true;
				//	return;
				//}
				//return;;
				contin = false;
				break;
			}
			m_syn->cleanIDs();
			m_syn->cleanLocal();
			m_syn->cleanParams();

		}
		else if (t != nullptr &&t->getLex() == "main")
		{
			m_syn->isMain = true;
			//m_syn->category = Compiler::ESYMBOL_CAT::FUNCTION;
			Syntax_State_Main* ma = new Syntax_State_Main(m_lex, m_syn, m_parent, m_stateName);
			ma->checkSyntax();
			delete ma;
			t = m_lex->getNextToken();
			if (t == nullptr)
			{
				contin = false;
				break;
			}
			m_syn->cleanIDs();
			m_syn->cleanLocal();
			m_syn->cleanParams();

		}
		else
		{
			t = m_lex->getPrevToken();
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaban otra Expresion", gcnew String(t->getLex().c_str()));
			t = m_lex->getNextToken();
			//AGREGAR ERROR
			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			t = m_lex->getNextToken();
			if (t == nullptr)
			{
				m_syn->finishAnalysis = true;

				//agregar error
				t = m_lex->getPrevToken();
				m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
				t = m_lex->getNextToken();
				if (!checkCanMoreErrors())
				{
					m_syn->finishAnalysis = true;
					return;
				}
				return;;
				contin = false;
				break;
			}
		}
		if (t == nullptr)
		{
			break;
		}

	}
	m_syn->cleanIDs();
	m_syn->cleanLocal();
	m_syn->cleanParams();
	if (!m_syn->isMain)
	{
		t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber()+1, "se esperaban funcion 'main'"," ");
		t = m_lex->getNextToken();
		//agregar error, se esperaba main
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
	}
}
