/*
** HFCL - HybridOS Foundation Class Library
**
** Copyright (C) 2018 Beijing FMSoft Technologies Co., Ltd.
**
** This file is part of HFCL.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#ifndef  _BUSYLISTVIEW_H
#define  _BUSYLISTVIEW_H

namespace hfcl {

////////////////////// Features /////////////////////////
class BitMark;
class PointerKeeper;
class PanelView;

////////////////////// Features /////////////////////////
// 1. equal item height.
// 2. special hilight item height.
// 3. same item view template.
// 4. scrollbar support.
// 5. panelview's features.
//
class BusyListView : public PanelView
{
    public:
        ///////////// Constructor/Destructor
        BusyListView(View* parent);
        BusyListView(View* parent, DrawableSet* drset);
        virtual ~BusyListView();

        ///////////// item ops
        bool addItem(void);
        bool addItem(void* addData);
        bool addItemByIndex(int index);
        bool addItemByIndex(int index, void* addData);
        bool removeItem(int index);
        int itemCount(void);
        ///////////// set/get normal item height
        bool setItemHeight(int height);
        int itemHeight(void);
        ////////////// set/get hilight item height
        bool setHilightItemHeight(int height);
        int hilightItemHeight(void);
        ////////////// ui item
        void setItemTemplateId(int item_res_id);
        ////////////// hilight item
        void hilight(int index);
        void hilight(int index, bool focus);
        int hilightItemIndex(void);
        bool isFocused(void){return m_focus;}
        View* hilightItem(void);
        View* itemFromIndex(int index);
        ////////////// dispatch event
        virtual bool dispatchEvent(Event* event);
        //virtual bool setRect(const IntRect& irc);
        void reLayout(int index);
        void reLayout(void);

        void setScrollGap(int gapWidth){m_scrollGap = gapWidth;}
        int scrollGap(void){return m_scrollGap;}

        void setItemRowGap(int gapHeight){m_itemRowGap = gapHeight;}
        int itemRowGap(void){return m_itemRowGap;}

        ////////////// scrollbar related
        void setScrollbarWidth(int w);
        int scrollbarWidth(void);
        void setScrollbarMarginRight(int m);
        int scrollbarMarginRight(void);
        ///////////// re-load data
        int reLoadData(void);
        ///////////// clear
        void clear(void);
        ///////////// freeze
        void freeze(bool f);
        ///////////// status & addData
        void initSelectMark(int count);
        void selectItem(int index, bool sel);
        void select(int index, bool sel);
        void selectAll(bool sel);
        bool isItemSelected(int index);
        void initItemAddData(int count);
        void setItemAddData(int index, void* data);
        void* itemAddData(int index);

        void setScrollBarFloating(bool b) { m_bScrollFloating = b; }
        bool isScrollBarFloating(void) { return m_bScrollFloating; }
        void setSpecialItemIndex(int index){m_special_item_index = index;}
    protected:
        void init(void);
        void reInit(void);

        virtual void prepareVisibleItems(bool add_one = true, bool clean = false);

        ////////////// key process
        bool onKeyPressed(int keyCode);

        void   setHilightView(View* view);

        ////////////// draw ops
        virtual void drawContent(GraphicsContext* context, IntRect &rc, int status);
        virtual void drawScroll(GraphicsContext* context, IntRect &rc, int status);

        ////////////// layout
        virtual void layoutDownToUp(int from_height = -1, int hilight_index = 1);
        virtual void layoutUpToDown(int from_height = 0, int hilight_index = 1);

        ////////////// load data notify
        virtual void onLoadItemData(int index, View* view);

        ////////////// item ops
        virtual View* firstVisibleItem(void);
        virtual View* lastVisibleItem(void);
        virtual int getVisibleItemCountNeed(void);

    private:

    private:
        /// item count
        int m_item_count;
        /// normal item height
        int m_nm_height;
        /// hilight item height
        int m_hi_height;
        /// special item count
        int m_special_item_index;
        /// visible item count
        int m_visible_item_count;
        /// item view template id
        unsigned int m_item_templete_id;
        /// up index
        int m_up_index;
        /// down index
        int m_down_index;
        /// hi index
        int m_hi_index;
        /// items ready ?
        bool m_items_enough;
        /// scrollbar margin right
        int m_v_scrollbar_margin_right;
        /// scrollbar width
        int m_v_scrollbar_width;
        /// top dock - true, bottom dock - false
        int m_dock_top;
        /// freeze mark
        bool m_freeze;
        /// select mark
        BitMark m_select_mark;
        /// add data keeper
        PointerKeeper m_data_keeper;
        // the gap from item to scroll.
        int m_scrollGap;
        int m_itemRowGap;

        bool  m_focus;
        bool  m_bScrollFloating;

        DECLARE_CLASS_NAME(BusyListView)
};

} // namespace hfcl

#endif
