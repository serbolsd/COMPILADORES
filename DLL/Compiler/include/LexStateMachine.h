#pragma once

#include "Analyzer.h"
namespace Compiler
{
	class LexAnalyzer;
	class LexState
	{
	public:
		LexState() {};
		virtual ~LexState() {};
		virtual LexState *update(const char* src, LexAnalyzer* lexanalizer) { return nullptr; };
		virtual void clearState(LexAnalyzer* lexanalizer);
	private:

	};
}

