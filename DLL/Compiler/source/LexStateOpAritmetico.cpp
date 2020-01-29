#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateOpAritmetico::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	if (src[lexanalizer->indexNum] == '/'&&src[lexanalizer->indexNum + 1] == '/')
	{
		//comentaryOneLineParse(src, i);
	}
	if (src[lexanalizer->indexNum] == '/'&&src[lexanalizer->indexNum + 1] == '*')
	{
		//comentaryMoreLineParse(src, i);
		lexanalizer->lex.clear();
		lexanalizer->indexNum++;
		lexanalizer->indexNum++;
		lexanalizer->initLine = lexanalizer->m_numeberLine;
		return new LexStateCommentaryMultiLine();
	}
	if (src[lexanalizer->indexNum] == '-'&&src[lexanalizer->indexNum - 1] != ' ')
	{
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR);
		return new LexStateRead;
		//numParse(src, i);
	}
	if (src[lexanalizer->indexNum] == '+'&&src[lexanalizer->indexNum - 1] != ' ')
	{
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR);
		return new LexStateRead;
		//numParse(src, i);
	}
	if (src[lexanalizer->indexNum] == '-'&&src[lexanalizer->indexNum + 1] >= '0'&&src[lexanalizer->indexNum + 1] <= '9')
	{
		lexanalizer->indexNum++;
		return new LexStateNumber();
		//numParse(src, i);
	}
	if (src[lexanalizer->indexNum] == '+'&&src[lexanalizer->indexNum + 1] >= '0'&&src[lexanalizer->indexNum + 1] <= '9')
	{
		lexanalizer->indexNum++;
		return new LexStateNumber();
		//numParse(src, i);
	}
	if (src[lexanalizer->indexNum] == '-'&&src[lexanalizer->indexNum + 1] == '.')
	{
		lexanalizer->indexNum++;
		return new LexStateFloat();
		//floatParse(src, i);
	}
	lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR);
	return new LexStateRead;
}