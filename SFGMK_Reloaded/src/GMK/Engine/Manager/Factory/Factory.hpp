/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		28/01/2016
	@brief		Classe permettant l'instanciation dynamique de prefabs (notamment depuis les scripts)

--------------------------------------------------------------------------------------------------*/

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "stdafx.h"


namespace gmk
{
	class Factory : public SingletonTemplate<Factory>
	{
		friend class SingletonTemplate<Factory>;

		private:
			Factory();
			~Factory();

			std::unordered_map<r_string, Prefab*> m_Prefabs;
			std::unordered_map<r_string, r_uint32> m_PrefabsAccount;

		public:
			r_void loadPrefabs(const r_string& _Path);
			r_void savePrefabs(const r_string& _Path);
			r_bool addPrefabToBank(GameObject* _Model);
			r_bool createPrefab(GameObject* _Model, bool _save);
			r_bool removePrefab(const r_string& _PrefabId);
			r_bool applyChangesToPrefab(GameObject* _Model);

			GameObject* instantiate(const r_string& _PrefabId, GameObject* _NewGameObject = NULL);

			GameObject* duplicate(GameObject* _selectedGameObject);

			r_bool prefabExists(const r_string& _Name);
	};
}


#endif