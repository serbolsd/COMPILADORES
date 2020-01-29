#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateString::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	lexanalizer->indexNum++;

	if (src[lexanalizer->indexNum] == '"')
	{
		lexanalizer->lex += src[lexanalizer->indexNum];
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::STRING);
		return new LexStateRead();
	}
	if (src[lexanalizer->indexNum] == '\r' || src[lexanalizer->indexNum] == '\n' || src[lexanalizer->indexNum] == '\0')
	{
		String^ desc = gcnew String(lexanalizer->lex.c_str());
		String^errordes = LEX_STRING_NOT_CLOSED;
		lexanalizer->m_errorsExcedet = lexanalizer->m_refErrorMod->addError(lexanalizer->m_phase, lexanalizer->m_numeberLine, errordes, desc);
		lexanalizer->indexNum--;
		return new LexStateRead;
	}
	return new LexStateString();
}
