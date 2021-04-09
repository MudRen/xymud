inherit ROOM;
#include <ansi.h>
#include <localtime.h>
int block_cmd(string);
string chinese_time(int type,string get_time);

void create ()
{
	set ("short", "南城客栈");
  	set ("long", @LONG
这家客栈紧靠长安城中心，所以生意非常兴隆。兼之价钱低廉，更是
成了外地游客落脚的首选。露天摆了七八张桌子，三教九流人等在此
进进出出，络绎不绝，几个跑堂的小二来来回回招待着四方来客。二
楼上是雅厅，后面是客房。
LONG);
  	set("exits", ([
  		"east" : __DIR__"sleep",
  		"west" : __DIR__"zhuque-s1",
  		"north" : __DIR__"zhunbei",
  		"up": __DIR__"entrance",
]));
   	set("chat_room",1);
  	set("objects", ([
  		__DIR__"npc/xiaoer" : 1,
		"/d/ourhome/npc/bigeye" : 1,
  		"/d/city/npc/xiaoyi" : 1,
	]));
  	set("no_time",1);
	set("no_time", 1);
  	set("no_fight", 1);
  	set("no_magic", 1);
        set("freeze",1);
 	set("resource", ([ /* sizeof() == 1 */
  		"water" : 1,
	]));
  	set("valid_startroom", 1);
  	setup();
  	call_other("/obj/board/nancheng_b", "???");
}

void init()
{
    	add_action("block_cmd", "", 1);
}

int block_cmd(string args)
{
	string verb;
	verb = query_verb();

    // if (verb == "bian") return 1; // by mon 7/15
    if (verb == "xiudao") return 1;
    if (verb == "exert") return 1;
    if (verb == "bid") return 1;
      if (verb == "get") return 1;
    return 0;
}

int valid_leave(object me, string dir)
{
        object mbox;

        if ( !me->query_temp("rent_paid") && dir == "east" )
        return notify_fail("店小二满脸堆笑地挡住了你：对不起，后面是客人的卧房，不是本店的客人，不便打扰。\n");
        if( mbox = me->query_temp("mbox_ob") ) {
                tell_object(me, "你将信箱交回给邮差。\n");
                destruct(mbox);
        }

        return ::valid_leave(me, dir);
}