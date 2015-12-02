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
void ComponentTransform::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pos X", &parent->transform.position.x, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pos Y", &parent->transform.position.y, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Scale X", &parent->transform.scale.x, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Scale Y", &parent->transform.scale.y, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Rotation", &parent->transform.rotation, 0);
}
#endif