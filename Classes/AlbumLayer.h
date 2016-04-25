//
//  AlumLayer.h
//  ayh
//
//  Created by liuhui on 16/4/23.
//
//

#ifndef __ayh__AlumLayer__
#define __ayh__AlumLayer__

#include <cocos2d.h>
#include <cocos-ext.h>
#include <vector>
USING_NS_CC;
USING_NS_CC_EXT;


class AlbumLayer: public LayerColor, public TableViewDataSource
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(AlbumLayer);
    Size cellSizeForTable(TableView*);
    TableViewCell* tableCellAtIndex(TableView*, ssize_t);
    ssize_t numberOfCellsInTableView(TableView*);
    
public:
    float m_width;
    float m_height;
    TableView* tv;

};
#endif /* defined(__ayh__AlumLayer__) */
