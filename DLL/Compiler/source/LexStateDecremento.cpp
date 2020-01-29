#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"


Compiler::LexState * Compiler::LexStateDecremento::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, TOKEN_TYPE::DECREMENT);
	return new LexStateRead;
}