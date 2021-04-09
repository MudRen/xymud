// gate.c
inherit ROOM;

void create()
{
set ("short", "铁铺");
set ("long", @LONG

铁铺的主人是老李头，他打的铁器坚固耐用，名气在方圆几十里
是没的说．他这里的生意也特别的好．屋里到处是铁器，两个学
徒正帮着老李头打造农具．
LONG);
set("exits", ([ 
        "north" : __DIR__"road2",
//        "enter" : __FILE__,
]));
set("objects", ([
        __DIR__"npc/laoli": 1,
        __DIR__"npc/xuetu": 2
]) );
set("item_desc",([
        "enter" : "\n\n\n里面是冶炼各种矿石的作坊，雾气缭绕的，什么也看不清。\n",
]));            
set("no_clean_up", 0);
setup();
}

void init()
{
add_action("do_cmd","",1);
}

int err_msg(string arg)
{
write(arg);
return 1;
}
        
int do_cmd(string arg)
{
object room,me = this_player();
object lu;
string str = query_verb();

if ( str=="enter" || ( str=="go" && arg=="enter" ) )
        {
        if ( !userp(me) )       return 1;
        if ( !me->query_temp("挑战武器_锻造") )
                return err_msg("你没付手续费，进不了冶炼室。\n");
        room = me->query_temp("yelian_room");           
        if ( !room ) 
                room = clone_object("/d/wiz/yelian_room.c");
        if ( !room )
                return err_msg("冶炼室目前暂时不营业。\n");
        if ( !me->move(room) )
                return err_msg("冶炼室暂时不营业。\n");
        if ( !present("yelian lu",room) )   {  lu = new("/d/newguai/obj/yelian-lu");
        if ( lu )   lu->move(room);
        if ( lu )   lu->move(room); }
        message_vision("$N朝里进入了冶炼室。\n",me);    
        me->set_temp("yelian_room",room);
        return 1;
        }
return 0;
}               
