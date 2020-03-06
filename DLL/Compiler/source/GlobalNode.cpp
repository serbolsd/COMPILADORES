#include "../include/GlobalNode.h"

Compiler::GlobalNode::GlobalNode()
{
}

Compiler::GlobalNode::~GlobalNode()
{
}

void Compiler::GlobalNode::reset()
{
	if (m_val != nullptr)
	{
		delete m_val;
	}
	if (m_nodolocal != nullptr)
	{
		m_nodolocal->reset();
		delete m_nodolocal;
	}
	m_nodolocal = nullptr;
}