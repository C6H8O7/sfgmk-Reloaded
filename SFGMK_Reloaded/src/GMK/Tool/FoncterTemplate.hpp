/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		01/11/2015
	@brief		Classes permettant de créer un conteneur de fonction générique

--------------------------------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef FONCTER_TEMPLATE_HPP
#define FONCTER_TEMPLATE_HPP


#define CLASS_NULL FoncterTemplateNullInstance

namespace gmk
{
	class FoncterTemplateNullInstance
	{

	};

	class FoncterTemplate
	{
		public:
			FoncterTemplate() {}
			virtual ~FoncterTemplate() {}

			//Déclarer ici les prototypes de fonctions
			virtual inline r_void Execute() {}
			virtual inline r_void Execute(const r_int32&) {}
			virtual inline r_void Execute(const r_float&) {}

			virtual inline r_bool Execute(const r_string&) { return false; }	
	};

	template<typename InstanceType, typename T, typename... Args>
	class FoncterTemplateInstance : public FoncterTemplate
	{
		public:
			FoncterTemplateInstance(InstanceType* _Instance, T(InstanceType::*_Method)(Args...)) : m_Instance(_Instance), m_MethodPtr(_Method), m_FunctionPtr(NULL) {} //Constructeur methode
			FoncterTemplateInstance(T(*m_Function)(Args...)) : m_Instance(NULL), m_MethodPtr(NULL), m_FunctionPtr(m_Function) {} //Constructeur fonction
			~FoncterTemplateInstance() {}

		private:
			r_void* m_Instance;
			T(*m_FunctionPtr)(Args...);
			T(InstanceType::*m_MethodPtr)(Args...);

		public:
			inline T Execute(Args... _Args) 
			{ 
				if( m_Instance )
					return (((InstanceType*)(m_Instance))->*m_MethodPtr)(_Args...); 
				else
					return (*m_FunctionPtr)(_Args...);
			}
	};

	class FoncterTemplateArray
	{
		public:
			FoncterTemplateArray() {}
			~FoncterTemplateArray() { m_FunctionsArray.deleteAndClear(); }

			gmk::vector<FoncterTemplate*> m_FunctionsArray;

			inline r_void operator[] (const r_uint32& _Index) { m_FunctionsArray[_Index]->Execute(); }
	};
}


#endif