inherit ROOM; 
void create() 
{ 
        set("short", "廊间"); 
        set("long", @LONG 
四下里静寂无声，借着月光只见长廊延伸到黑暗之中。小廊上是木
板铺地，打扫的极为干净，走在上面发出吱吱的响声，在这黑夜尤为刺
耳。走廊两面的木格上雕着一些山水人物。

LONG
); 
        set("virtual_room", 1); 
        set("no_magic",1);
        set("exits", ([
                "west" : __DIR__"maze/entry", 
        ])); 
        setup();
} 

int valid_leave(object who,string dir)
{
	if( !who->query_temp("maze/zuixing") )
        	return notify_fail("你是怎么混进来的？！\n");
        return ::valid_leave(who,dir);
}			  		 
