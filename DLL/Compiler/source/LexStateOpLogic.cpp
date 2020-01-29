#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateOpLogic::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	lexanalizer->indexNum++;
	if (src[lexanalizer->indexNum-1] == '|'&&src[lexanalizer->indexNum] == '|')
	{
		lexanalizer->lex += src[lexanalizer->indexNum];
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
	}
	else if (src[lexanalizer->indexNum-1] == '&'&&src[lexanalizer->indexNum] == '&')
	{
		lexanalizer->lex += src[lexanalizer->indexNum];
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
	}
	else
	{
		//agregar error
		lexanalizer->indexNum--;
		std::string error;
		error += src[lexanalizer->indexNum];
		String^ desc = gcnew String(error.c_str());
		String^errordes = LEX_INVALID_OP_LOG;
		lexanalizer->m_errorsExcedet = lexanalizer->m_refErrorMod->addError(lexanalizer->m_phase, lexanalizer->m_numeberLine, errordes, desc);
	}
	lexanalizer->lex.clear();
	return new LexStateRead();
}