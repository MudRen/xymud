#include <room.h>
inherit HOCKSHOP;

void create ()
{
	set("short", "吴家当铺");
  	set("long", @LONG
这是傲来国里最大的一家当铺了。素来以买卖公平着称。门口挂
了一块牌子 (paizi)。这里的吴老板是个精明人，靠倒卖些东西赚了
不少钱。

LONG);
  	set("objects", ([
		__DIR__"npc/wu" : 1,
		"/d/city/npc/xiaoyi" : 1,
	]));
	set("exits", ([ 
  		"west" : __DIR__"north2.c",
	]));
  	set("item_desc", ([
  		"paizi" : "
本当铺财力雄厚，童叟无欺，欢迎惠顾，绝对保密。客官可以在
这里估价(value)，典当(pawn)，卖断(sell)，赎回(retrieve stamp)，
购买(buy)  (用list查看)。各种货物，铜钱、银两、黄金、银票
一概通用。
",
]));
  	set("no_clean_up", 1);
	setup();
}