#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateDelimitator::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);

	std::string newLex;
	newLex = src[lexanalizer->indexNum];
	lexanalizer->detecteToken(newLex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::DELIMITER);
	return new LexStateRead;
}