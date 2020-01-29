#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateOpRelacional::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	lexanalizer->indexNum++;
	if (src[lexanalizer->indexNum] == '=')
	{
		lexanalizer->lex += src[lexanalizer->indexNum];
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::RELATIVE_OPERATOR);
		lexanalizer->lex.clear();
		return new LexStateRead();
	}
	else if (src[lexanalizer->indexNum-1] == '!')
	{
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::UNILATERAL_LOGIC_OPERATOR);
	}
	else if (src[lexanalizer->indexNum-1] == '=')
	{
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::ASIGNATION);
	}
	else
	{
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::RELATIVE_OPERATOR);
	}
	lexanalizer->lex.clear();
	lexanalizer->indexNum--;
	return new LexStateRead();
}