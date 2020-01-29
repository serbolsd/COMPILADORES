#pragma once
#include "LexStateMachine.h"
namespace Compiler
{
	class LexStateRead : public LexState
	{
	public:
		LexStateRead() {};
		~LexStateRead() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;
		
	private:

	};
	class LexStateDelimitator : public LexState
	{
	public:
		LexStateDelimitator() {};
		~LexStateDelimitator() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:

	};
	class LexStateOpAritmetico: public LexState
	{
	public:
		LexStateOpAritmetico() {};
		~LexStateOpAritmetico() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:

	};
	class LexStateCommentaryMultiLine : public LexState
	{
	public:
		LexStateCommentaryMultiLine() {};
		~LexStateCommentaryMultiLine() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;
	private:

	};
	class LexStateNumber : public LexState
	{
	public:
		LexStateNumber() {};
		~LexStateNumber() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:

	};
	class LexStateFloat : public LexState
	{
	public:
		LexStateFloat() {};
		~LexStateFloat() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:

	};
	class LexStateOpLogic: public LexState
	{
	public:
		LexStateOpLogic() {};
		~LexStateOpLogic() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:

	};
	class LexStateOpRelacional : public LexState
	{
	public:
		LexStateOpRelacional() {};
		~LexStateOpRelacional() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:

	};
	class LexStateString : public LexState
	{
	public:
		LexStateString() {};
		~LexStateString() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:

	};
	class LexStateID : public LexState
	{
	public:
		LexStateID() {};
		~LexStateID() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:

	};
	class LexStateIncremento : public LexState
	{
	public:
		LexStateIncremento() {};
		~LexStateIncremento() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:
	};
	class LexStateDecremento : public LexState
	{
	public:
		LexStateDecremento() {};
		~LexStateDecremento() {};
		LexState *update(const char* src, LexAnalyzer* lexanalizer) override;

	private:
	};
}