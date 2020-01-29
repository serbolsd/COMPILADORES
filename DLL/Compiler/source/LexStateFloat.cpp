#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateFloat::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	lexanalizer->indexNum++;
	if (!(src[lexanalizer->indexNum] >= '0' && src[lexanalizer->indexNum] <= '9'))
	{
		if ((lexanalizer->lex[lexanalizer->lex.size() - 1] == '.'))
		{
			lexanalizer->lex += src[lexanalizer->indexNum];
			String^ desc = gcnew String(lexanalizer->lex.c_str());
			String^errordes = LEX_INVALID_FLOAT;
			lexanalizer->m_errorsExcedet = lexanalizer->m_refErrorMod->addError(lexanalizer->m_phase, lexanalizer->m_numeberLine, errordes, desc);
			if (src[lexanalizer->indexNum]=='.')
			{
				lexanalizer->indexNum--;
				lexanalizer->indexNum++;
			}
			else
			{
				lexanalizer->indexNum--;
			}
		}
		else
		{
			lexanalizer->detecteToken(lexanalizer->lex, lexanalizer->m_numeberLine, Compiler::TOKEN_TYPE::FLOAT);
			lexanalizer->indexNum--;

		}
		return new LexStateRead();
	}
	return new LexStateFloat();
}