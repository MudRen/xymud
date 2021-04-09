#include <ansi.h>
inherit "/d/maze/xiaoyan-ta/room.c";

void create() 
{ 
        set("short", "甬道尽头"); 
        set("long", @LONG 
洞内四面纵横十余丈，其中错牙交错的甬道连接四方，两面的
石壁上画满佛符，不过给人胡乱涂去了。
    地上摆着一个大火盆，四周涂着杂七杂八的符号，数名穿
着奇装异服的汉子在拜倒在地，对着火盆行礼。

LONG
); 
	set("objects",([
		"/d/maze/xiaoyan-ta/npc/guai" : 1+random(2),
		"/d/maze/xiaoyan-ta/npc/eba" : 1,
	]));	
	set("alternative_die",1);
	set("virtual_room",1);	
        setup();
}

void init()
{
	object guai;
	if( userp(this_player()) )
	{
		if( objectp(guai=present("sha shou",this_object()))
		 && !userp(guai) && living(guai)
		 && !guai->is_fighting() )
		{
			message_vision(HIR"\n$N"HIR"恶狠狠的叫道：还在庆幸在此处寻得一处隐秘之所，却怎想这么快就被人发现了，留他不得！\n"NOR,guai);
			message_vision(CYN"$N"CYN"说道：此处拜火教圣地，闲杂人等不得进入！\n"NOR,guai);
			guai->kill_ob(this_player());
		}
	}
}		 