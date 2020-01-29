#include "../include/LexStates.h"
#include "../include/LexAnalyzer.h"

Compiler::LexState * Compiler::LexStateCommentaryMultiLine::update(const char * src, LexAnalyzer * lexanalizer)
{
	clearState(lexanalizer);
	lexanalizer->lex += src[lexanalizer->indexNum];
	lexanalizer->indexNum++;
	if ((src[lexanalizer->indexNum] == '\r' || src[lexanalizer->indexNum] == '\n'))
	{
		if (src[lexanalizer->indexNum] == '\r'&&src[lexanalizer->indexNum + 1] == '\n')
		{
			//lex += src[i];
			lexanalizer->indexNum++;
			lexanalizer->m_numeberLine++;
		}
		else
		{
			lexanalizer->m_numeberLine++;
		}
	}
	if (src[lexanalizer->indexNum]=='*'&&src[lexanalizer->indexNum+1]=='/')
	{
		lexanalizer->indexNum++;
		lexanalizer->addComentary(lexanalizer->lex);
		return new LexStateRead();
	}
	if (src[lexanalizer->indexNum] == '\0')
	{
		//error de que no se cerro el comentario
		String^ desc = gcnew String(lexanalizer->lex.c_str());
		String^errordes = LEX_COMMENT_NOT_CLOSED;
		lexanalizer->m_errorsExcedet = lexanalizer->m_refErrorMod->addError(lexanalizer->m_phase, lexanalizer->initLine, errordes, desc);
		return nullptr;
	}
	return new LexStateCommentaryMultiLine();
}