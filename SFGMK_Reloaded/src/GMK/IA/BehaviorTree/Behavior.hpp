/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		20/03/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include "stdafx.h"


namespace gmk
{
	#define BEHAVIOR_FUNCTIONS_NUMBER 3U

	enum eBEHAVIOR_STATUS
	{
		BH_NOT_INITIALISED = 0,
		BH_RUNNING,
		BH_TERMINATING,
		BH_SUCCESS,
		BH_FAILURE,
		BH_ABORTED
	};

	class Behavior
	{
		public:
			Behavior();
			virtual ~Behavior();

			virtual r_void reInit();

			const eBEHAVIOR_STATUS& process(const r_float& _DeltaTime);

			virtual const eBEHAVIOR_STATUS& initialise(const r_float& _DeltaTime) = 0;
			virtual const eBEHAVIOR_STATUS& update(const r_float& _DeltaTime) = 0;
			virtual const eBEHAVIOR_STATUS& terminate(const r_float& _DeltaTime) = 0;

			const eBEHAVIOR_STATUS& getStatus() const;

			r_void setParent(Behavior* _Parent);

		protected:
			Behavior* m_Parent;
			eBEHAVIOR_STATUS m_Status;
			const eBEHAVIOR_STATUS& (Behavior::*m_Functions[BEHAVIOR_FUNCTIONS_NUMBER])(const r_float&) = { &Behavior::initialise, &Behavior::update, &Behavior::terminate };
	};

	struct stBEHAVIOR_STATUS
	{
		eBEHAVIOR_STATUS Status;
		Behavior* Behavior;
	};
}


#endif