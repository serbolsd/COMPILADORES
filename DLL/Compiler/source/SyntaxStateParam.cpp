#include "../include/SyntaxState.h"
#include "../include/SyntaxAnalizer.h"


Compiler::Syntax_State_Params::Syntax_State_Params(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

void Compiler::Syntax_State_Params::checkSyntax()
{
	m_syn->category = Compiler::ESYMBOL_CAT::PARAMETER;
	bool conti = true;
	Compiler::Token*t = m_lex->getNextToken();
	while (conti)
	{
		
		if (t == nullptr)
		{

			//AGRAGAR ERROR
			m_syn->finishAnalysis = true;
			t = m_lex->getPrevToken();
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
			t = m_lex->getNextToken();
			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			conti = false;
			break;
		}
		if (t != nullptr &&t->getType() != ID)
		{
			// NOT VALID PARAM
			//agregar error terminar analisis(por ahora)
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un 'ID' valido", gcnew String(t->getLex().c_str()));

			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			m_syn->finishAnalysis = true;
			return;
		}
		else if (t != nullptr)
		{
			m_syn->m_ParamsIDs.push_back(t->getLex());
			m_syn->lineaParams.push_back(t->getLineNumber());
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
				conti = false;
				break;
			}
			//si es [ pasar al estado de dimencion
		}
		//t = m_lex->getNextToken();
		if (t != nullptr &&t->getLex() == "[")
		{
			Syntax_State_Dimension* dim = new Syntax_State_Dimension(m_lex, m_syn, m_parent, m_stateName);
			m_syn->m_Dimension.push_back(dim->checkSyntax());
			delete dim;
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
				conti = false;
				break;
			}
		}
		else
		{
			m_syn->m_DimensionParams.push_back("0");
		}
		if (t != nullptr &&t->getLex() == ":")
		{
			Syntax_State_Type*typ = new Syntax_State_Type(m_lex, m_syn, m_parent, m_stateName);
			type=typ->checkSyntax();
			addToSymbolTable();
			delete typ;
			t = m_lex->getNextToken();
			if (t->getLex()!=")")
			{
				//agregar error terminar programa
				m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un ')' ", gcnew String(t->getLex().c_str()));

				if (!checkCanMoreErrors())
				{
					m_syn->finishAnalysis = true;
					return;
				}
				m_syn->finishAnalysis = true;
				return;
			}
			return;
		}
		if (t != nullptr &&t->getLex() != ":"&&t->getLex() != ","&&t->getType() != ID)
		{
			//aregar error //terinar Analisis
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un ')' ", gcnew String(t->getLex().c_str()));

			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			m_syn->finishAnalysis = true;
			return;
		}
		t = m_lex->getNextToken();
	}
}

void Compiler::Syntax_State_Params::addToSymbolTable()
{
	for (int i = 0; i < m_syn->m_ParamsIDs.size(); i++)
	{
		int number;
		std::istringstream iss(m_syn->m_ParamsIDs[i]);
		iss >> number;
		if (m_syn->inFunction)
		{
			if (m_syn->m_ParamsIDs[i]== m_syn->function)
			{
				m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, m_syn->lineaParams[i], "El parametro no puede llamarse igual que su funcion ", gcnew String(m_syn->m_ParamsIDs[i].c_str()));

				if (!checkCanMoreErrors())
				{
					m_syn->finishAnalysis = true;
					return;
				}
				m_syn->finishAnalysis = true;
			}
			else
			{
				if (m_syn->m_stab->addSymbol(m_syn->lineaParams[i], m_syn->m_ParamsIDs[i], number, ESYMBOL_CAT::PARAMETER, m_syn->function, type))
				{

				}
				else
				{
					//agregar error de agregado de symbolo
					if (!checkCanMoreErrors())
					{
						m_syn->finishAnalysis = true;
						return;
					}
				}
			}
			
		}
	}
}
