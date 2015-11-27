GameObjectComponent::GameObjectComponent(std::string _type, GameObject * _parent)
	: type(_type), parent(_parent), active(true), unique(true)
{
	
}

GameObjectComponent::~GameObjectComponent()
{

}

void GameObjectComponent::beginRegister()
{
	ComponentProperty* cproperty = new ComponentProperty();

	cproperty->name = type;
	cproperty->type = ePROPERTY_TYPE::TYPE_CATEGORY;
	cproperty->wxProperty = 0;
	cproperty->changed = 0;

	m_Properties.push_back(cproperty);
}

void GameObjectComponent::registerProperty(ePROPERTY_TYPE _type, std::string _name, void* _pData, bool* _pChanged)
{
	ComponentProperty* cproperty = new ComponentProperty();

	cproperty->name = _name;
	cproperty->data = _pData;
	cproperty->type = _type;
	cproperty->wxProperty = 0;
	cproperty->changed = _pChanged;

	m_Properties.push_back(cproperty);
}

void GameObjectComponent::endRegister()
{

}

void GameObjectComponent::OnUpdate()
{

}

void GameObjectComponent::OnDraw()
{

}

void GameObjectComponent::OnRegistration()
{

}

void GameObjectComponent::OnPropertiesApparition()
{
	wxPropertyGrid* grid = MyGUI::GetGUI()->GUI_PropertyGrid;

	for (unsigned int i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* cproperty = m_Properties[i];
		const char* cname = (const char*)cproperty->name.c_str();

		switch (cproperty->type)
		{
			case ePROPERTY_TYPE::TYPE_CATEGORY:
				cproperty->wxProperty = grid->Append(new wxPropertyCategory(cname, cname));
				break;

			case ePROPERTY_TYPE::TYPE_FLOAT:
				cproperty->wxProperty = grid->Append(new wxFloatProperty(cname, cname));
				cproperty->wxProperty->SetValue(wxVariant(*(float*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_INT:
				cproperty->wxProperty = grid->Append(new wxIntProperty(cname, cname));
				cproperty->wxProperty->SetValue(wxVariant(*(int*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_STRING:
				cproperty->wxProperty = grid->Append(new wxStringProperty(cname, cname));
				cproperty->wxProperty->SetValue(wxVariant(((std::string*)cproperty->data)->c_str()));
				break;
		}
	}
}

void GameObjectComponent::OnPropertiesDisapparition()
{
	wxPropertyGrid* grid = MyGUI::GetGUI()->GUI_PropertyGrid;

	for (unsigned int i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* cproperty = m_Properties[i];

		wxPGProperty* prop = cproperty->wxProperty;

		if(prop && cproperty->type == ePROPERTY_TYPE::TYPE_CATEGORY)
			grid->DeleteProperty(prop);
	}
}

void GameObjectComponent::OnUnegistration()
{
	
}

void GameObjectComponent::OnPropertyGridChanged(wxPropertyGridEvent& _event)
{
	wxPGProperty* prop = _event.GetProperty();

	for (unsigned int i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* component_prop = m_Properties[i];

		if (component_prop->wxProperty == prop)
		{
			switch (component_prop->type)
			{
				case ePROPERTY_TYPE::TYPE_FLOAT:
					*(float*)component_prop->data = (float)prop->GetValue().GetDouble();
					break;

				case ePROPERTY_TYPE::TYPE_INT:
					*(int*)component_prop->data = (int)prop->GetValue().GetInteger();
					break;

				case ePROPERTY_TYPE::TYPE_STRING:
					*(std::string*)component_prop->data = (const char*)prop->GetValue().GetString().c_str();
					break;
			}

			if (component_prop->changed)
				*component_prop->changed = true;
		}
	}
}