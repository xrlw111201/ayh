//
//  AlumLayer.cpp
//  ayh
//
//  Created by liuhui on 16/4/23.
//
//
#include "AlbumLayer.h"
#include "Global.h"

Scene* AlbumLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = AlbumLayer::create();
    scene->addChild(layer);
    return scene;
}

bool AlbumLayer::init()
{
    if ( !LayerColor::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_width = visibleSize.width;
    m_height = visibleSize.height;
    
    /*
    tv = TableView::create(this, visibleSize);
//        tv->setAnchorPoint(Point(0, 0));
    tv->setPosition(0, 0);
    addChild(tv);
    return true;*/
}

Size AlbumLayer::cellSizeForTable(TableView *table){
    return Size(m_width, m_height/5);
}
/*
TableViewCell* cell = table->dequeueCell();
if(NULL == cell){
    cell = TableViewCell::create();
    cell->autorelease();
    
    for(int i=0; i<3; i++){
        Label* lbl = Label::create();
        lbl->setTextColor(Color4B::WHITE);
        lbl->setSystemFontSize(40.00);
        lbl->setAnchorPoint(Point(0, 0));
        lbl->setHorizontalAlignment(TextHAlignment::CENTER);
        lbl->setTag(100+i);
        float x = lbl->getPositionX();
        lbl->setPositionX(x+i*m_width/3);
        cell->addChild(lbl);
    }
}
*/
/*
 TableViewCell* cell = table->dequeueCell();
 if(NULL == cell){
 cell = TableViewCell::create();
 
 for(int i=0; i<3; i++){
 Label* lbl = Label::create();
 lbl->setTextColor(Color4B::WHITE);
 lbl->setSystemFontSize(40.00);
 lbl->setAnchorPoint(Point(0, 0));
 lbl->setHorizontalAlignment(TextHAlignment::CENTER);
 lbl->setTag(100+i);
 float x = lbl->getPositionX();
 lbl->setPositionX(x+i*m_width/3);
 cell->addChild(lbl);
 }
 }
 ((Label*)cell->getChildByTag(100))->setString(StringUtils::format("Label %ld-1", idx));
 ((Label*)cell->getChildByTag(101))->setString(StringUtils::format("Label %ld-2", idx));
 ((Label*)cell->getChildByTag(102))->setString(StringUtils::format("Label %ld-3", idx));
 return cell;
 */
TableViewCell* AlbumLayer::tableCellAtIndex(TableView *table, ssize_t idx){
    

    TableViewCell* cell = table->dequeueCell();
    Sprite* s = NULL;
    if(NULL == cell){

        cell = TableViewCell::create();
        cell->removeAllChildren();
        for(int i=0; i<3; i++){

        }
    }else{

    }
    return cell;
}

ssize_t AlbumLayer::numberOfCellsInTableView(TableView *table){
//    unsigned long count = Global::g_vecAlbum.size();
//    log("*******%lu******%lu******", count, (count+2)/3);
//    return (count+2)/3;
    return 20;
}







