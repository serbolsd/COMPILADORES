#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateNumber::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	lexanalizer->indexNum++;
	if (!(src[lexanalizer->indexNum] >= '0' && src[lexanalizer->indexNum] <= '9'))
	{
		if (src[lexanalizer->indexNum] == '.')
		{
			//detecteToken(lex, Compiler::TOKEN_TYPE::INT);
			//floatParse(src, i, lex);
			return new LexStateFloat();
		}
		lexanalizer->indexNum--;
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::INT);
		lexanalizer->lex.clear();
		return new LexStateRead();
	}
	return new LexStateNumber();
}