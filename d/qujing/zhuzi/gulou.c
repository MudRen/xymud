// by snowcat 11/6/1997
inherit ROOM;

void create()
{
  set ("short", "鼓楼");
  set ("long", @LONG

鼓楼位于朱紫国的城中心，人多喧哗，经常挤挤挨挨，偶尔可见一
些校尉来往行走。往西是夕林街为食品闹市，往东则有一些会馆客
栈，南边可见朱紫国皇宫。鼓楼上贴有一皇榜(huang bang)，有人
围观。

LONG);

  set("exits", ([ 
    "north" : __DIR__"zhuzi3",
    "south" : __DIR__"zhuzi4",
    "west" : __DIR__"xi4",
//    "up" : __DIR__"jitan",
    "east" : __DIR__"tian1",
  ]));
  set("item_desc",([
   "huang bang" : "  朕西牛贺洲朱紫国王近因国事不详\n"+
                  "  沉疴伏枕淹延日久难痊本国太医院\n"+
                  "  未能调治今出此榜普招天下贤士请\n"+
                  "  登宝殿疗理朕躬为此出给张挂须至\n"+
                  "  榜者\n",
  ]));
  set("objects", ([
    __DIR__"npc/taijian" : 3,
    __DIR__"npc/xiaowei" : 3,
  ]));
  set("outdoors", __DIR__"");
  setup();
}