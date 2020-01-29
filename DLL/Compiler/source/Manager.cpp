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
	cli::array<String^>^compilationdetails;
	compilationdetails = gcnew cli::array<String^>(4);
	TokenLex = m_lexico->getTokensList();
	String^ outErrors=nullptr;
	if (m_lexico->m_errorsExcedet)
	{
		for (int i = 0; i < m_errors->getErrors()->Length; i++)
		{
			// Concatenate in strings the group of line, lexem and type
			outErrors += m_errors->getErrors()[i] + "\r\n";
		}

		compilationdetails[0] = gcnew String("---DEMASIADOS ERRORES, NO SE PUDO TERMINAR DE COMPILAR---");
		compilationdetails[1] = gcnew String(TokenLex);
		compilationdetails[2] = gcnew String(outErrors);
		compilationdetails[3] = gcnew String(SymbolTable);
	}
	else
	{
		for (int i = 0; i < m_errors->m_numErrors; i++)
		{
			// Concatenate in strings the group of line, lexem and type
			outErrors += m_errors->getErrors()[i] + "\r\n";
		}

		compilationdetails[0] = gcnew String("---COMILER OK---");
		compilationdetails[1] = gcnew String(TokenLex);
		compilationdetails[2] = gcnew String(outErrors);
		compilationdetails[3] = gcnew String(SymbolTable);
	}
	return compilationdetails;
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
	if (m_lexico != nullptr); {
		m_lexico->clean();
		delete m_lexico;
	}
}

cli::array<String^>^ Compiler::Manager::compileProgram(String ^ srcCode)
{

	clean();
	lexAnalysis(srcCode);
	
	return getCompilationItems();
	// TODO: insertar una instrucción return aquí
}
