#include "../include/SyntaxState.h"
#include <sstream>
#include "../include/SyntaxAnalizer.h"



Compiler::Syntax_State_Expression_Block::Syntax_State_Expression_Block(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Expression_Block::~Syntax_State_Expression_Block()
{
}

void Compiler::Syntax_State_Expression_Block::checkSyntax()
{
	bool conti = true;
	Compiler::Token*t = m_lex->getNextToken();
	int index = m_lex->m_tokensIndex;
	if (t == nullptr)
	{
		m_syn->finishAnalysis = true;
		t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaba '}' ", " ");
		t = m_lex->getNextToken();
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;
	}
	if (t->getLex() == "}")
	{
		conti = false;
		return;
	}
	while (conti)
	{
		if (t->getLex() == "}")
		{
			conti = false;
			break;
		}
		else if (t == nullptr)
		{
			//agregar error y terminar programa
			m_syn->finishAnalysis = true;
			t = m_lex->getPrevToken();
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaba '}' ", " ");
			t = m_lex->getNextToken();
			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			return;
		}
		t = m_lex->getNextToken();
	}
	t = m_lex->setIndexToken(index);
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

	conti = true;
	while (conti)
	{

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
			if (t->getLex() == "=")
			{
				Syntax_State_Assignation* assigna = new Syntax_State_Assignation(m_lex, m_syn, this, "ASSIGNATION");
				//call function
				assigna->checkSyntax();
				if (m_syn->finishAnalysis)
				{
					//agregar error 
					delete assigna;
					return;
				}
				delete assigna;
				//t = m_lex->getNextToken();
				//if (t == nullptr)
				//{
				//	m_syn->finishAnalysis = true;
				//	//AGREGAR ERROR
				//	conti = false;
				//	return;
				//}
				//t = m_lex->getNextToken();
				//asignacion
			}
			else if (t->getLex() == "+")
			{
				//incremento
				Syntax_State_Increment* incre = new Syntax_State_Increment(m_lex, m_syn, this, "INCREMENT");
				//call function
				incre->checkSyntax();
				delete incre;
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
			else if (t->getLex() == "-")
			{
				//decremento
				//incremento
				Syntax_State_Decrement* decre = new Syntax_State_Decrement(m_lex, m_syn, this, "DECREMENT");
				//call function
				decre->checkSyntax();
				delete decre;
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
			else if (t->getLex() == "(")
			{
				Syntax_State_Call_Function* cllfunc = new Syntax_State_Call_Function(m_lex, m_syn, this, "CALL FUNCTION");
				//call function
				cllfunc->checkSyntax();
				delete cllfunc;
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
				//t = m_lex->getNextToken();
			}
			else
			{
				m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba una expresion valida", gcnew String(t->getLex().c_str()));

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
		}
		else if (t->getLex() == "if")
		{
			Syntas_State_IF_Else* ifelse = new Syntas_State_IF_Else(m_lex, m_syn, m_parent, "IF");
			ifelse->checkSyntax();
			delete ifelse;
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
		else if (t->getLex() == "while")
		{
			Syntas_State_While* whileS = new Syntas_State_While(m_lex, m_syn, m_parent, "WHILE");
			whileS->checkSyntax();
			delete whileS;
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
		else if (t->getLex() == "for")
		{
			Syntas_State_For* forsyn = new Syntas_State_For(m_lex, m_syn, m_parent, "FOR");
			forsyn->checkSyntax();
			delete forsyn;
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
		else if (t->getLex() == "switch")
		{
			Syntas_State_Switch* switchsyn = new Syntas_State_Switch(m_lex, m_syn, m_parent, "SWITCH");
			switchsyn->checkSyntax();
			delete switchsyn;
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
		else if (t->getLex() == "print")
		{
			Syntas_State_Print* printsyn = new Syntas_State_Print(m_lex, m_syn, m_parent, "PRINT");
			printsyn->checkSyntax();
			delete printsyn;
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
		else if (t->getLex() == "read")
		{
			Syntas_State_Read* readsyn = new Syntas_State_Read(m_lex, m_syn, m_parent, "READ");
			readsyn->checkSyntax();
			delete readsyn;
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
		else if (t->getLex() == "return")
		{
			Syntax_State_Return* returnsyn = new Syntax_State_Return(m_lex, m_syn, m_parent, "READ");
			returnsyn->checkSyntax();
			delete returnsyn;
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
			//error token unespectec
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba una expresion valida", gcnew String(t->getLex().c_str()));

			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
		}
		 if (t->getLex() == "}")
		{
		//t = m_lex->getNextToken();
		conti = false;
		break;
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
}
