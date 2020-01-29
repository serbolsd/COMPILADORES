#include "LexStateMachine.h"
#include "LexAnalyzer.h"
void Compiler::LexState::clearState(LexAnalyzer * lexanalizer)
{
	delete lexanalizer->State;
}
