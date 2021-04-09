inherit ROOM;                                                        
                                                                     
void create ()                                                       
{                                                                    
  	set ("short", "竹林");                                   
  	set ("long", @LONG
四周长满了竹子，绿影婆裟，宛如鬼影重重，你不禁感到暗暗心惊，脚下
也不由的加快了几分。
	
LONG);                                                          
	set("exits", ([
  		"north" : __DIR__"bamboo",                                         
  		"east" : __DIR__"bamboo",                                    
  		"west" : __DIR__"bamboo1",                                       
  		"south" : __DIR__"houshan",
	]));                                                                 
        setup();                                                           
}

void reset()
{
	object room;
	int i;
	string *dirs,dir;
	string r1,r2,r3,r4;
	mapping ext;
	::reset();
	r1 = (__DIR__"bamboo1.c");
	r2 = (__DIR__"bamboo2.c");
	r3 = (__DIR__"bamboo3.c");
	r4 = (__DIR__"bamboo4.c");
	delete("exits");		
	ext = ([
		"north" : "south",
		"west"	: "east",
		"east"	: "west",
	]);
	
	dirs = keys(ext);
	dir = dirs[random(sizeof(dirs))];
	dirs-= ({dir});
	set("exits/south",__DIR__"houshan");
	set("exits/"+dir,__DIR__"bamboo1");
	for(i=0;i<sizeof(dirs);i++)
		set("exits/"+dirs[i],__FILE__);
	tell_room(this_object(),"\n一阵微风吹过，顿时绿影婆裟，感觉竹林中的道路有了些许变化。\n\n");
	
	dir = ext[dir];
	r1->delete("exits");
	r1->set("exits/"+dir,__FILE__);
	
	ext = ([
		"north" : "south",
		"west"	: "east",
		"east"	: "west",
		"south" : "north",
	]);
	dirs = keys(ext);
	dirs-= ({dir});
	dir = dirs[random(sizeof(dirs))];
	r1->set("exits/"+dir,__DIR__"bamboo2");
	dirs-= ({dir});
	for(i=0;i<sizeof(dirs);i++)
		r1->set("exits/"+dirs[i],__FILE__);
	if( objectp(room=find_object(r1)) )	
		tell_room(room,"\n一阵微风吹过，顿时绿影婆裟，感觉竹林中的道路有了些许变化。\n\n");
	
	dir = ext[dir];
	r2->delete("exits");
	r2->set("exits/"+dir,__DIR__"bamboo1");
	ext = ([
		"north" : "south",
		"west"	: "east",
		"east"	: "west",
		"south" : "north",
	]);
	dirs = keys(ext);
	dirs-= ({dir});
	dir = dirs[random(sizeof(dirs))];
	r2->set("exits/"+dir,__DIR__"bamboo3");
	dirs-= ({dir});
	for(i=0;i<sizeof(dirs);i++)
		r2->set("exits/"+dirs[i],__FILE__);
	if( objectp(room=find_object(r2)) )	
		tell_room(room,"\n一阵微风吹过，顿时绿影婆裟，感觉竹林中的道路有了些许变化。\n\n");
	
	dir = ext[dir];
	r3->delete("exits");
	r3->set("exits/"+dir,__DIR__"bamboo2");
	ext = ([
		"north" : "south",
		"west"	: "east",
		"east"	: "west",
		"south" : "north",
	]);
	dirs = keys(ext);
	dirs-= ({dir});
	dir = dirs[random(sizeof(dirs))];
	r3->set("exits/"+dir,__DIR__"bamboo4");
	dirs-= ({dir});
	for(i=0;i<sizeof(dirs);i++)
		r3->set("exits/"+dirs[i],__FILE__);
	if( objectp(room=find_object(r3)) )	
		tell_room(room,"\n一阵微风吹过，顿时绿影婆裟，感觉竹林中的道路有了些许变化。\n\n");

	dir = ext[dir];
	r4->delete("exits");
	r4->set("exits/"+dir,__DIR__"bamboo3");
	ext = ([
		"north" : "south",
		"west"	: "east",
		"east"	: "west",
		"south" : "north",
	]);
	dirs = keys(ext);
	dirs-= ({dir});
	dir = dirs[random(sizeof(dirs))];
	r4->set("exits/"+dir,__DIR__"tower");
	dirs-= ({dir});
	for(i=0;i<sizeof(dirs);i++)
		r4->set("exits/"+dirs[i],__FILE__);
	if( objectp(room=find_object(r4)) )	
		tell_room(room,"\n一阵微风吹过，顿时绿影婆裟，感觉竹林中的道路有了些许变化。\n\n");
}	