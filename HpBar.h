#pragma once
#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "ui\UIScale9Sprite.h"

class HpBar : public cocos2d::Node
{
    // ゲージの枠
    cocos2d::ui::Scale9Sprite* _frame = nullptr;

    // 各色バーと現在表示中のバー
    cocos2d::Sprite* _bar_green = nullptr;
    cocos2d::Sprite* _bar_yellow = nullptr;
    cocos2d::Sprite* _bar_red = nullptr;
    cocos2d::Sprite* _bar_current = nullptr;

    unsigned int _max;
    unsigned int _current;

public:

    // いつもの
    HpBar();

    // いつもの
    ~HpBar();

    // いつもの
    virtual bool init(const int bar_width, const int bar_height, const unsigned int max);

    // いつもの
    static HpBar* create(const int bar_width, const int bar_height, const unsigned int max);

    // バーの量を変更する
    void changeValue(const unsigned int value);

    // 新しい最大値と値を設定して表示を更新する
    void changeMax(const unsigned int max, const unsigned int value);

private:

    // 使用するリソースの読み込み
    void loadResources();

    // バーのロード
    cocos2d::Sprite* loadSprite(const std::string& name);

    // 指定した値に対応するバーのSpriteを取得する
    cocos2d::Sprite* getSprite(const unsigned int value);
};