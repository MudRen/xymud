// virtuald.c
#include <ansi.h>
inherit F_DBASE;

nosave mapping Exits = ([
	"west" : "east",
	"east" : "west",
	"north": "south",
	"south": "north",
	"up"   : "down",
	"down" : "up",
	"northeast" : "southwest",
	"northwest" : "southeast",
	"northup"   : "soutndown",
	"northdown" : "southup",
	"southeast" : "northwest",
	"southwest" : "northeast",
	"southup"   : "northdown",
	"southdown" : "northup",
	"enter"	    : "out",
	"out"	    : "enter",
]);	 

void create()
{
	seteuid(getuid());
	set("channel_id","虚拟底层(Virtuald)");
}

string query_other_exit(string arg)
{
	mapping exit = ([
		"north" : "south",
		"south" : "north",
		"west"  : "east",
		"east"  : "west",
		
		"up"	: "down",
		"down"	: "up",
		"enter" : "out",
		"out"	: "enter",
		
		"northwest" : "southeast",
		"southeast" : "northwest",
		"northeast" : "southwest",
		"southwest" : "northeast",
		
		"northup"   : "southdown",
		"southdown" : "northup",
		"northdown" : "southup",
		"southup"   : "northdown",
		
		"westup"    : "eastdown",
		"eastdown"  : "westup",
		"westdown"  : "eastup",
		"eastup"    : "westdown",
		
	]);
	if( undefinedp(exit[arg]) )
		return 0;
	return exit[arg];	
}

object pre_object()
{
	int i;
	object *obj = previous_object(-1);
	if( !obj || !arrayp(obj) || sizeof(obj)<1 )
		return 0;
	i = sizeof(obj);
	return obj[i-1];
}	

public object compile_object(string file)
{
	string *path,pname = file;
    	object ob;
    	object preob;
    	if(!file)
        	return 0;
	preob=pre_object();
    	CHANNEL_D->do_channel(this_object(),"sys",sprintf("VIRTUAL_D->previous object: %O\n",preob));
    	path = explode(file,"/");
    	if(sizeof(path)>0 && path[0] == "maze")
		return MAZE_D->query_maze_room(path);
	while (1)
    	{
        	int idx = strsrch(pname, "/", -1);
		if(idx == -1)
            		return 0;
		if( idx != 0 )
            		pname = pname[0..idx-1];
		if(file_size(pname + ".c") >= 0)
            	if(ob = pname->query_maze_room(file[idx+1..]))
            	{
                	ob->set_virtual_flag();
                	return ob;
            	}
        	if(!idx)
            		return 0;
    	}		
	return 0;
}

void remove()
{
	REMOVE_D->init_room();
}
