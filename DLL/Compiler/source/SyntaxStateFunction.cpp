#include "../include/SyntaxState.h"
#include "../include/Token.h"
#include "../include/SyntaxAnalizer.h"


Compiler::Syntax_State_Function::Syntax_State_Function(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{

}

Compiler::Syntax_State_Function::~Syntax_State_Function()
{
}

void Compiler::Syntax_State_Function::checkSyntax()
{
	Compiler::Token * t = m_lex->getNextToken();
	
	if (t == nullptr)
	{
		m_syn->finishAnalysis = true;
		//agregar error y finalizar programa
		t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER,t->getLineNumber()+1,"se esperaban mas expresiones"," ");
		t = m_lex->getNextToken();
		return;
	}
	if (t != nullptr &&t->getType() != ID)
	{
		//AGRAGAR ERROR y finalizar Analisis
		int line = t->getLineNumber();
		t = m_lex->getPrevToken();
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, line, "se esperaban un ID", gcnew String(t->getLex().c_str()));
		t = m_lex->getNextToken();
		m_syn->finishAnalysis = true;
		return;
	}
	else if (t != nullptr)
	{
		functionName=t->getLex();
		linea=t->getLineNumber();
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
	//t = m_lex->getNextToken();
	m_syn->m_Dimension.push_back("0");
	if (t != nullptr &&t->getLex() == "(")
	{
		CheckParams();
		if (m_syn->finishAnalysis)
		{
			//finalizar analisis
			return;
		}
		if (hadInParentesis)
		{
			m_syn->inFunction = true;
			m_syn->function = functionName;
			m_syn->inFunctionCategory = Compiler::ESYMBOL_CAT::PARAMETER;
			Syntax_State_Params * parm = new Syntax_State_Params(m_lex, m_syn, m_parent, m_stateName);
			parm->checkSyntax();
			delete parm;
			if (m_syn->finishAnalysis)
			{
				return;
			}
			m_syn->inFunction = false;
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
		
	}
	if (t != nullptr &&t->getLex() == ":")
	{
		m_syn->category = Compiler::ESYMBOL_CAT::FUNCTION;
		Syntax_State_Type*typ = new Syntax_State_Type(m_lex, m_syn, m_parent, m_stateName);
		type=typ->checkSyntax();
		delete typ;
		if (m_syn->finishAnalysis)
		{
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
		}

	}
	if (t != nullptr &&t->getLex() == "{")
	{
		m_syn->inFunction = true;
		m_syn->function = functionName;
		m_syn->inFunctionCategory = Compiler::ESYMBOL_CAT::LOCAL_VAR;
		Syntax_State_Function_Block *fBlock = new Syntax_State_Function_Block(m_lex, m_syn, m_parent, m_stateName);
		fBlock->checkSyntax();
		if (m_syn->finishAnalysis)
		{
			//finalizar analisis
			return;
		}
		m_syn->inFunction = false;
		m_syn->cleanLocal();
		addToSymbolTable();
	}
	else
	{
		m_syn->finishAnalysis = true;
			//agregar error y finalizar programa
		m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba un '{'", gcnew String(t->getLex().c_str()));

		if (!checkCanMoreErrors())
		{
			m_syn->finishAnalysis = true;
			return;
		}
		return;

	}
	//if (t != nullptr &&t->getLex() != ":")
	//{
	//	if (t->getLex() == "}")
	//	{
	//		t = m_lex->getNextToken();
	//		break;
	//	}
	//	//aregar error
	//	return;
	//}
	//t = m_lex->getNextToken();
	
}

void Compiler::Syntax_State_Function::CheckParams()
{
	indexParentesis = m_lex->getIndexToken();
	Compiler::Token * t = m_lex->getNextToken();
	if (t->getLex() != ")")
	{
		hadInParentesis=true;
	}
	while (t->getLex()!=")")
	{

		t = m_lex->getNextToken();
		if (t==nullptr)
		{
			//agregar error y terminar analisis;
			t = m_lex->getPrevToken();
			m_syn->m_err->addError(ERROR_PHASE::SYN_ANALYZER, t->getLineNumber(), "se esperaba ')'", gcnew String(t->getLex().c_str()));
			t = m_lex->getNextToken();
			m_syn->finishAnalysis = true;
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

void Compiler::Syntax_State_Function::PanicFunctionFinish()
{
	Compiler::Token * t = m_lex->getNextToken();
	while (t->getLex() != ")")
	{
		t = m_lex->getNextToken();
		if (t == nullptr)
		{
			//agregar error y terminar analisis;
			m_syn->finishAnalysis = true;
		}
	}
}

void Compiler::Syntax_State_Function::addToSymbolTable()
{
		if (m_syn->m_stab->addSymbol(linea, functionName, 0, ESYMBOL_CAT::FUNCTION,"<GLOBAL SCOPE>", type))
		{

		}
		else
		{
			if (!checkCanMoreErrors())
			{
				m_syn->finishAnalysis = true;
				return;
			}
		}
}
