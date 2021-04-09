//maximum mapping size : 40000
//maximum array size : 30000
#include <ansi.h>
#include <command.h>
#include <localtime.h>
inherit F_DBASE;
#include <questd.h>

// #pragma save_binary

nosave mapping Rooms;
void init_room();

void create()
{
	seteuid(ROOT_UID);
	set("channel_id", "清除精灵");
	set_heart_beat(1);
	init_room();
	CHANNEL_D->do_channel(this_object(),"sys","全局地图清理已启动。");
}

int clean_up()
{
	return 1;
}

mixed *query_Rooms()
{
	mixed *obj;
	if( !Rooms || !mapp(Rooms) )
		return 0;
	obj = keys(Rooms);
	if( !obj || !arrayp(obj) || sizeof(obj)<1 )
		return 0;
	obj-=({0});
	return obj;
}

void remove_room(object ob)
{
	string startroom;
	object *inv;
	int i;
	if( !ob )
		return;
	inv = all_inventory(ob);
	for(i=0;i<sizeof(inv);i++)
	{
		if( !inv[i] )
			continue;
		if( userp(inv[i]) )
		{
			message("vision","\n一阵清风拂过，"+inv[i]->name()+"化作一道青烟而去。\n\n",ob,inv[i]);
			tell_object(inv[i],"你只觉眼前一花，方才种种宛如一梦。。。。\n\n\n");
			startroom = inv[i]->query("startroom");
			if( !startroom )
				startroom = "/d/city/kezhan";
			inv[i]->move(startroom);
		}
		else	destruct(inv[i]);
	}
	destruct(ob);
}

void init_room()
{
	int i,k;
	mixed *obj;
	if( !Rooms || !mapp(Rooms) )
		Rooms = ([]);
	else
	{
		obj = keys(Rooms);
		if( !obj || !arrayp(obj) || sizeof(obj)<1 )
			return;
		k = 0;
		for(i=0;i<sizeof(obj);i++)
		{
			remove_room(obj[i]);
			k++;
		}
		CHANNEL_D->do_channel(this_object(),"sys","共清除"+k+"个虚拟地图。");
	}
	CHANNEL_D->do_channel(this_object(),"sys","全局地图清理已初始成功。");
}

void remove()
{
	init_room();
	CHANNEL_D->do_channel(this_object(),"sys","全局地图清理已重新启动。");
}

varargs mixed add_room(object ob,int delay)
{
	if( !ob )
		return "无生成的虚拟房间";
	if( !delay )
		delay = ob->query_delay_time();
	if( delay<=0 )
		delay = 3600;
	if( !Rooms || !mapp(Rooms) )
		Rooms = ([ ob : delay ]);
	else
	{
		if( !undefinedp(Rooms[ob]) )
			Rooms[ob] = delay;
		else if( sizeof(Rooms)>30000 )
			return "mapping数量已到上限";
		else if( sizeof(keys(Rooms))>20000 )
			return "array数量已到上限";
		else	Rooms[ob] = delay;
	}
	map_delete(Rooms,0);
	return 1;
}

void check_rooms()
{
	mixed *obj;
	int i,t;
	if( !Rooms || !mapp(Rooms) )
		return;
	obj = keys(Rooms);
	if( !obj || !arrayp(obj) || sizeof(obj)<1 )
		return;
	for(i=0;i<sizeof(obj);i++)
	{
		t = Rooms[obj[i]];
		t = t-1;
		if( t<=0 )
			remove_room(obj[i]);
		else	Rooms[obj[i]] = t;
	}
}

void heart_beat()
{
	check_rooms();
}
