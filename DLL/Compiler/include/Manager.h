#pragma once

#include "windows.h"
#include "ErrorModule.h"
#include "LexAnalyzer.h"
using namespace System;

namespace Compiler {
	public ref class Manager
	{

	private:
		void lexAnalysis(String ^ srcCode);
		//void sinAnalysis(String ^ srcCode);
		LexAnalyzer *m_lexico=nullptr;
		ErrorModule ^m_errors;
		//SymbolTable* symTable = nullptr;
		//SyntaxAnalysis * sin;
		//SemanticAnalysis * sem;
		cli::array<String^>^ getCompilationItems();
		void clean();
	public:
		Manager();
		~Manager();
		cli::array<String^>^compileProgram(String^srcCode);
		String^ TokenLex;
		String^ SymbolTable;


		// TODO: Agregar aquí los métodos de la clase.
	};
}
