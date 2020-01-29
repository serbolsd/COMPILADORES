#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"
Compiler::LexState * Compiler::LexStateRead::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->indexNum++;
	lexanalizer->lex.clear();
	if ((src[lexanalizer->indexNum] == '\r' || src[lexanalizer->indexNum] == '\n'))
	{
		//salto de linea
		if (src[lexanalizer->indexNum] == '\r'&&src[lexanalizer->indexNum + 1] == '\n')
		{
			lexanalizer->indexNum++;
			lexanalizer->m_numeberLine++;
			return new LexStateRead;
		}
		else
		{
			lexanalizer->m_numeberLine++;
			return new LexStateRead;

		}
	}
	//Espacio o tabulacion
	if (src[lexanalizer->indexNum] == ' ' || src[lexanalizer->indexNum] == '\t')
	{
		return new LexStateRead;
	}
	for (int j = 0; j < lexanalizer->delimitador.size(); j++)
	{
		if (src[lexanalizer->indexNum] == lexanalizer->delimitador[j])
		{
			return new LexStateDelimitator;
		}
	}
	for (int j = 0; j < lexanalizer->op_arit.size(); j++)
	{

		if (src[lexanalizer->indexNum] == lexanalizer->op_arit[j])
		{
			return new LexStateOpAritmetico;
		}
	}
	for (int j = 0; j < lexanalizer->op_dim.size(); j++)
	{
		if (src[lexanalizer->indexNum] == lexanalizer->op_dim[j])
		{
			std::string newstring;
			newstring = src[lexanalizer->indexNum];
			lexanalizer->detecteToken(newstring, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATOR);
			return new LexStateRead();
		}
	}
	for (int j = 0; j < lexanalizer->op_agrup.size(); j++)
	{
		if (src[lexanalizer->indexNum] == lexanalizer->op_agrup[j])
		{
			std::string newstring;
			newstring = src[lexanalizer->indexNum];
			lexanalizer->detecteToken(newstring, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::AGRUPE_OPERATOR);
			return new LexStateRead();
		}
	}
	for (int j = 0; j < lexanalizer->op_log.size(); j++)
	{
		if (src[lexanalizer->indexNum] == lexanalizer->op_log[j])
		{
			return new LexStateOpLogic();
		}
	}
	for (int j = 0; j < lexanalizer->op_rel.size(); j++)
	{
		if (src[lexanalizer->indexNum] == lexanalizer->op_rel[j])
		{
			return new LexStateOpRelacional();
		}
	}
	//string
	if (src[lexanalizer->indexNum] == '"')
	{
		return new LexStateString;
		//stringParse(src, i);
	}
	//ID
	if (((src[lexanalizer->indexNum] >= 'a'&&src[lexanalizer->indexNum] <= 'z') || (src[lexanalizer->indexNum] >= 'A'&&src[lexanalizer->indexNum] <= 'Z') || src[lexanalizer->indexNum] == '_'))
	{
		return new LexStateID;
		//letrasParse(src, i);
	}
	//numero
	if ((src[lexanalizer->indexNum] >= '0'&&src[lexanalizer->indexNum] <= '9'))
	{
		return new LexStateNumber();
	}
	//float
	if ((src[lexanalizer->indexNum] == '.'))
	{
		return new LexStateFloat();
	}
	//end
	if (src[lexanalizer->indexNum] == '\0')
	{
		return nullptr;
	}

	std::string error;
	error = src[lexanalizer->indexNum];
	String^ desc = gcnew String(error.c_str());
	String^errordes = LEX_INVALID_CHAR;
	lexanalizer->m_errorsExcedet = lexanalizer->m_refErrorMod->addError(lexanalizer->m_phase, lexanalizer->m_numeberLine, errordes, desc);
	return new LexStateRead();
}
