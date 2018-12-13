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

#ifndef HFCL_CSS_STYLESHEET_H_
#define HFCL_CSS_STYLESHEET_H_

#include "../common/common.h"
#include "../common/stlalternative.h"

#define MAKE_PROPERTY_VALUE(id, type, keyword)  \
    ((DWORD32)(                                 \
        ((DWORD32)((keyword) & 0xFFFF)) |       \
        ((DWORD32)((type) & 0x000F) << 16) |    \
        ((DWORD32)((id) & 0x0FFF) << 20)        \
    ))

#define PROPERTY_VALUE_ID(value)        (((value) & 0xFFF00000) >> 20)
#define PROPERTY_VALUE_TYPE(value)      (((value) & 0x000F0000) >> 16)
#define PROPERTY_VALUE_KEYWORD(value)   ((value) & 0x0000FFFF)

namespace hfcl {

#include "propertiesandvalues.inc"

class PropertyValueSpecified {
public:
    PropertyValueSpecified();
    PropertyValueSpecified(DWORD32 value, HTData data = 0);
    ~PropertyValueSpecified() {};

    DWORD32 getValue() const { return m_value; }
    int getProperty() const { return PROPERTY_VALUE_ID(m_value); }
    int getKeyword() const { return PROPERTY_VALUE_KEYWORD(m_value); }
    int getType() const { return PROPERTY_VALUE_TYPE(m_value); }

    HTData getData() const { return m_data; }
    HTReal getDataAsNumber() const { return (HTReal)m_data; }
    int getDataAsInteger() const { return (int)m_data; }
    const char* getDataAsCString() const { return (const char*)m_data; }

#if 0
    HTReal getComputed () const { return m_computed; }
    void setComputed (HTReal computed) { m_computed = computed; }

    string& getComputedString () const { return m_computed_string; }
    void setComputedString (const string& new_str) {
        m_computed_string = new_str;
    }

    HTReal getUsed () const { return m_used; }
    void setUsed (HTReal used) { m_used = used; }

    string& getUsedString () const { return m_used_str; }
    void setUsedString (const string& new_str) {
        m_used_str = new_str;
    }

    HTReal getActual () const { return m_actual; }
    void setActual (HTReal actual) { m_actual = actual; }
#endif

private:
    DWORD32 m_value;
    HTData m_data;

#if 0
    HTReal m_computed;
    HTReal m_used;
    HTReal m_actual;

    // for URI and other content
    string m_computed_string;
    string m_used_string;
    string m_actual_string;
#endif
};

class PropertyValueComputed {
public:
    PropertyValueComputed();
    PropertyValueComputed(View* view, PropertyValueSpecified* m_specified);
    ~PropertyValueComputed();

    DWORD32 getValue() const { return m_value; }
    int getProperty() const { return PROPERTY_VALUE_ID(m_value); }
    int getKeyword() const { return PROPERTY_VALUE_KEYWORD(m_value); }
    int getType() const { return PROPERTY_VALUE_TYPE(m_value); }

    HTData getData() const { return m_data; }
    HTReal getDataAsNumber() const { return (HTReal)m_data; }
    int getDataAsInteger() const { return (int)m_data; }
    const char* getDataAsCString() const { return (const char*)m_data; }

private:
    DWORD32 m_value;
    HTData m_data;

    PropertyValueSpecified* m_specified;
    View* m_view;
}

class StyleSheet {
public:
    StyleSheet () : m_id (0) {}
    StyleSheet (int id) : m_id (id) {}
    ~StyleSheet () {}

    // Operator for property background-attachment
    bool setBackgroundAttachment (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BACKGROUND_ATTACHMENT, value, addData);
    }

    // Operator for property background-color
    bool setBackgroundColor (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BACKGROUND_COLOR, value, addData);
    }

    // Operator for property background-image
    bool setBackgroundImage (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BACKGROUND_IMAGE, value, addData);
    }

    // Operator for property background-position-x
    bool setBackgroundPositionX (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BACKGROUND_POSITION_X, value, addData);
    }

    // Operator for property background-position-y
    bool setBackgroundPositionY (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BACKGROUND_POSITION_Y, value, addData);
    }

    // Operator for property background-repeat
    bool setBackgroundRepeat (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BACKGROUND_REPEAT, value, addData);
    }

    // Operator for property border-bottom-color
    bool setBorderBottomColor (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_BOTTOM_COLOR, value, addData);
    }

    // Operator for property border-bottom-style
    bool setBorderBottomStyle (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_BOTTOM_STYLE, value, addData);
    }

    // Operator for property border-bottom-width
    bool setBorderBottomWidth (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_BOTTOM_WIDTH, value, addData);
    }

    // Operator for property border-collapse
    bool setBorderCollapse (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_COLLAPSE, value, addData);
    }

    // Operator for property border-left-color
    bool setBorderLeftColor (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_LEFT_COLOR, value, addData);
    }

    // Operator for property border-left-style
    bool setBorderLeftStyle (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_LEFT_STYLE, value, addData);
    }

    // Operator for property border-left-width
    bool setBorderLeftWidth (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_LEFT_WIDTH, value, addData);
    }

    // Operator for property border-right-color
    bool setBorderRightColor (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_RIGHT_COLOR, value, addData);
    }

    // Operator for property border-right-style
    bool setBorderRightStyle (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_RIGHT_STYLE, value, addData);
    }

    // Operator for property border-right-width
    bool setBorderRightWidth (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_RIGHT_WIDTH, value, addData);
    }

    // Operator for property border-spacing
    bool setBorderSpacing (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_SPACING, value, addData);
    }

    // Operator for property border-top-color
    bool setBorderTopColor (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_TOP_COLOR, value, addData);
    }

    // Operator for property border-top-style
    bool setBorderTopStyle (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_TOP_STYLE, value, addData);
    }

    // Operator for property border-top-width
    bool setBorderTopWidth (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BORDER_TOP_WIDTH, value, addData);
    }

    // Operator for property bottom
    bool setBottom (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_BOTTOM, value, addData);
    }

    // Operator for property caption-side
    bool setCaptionSide (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_CAPTION_SIDE, value, addData);
    }

    // Operator for property clear
    bool setClear (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_CLEAR, value, addData);
    }

    // Operator for property clip
    bool setClip (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_CLIP, value, addData);
    }

    // Operator for property color
    bool setColor (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_COLOR, value, addData);
    }

    // Operator for property content
    bool setContent (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_CONTENT, value, addData);
    }

    // Operator for property counter-increment
    bool setCounterIncrement (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_COUNTER_INCREMENT, value, addData);
    }

    // Operator for property counter-reset
    bool setCounterReset (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_COUNTER_RESET, value, addData);
    }

    // Operator for property cursor
    bool setCursor (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_CURSOR, value, addData);
    }

    // Operator for property direction
    bool setDirection (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_DIRECTION, value, addData);
    }

    // Operator for property display
    bool setDisplay (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_DISPLAY, value, addData);
    }

    // Operator for property empty-cells
    bool setEmptyCells (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_EMPTY_CELLS, value, addData);
    }

    // Operator for property float
    bool setFloat (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_FLOAT, value, addData);
    }

    // Operator for property font-family
    bool setFontFamily (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_FONT_FAMILY, value, addData);
    }

    // Operator for property font-size
    bool setFontSize (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_FONT_SIZE, value, addData);
    }

    // Operator for property font-style
    bool setFontStyle (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_FONT_STYLE, value, addData);
    }

    // Operator for property font-variant
    bool setFontVariant (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_FONT_VARIANT, value, addData);
    }

    // Operator for property font-weight
    bool setFontWeight (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_FONT_WEIGHT, value, addData);
    }

    // Operator for property height
    bool setHeight (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_HEIGHT, value, addData);
    }

    // Operator for property left
    bool setLeft (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_LEFT, value, addData);
    }

    // Operator for property letter-spacing
    bool setLetterSpacing (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_LETTER_SPACING, value, addData);
    }

    // Operator for property line-height
    bool setLineHeight (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_LINE_HEIGHT, value, addData);
    }

    // Operator for property list-style-image
    bool setListStyleImage (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_LIST_STYLE_IMAGE, value, addData);
    }

    // Operator for property list-style-position
    bool setListStylePosition (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_LIST_STYLE_POSITION, value, addData);
    }

    // Operator for property list-style-type
    bool setListStyleType (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_LIST_STYLE_TYPE, value, addData);
    }

    // Operator for property margin-bottom
    bool setMarginBottom (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_MARGIN_BOTTOM, value, addData);
    }

    // Operator for property margin-left
    bool setMarginLeft (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_MARGIN_LEFT, value, addData);
    }

    // Operator for property margin-right
    bool setMarginRight (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_MARGIN_RIGHT, value, addData);
    }

    // Operator for property margin-top
    bool setMarginTop (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_MARGIN_TOP, value, addData);
    }

    // Operator for property max-height
    bool setMaxHeight (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_MAX_HEIGHT, value, addData);
    }

    // Operator for property max-width
    bool setMaxWidth (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_MAX_WIDTH, value, addData);
    }

    // Operator for property min-height
    bool setMinHeight (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_MIN_HEIGHT, value, addData);
    }

    // Operator for property min-width
    bool setMinWidth (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_MIN_WIDTH, value, addData);
    }

    // Operator for property orphans
    bool setOrphans (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_ORPHANS, value, addData);
    }

    // Operator for property outline-color
    bool setOutlineColor (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_OUTLINE_COLOR, value, addData);
    }

    // Operator for property outline-style
    bool setOutlineStyle (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_OUTLINE_STYLE, value, addData);
    }

    // Operator for property outline-width
    bool setOutlineWidth (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_OUTLINE_WIDTH, value, addData);
    }

    // Operator for property overflow
    bool setOverflow (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_OVERFLOW, value, addData);
    }

    // Operator for property padding-bottom
    bool setPaddingBottom (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_PADDING_BOTTOM, value, addData);
    }

    // Operator for property padding-left
    bool setPaddingLeft (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_PADDING_LEFT, value, addData);
    }

    // Operator for property padding-right
    bool setPaddingRight (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_PADDING_RIGHT, value, addData);
    }

    // Operator for property padding-top
    bool setPaddingTop (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_PADDING_TOP, value, addData);
    }

    // Operator for property page-break-after
    bool setPageBreakAfter (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_PAGE_BREAK_AFTER, value, addData);
    }

    // Operator for property page-break-before
    bool setPageBreakBefore (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_PAGE_BREAK_BEFORE, value, addData);
    }

    // Operator for property page-break-inside
    bool setPageBreakInside (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_PAGE_BREAK_INSIDE, value, addData);
    }

    // Operator for property position
    bool setPosition (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_POSITION, value, addData);
    }

    // Operator for property quotes
    bool setQuotes (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_QUOTES, value, addData);
    }

    // Operator for property right
    bool setRight (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_RIGHT, value, addData);
    }

    // Operator for property table-layout
    bool setTableLayout (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_TABLE_LAYOUT, value, addData);
    }

    // Operator for property text-align
    bool setTextAlign (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_TEXT_ALIGN, value, addData);
    }

    // Operator for property text-decoration
    bool setTextDecoration (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_TEXT_DECORATION, value, addData);
    }

    // Operator for property text-indent
    bool setTextIndent (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_TEXT_INDENT, value, addData);
    }

    // Operator for property text-transform
    bool setTextTransform (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_TEXT_TRANSFORM, value, addData);
    }

    // Operator for property top
    bool setTop (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_TOP, value, addData);
    }

    // Operator for property unicode-bidi
    bool setUnicodeBidi (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_UNICODE_BIDI, value, addData);
    }

    // Operator for property vertical-align
    bool setVerticalAlign (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_VERTICAL_ALIGN, value, addData);
    }

    // Operator for property visibility
    bool setVisibility (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_VISIBILITY, value, addData);
    }

    // Operator for property white-space
    bool setWhiteSpace (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_WHITE_SPACE, value, addData);
    }

    // Operator for property widows
    bool setWidows (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_WIDOWS, value, addData);
    }

    // Operator for property width
    bool setWidth (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_WIDTH, value, addData);
    }

    // Operator for property word-spacing
    bool setWordSpacing (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_WORD_SPACING, value, addData);
    }

    // Operator for property z-index
    bool setZIndex (DWORD32 value, HTData addData = 0) {
        return setProperty (PID_Z_INDEX, value, addData);
    }

protected:
    bool setProperty (PropertyIds id, DWORD32 value, HTData addData = 0);

private:
    MAPCLASSKEY(PropertyIds, PropertyValueSpecified, PropertyValueMap);
    PAIR(PropertyIds, PropertyValueSpecified, PropertyValuePair);

    int m_id;
    PropertyValueMap m_map;
}

namespace css {

} // namespace css

} // namespace hfcl

#endif /* HFCL_CSS_STYLESHEET_H_ */

