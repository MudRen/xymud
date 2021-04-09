// Room: /d/huanggong/guangchang.c
inherit ROOM;

void create ()
{
  set ("short", "朝天场");
  set ("long", @LONG

皇宫前的大广场，长宽俱有二十余长。地下乃是从终南山运来
的青砖铺就，与宫殿的红墙黄瓦交相辉映。有重大事件或节日
时皇帝便在此会见群臣。北边是一排排的宫圉楼阁，东西是群
臣上朝前休息的朝房。
LONG);

  set("exits", ([ /* sizeof() == 4 */
  "west" : __DIR__"baihu.c",
  "south" : __DIR__"damen",
  "east" : __DIR__"qinglong.c",
  "northup" : __DIR__"baiyujie.c",
]));
  set("outdoors", "/d/huanggong");

  setup();
}

int valid_leave(object who,string dir)
{
int i;
object *inv;    
if ( !userp(who) )
        return 0;
if ( dir=="west" )
        {
        if ( who->query("family/family_name")=="火系魔法教派" )
              return notify_fail("由于你的门派在调整中，所以暂时不能进入演练了。\n");
        inv = all_inventory(who);
        for(i=0;i<sizeof(inv);i++)
                {
                if ( inv[i]->is_character() 
                  || inv[i]->is_container()
                  || inv[i]->is_zhaohuan() )
                        return notify_fail("请将你身上的"+inv[i]->name()+"放下。\n");
                }
        }
return ::valid_leave(who,dir);
}

void init()
{
add_action("do_drop","drop");
}

int do_drop(string arg)
{
object obj,me = this_player();
if ( !arg )   return 0;
obj = present(arg,me);
if ( !obj || obj->is_character() )
        return 0;
if ( !obj->query("value") && !obj->query("no_drop") )
        return 0;
message_vision("$N丢下一"+(obj->query("unit")?obj->query("unit"):"些")+obj->name()+"。\n",me);
destruct(obj);
return 1;
}
