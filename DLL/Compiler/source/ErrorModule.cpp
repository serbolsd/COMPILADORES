#include "../include/ErrorModule.h"

using namespace System;
Compiler::ErrorModule::ErrorModule()
{
	m_numErrors = 0;
	m_errorsArray = gcnew cli::array<String^>(MAX_ERRORS);
	for (int i = 0; i < MAX_ERRORS; i++)
	{
		m_errorsArray[i] = gcnew String("");
	}
}

Compiler::ErrorModule::~ErrorModule()
{

}

void Compiler::ErrorModule::clean()
{
	m_numErrors = 0;
	m_errorsArray->Clear;
	return Void();
}

bool Compiler::ErrorModule::addError(ERROR_PHASE phase, int lineNumber, String ^ errorDesc, String ^ errorLine)
{
	if (m_numErrors < (MAX_ERRORS - 1))
	{
		m_errorsArray->SetValue(String::Format("{0}: {1}{2}{3}", phase.ToString(),"Line: " +lineNumber + " ","Error desc: " +errorDesc + " ", "Erro: "+errorLine + " "), m_numErrors);
		m_numErrors++;
		return false;
	}
	return true;
}

Void Compiler::ErrorModule::clearErrors()
{
	return Void();
}
