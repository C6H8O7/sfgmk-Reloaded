/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		05/02/2016
	@brief		Classe mère des steering components

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_HPP
#define SFGMKR_COMPONENT_STEERING_HPP

#include "stdafx.h"


template<typename T>
class ComponentSteering : public GameObjectComponent
{
	public:
		ComponentSteering(const r_string& _typeName, GameObject* _parent) 
			: GameObjectComponent(_typeName, _parent), m_Steering(_parent), m_fSteeringWeight(STEERING_DEFAULT_WEIGHT), m_bSteeringWeightChanged(false), m_sTargetName(""), m_bTargetNameChanged(false)
		{
			if( parent->steeringPtr )
				parent->steeringPtr->addBehavior(&m_Steering, STEERING_DEFAULT_WEIGHT);
		}

		virtual ~ComponentSteering() 
		{
			if( parent->steeringPtr )
				parent->steeringPtr->removeBehavior(&m_Steering);
		}


		virtual r_void OnMembersUpdate()
		{
			if( m_bSteeringWeightChanged )
			{
				m_bSteeringWeightChanged = false;
				parent->steeringPtr->modifyBehaviorWeight(&m_Steering, m_fSteeringWeight);
			}

			if( m_bTargetNameChanged )
			{
				m_bTargetNameChanged = false;
				m_Steering.setTarget(SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_sTargetName));
			}
		}

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration()
		{
			registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Weight", &m_fSteeringWeight, &m_bSteeringWeightChanged);
			registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Target", &m_sTargetName, &m_bTargetNameChanged);
		}
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element)
		{
			_element->SetAttribute("weight", m_fSteeringWeight);
			_element->SetAttribute("target", m_sTargetName.c_str());
		}
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element)
		{
			m_fSteeringWeight = _element->FloatAttribute("weight");
			m_bSteeringWeightChanged = true;
			m_sTargetName = _element->Attribute("target");
			m_bTargetNameChanged = true;
		}

	protected:
		T m_Steering;

		r_float m_fSteeringWeight;
		r_bool m_bSteeringWeightChanged;

		r_string m_sTargetName;
		r_bool m_bTargetNameChanged;
};


#endif