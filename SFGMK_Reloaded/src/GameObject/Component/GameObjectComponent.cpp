GameObjectComponent::GameObjectComponent(std::string _type, GameObject * _parent)
	: type_name(_type), parent(_parent), active(true), unique(true), deletion(false)
{
	
}

GameObjectComponent::~GameObjectComponent()
{
	m_Properties.deleteAndClear();
}

void GameObjectComponent::beginRegister()
{
	registerProperty(ePROPERTY_TYPE::TYPE_CATEGORY, type_name, 0, 0);
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
	registerProperty(ePROPERTY_TYPE::TYPE_BOOL, "Delete", &deletion, 0);
}

void GameObjectComponent::OnUpdate()
{

}

void GameObjectComponent::OnComponentUpdate()
{
	OnUpdate();

	if (deletion)
	{
		OnPropertiesDisapparition();
		parent->removeComponent(this);
	}
}

void GameObjectComponent::OnDraw(sf::RenderWindow* _render)
{

}

void GameObjectComponent::OnRegistration()
{

}

void GameObjectComponent::OnPropertiesUpdate()
{
	wxPropertyGrid* grid = MyGUI::GetGUI()->GUI_PropertyGrid;

	for (unsigned int i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* cproperty = m_Properties[i];
		const char* cname = (const char*)cproperty->name.c_str();

		sf::Color* color = 0;

		switch (cproperty->type)
		{
			case ePROPERTY_TYPE::TYPE_FLOAT:
				cproperty->wxProperty->SetValue(wxVariant(*(float*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_INT:
				cproperty->wxProperty->SetValue(wxVariant(*(int*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_STRING:
				cproperty->wxProperty->SetValue(wxVariant(((std::string*)cproperty->data)->c_str()));
				break;

			case ePROPERTY_TYPE::TYPE_COLOR:
				color = (sf::Color*)cproperty->data;
				cproperty->wxProperty->SetValue(wxVariant(wxColor(color->r, color->g, color->b, color->a)));
				break;

			case ePROPERTY_TYPE::TYPE_BOOL:
				cproperty->wxProperty->SetValue(wxVariant(*(bool*)cproperty->data));
				break;
		}
	}
}

void GameObjectComponent::OnPropertiesApparition()
{
	wxPropertyGrid* grid = MyGUI::GetGUI()->GUI_PropertyGrid;

	for (unsigned int i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* cproperty = m_Properties[i];

		const char* cname = (const char*)cproperty->name.c_str();

		std::string strnameRand = cproperty->name + std::to_string((int)cproperty);
		const char* cnameRand = strnameRand.c_str();

		sf::Color* color = 0;

		switch (cproperty->type)
		{
			case ePROPERTY_TYPE::TYPE_CATEGORY:
				cproperty->wxProperty = grid->Append(new wxPropertyCategory(cname, cnameRand));
				break;

			case ePROPERTY_TYPE::TYPE_FLOAT:
				cproperty->wxProperty = grid->Append(new wxFloatProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(*(float*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_INT:
				cproperty->wxProperty = grid->Append(new wxIntProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(*(int*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_STRING:
				cproperty->wxProperty = grid->Append(new wxStringProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(((std::string*)cproperty->data)->c_str()));
				break;

			case ePROPERTY_TYPE::TYPE_COLOR:
				color = (sf::Color*)cproperty->data;
				cproperty->wxProperty = grid->Append(new wxColourProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(wxColor(color->r, color->g, color->b, color->a)));
				break;

			case ePROPERTY_TYPE::TYPE_BOOL:
				cproperty->wxProperty = grid->Append(new wxBoolProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(*(bool*)cproperty->data));
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

		wxColor color;

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

				case ePROPERTY_TYPE::TYPE_COLOR:
					color = ((wxAny)prop->GetValue()).As<wxColour>();
					*(sf::Color*)component_prop->data = sf::Color(color.Red(), color.Green(), color.Blue(), color.Alpha());
					break;

				case ePROPERTY_TYPE::TYPE_BOOL:
					*(bool*)component_prop->data = (bool)prop->GetValue().GetBool();
					break;
			}

			if (component_prop->changed)
				*component_prop->changed = true;
		}
	}
}

void GameObjectComponent::OnXMLSave(tinyxml2::XMLElement* _element)
{

}

void GameObjectComponent::OnXMLLoad(tinyxml2::XMLElement* _element)
{

}