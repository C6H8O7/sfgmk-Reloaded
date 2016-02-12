/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		09/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_NEURONAL_NETWORK_HPP
#define SFGMKR_COMPONENT_NEURONAL_NETWORK_HPP

#include "stdafx.h"


class ComponentNeuronalNetwork : public GameObjectComponent
{
	public:
		ComponentNeuronalNetwork(GameObject* _parent);
		~ComponentNeuronalNetwork();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:
		vector<unsigned> m_Topology;
		vector<double> m_Results;

		C_RESEAU* m_Network;

		r_string m_sTargetName;
		r_bool m_bTargetChanged;
		GameObject* m_Target;
};


#endif