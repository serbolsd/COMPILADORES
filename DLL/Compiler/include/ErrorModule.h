#pragma once

#include "windows.h"

using namespace System;

namespace Compiler {
	#define  MAX_ERRORS 30
	public enum class ERROR_PHASE
	{
		GLOBAL,
		LEX_ANALYZER,
		SYN_ANALYZER,
		SEM_ANALYZER,
		CODE_GENERATION
	};
	public ref class ErrorModule
	{
	public:
		ErrorModule();
		~ErrorModule();
		void clean(); 
		cli::array<String^>^getErrors()
		{
			return m_errorsArray;
		}
		bool addError(ERROR_PHASE phase, int lineNumber, String^errorDesc, String^errorLine);
		Void clearErrors();
	private:
		int m_numErrors;
		cli::array<String^>^m_errorsArray;
		
	};
}