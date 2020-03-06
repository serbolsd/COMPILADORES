#include "../include/SyntaxState.h"
#include <sstream>
#include "../include/SyntaxAnalizer.h"

Compiler::Syntax_State_Exp_Log::Syntax_State_Exp_Log(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Exp_Log::~Syntax_State_Exp_Log()
{
}

void Compiler::Syntax_State_Exp_Log::checkSyntax()
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
	int parent = 0;
	while (true)
	{
		if (t->getLex() == "(")
		{
			parent++;
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
		else if (t->getLex() == ")")
		{
			if (parent==0)
			{
				return;
			}
			parent--;
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
		else if(t->getLex()=="," || t->getLex() == ";")
		{
			if (parent == 0)
			{
				return;
			}
		}

		if (t->getType()!=ID&&t->getType() != STRING&& t->getType() != INT && t->getType() != FLOAT && t->getLex() != "true"&& t->getLex() != "false")
		{
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba una expresion valida", gcnew String(t->getLex().c_str()));

			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
		}
		else
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
				if (t->getLex()=="(")
				{
					Syntax_State_Call_Function* cllfunc = new Syntax_State_Call_Function(m_lex,m_syn,this,"CALL FUNCTION");
					//call function
					cllfunc->checkSyntax();
					t = m_lex->getCurrentToken();
					delete cllfunc;
					if (m_syn->finishAnalysis)
					{
						return;
					}
					//t = m_lex->getNextToken();
				}
				else
				{
					t = m_lex->getPrevToken();
				}
			}
			t = m_lex->getNextToken();
			if (t->getLex() == ")"|| t->getLex() == "," || t->getLex() == ";")
			{
				if (parent == 0)
				{
					return;
				}
				if (t->getLex() == ")")
				{
					parent--;
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
					if (t->getLex() == ")" || t->getLex() == "," || t->getLex() == ";")
					{
						if (Recurrense(parent))
						{
							return;
						}

					}
				}
				else
				{
					m_syn->finishAnalysis = true;
					m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaban mas expresiones", " ");
					
					if (!checkCanMoreErrors())
					{
						m_syn->finishAnalysis = true;
						return;
					}
					return;
				
				}
			}
			
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
			if (t->getType() != RELATIVE_OPERATOR && t->getType() != ARITMETIC_OPERATOR && t->getType() != LOGIC_OPERATOR)
			{
				//agregar Error
				m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba una expresion logica", gcnew String(t->getLex().c_str()));

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
			if (t->getType() != ID && t->getType() != STRING && t->getType() != INT && t->getType() != FLOAT)
			{
				m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba una expresion valida", gcnew String(t->getLex().c_str()));

				if (!checkCanMoreErrors())
				{
					m_syn->finishAnalysis = true;
					return;
				}
			}
		}
	}
	
}

bool Compiler::Syntax_State_Exp_Log::Recurrense(int &_parent)
{
	Compiler::Token*t = m_lex->getCurrentToken();
	//if (t == nullptr)
	//{
	//	m_syn->finishAnalysis = true;
	//	t = m_lex->getPrevToken();
	//	m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
	//	t = m_lex->getNextToken();
	//	if (!checkCanMoreErrors())
	//	{
	//		m_syn->finishAnalysis = true;
	//		return true;
	//	}
	//	return true;
	//}
	if (t->getLex() == ")" || t->getLex() == "," || t->getLex() == ";")
	{
		if (_parent == 0)
		{
			return true;
		}
		if (t->getLex() == ")")
		{
			_parent--;
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
					return true;
				}
				return true;
			}
			if (t->getLex() == ")")
			{
				return Recurrense(_parent);
			}
		}
		else
		{
			m_syn->finishAnalysis = true;
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaban mas expresiones", " ");

			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return true;
			}
			return true;

		}
	}
}
