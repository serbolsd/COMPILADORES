#include "../include/SyntaxState.h"
#include <cstdlib>
#include "../include/SyntaxAnalizer.h"

Compiler::Syntax_State_Dimension::Syntax_State_Dimension(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Dimension::~Syntax_State_Dimension()
{
}

std::string Compiler::Syntax_State_Dimension::checkSyntax()
{
	Compiler::Token*t = m_lex->getNextToken();
	if (t == nullptr)
	{
		m_syn->finishAnalysis = true;
		//agregar error
		t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber() + 1, "se esperaban mas expresiones", " ");
		t = m_lex->getNextToken();

		return 0;
	}
	std::string dim = "0";
	if (t->getType() != Compiler::TOKEN_TYPE::INT)
	{
		//t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba 'INTEGER'", gcnew String(t->getLex().c_str()));
		//t = m_lex->getNextToken();
		//agregar error, se esperaba main
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return dim;
		}
		// Agregar Error
	}
	int n = std::atoi(t->getLex().c_str());
	if (n < 0)
	{
		//agregar error
		//t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba 'INTEGER' mayor a 0", gcnew String(t->getLex().c_str()));
		//t = m_lex->getNextToken();
		//agregar error, se esperaba main
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return dim;
		}
	}
	else
	{
		dim = t->getLex().c_str();
	}
	t = m_lex->getNextToken();
	if (t->getLex()!="]")
	{
		//agregar error pero seguir
		//agregar error
		//t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba ']'", gcnew String(t->getLex().c_str()));
		//t = m_lex->getNextToken();
		//agregar error, se esperaba main
		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return dim;
		}
	}
	return dim;
	//if (m_syn->category == Compiler::ESYMBOL_CAT::PARAMETER)
	//{
	//	Compiler::Token*t = m_lex->getNextToken();
	//	if (t->getType() != Compiler::TOKEN_TYPE::INT)
	//	{
	//		// Agregar Error
	//		m_syn->m_ParamsIDs.pop_back();
	//		m_syn->m_DimensionParams.pop_back();
	//		m_syn->lineaParams.pop_back();
	//		return;
	//	}
	//	int n = std::atoi(t->getLex().c_str());
	//	if (n < 0)
	//	{
	//		//agregar error;
	//		m_syn->m_ParamsIDs.pop_back();
	//		m_syn->m_DimensionParams.pop_back();
	//		m_syn->lineaParams.pop_back();
	//		return;
	//	}
	//	m_syn->m_DimensionParams.push_back(t->getLex());
	//	return;
	//}
	//else if (m_syn->category == Compiler::ESYMBOL_CAT::LOCAL_VAR)
	//{
	//	Compiler::Token*t = m_lex->getNextToken();
	//	if (t->getType() != Compiler::TOKEN_TYPE::INT)
	//	{
	//		// Agregar Error
	//		return;
	//	}
	//	int n = std::atoi(t->getLex().c_str());
	//	if (n < 0)
	//	{
	//		//agregar error;
	//		m_syn->m_LocalIDs.pop_back();
	//		m_syn->m_LocalDimension.pop_back();
	//		m_syn->lineaLocal.pop_back();
	//		return;
	//	}
	//	m_syn->m_LocalDimension.push_back(t->getLex());
	//	return;
	//}
	//else
	//{
	//	Compiler::Token*t = m_lex->getNextToken();
	//	if (t->getType() != Compiler::TOKEN_TYPE::INT)
	//	{
	//		// Agregar Error
	//		m_syn->m_IDs.pop_back();
	//		m_syn->m_Dimension.pop_back();
	//		m_syn->linea.pop_back();
	//		return;
	//	}
	//	int n = std::atoi(t->getLex().c_str());
	//	if (n < 0)
	//	{
	//		//agregar error;
	//		m_syn->m_IDs.pop_back();
	//		m_syn->m_Dimension.pop_back();
	//		m_syn->linea.pop_back();
	//		return;
	//	}
	//	m_syn->m_Dimension.push_back(t->getLex());
	//	return;
	//
	//}
}
