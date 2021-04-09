inherit __DIR__"r.c";

void create()
{
::create();
set("short","凝香");
set("number",14);
set("master","ningmou xianzi");
set("exits",([
        "up" : __FILE__,
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/baihua"  : 1,
      __DIR__"npc/baihua2" : 5+random(3),
]));
setup();
}               

int valid_leave(object who,string arg)
{
	string *file,f;
	object npc,room,*inv;
	int i;
	
	if( !userp(who) )
		return 0;
	if( who->is_fighting() )   
		return notify_fail("你停住了脚步专心备战。\n");
	if( get_player(who) )
		return notify_fail("你要先将身上的玩家放下。\n");
	if( !who->query("mark/tiaozhan/凝眸仙子") )
		return notify_fail("此关你尚未闯过，如何走得？\n");
	if( time()<who->query("mark/tiaozhan/top1")+1800 )
		return notify_fail("你刚刚来过，还是再等"+FINGER_D->age_string(1800+who->query("mark/tiaozhan/top1")-time())+"。\n");
	
	
	inv = all_inventory();
	for(i=0;i<sizeof(inv);i++)
	{
		if( inv[i]->is_job() )
			return notify_fail(inv[i]->name()+"伸手拦住了你的去路。\n");
	}
	
	room = find_object(__DIR__"top1.c");
	if( !room )
		room = load_object(__DIR__"top1.c");
	if( !room )
		return notify_fail("你踌躇不前。\n");
	inv = all_inventory(room);
	for(i=0;i<sizeof(inv);i++)
	{
                if( userp(inv[i]) && !wizardp(inv[i]) )
			return notify_fail(inv[i]->name(1)+"现在在里面呢。\n");
	}
	for(i=0;i<sizeof(inv);i++)
           if( !userp(inv[i]) )   destruct(inv[i]);

	file = ({
		"baihua3","fc3","hell3","hyd3","jjf3","moon3",
		"pansi3","putuo3","sanxian3","sea3","shushan3",
		"wdd3","wzg3","xs3",
	});
	
	for(i=0;i<=1;i++)	
	{
		f = file[random(sizeof(file))];	
		file-= ({f});
		npc = new(__DIR__"npc/"+f);
		npc->move(room);
	}
	who->set("mark/tiaozhan/top1",time());
	who->move(room);
	return 2;
}				

int is_job(){return 1;}
