#pragma once
#pragma execution_character_set("utf-8")

#include "HpBar.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

HpBar::HpBar()
{
    // nop
}

HpBar::~HpBar()
{
    this->_bar_green->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE_NULL(this->_bar_green);

    this->_bar_yellow->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE_NULL(this->_bar_yellow);

    this->_bar_red->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE_NULL(this->_bar_red);

    this->_frame->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE_NULL(this->_frame);
}

bool HpBar::init(const int bar_width, const int bar_height, const unsigned int max)
{
    if (!Node::init())
    {
        return false;
    }

    this->_max = max;
    //this->_current = max;

    // ゲージのフレーム部分の作成
    const Rect outer_rect(0, 0, 24, 24);
    const Rect inner_rect(1, 1, 22, 22);
    
    this->_frame = Scale9Sprite::create("hp_frame.png", outer_rect, inner_rect);
    this->_frame->getTexture()->setAliasTexParameters();
    this->_frame->setContentSize(Size(bar_width, bar_height));
    
    this->addChild(this->_frame);

    // 残りの画像をロード
    this->loadResources();

    // 緑色のバーを設定しておく
    this->_bar_current = this->_bar_green;
    this->_frame->addChild(this->_bar_green);

    // 初期値を設定
    this->changeValue(this->_max);

    return true;
}

HpBar * HpBar::create(const int bar_width, const int bar_height, const unsigned int max)
{
    HpBar *pRet = new(std::nothrow) HpBar();
    if (pRet && pRet->init(bar_width, bar_height, max))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

void HpBar::changeValue(const unsigned int value)
{
    if (this->_current == value)
    {
        return; // 現在地と同じなら無視
    }

    // 色が変わったときはバーの入れ替え
    Sprite* newSprite = this->getSprite(value);
    if (this->_bar_current != newSprite)
    {
        this->_bar_current->removeFromParent();
        this->_bar_current = newSprite;
        this->_frame->addChild(this->_bar_current);
    }

    // 管理値の最大値に対する現在値の比率を計算
    float ratio = (float)value / this->_max;

    // 新しいゲージの横幅
    float newWidth = (this->_frame->getBoundingBox().size.width - 2) * ratio;
    float newHeight = this->_frame->getBoundingBox().size.height - 2;

    // 現在のバーサイズを変更
    this->_bar_current->setContentSize(Size(newWidth, newHeight));

    this->_current = value;
}

void HpBar::changeMax(const unsigned int max, const unsigned int value)
{
    this->_max = max;
    this->changeValue(value);
}

void HpBar::loadResources()
{
    this->_bar_green = this->loadSprite("hp_bar_green.png");
    this->_bar_yellow = this->loadSprite("hp_bar_yellow.png");
    this->_bar_red = this->loadSprite("hp_bar_red.png");
}

Sprite* HpBar::loadSprite(const string& name)
{
    auto sp = Sprite::create(name);
    
    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sp->setPosition(Vec2(1, 1));
    sp->getTexture()->setAliasTexParameters();
    sp->retain();

    return sp;
}

cocos2d::Sprite * HpBar::getSprite(const unsigned int value)
{
    if (value >= this->_max)
    {
        return this->_bar_green; // 最大値
    }

    float ratio = (float)value / this->_max;

    if (ratio < 0.25f)
    {
        return this->_bar_red;
    }
    else if (ratio < 0.5f)
    {
        return this->_bar_yellow;
    }

    return this->_bar_green;
}
