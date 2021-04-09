inherit ROOM;
void create ()
{
    	set ("short", "新手成长室");
  	set ("long", @LONG
这里是新手恢复身体的地方，请输入(fullme)。
LONG);
	set("exits", ([
        	"out" :"/d/kaifeng/tieta",
      	]));
	set("outdoors", __DIR__);
    	set("no_fight", 1);
      	set("no_magic", 1);
	setup();

}

int init ()
{
	add_action ("do_recover","fullme");
}

int do_recover()
{
  	object me = this_player();
	if( me->query_level()>=10 && !wizardp(me) )
		return notify_fail ("你不算新手了。\n");
    	me->powerup(0,1);	
    	write("你的身体恢复了。\n");
	return 1;
}


