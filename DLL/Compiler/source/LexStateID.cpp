#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateID::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	lexanalizer->indexNum++;
	if (!((src[lexanalizer->indexNum] >= 'a'&&src[lexanalizer->indexNum] <= 'z') || 
		(src[lexanalizer->indexNum] >= 'A'&&src[lexanalizer->indexNum] <= 'Z') || 
		src[lexanalizer->indexNum] == '_' || (src[lexanalizer->indexNum] >= '0'&& src[lexanalizer->indexNum] <= '9')))
	{
		//if (lex[lex.size() - 1] == '_')
		//{
		//
		//	String^ desc = gcnew String(lex.c_str());
		//	String^errordes = LEX_INVALID_CHAR;
		//	m_errorsExcedet = m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
		//}
		//else
		//{
		//	detecteToken(lex, m_numeberLine, Compiler::TOKEN_TYPE::ID);
		//}
		lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::ID);
		lexanalizer->indexNum--;
		return new LexStateRead();
	}
	return new LexStateID();
}