#ifndef _G_ITEMS_H_
#define _G_ITEMS_H_

//#include <strg.h>

#define FRACTION_PADDING 10
#define ROOT_PADDING 10

typedef struct _GItem GItem;
typedef struct _GNode GNode;
typedef struct _GList GList;

typedef enum {GITEM_CHAR, GITEM_POWER, GITEM_FRACTION, GITEM_ROOT} GItemType;

typedef void (*freeFunc) (GItem* _this);
//typedef void (*_toStringFunc) (GItem* _this, String* str);
typedef void (*fontIdFunc) (GItem* _this, int id);
typedef int (*widthFunc) (GItem* _this, HDC hdc);
typedef int (*heightFunc) (GItem* _this, HDC hdc);
typedef int (*baseLineYFunc) (GItem* _this, HDC hdc);
typedef void (*calcXYFunc) (GItem* _this, HDC hdc, int x0, int y0);
typedef void (*drawFunc) (GItem* _this, HDC hdc);

typedef struct _GNode
{
	GItem* _pGItem;

	struct _GNode* _next;
	struct _GNode* _prev;
} GNode;

typedef struct _GList
{
	GNode* _front;
	GNode* _rear;
	GNode* _current; // used by editor

	GList* _parent;
	int _width, _height, _baseLineY;
	int _x0, y0;
} GList;

typedef struct _GItem
{
	GItemType _type;

	int _fontId;
	int _width, _height;
	int _baseLineY;
	int _x0, _y0;

	freeFunc _freeFunc;
	
	fontIdFunc _fontIdFunc;
	widthFunc _widthFunc;
	heightFunc _heightFunc;
	baseLineYFunc _baseLineYFunc;
	calcXYFunc _calcXYFunc;
	drawFunc _drawFunc;
	//_toStringFunc _toStringFunc;
} GItem;

typedef struct
{
	GItem _gitem;

	wchar_t _ch;
} GItemChar;

typedef struct
{
	GItem _gitem;

	GList* _exponent;
} GItemPower;

typedef struct
{
	GItem _gitem;

	GList* _numerator;
	GList* _denominator;
} GItemFraction;

typedef struct
{
	GItem _gitem;

	GList* _expr;
	GList* _root;
} GItemRoot;

GNode* GNode_init(GItem* pGItem, GNode* n, GNode* p);
void GNode_free(GNode* pn);

GList* GList_init(GList* parent);
void GList_free(GList* gll);
void GList_pushback(GList* gll, GItem* pGItem);

//void GList_toString(GList* gll, String* str);

void GList_calcFontId(GList* gll, int id);
void GList_calcWidth(GList* gll, HDC hdc);
void GList_calcHeight(GList* gll, HDC hdc);
void GList_calcBaseLineY(GList* gll, HDC hdc);
void GList_calcXY(GList* gll, HDC hdc, int x0, int y0);
void GList_draw(GList* gll, HDC hdc);

GItemChar* GItemChar_init(const wchar_t ch);
GItemPower* GItemPower_init(GList* exponent);
GItemFraction* GItemFraction_init(GList* num, GList* den);
GItemRoot* GItemRoot_init(GList* expr, GList* root);

#endif /* _G_ITEMS_H_ */
