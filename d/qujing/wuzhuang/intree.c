//Cracked by Roath
//  妖神之争 １。０
//  by happ@YSZZ 2000.4.9
//  /d/qujing/wuzhuang/intree.c


inherit ROOM;
#include <ansi.h>
void kill(object ob);
void appear(object ob);
  void restoration(object where);

void create ()
{
   set ("short", "果树上");
   set ("long", @LONG

你终于爬到了果树的顶上，人参果在你的身边摇摆不定，这人参果
三千年一开花，三千年一结果，再三千年才得熟，短头一万年才可
吃，那果子的模样，就和三朝未满的小孩相似，四肢齐全，五官俱
全。

LONG);

   set("exits", 
   ([ //sizeof() == 4
        "down": __DIR__"shugan3",
   ]));
   setup();
}