/****************************************************************************
** Copyright (c) 2013 Debao Zhang <hello@debao.me>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#include "xlsxformat.h"

namespace QXlsx {

Format::Format()
{
    m_font.bold = false;
    m_font.color = QColor(Qt::black);
    m_font.italic = false;
    m_font.name = "Calibri";
    m_font.scirpt = FontScriptNormal;
    m_font.size = 11;
    m_font.strikeOut = false;
    m_font.underline = FontUnderlineNone;
    m_font.shadow = false;
    m_font.outline = false;
    m_font.family = 2;
    m_font.scheme = "minor";
    m_font.charset = 0;
    m_font.condense = 0;
    m_font.extend = 0;
    m_font.redundant = false;
    m_font.index = 0;

    m_alignment.alignH = AlignHGeneral;
    m_alignment.alignV = AlignBottom;
    m_alignment.wrap = false;
    m_alignment.rotation = 0;
    m_alignment.indent = 0;
    m_alignment.shinkToFit = false;

    m_is_dxf_fomat = false;

    m_xf_index = 0;
    m_dxf_index = 0;

    m_num_format_index = 0;
    m_theme = 0;
    m_color_indexed = 0;

    m_has_fill = false;
    m_fill_index = 0;

    m_has_borders = false;
    m_border_index = false;
}

int Format::fontSize() const
{
    return m_font.size;
}

void Format::setFontSize(int size)
{
    m_font.size = size;
}

bool Format::fontItalic() const
{
    return m_font.italic;
}

void Format::setFontItalic(bool italic)
{
    m_font.italic = italic;
}

bool Format::fontStrikeOut() const
{
    return m_font.strikeOut;
}

void Format::setFontStricOut(bool stricOut)
{
    m_font.strikeOut = stricOut;
}

QColor Format::fontColor() const
{
    return m_font.color;
}

void Format::setFontColor(const QColor &color)
{
    m_font.color = color;
}

bool Format::fontBold() const
{
    return m_font.bold;
}

void Format::setFontBold(bool bold)
{
    m_font.bold = bold;
}

Format::FontScript Format::fontScript() const
{
    return m_font.scirpt;
}

void Format::setFontScript(FontScript script)
{
    m_font.scirpt = script;
}

Format::FontUnderline Format::fontUnderline() const
{
    return m_font.underline;
}

void Format::setFontUnderline(FontUnderline underline)
{
    m_font.underline = underline;
}

bool Format::fontOutline() const
{
    return m_font.outline;
}

void Format::setFontOutline(bool outline)
{
    m_font.outline = outline;
}

QString Format::fontName() const
{
    return m_font.name;
}

void Format::setFontName(const QString &name)
{
    m_font.name = name;
}

Format::HorizontalAlignment Format::horizontalAlignment() const
{
    return m_alignment.alignH;
}

void Format::setHorizontalAlignment(HorizontalAlignment align)
{
    if (m_alignment.indent &&(align != AlignHGeneral && align != AlignLeft &&
                              align != AlignRight && align != AlignHDistributed)) {
        m_alignment.indent = 0;
    }

    if (m_alignment.shinkToFit && (align == AlignHFill || align == AlignHJustify
                                   || align == AlignHDistributed)) {
        m_alignment.shinkToFit = false;
    }

    m_alignment.alignH = align;
}

Format::VerticalAlignment Format::verticalAlignment() const
{
    return m_alignment.alignV;
}

void Format::setVerticalAlignment(VerticalAlignment align)
{
    m_alignment.alignV = align;
}

bool Format::textWrap() const
{
    return m_alignment.wrap;
}

void Format::setTextWarp(bool wrap)
{
    if (wrap && m_alignment.shinkToFit)
        m_alignment.shinkToFit = false;

    m_alignment.wrap = wrap;
}

int Format::rotation() const
{
    return m_alignment.rotation;
}

void Format::setRotation(int rotation)
{
    m_alignment.rotation = rotation;
}

int Format::indent() const
{
    return m_alignment.indent;
}

void Format::setIndent(int indent)
{
    if (indent && (m_alignment.alignH != AlignHGeneral
                   && m_alignment.alignH != AlignLeft
                   && m_alignment.alignH != AlignRight
                   && m_alignment.alignH != AlignHJustify)) {
        m_alignment.alignH = AlignLeft;
    }
    m_alignment.indent = indent;
}

bool Format::shrinkToFit() const
{
    return m_alignment.shinkToFit;
}

void Format::setShrinkToFit(bool shink)
{
    if (shink && m_alignment.wrap)
        m_alignment.wrap = false;
    if (shink && (m_alignment.alignH == AlignHFill
                  || m_alignment.alignH == AlignHJustify
                  || m_alignment.alignH == AlignHDistributed)) {
        m_alignment.alignH = AlignLeft;
    }

    m_alignment.shinkToFit = shink;
}

bool Format::alignmentChanged() const
{
    return m_alignment.alignH != AlignHGeneral
            || m_alignment.alignV != AlignBottom
            || m_alignment.indent != 0
            || m_alignment.wrap
            || m_alignment.rotation != 0
            || m_alignment.shinkToFit;
}

QString Format::horizontalAlignmentString() const
{
    QString alignH;
    switch (m_alignment.alignH) {
    case Format::AlignLeft:
        alignH = "left";
        break;
    case Format::AlignHCenter:
        alignH = "center";
        break;
    case Format::AlignRight:
        alignH = "right";
        break;
    case Format::AlignHFill:
        alignH = "fill";
        break;
    case Format::AlignHJustify:
        alignH = "justify";
        break;
    case Format::AlignHMerge:
        alignH = "centerContinuous";
        break;
    case Format::AlignHDistributed:
        alignH = "distributed";
        break;
    default:
        break;
    }
    return alignH;
}

QString Format::verticalAlignmentString() const
{
    QString align;
    switch (m_alignment.alignV) {
    case AlignTop:
        align = "top";
        break;
    case AlignVCenter:
        align = "center";
        break;
    case AlignVJustify:
        align = "justify";
        break;
    case AlignVDistributed:
        align = "distributed";
        break;
    default:
        break;
    }
    return align;
}

bool Format::isDxfFormat() const
{
    return m_is_dxf_fomat;
}


void Format::setForegroundColor(const QColor &color)
{
    m_fg_color = color;
}

void Format::setBackgroundColor(const QColor &color)
{
    m_bg_color = color;
}

} // namespace QXlsx
