#include "../include/Manager.h" 
#include "../include/ErrorModule.h"
void Compiler::Manager::lexAnalysis(String ^ srcCode)
{
	if (m_lexico!=nullptr)
	{
		m_lexico->parseSourceCode((const char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(srcCode).ToPointer());
	}
}

cli::array<String^>^ Compiler::Manager::getCompilationItems()
{
	cli::array<String^>^ test= gcnew cli::array<String^>(1);
	test[0] = gcnew String("si jala wei");
	return test;
	// TODO: insertar una instrucción return aquí
}

void Compiler::Manager::clean()
{
	if (m_lexico != nullptr); {
		m_lexico->clean();
	}
	if (m_errors!=nullptr)
	{
		m_errors->clean();
	}
}

Compiler::Manager::Manager()
{

	m_errors = gcnew ErrorModule();
	m_lexico = new LexAnalyzer(m_errors);
}

Compiler::Manager::~Manager()
{
}

cli::array<String^>^ Compiler::Manager::compileProgram(String ^ srcCode)
{
	clean();
	lexAnalysis(srcCode);
	return getCompilationItems();
	// TODO: insertar una instrucción return aquí
}
