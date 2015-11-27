GameObjectComponent::GameObjectComponent(GameObject * _parent)
	: parent(_parent), active(true), unique(true)
{

}

GameObjectComponent::~GameObjectComponent()
{

}

void GameObjectComponent::beginRegister()
{
	MyGUI* gui = MyGUI::GetGUI();
	
	wxPropertyGrid* grid = gui->GUI_PropertyGrid;
}

void GameObjectComponent::registerProperty()
{

}

void GameObjectComponent::endRegister()
{

}