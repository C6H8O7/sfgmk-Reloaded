ComponentTransform::ComponentTransform(GameObject * _parent)
	: GameObjectComponent("Transform", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentTransform::~ComponentTransform()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentTransform::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pos X", &parent->transform.position.x, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pos Y", &parent->transform.position.y, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Scale X", &parent->transform.scale.x, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Scale Y", &parent->transform.scale.y, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Rotation", &parent->transform.rotation, 0);
}
#endif

r_void ComponentTransform::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("position_x", parent->transform.position.x);
	_element->SetAttribute("position_y", parent->transform.position.y);

	_element->SetAttribute("scale_x", parent->transform.scale.x);
	_element->SetAttribute("scale_y", parent->transform.scale.y);

	_element->SetAttribute("rotation", parent->transform.rotation);
}

r_void ComponentTransform::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	parent->transform.position.x = _element->FloatAttribute("position_x");
	parent->transform.position.y = _element->FloatAttribute("position_y");

	parent->transform.scale.x = _element->FloatAttribute("scale_x");
	parent->transform.scale.y = _element->FloatAttribute("scale_y");

	parent->transform.rotation = _element->FloatAttribute("rotation");
}