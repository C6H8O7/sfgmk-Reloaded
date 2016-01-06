GameObjectComponent::GameObjectComponent(r_string _type, GameObject * _parent)
	: type_name(_type), parent(_parent), active(true), unique(true), deletion(false)
{
	
}

GameObjectComponent::~GameObjectComponent()
{
#ifdef SFGMKR_EDITOR
	m_Properties.deleteAndClear();
#endif
}

#ifdef SFGMKR_EDITOR
r_void GameObjectComponent::beginRegister()
{
	registerProperty(ePROPERTY_TYPE::TYPE_CATEGORY, type_name, 0, 0);
}

GameObjectComponent::ComponentProperty* GameObjectComponent::registerProperty(ePROPERTY_TYPE _type, r_string _name, r_void* _pData, r_bool* _pChanged, r_bool _readOnly)
{
	ComponentProperty* cproperty = new ComponentProperty();

	cproperty->name = _name;
	cproperty->data = _pData;
	cproperty->type = _type;
	cproperty->wxProperty = 0;
	cproperty->read_only = _readOnly;
	cproperty->changed = _pChanged;

	m_Properties.push_back(cproperty);

	return cproperty;
}

r_void GameObjectComponent::endRegister()
{
	registerProperty(ePROPERTY_TYPE::TYPE_BOOL, "Delete", &deletion, 0);
}
#endif

r_void GameObjectComponent::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void GameObjectComponent::OnComponentUpdate(SFMLCanvas * _canvas)
{
	OnUpdate(_canvas);

	if (deletion)
	{
#ifdef SFGMKR_EDITOR
		OnPropertiesDisapparition();

		MyGUI* gui = MyGUI::GetGUI();

		if (gui->selectedGameObjectComponent == this)
			gui->selectedGameObjectComponent = 0;
#endif
		parent->removeComponent(this);
	}
}

r_void GameObjectComponent::OnMembersUpdate()
{

}

r_void GameObjectComponent::OnDraw(SFMLCanvas* _canvas)
{

}

#ifdef SFGMKR_EDITOR
r_void GameObjectComponent::OnRegistration()
{

}

r_void GameObjectComponent::OnPropertiesUpdate()
{
	wxPropertyGrid* grid = MyGUI::GetGUI()->GUI_PropertyGrid;

	for (r_uint32 i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* cproperty = m_Properties[i];
		const r_int8* cname = (const r_int8*)cproperty->name.c_str();

		sf::Color* color = 0;

		if (cproperty->wxProperty == grid->GetSelectedProperty())
			continue;

		switch (cproperty->type)
		{
			case ePROPERTY_TYPE::TYPE_FLOAT:
				cproperty->wxProperty->SetValue(wxVariant(*(r_float*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_INT:
				cproperty->wxProperty->SetValue(wxVariant(*(r_int32*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_STRING:
				cproperty->wxProperty->SetValue(wxVariant(((r_string*)cproperty->data)->c_str()));
				break;

			case ePROPERTY_TYPE::TYPE_COLOR:
				color = (sf::Color*)cproperty->data;
				cproperty->wxProperty->SetValue(wxVariant(wxColour(color->r, color->g, color->b, color->a)));
				break;

			case ePROPERTY_TYPE::TYPE_BOOL:
				cproperty->wxProperty->SetValue(wxVariant(*(r_bool*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_ENUM:
				cproperty->wxProperty->SetValue(wxVariant(*(r_int32*)cproperty->data));
				break;
		}
	}
}

r_void GameObjectComponent::OnPropertiesApparition()
{
	wxPropertyGrid* grid = MyGUI::GetGUI()->GUI_PropertyGrid;

	for (r_uint32 i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* cproperty = m_Properties[i];

		const r_int8* cname = (const r_int8*)cproperty->name.c_str();

		r_string strnameRand = cproperty->name + std::to_string((r_int32)cproperty);
		const r_int8* cnameRand = strnameRand.c_str();

		sf::Color* color = 0;

		switch (cproperty->type)
		{
			case ePROPERTY_TYPE::TYPE_CATEGORY:
				cproperty->wxProperty = grid->Append(new wxPropertyCategory(cname, cnameRand));
				break;

			case ePROPERTY_TYPE::TYPE_FLOAT:
				cproperty->wxProperty = grid->Append(new wxFloatProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(*(r_float*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_INT:
				cproperty->wxProperty = grid->Append(new wxIntProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(*(r_int32*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_STRING:
				cproperty->wxProperty = grid->Append(new wxStringProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(((r_string*)cproperty->data)->c_str()));
				break;

			case ePROPERTY_TYPE::TYPE_COLOR:
				color = (sf::Color*)cproperty->data;
				cproperty->wxProperty = grid->Append(new wxColourProperty(cname, cnameRand));
				cproperty->wxProperty->SetAttribute(wxPG_COLOUR_HAS_ALPHA, true);
				cproperty->wxProperty->SetValue(wxVariant(wxColour(color->r, color->g, color->b, color->a)));
				break;

			case ePROPERTY_TYPE::TYPE_BOOL:
				cproperty->wxProperty = grid->Append(new wxBoolProperty(cname, cnameRand));
				cproperty->wxProperty->SetAttribute(wxPG_BOOL_USE_CHECKBOX, true);
				cproperty->wxProperty->SetValue(wxVariant(*(r_bool*)cproperty->data));
				break;

			case ePROPERTY_TYPE::TYPE_ENUM:
				cproperty->wxProperty = grid->Append(new wxEnumProperty(cname, cnameRand));
				cproperty->wxProperty->SetValue(wxVariant(*(r_int32*)cproperty->data));
				cproperty->wxProperty->SetChoices(cproperty->wxChoices);
				break;
		}

		if (cproperty->wxProperty)
			cproperty->wxProperty->Enable(!cproperty->read_only);
	}
}

r_void GameObjectComponent::OnPropertiesDisapparition()
{
	wxPropertyGrid* grid = MyGUI::GetGUI()->GUI_PropertyGrid;

	for (r_uint32 i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* cproperty = m_Properties[i];

		if (cproperty->wxProperty && cproperty->type == ePROPERTY_TYPE::TYPE_CATEGORY)
		{
			grid->DeleteProperty(cproperty->wxProperty);
			cproperty->wxProperty = 0;
		}
	}
}

r_void GameObjectComponent::OnUnegistration()
{
	
}

r_void GameObjectComponent::OnPropertyGridChanged(wxPropertyGridEvent& _event)
{
	wxPGProperty* prop = _event.GetProperty();

	for (r_uint32 i = 0; i < m_Properties.getElementNumber(); i++)
	{
		ComponentProperty* component_prop = m_Properties[i];

		wxColour color;

		if (component_prop->wxProperty == prop)
		{
			switch (component_prop->type)
			{
				case ePROPERTY_TYPE::TYPE_FLOAT:
					*(r_float*)component_prop->data = (r_float)prop->GetValue().GetDouble();
					break;

				case ePROPERTY_TYPE::TYPE_INT:
					*(r_int32*)component_prop->data = (r_int32)prop->GetValue().GetInteger();
					break;

				case ePROPERTY_TYPE::TYPE_STRING:
					*(r_string*)component_prop->data = (const r_int8*)prop->GetValue().GetString().c_str();
					break;

				case ePROPERTY_TYPE::TYPE_COLOR:
					color = ((wxAny)prop->GetValue()).As<wxColour>();
					*(sf::Color*)component_prop->data = sf::Color(color.Red(), color.Green(), color.Blue(), color.Alpha());
					break;

				case ePROPERTY_TYPE::TYPE_BOOL:
					*(r_bool*)component_prop->data = (r_bool)prop->GetValue().GetBool();
					break;

				case ePROPERTY_TYPE::TYPE_ENUM:
					*(r_int32*)component_prop->data = (r_int32)prop->GetValue().GetInteger();
					break;
			}

			if (component_prop->changed)
				*component_prop->changed = true;
			
			OnMembersUpdate();
		}
	}
}

r_void GameObjectComponent::OnEditorUpdate()
{

}
#endif

r_void GameObjectComponent::OnXMLSave(tinyxml2::XMLElement* _element)
{

}

r_void GameObjectComponent::OnXMLLoad(tinyxml2::XMLElement* _element)
{

}