/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		02/07/2015
	@brief		Classe ajoutant des fonctionnalités aux std::thread
				Samples:	Function:		ThreadTemplate<Args...> NewThread(new FoncterTemplateInstance<CLASS_NULL, void>(&Function));			
							Method:			ThreadTemplate<Args...> NewThread(new FoncterTemplateInstance<Classe, void>(Instance, &Classe::Function));
							Launch thread:	ThreadTemplate.Launch(...Args)

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_THREAD_TEMPLATE_HPP
#define SFGMK_THREAD_TEMPLATE_HPP


namespace gmk
{
	template<typename... Args>
	class ThreadTemplate
	{
		private:
			std::thread* m_Thread;
			FoncterTemplate* m_Function;
			r_bool m_bLaunched;
			r_bool m_bWaited;

			inline r_void Run(Args... _Args)
			{
				m_Function->Execute(_Args...);
			}

		public:
			ThreadTemplate(FoncterTemplate* _Foncter = NULL) : m_Thread(NULL), m_Function(_Foncter), m_bLaunched(false), m_bWaited(false) {}
			~ThreadTemplate() { Wait(); SAFE_DELETE(m_Function); }

			r_bool SetFunc(FoncterTemplate* _Foncter)
			{
				if( m_bLaunched )
					return false;

				m_Function = _Foncter;
				return true;
			}

			r_bool Launch(Args... _Args)
			{
				if( !m_bLaunched && m_Function )
				{
					m_bLaunched = true;
					m_Thread = new std::thread(&ThreadTemplate::Run, this, _Args...);
					return true;
				}

				return false;
			}

			r_void Wait()
			{
				if( m_bLaunched && !m_bWaited )
				{
					m_Thread->join();
					m_bWaited = true;
				}
			}

			r_void Reset()
			{
				if( !m_bLaunched || m_bWaited )
				{
					SAFE_DELETE(m_Thread);
					m_bLaunched = false;;
					m_bWaited = false;
				}
			}

			BOOL Kill() //A utiliser à vos risques et périls
			{
				BOOL bResult(false);

				if( m_bLaunched && !m_bWaited )
					bResult = TerminateThread((HANDLE)m_Thread->native_handle(), 0);

				return bResult;
			}

			inline BOOL SetPriority(const int& _Priority) //Pas certain que ça fonctionne
			{
				if( m_Thread )
					return SetThreadPriority((HANDLE)m_Thread->native_handle(), _Priority);
				return false;
			}
	};
}


#endif