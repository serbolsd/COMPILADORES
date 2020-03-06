#include "../include/SymbolTable.h"
#include <sstream>
Compiler::SymbolTable::SymbolTable()
{
}

Compiler::SymbolTable::SymbolTable(ErrorModule ^ err)
{
	m_err = err;
}

Compiler::SymbolTable::~SymbolTable()
{
}

void Compiler::SymbolTable::getAllSymbols()
{
}

bool Compiler::SymbolTable::addSymbol(int lineNum, std::string sym, int dim, ESYMBOL_CAT cat, std::string func, std::string tp)
{
	bool esto = symbolExists( lineNum, sym, dim, cat,func,tp);
	if (!esto)
	{
		int index = 0;
		bool find=false;
		for (int i = 0; i < m_symbols.size(); i++)
		{
			if (m_symbols[i]->getSymbol() == sym)
			{
				index = i;
				find = true;
				break;
			}
		}
		if (cat == ESYMBOL_CAT::GLOBAL_VAR)
		{
			if (find)
			{
				m_symbols[index]->setLine(lineNum);
				m_symbols[index]->setSymbol(sym);
				m_symbols[index]->setDim(dim);
				m_symbols[index]->setCat(cat);
				m_symbols[index]->setType(tp);
				m_symbols[index]->setFunction(func);
			}
			else
			{
				GlobalNode* newGlobal = new GlobalNode();
				newGlobal->setLine(lineNum);
				newGlobal->setSymbol(sym);
				newGlobal->setDim(dim);
				newGlobal->setCat(cat);
				newGlobal->setType(tp);
				newGlobal->setFunction(func);
				m_symbols.push_back(newGlobal);
			}
			
			return true;
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		if (cat == ESYMBOL_CAT::FUNCTION)
		{
			if (find)
			{
				m_symbols[index]->setLine(lineNum);
				m_symbols[index]->setSymbol(sym);
				m_symbols[index]->setDim(dim);
				m_symbols[index]->setCat(cat);
				m_symbols[index]->setType(tp);
				m_symbols[index]->setFunction(func);
			}
			else
			{
				GlobalNode* newGlobal = new GlobalNode();
				newGlobal->setLine(lineNum);
				newGlobal->setSymbol(sym);
				newGlobal->setDim(dim);
				newGlobal->setCat(cat);
				newGlobal->setType(tp);
				newGlobal->setFunction(func);
				m_symbols.push_back(newGlobal);
			}
			return true;
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		if (cat == ESYMBOL_CAT::PARAMETER)
		{
			GlobalNode* newGlobal = new GlobalNode();
			//newGlobal->setLine(lineNum);
			newGlobal->setSymbol(sym);
			//newGlobal->setDim(dim);
			newGlobal->setCat(Compiler::ESYMBOL_CAT::UNDEFINE);
			newGlobal->setType("<UNKNOW>");
			//newGlobal->setFunction(func);
			m_symbols.push_back(newGlobal);
			LocalNode *newln = m_symbols[m_symbols.size() - 1]->getNodolocal();
			newln = new LocalNode();
			newln->setLine(lineNum);
			//newln->setSymbol(sym);
			newln->setDim(dim);
			newln->setCat(cat);
			newln->setType(tp);
			newln->setFunc(func);
			m_symbols[m_symbols.size() - 1]->setNodolocal(newln);
			return true;
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		if (cat == ESYMBOL_CAT::LOCAL_VAR)
		{
			GlobalNode* newGlobal = new GlobalNode();
			//newGlobal->setLine(lineNum);
			newGlobal->setSymbol(sym);
			//newGlobal->setDim(dim);
			newGlobal->setCat(Compiler::ESYMBOL_CAT::UNDEFINE);
			newGlobal->setType("<UNKNOW>");
			//newGlobal->setFunction(func);
			m_symbols.push_back(newGlobal);
			LocalNode *newln = m_symbols[m_symbols.size() - 1]->getNodolocal();
			newln = new LocalNode();
			newln->setLine(lineNum);
			//newln->setSymbol(sym);
			newln->setDim(dim);
			newln->setCat(cat);
			newln->setType(tp);
			newln->setFunc(func);
			m_symbols[m_symbols.size() - 1]->setNodolocal(newln);
			return true;
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		//if (cat == ESYMBOL_CAT::LOCAL_VAR)
		//{
		//	//verificar que no exista como parametro de la misma funcion
		//	//verificar que no se llame igual que la funcion
		//	//error
		//}
		//if (cat == ESYMBOL_CAT::PARAMETER)
		//{
		//	//verificar que no se llame igual que una variable de la misma funcion
		//	//verificar que no se llame como una funcion
		//	//error
		//}
	}
	else
	{
		int index;
		for (int i = 0; i < m_symbols.size(); i++)
		{
			if (m_symbols[i]->getSymbol() == sym)
			{
				if ((m_symbols[i]->getCat() == FUNCTION&& cat==FUNCTION)|| (m_symbols[i]->getCat() == GLOBAL_VAR && cat == GLOBAL_VAR))
				{
					m_err->addError(ERROR_PHASE::SYN_ANALYZER, lineNum, "ya se definio el 'ID' en el mismo 'SCOPE' ", gcnew String(sym.c_str()));
					return false;
				}
				if (m_symbols[i]->getCat() == FUNCTION)
				{
					
					{
						m_err->addError(ERROR_PHASE::SYN_ANALYZER, lineNum, "ya se definio el'ID' como funcion ", gcnew String(sym.c_str()));
					}
					return false;
					
				}
				if (m_symbols[i]->getCat() == GLOBAL_VAR && cat == FUNCTION)
				{

					{
						m_err->addError(ERROR_PHASE::SYN_ANALYZER, lineNum, "ya se definio el'ID' como 'GLOBAL VAR' ", gcnew String(sym.c_str()));
					}
					return false;

				}

				index = i;
				break;
				
			}
		}
		if (cat == ESYMBOL_CAT::PARAMETER)
		{
			LocalNode *getln = m_symbols[index]->getNodolocal();
			if (getln == nullptr)
			{
				int index2 = 0;
				bool find2 = false;
				for (int i = 0; i < m_symbols.size(); i++)
				{
					if (m_symbols[i]->getSymbol() == sym)
					{
						index2 = i;
						find2 = true;
						break;
					}
				}
				LocalNode *newln = new LocalNode();
				newln->setLine(lineNum);
				//newln->setSymbol(sym);
				newln->setDim(dim);
				newln->setCat(cat);
				newln->setType(tp);
				newln->setFunc(func);
				m_symbols[index2]->setNodolocal(newln);
				return true;
			}
			LocalNode *getln2 = getln;
			while (getln != nullptr)
			{
				getln2 = getln;
				getln = getln->getNodolocal();
			}
			LocalNode *newln = new LocalNode();
			newln->setLine(lineNum);
			//newln->setSymbol(sym);
			newln->setDim(dim);
			newln->setCat(cat);
			newln->setType(tp);
			newln->setFunc(func);
			getln2->setNodoLocal(newln);
			return true;
			//m_symbols.push_back(newGlobal);
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		if (cat == ESYMBOL_CAT::LOCAL_VAR)
		{
			LocalNode *getln = m_symbols[index]->getNodolocal();
			if (getln== NULL)
			{
				int index2 = 0;
				bool find2 = false;
				for (int i = 0; i < m_symbols.size(); i++)
				{
					if (m_symbols[i]->getSymbol() == sym)
					{
						index2 = i;
						find2 = true;
						break;
					}
				}
				LocalNode *newln = new LocalNode();
				newln->setLine(lineNum);
				//newln->setSymbol(sym);
				newln->setDim(dim);
				newln->setCat(cat);
				newln->setType(tp);
				newln->setFunc(func);
				m_symbols[index2]->setNodolocal(newln);
				return true;
			}
			LocalNode *getln2 = getln;
			while (getln != nullptr)
			{
				getln2 = getln;
				if (getln->getFunc() == func)
				{
					if (getln->getCat() == PARAMETER && getln->getCat() == cat)
					{
						//agregar error ya se definio el parametro
						m_err->addError(ERROR_PHASE::SYN_ANALYZER, lineNum, "ya se definio 'ID' como parametro", gcnew String(sym.c_str()));
					}
					else if (getln->getCat() == PARAMETER)
					{
						//agregar error ya se definio como parametro
						m_err->addError(ERROR_PHASE::SYN_ANALYZER, lineNum, "ya se definio 'ID' como parametro", gcnew String(sym.c_str()));
					}
					return false;
				}
				getln = getln->getNodolocal();
			}
			LocalNode *newln = new LocalNode();
			newln->setLine(lineNum);
			//newln->setSymbol(sym);
			newln->setDim(dim);
			newln->setCat(cat);
			newln->setType(tp);
			newln->setFunc(func);
			getln2->setNodoLocal(newln);
			return true;
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		//agregar error (symbolo ya esta definifo)
		//m_err->addError(ERROR_PHASE::SYN_ANALYZER, lineNum, "ya se definio 'ID' ", gcnew String(sym.c_str()));
	}
	return false;

}

bool Compiler::SymbolTable::symbolExists(int lineNum, std::string sym, int dim, ESYMBOL_CAT cat, std::string func, std::string tp)
{
	bool find = false;
	int index;
	if (m_symbols.size() <= 0)
	{
		return false;
	}
	for (int i = 0; i < m_symbols.size(); i++)
	{
		if (m_symbols[i]->getSymbol() == sym)
		{
			index = i;
			find = true;
			break;
		}
	}
	if (!find)
	{
		return false;
	}
	else
	{
		if (cat == ESYMBOL_CAT::GLOBAL_VAR || cat == ESYMBOL_CAT::FUNCTION)
		{
			if (m_symbols[index]->getCat() == GLOBAL_VAR || m_symbols[index]->getCat() == FUNCTION)
			{
				return true;
			}
			if (m_symbols[index]->getCat()==UNDEFINE)
			{
				LocalNode* n = m_symbols[index]->getNodolocal();
				while (n != nullptr)
				{
					if (m_symbols[index]->getCat() == GLOBAL_VAR || m_symbols[index]->getCat() == FUNCTION)
					{
						//return true;
					}
					else if (cat == ESYMBOL_CAT::FUNCTION)
					{
						n->setType("<UNKNOW>");
						m_err->addError(ERROR_PHASE::SYN_ANALYZER, n->getLine(), "ya se definio 'ID' como funcion ", gcnew String(sym.c_str()));
						m_symbols[index]->setLine(lineNum);
						m_symbols[index]->setSymbol(sym);
						m_symbols[index]->setDim(dim);
						m_symbols[index]->setCat(cat);
						m_symbols[index]->setType(tp);
						m_symbols[index]->setFunction(func);
					}
					else
					{

					}
					n = n->getNodolocal();
				}
						return false;
			}
			return true;
			//return true;
		}
		else
		{
			if (m_symbols[index]->getCat()== FUNCTION || m_symbols[index]->getCat() == GLOBAL_VAR)
			{
				return true;
			}
			//auto it = m_symbols.find(sym);
			//LocalNode * n = it->second->getNodolocal();
			LocalNode* n = m_symbols[index]->getNodolocal();
			while (n != nullptr)
			{
				if (n->getFunc() == func)
				{
					if (n->getCat() == PARAMETER && n->getCat()==cat)
					{
						//agregar error ya se definio el parametro
					}
					else if (n->getCat() == PARAMETER)
					{
						//agregar error ya se definio como parametro
						
					}
					else
					{
						//agregar error ya se definio
					}
						return true;
				}
				n = n->getNodolocal();
			}
			return false;
		}
	}
	return false;
}

void Compiler::SymbolTable::reset()
{
	for (int i = 0; i < m_symbols.size(); i++)
	{
		m_symbols[i]->reset();
		delete m_symbols[i];
		m_symbols[i] = nullptr;
	}
	m_symbols.clear();
}

void * Compiler::SymbolTable::getSymbol(std::string name, ESYMBOL_CAT cat, std::string func)
{
	if (symbolExists(0,name,0,cat,func,""))
	{
		int index = 0;
		for (int i = 0; i < m_symbols.size(); i++)
		{
			if (m_symbols[i]->getSymbol() == name)
			{
				index = i;
				break;
			}
		}
		if (func=="<GLOBAL SCOPE>")
		{
			return m_symbols[index];
		}
		else
		{
			LocalNode* n = m_symbols[index]->getNodolocal();
			while (n != nullptr)
			{
				if (n->getFunc() == func)
				{
					return n;
				}
				n = n->getNodolocal();
			}
		}
	}
	return nullptr;
}
