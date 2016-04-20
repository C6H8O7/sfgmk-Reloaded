#include "stdafx.h"


ComponentNeuronalNetwork::ComponentNeuronalNetwork(GameObject* _parent)
	: GameObjectComponent("NeuronalNetwork", _parent), m_sTargetName(""), m_bTargetChanged(false), m_Target(NULL)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Topology.push_back(6);
	m_Topology.push_back(2);
	m_Topology.push_back(3);

	m_Network = new C_RESEAU(m_Topology);

	double L_Erreur;

	for( int i(0); i < 2048 * 128; i++ )
	{
		L_Erreur = 0;

		/*m_Network->Run({ 0.5, 0.5, 0.0, 0.0, 0.0, 0.0 });
		m_Network->Retropropagation({ 1.0, 1.0, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();

		m_Network->Run({ 0.5, 0.5, 0.0, 1.0, 0.0, 0.0 });
		m_Network->Retropropagation({ -1.0, 1.0, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();

		m_Network->Run({ 0.5, 0.5, 0.0, 0.0, 1.0, 0.0 });
		m_Network->Retropropagation({ 1.0, -1.0, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();

		m_Network->Run({ 0.5, 0.5, 0.0, 1.0, 1.0, 0.0 });
		m_Network->Retropropagation({ -1.0, -1.0, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();

		m_Network->Run({ 0.5, 0.5, 0.0, 0.25, 0.25, 0.0 });
		m_Network->Retropropagation({ 1.0, 1.0, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();

		m_Network->Run({ 0.5, 0.5, 0.0, 0.75, 0.25, 0.0 });
		m_Network->Retropropagation({ -1.0, 1.0, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();

		m_Network->Run({ 0.5, 0.5, 0.0, 0.25, 0.75, 0.0 });
		m_Network->Retropropagation({ 1.0, -1.0, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();

		m_Network->Run({ 0.5, 0.5, 0.0, 0.75, 0.75, 0.0 });
		m_Network->Retropropagation({ -1.0, -1.0, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();*/


		r_vector2f PositionTarget((r_float)RAND(0, 1280), (r_float)RAND(0, 720));
		r_vector2f MyPosition((r_float)RAND(0, 1280), (r_float)RAND(0, 720));
		r_vector2f Vector = PositionTarget - MyPosition;

		double SolutionX;
		double SolutionY;

		if( Vector.x > 0 )
			SolutionX = 1.0f;
		else 
			SolutionX = -1.0f;

		if( Vector.y > 0 )
			SolutionY = 1.0f;
		else
			SolutionY = -1.0f;

		m_Network->Run({ PositionTarget.x / 1280.0 , PositionTarget.y / 720.0, 0.0, MyPosition.x / 1280.0, MyPosition.y / 720.0, 0.0 });
		m_Network->Retropropagation({ SolutionX, SolutionY, 0.0 });
		L_Erreur += m_Network->Get_Erreur_Moyenne();
	}
}

ComponentNeuronalNetwork::~ComponentNeuronalNetwork()
{
	m_Topology.clear();
	m_Results.clear();

	delete m_Network;
}


r_void ComponentNeuronalNetwork::OnUpdate(SFMLCanvas * _canvas)
{
	if( m_Target )
	{
		r_vector2f ParentPosition(parent->getCenter());
		r_vector2f TargetPosition(m_Target->getCenter());
		m_Network->Run({ ParentPosition.x / 1280.0, ParentPosition.y / 720.0, 0.0, TargetPosition.x / 1280.0, TargetPosition.y / 720.0, 0.0 });
		m_Network->Get_Sorties(m_Results);

		double dX(m_Results[0]);
		double dY(m_Results[1]);

		/*if( dY > 0.0 )
			std::cout << "Haut";
		else if( dY < 0.0 )
			std::cout << "Bas";

		if( dX > 0.0 )
			std::cout << " Gauche";
		else if( dX < 0.0 )
			std::cout << " Droite";*/

		r_float fDeltaTime = gmk::TimeManager::GetSingleton()->getDeltaTime();
		r_vector2f Translation = r_vector2f((r_float)(1.0f * -dX), (r_float)(1.0f * -dY));
		parent->transform.move(Translation * fDeltaTime * 100.0f);

	//	std::cout << '\t' << dX << '\t' << dY << std::endl;

		//std::cout << std::endl;
	}
}

r_void ComponentNeuronalNetwork::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentNeuronalNetwork::OnMembersUpdate()
{
	if( m_bTargetChanged )
	{
		m_bTargetChanged = false;
		m_Target =
		SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_sTargetName);
	}
}


#ifdef SFGMKR_EDITOR
r_void ComponentNeuronalNetwork::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Target", &m_sTargetName, &m_bTargetChanged);

	endRegister();
}
#endif


r_void ComponentNeuronalNetwork::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("target", m_sTargetName.c_str());
}

r_void ComponentNeuronalNetwork::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_sTargetName = _element->Attribute("target");
	m_bTargetChanged = true;
}