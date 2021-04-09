#include <ansi.h>
inherit "/d/maze/qingling-1/room.c";

void create() 
{ 
        set("short", "始皇陵二层入口");
        set("long2","\n                   "REV HIY"       "NOR HBYEL HIY"`"NOR"
                   "REV HIY"   秦  "NOR REV YEL" "NOR"
                   "REV HIY"   始  "NOR REV YEL" "NOR"
                   "REV HIY"   皇  "NOR REV YEL" "NOR"
                   "REV HIY"   陵  "NOR REV YEL" "NOR"
                   "REV HIY"   二  "NOR REV YEL" "NOR"
                   "REV HIY"   层  "NOR REV YEL" "NOR"
                   "REV HIY"   入  "NOR REV YEL" "NOR"
                   "REV HIY"   口  "NOR REV YEL" "NOR"                                                                            
                   "REV HIY"       "NOR HBYEL HIY"_"NOR"
                  "REV YEL"          "NOR"\n\n");
        set("virtual_room", 1); 
        set("exits", ([
                "down" : __FILE__,
                "south" :__DIR__"maze/exit",
        ])); 
        set("alternative_die",1);   
        set("item_desc",([
                "down" : "下面黑布隆冬的，你看不清楚。\n",
        ]));    
        setup();
} 

int valid_leave(object who,string dir)
{
        if( dir=="down" )
        {
                if( !userp(who) )
                        return 0;
                if( who->query_level()<40 )
                        return notify_fail("一旁闪出几位守护官兵，拦住了你：太危险，你下去就是「肉包子打狗，有去无回」！\n");
                return notify_fail("一旁的官兵冷冷的看着你。\n");
        }
        return ::valid_leave(who,dir);
}       

void create_guai()
{
        object boss = new("/d/maze/qingling-1/npc/boss");
        tell_room(this_object(),HIC"\n忽然从石碑后面窜出一道黑影！\n\n"NOR);
        boss->set("create",1);
        boss->move(this_object());
        set("guai",1);
}

void init()
{
        ::init();
        if( userp(this_player())&& !query("guai") 
         && time()>this_player()->query("maze/last_QLboss1")+2400 )
         
        {
                remove_call_out("create_guai");
                call_out("create_guai",2);
        }        
}
