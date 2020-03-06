#include "../include/LexAnalyzer.h"
#include "../include/LexStates.h"


Compiler::LexAnalyzer::LexAnalyzer(ErrorModule ^ errormod)
{
	m_refErrorMod = errormod;
	m_keyWords.insert(std::make_pair("var", ""));
	m_keyWords.insert(std::make_pair("for", ""));
	m_keyWords.insert(std::make_pair("while", ""));
	m_keyWords.insert(std::make_pair("int", ""));
	m_keyWords.insert(std::make_pair("float", ""));
	m_keyWords.insert(std::make_pair("if", ""));
	m_keyWords.insert(std::make_pair("bool", ""));
	m_keyWords.insert(std::make_pair("string", ""));
	m_keyWords.insert(std::make_pair("void", ""));
	m_keyWords.insert(std::make_pair("function", ""));
	m_keyWords.insert(std::make_pair("else", ""));
	m_keyWords.insert(std::make_pair("main", ""));
	m_keyWords.insert(std::make_pair("switch", ""));
	m_keyWords.insert(std::make_pair("default", ""));
	m_keyWords.insert(std::make_pair("print", ""));
	m_keyWords.insert(std::make_pair("read", ""));
	m_keyWords.insert(std::make_pair("case", ""));
	m_keyWords.insert(std::make_pair("return", ""));
	m_keyWords.insert(std::make_pair("true", ""));
	m_keyWords.insert(std::make_pair("false", ""));
	m_keyWords.insert(std::make_pair("inc", ""));
	m_keyWords.insert(std::make_pair("dec", ""));
	State = new LexStateRead;
	//PrevState = new LexStateRead;
}

Compiler::LexAnalyzer::~LexAnalyzer()
{
}

void Compiler::LexAnalyzer::parseSourceCode(const char * src)
{
	while (!m_errorsExcedet && src[indexNum] != '\0')
	{
		while (src[indexNum] != '\0')
		{
			if (m_errorsExcedet||State==nullptr)
			{
				break;
			}
			State = State->update(src,this);
		}
		if (src[indexNum] == '\0')
		{
			break;
		}
	}
	indexNum = 0;
}

void Compiler::LexAnalyzer::clean()
{
	clearTokens();
	comentarys.clear();
	lex.clear();
	m_errorsExcedet = false;
	m_tokensIndex = -1;
	indexNum = -1;
	m_numeberLine = 1;
	State = new LexStateRead;
}

void Compiler::LexAnalyzer::detecteToken(std::string lexema, int line, int type)
{
	Compiler::TOKEN_TYPE tType = Compiler::TOKEN_TYPE::UNDEFINDED;
	switch (type)
	{
	case Compiler::TOKEN_TYPE::ID:
		tType = Compiler::TOKEN_TYPE::ID;
		break;
	case Compiler::TOKEN_TYPE::INT:
		tType = Compiler::TOKEN_TYPE::INT;
		break;
	case Compiler::TOKEN_TYPE::FLOAT:
		tType = Compiler::TOKEN_TYPE::FLOAT;
		break;
	case Compiler::TOKEN_TYPE::LOGIC_OPERATOR:
		tType = Compiler::TOKEN_TYPE::LOGIC_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::UNILATERAL_LOGIC_OPERATOR:
		tType = Compiler::TOKEN_TYPE::UNILATERAL_LOGIC_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR:
		tType = Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATOR:
		tType = Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::AGRUPE_OPERATOR:
		tType = Compiler::TOKEN_TYPE::AGRUPE_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::RELATIVE_OPERATOR:
		tType = Compiler::TOKEN_TYPE::RELATIVE_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::ASIGNATION:
		tType = Compiler::TOKEN_TYPE::ASIGNATION;
		break;
	case Compiler::TOKEN_TYPE::DELIMITER:
		tType = Compiler::TOKEN_TYPE::DELIMITER;
		break;
	case Compiler::TOKEN_TYPE::STRING:
		tType = Compiler::TOKEN_TYPE::STRING;
		break;
	case Compiler::TOKEN_TYPE::COMENTARY:
		tType = Compiler::TOKEN_TYPE::COMENTARY;
		break;
	case Compiler::TOKEN_TYPE::INCREMENT:
		tType = Compiler::TOKEN_TYPE::INCREMENT;
		break;
	case Compiler::TOKEN_TYPE::DECREMENT:
		tType = Compiler::TOKEN_TYPE::DECREMENT;
		break;
	default:
		break;
	}
	for (int i = 0; i < m_keyword.size(); i++)
	{
		if (lexema == m_keyword[i])
		{
			tType = Compiler::TOKEN_TYPE::KEYWORD;
		}
	}
	//if (tType == Compiler::TOKEN_TYPE::ID)
	//{
	//	for (int i = 0; i < lexema.size(); i++)
	//	{
	//		if (!(lexema[i] >= 'a'&&lexema[i] <= 'z') && !(lexema[i] >= 'A'&&lexema[i] <= 'Z') && lexema[i] != '_'&& !(lexema[i] >= '0'&&lexema[i] <= '9'))
	//		{
	//			String^ desc = gcnew String(lexema.c_str());
	//			String^errordes = LEX_INVALID_CHAR;
	//			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
	//			return;//agregar error
	//		}
	//	}
	//}

	//if (tType == Compiler::TOKEN_TYPE::INT)
	//{
	//	for (int i = 0; i < lexema.size(); i++)
	//	{
	//		if (!(lexema[i] >= '0'&&lexema[i] <= '9') && lexema[i] != '-')
	//		{
	//			String^ desc = gcnew String(lexema.c_str());
	//			String^errordes = LEX_INVALID_INT;
	//			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
	//			return;//agregar error
	//			
	//		}
	//	}
	//}
	//if (tType == Compiler::TOKEN_TYPE::FLOAT)
	//{
	//	int numPoints = 0;
	//	for (int i = 0; i < lexema.size(); i++)
	//	{
	//		if (!(lexema[i] >= '0'&&lexema[i] <= '9')&& lexema[i]!='.'&& lexema[i] != '-')
	//		{
	//			String^ desc = gcnew String(lexema.c_str());
	//			String^errordes = LEX_INVALID_FLOAT;
	//			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
	//			return;//agregar error
	//			
	//		}
	//		if (lexema[i] == '.')
	//		{
	//			numPoints++;
	//		}
	//		if (numPoints>1)
	//		{
	//			String^ desc = gcnew String(lexema.c_str());
	//			String^errordes = LEX_INVALID_FLOAT;
	//			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
	//			return;//agregar error
	//			//agregar error
	//			return;
	//		}
	//	}
	//}

	addToken(lexema.c_str(), line, tType);
}

void Compiler::LexAnalyzer::clearTokens()
{
	for (size_t i = 0; i < m_Tokens.size(); i++)
	{
		delete m_Tokens[i];
	}
	m_Tokens.clear();
}

void Compiler::LexAnalyzer::getTokens(std::vector<Token*>* tokensVec)
{

}

Compiler::Token * Compiler::LexAnalyzer::getNextToken()
{
	m_tokensIndex++;
	if (m_tokensIndex >= m_Tokens.size())
	{
		return nullptr;
	}
	return m_Tokens[m_tokensIndex];
}

Compiler::Token * Compiler::LexAnalyzer::getCurrentToken()
{
	if (m_tokensIndex >= m_Tokens.size())
	{
		return nullptr;
	}
	return m_Tokens[m_tokensIndex];
}

Compiler::Token * Compiler::LexAnalyzer::getPrevToken()
{
	m_tokensIndex--;
	if (m_tokensIndex<0)
	{
		m_tokensIndex = 0;
	}
	if (m_Tokens.size()==0)
	{
		return nullptr;
	}
	return m_Tokens[m_tokensIndex];
}

Compiler::Token * Compiler::LexAnalyzer::peeckToken(int idx)
{
	if (idx >= m_Tokens.size() || idx < 0)
	{
		//invalid index
		return nullptr;
	}
	return m_Tokens[idx];
}

Compiler::Token * Compiler::LexAnalyzer::setIndexToken(int idx)
{
	m_tokensIndex = idx;
	return m_Tokens[m_tokensIndex];
}

void Compiler::LexAnalyzer::addToken(std::string lex, int lineNum, TOKEN_TYPE tp)
{
	std::string lexema = lex;
	Compiler::Token*tok = new Compiler::Token(lexema, tp, lineNum);
	m_Tokens.push_back(tok);
}

void Compiler::LexAnalyzer::addComentary(std::string comentary)
{
	comentarys.push_back(comentary);
}

String ^ Compiler::LexAnalyzer::getTokensList()
{
	// TODO: insertar una instrucción return aquí
	String^ str;
	for (int i = 0; i < m_Tokens.size(); i++)
	{
		str += m_Tokens[i]->getLineNumber().ToString();
		str += "\n";
		std::string st = m_Tokens[i]->getLex();
		String^ strr = gcnew String(st.c_str());
		str += strr;
		str += "\n";
		int num = m_Tokens[i]->getType();
		switch (num)
		{
		case UNDEFINDED:
			str += "UNDEFINDED";
			break;
		case KEYWORD:
			str += "KEYWORD";
			break;
		case ID:
			str += "ID";
			break;
		case INT:
			str += "INT";
			break;
		case FLOAT:
			str += "FLOAT";
			break;
		case LOGIC_OPERATOR:
			str += "LOGIC_OPERATOR";
			break;
		case UNILATERAL_LOGIC_OPERATOR:
			str += "UNILATERAL_LOGIC_OPERATOR";
			break;
		case ARITMETIC_OPERATOR:
			str += "ARITMETIC_OPERATOR";
			break;
		case DIMENCIONAL_OPERATOR:
			str += "DIMENCIONAL_OPERATOR";
			break;
		case AGRUPE_OPERATOR:
			str += "GROUPING_OPERATOR";
			break;
		case RELATIVE_OPERATOR:
			str += "RELATIONAL_OPERATOR";
			break;
		case ASIGNATION:
			str += "ASIGNATION";
			break;
		case DELIMITER:
			str += "SEPARATOR";
			break;
		case STRING:
			str += "STRING";
			break;
		case COMENTARY:
			str += "COMENTARY";
			break;
		case INCREMENT:
			str += "INCREMENT";
			break;
		case DECREMENT:
			str += "DECREMENT";
			break;
		default:
			break;
		}
		str += "\n";
	}
	m_numeberLine = 1;
	m_tokensIndex = -1;
	return str;
}
