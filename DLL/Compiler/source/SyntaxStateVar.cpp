#include "../include/SyntaxState.h"
#include "../include/SyntaxAnalizer.h"

Compiler::Syntax_State_Var::Syntax_State_Var(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Var::~Syntax_State_Var()
{
}

void Compiler::Syntax_State_Var::checkSyntax()
{
	bool conti = true;
	Compiler::Token*t;
	while (conti)
	{

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
		}
		if (t != nullptr &&t->getType() != ID)
		{
			//AGRAGAR ERROR y un meotodo de erroes
			int line = t->getLineNumber();
			t = m_lex->getPrevToken();
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, line, "se esperaba un 'ID'", gcnew String(t->getLex().c_str()));
			t = m_lex->getNextToken();
			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			
		}
		else if (t != nullptr)
		{
			m_syn->m_IDs.push_back(t->getLex());
			m_syn->linea.push_back(t->getLineNumber());
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
			}
			//si es [ pasar al estado de dimencion
		}
		//t = m_lex->getNextToken();
		if (t != nullptr &&t->getLex() == "[")
		{
			Syntax_State_Dimension* dim = new Syntax_State_Dimension(m_lex, m_syn, m_parent, m_stateName);
			m_syn->m_Dimension.push_back(dim->checkSyntax());
			if (m_syn->finishAnalysis)
			{
				return;;
			}
			delete dim;
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
			}
		}
		else
		{
			m_syn->m_Dimension.push_back("0");
		}
		if (t != nullptr &&t->getLex() == ":")
		{
			Syntax_State_Type*typ = new Syntax_State_Type(m_lex, m_syn, m_parent, m_stateName);
			m_syn->tipe = typ->checkSyntax();
			if (m_syn->finishAnalysis)
			{
				return;;
			}
			delete typ;
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
			}
			//return;
		}
		else if(t->getLex() != ",")
		{
			//agregar error
			int line = t->getLineNumber();
			t = m_lex->getPrevToken();
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, line, "se esperaba un ':'", gcnew String(t->getLex().c_str()));
			t = m_lex->getNextToken();
			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
		}
		if (t != nullptr &&t->getLex() != ":"&&t->getLex() != ",")
		{
			if (t->getLex() == ";")
			{
				conti = false;
				AddTosymbolTable();
				if (!checkCanMoreErrors())
				{
					m_syn->finishAnalysis = true;
					return;
				}
				break;
			}
			//aregar error
			int line = t->getLineNumber();
			t = m_lex->getPrevToken();
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, line, "se esperaba un ';'", gcnew String(t->getLex().c_str()));
			t = m_lex->getNextToken();
			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
			return;
		}
		
	}

}

void Compiler::Syntax_State_Var::AddTosymbolTable()
{
	for (int i = 0; i < m_syn->m_IDs.size(); i++)
	{
		int number;
		std::istringstream iss(m_syn->m_Dimension[i]);
		iss >> number;
		if (m_syn->inFunction)
		{
			if (m_syn->m_IDs[i] == m_syn->function)
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
				if (m_syn->m_stab->addSymbol(m_syn->linea[i], m_syn->m_IDs[i], number, ESYMBOL_CAT::LOCAL_VAR, m_syn->function, m_syn->tipe))
				{

				}
				else
				{
					if (!checkCanMoreErrors())
					{
						m_syn->finishAnalysis = true;
						return;
					}
					//agregar error de agregado de symbolo
				}
			}	
		}
		else
		{
			if (m_syn->m_stab->addSymbol(m_syn->linea[i], m_syn->m_IDs[i], number,ESYMBOL_CAT::GLOBAL_VAR, "<GLOBAL SCOPE>", m_syn->tipe))
			{

			}
			else
			{
				if (!checkCanMoreErrors())
				{
					m_syn->finishAnalysis = true;
					return;
				}
				//agregar error de agregado de symbolo
			}
		}
		
	}
	m_syn->m_IDs.clear();
	m_syn->m_Dimension.clear();
	m_syn->linea.clear();
	return;
	//t = m_lex->getNextToken();
	//if (t->getLex() == ";")
	//{
	//	for (int i = 0; i < m_syn->m_IDs.size(); i++)
	//	{
	//		int number;
	//		std::istringstream iss(m_syn->m_Dimension[i]);
	//		iss >> number;
	//		if (m_syn->m_stab->addSymbol(m_syn->linea[i], m_syn->m_IDs[i], number, m_syn->category, m_syn->function, m_syn->tipe))
	//		{
	//
	//		}
	//		else
	//		{
	//			//agregar error de agregado de symbolo
	//		}
	//	}
	//	return;
	//}
	//else
	//{
	//	// Agregar error
	//}
	if (m_syn->category == Compiler::ESYMBOL_CAT::PARAMETER)
	{
		for (int i = 0; i < m_syn->m_ParamsIDs.size(); i++)
		{
			int number;
			std::istringstream iss(m_syn->m_DimensionParams[i]);
			iss >> number;
			if (m_syn->m_stab->addSymbol(m_syn->lineaParams[i], m_syn->m_ParamsIDs[i], number, m_syn->category, m_syn->function, m_syn->tipe))
			{

			}
			else
			{
				//agregar error de agregado de symbolo
			}
		}
		m_syn->m_ParamsIDs.clear();
		m_syn->m_DimensionParams.clear();
		m_syn->lineaParams.clear();
		return;
	}
	else if (m_syn->category == Compiler::ESYMBOL_CAT::LOCAL_VAR)
	{
		
	}
	else if (m_syn->category == Compiler::ESYMBOL_CAT::FUNCTION)
	{
		for (int i = 0; i < m_syn->m_IDs.size(); i++)
		{
			int number;
			std::istringstream iss(m_syn->m_Dimension[i]);
			iss >> number;
			if (m_syn->m_stab->addSymbol(m_syn->linea[0], m_syn->m_IDs[0], number, Compiler::ESYMBOL_CAT::FUNCTION, "<GLOBAL SCOPE>", m_syn->tipe))
			{

			}
			else
			{
				//agregar error de agregado de symbolo
			}
		}
	}
	else
	{
		
	}
}

void Compiler::Syntax_State_Var::checkForLimitator()
{

}
