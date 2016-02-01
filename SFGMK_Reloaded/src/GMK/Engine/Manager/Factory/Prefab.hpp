/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		28/01/2016
	@brief		Classe de stockage d'un modèle de game object

--------------------------------------------------------------------------------------------------*/

#ifndef PREFAB_HPP
#define PREFAB_HPP

#include "stdafx.h"


namespace gmk
{
	class Prefab
	{
		friend class Factory;

		private:
			Prefab(tinyxml2::XMLElement* _Xml);
			Prefab(GameObject* _Model);
			~Prefab();

			void loadFromXml(tinyxml2::XMLElement* _Xml);

			GameObject* m_GameObject;

			GameObject* getGameObject();
	};
}


#endif