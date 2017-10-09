#include"gamepause.h"
USING_NS_CC;
Scene* Gamepause::scene(RenderTexture* sqr)
{
	Scene *scene = Scene::create();
	Gamepause * layer = Gamepause::create();
	scene->addChild(layer, 1);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	back_spr->setFlippedY(true);
	back_spr->setColor(Color3B::GRAY);
	scene->addChild(back_spr);
	return scene;
}
bool Gamepause::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MenuItemImage *pContinueItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(Gamepause::menuContinueCallback,this));
	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));
	Menu* pMenu = Menu::create(pContinueItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 2);
	return true;
}
void Gamepause::menuContinueCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}