#include <ansi.h>
inherit ROOM;

nomask object query_maze_room(string str) 
{ 
	int idx,x,y,exits; 
    int box_type,trap_type; 
    object ob,obj; 
    string f,*exs; 
    int unique_flag; 
 
    if( !stringp(str) || str == "" ) 
    	return 0; 
	f = __FILE__;
	ob = load_object(f); 
    if( !ob ) 
    	return 0; 
	ob->set("maze", 1); 
	ob->set("virtual_room",1); 
	return ob; 
} 
