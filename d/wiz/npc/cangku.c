#include <ansi.h>
inherit NPC;
inherit F_SAVE;

string query_save_file()
{
	string id;
	id = query("serve_id");
	if( !id || !stringp(id) )
		return 0;
	return sprintf(DATA_DIR "store/%c/%s", id[0], id);	
}

void create()
{
	set_name("呢喃",({"ni nan","boss","player",}));
	set("no_bian",1);
	set("age",30);
	set("gender","女性");
	set_level(39);
	set("per",100);
	set("title",HIW"仓库大使"NOR);
	set("long","这就是传说中的呢喃大美女了，你可以在她这里存东西，直接给她就行了。
你还可以通过 list 命令来查看你存的东西。\n");
	setup();
	carry_object(0,"cloth",1)->wear();
}

int check_owner(object me)
{
	string id;
	object who;
	id = query("serve_id");
	if( !id )
		return 0;
	who = find_player(id);
	if( !who )
	{
		delete("serve_id");
		delete("store");
		return 0;
	}
	if( !present(who,environment()) )
	{
		if( living(who) )
			tell_object(who,HIR"【系统】由于你离开了，你的仓库服务进程自动取消了。"NOR"\n");
		delete("serve_id");
		delete("store");
		return 0;
	}
	if( me==who )
		return 0;
	return 1;	
}

int accept_money(object me,int amount)
{
	string str,*strs;
	if( !userp(me) || amount<5 )
		return 0;
	if( me->query_temp("store_gived") )
	{
		tell_object(me,CYN+name()+CYN"说道：这怎么好意思，你刚刚已经给过了。\n"NOR);
		return 0;
	}	
	me->set_temp("store_gived",1);
	strs = ({"zeze","smile","great","good","pat","touch",});
	str = strs[random(sizeof(strs))];
	EMOTE_D->do_emote(this_object(), str,geteuid(me),CYN,0,0,0);
	tell_object(me,CYN+name()+CYN"说道：好好，有什么要存的，尽管给(give)我。\n"NOR);
	return 1;	
}

int accept_object(object me,object obj)
{
	int i,max;
	string file,*prop,name,*ids;	
	mapping data,store;
	
	if( !userp(me) )
		return 0;
	if( check_owner(me) )
	{
		tell_object(me,name()+"说道：稍等片刻，我现在正在处理其他人的仓库。\n");
		return 0;
	}
	if( !me->query_temp("store_gived") )
	{
		tell_object(me,CYN+name()+CYN"说道：呵呵，请交手续费，每次5文钱。\n"NOR);
		return 0;
	}
	if( obj->is_character() )
	{
		EMOTE_D->do_emote(this_object(), "pei",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：我可不是人贩子！\n"NOR);
		EMOTE_D->do_emote(this_object(), "renzha",geteuid(me),CYN,0,0,0);
		return 0;
	}
	if( obj->query("equipped") )
	{
		EMOTE_D->do_emote(this_object(), "baobao",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：你装备着，怎么给我？\n"NOR);
		EMOTE_D->do_emote(this_object(), "papaya2",geteuid(me),CYN,0,0,0);
		return 0;
	}
	set("serve_id",me->query("id"));
	restore();
	store = query("store");
	max = me->query_level()*2;
	if( max>100 )
		max = 100;
	if( store && mapp(store) )
	{
		if( sizeof(keys(store))>=max )
		{
			delete("store");
			delete("serve_id");
			EMOTE_D->do_emote(this_object(), "hmm",geteuid(me),CYN,0,0,0);
			tell_object(me,CYN+name()+CYN"说道：以你目前的人物等级，只能存"NOR HIR+max+NOR CYN"件。\n"NOR);
			return 0;
		}
	}
	me->start_busy(1);
	name = obj->query("name");
	ids = obj->query_my_id();
	data = obj->query_entire_dbase();
	file = base_name(obj);
	if( !store || !mapp(store) || sizeof(store)<1 )
		store = ([
			time() : ([
				"ids"	: ids,
				"dbase"	: data,
				"name"	: name,
				"file"	: file,
				"num"   : (obj->query_amount()>1?obj->query_amount():1),
			]),	
		]);
	else	store[time()] = ([
				"ids"	: ids,
				"dbase"	: data,
				"name"	: name,
				"file"	: file,
				"num"   : (obj->query_amount()>1?obj->query_amount():1),
		]);
	set("store",store);		
	if( this_object()->save() )
	{
		delete("store");
		delete("serve_id");
		me->delete_temp("store_gived");
		EMOTE_D->do_emote(this_object(), "ok",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：你随时可以来查看("NOR HIY"list"NOR CYN")和取出("NOR HIY"qu"NOR CYN")你存的物品。\n"NOR);
		this_object()->start_busy(1);
		return 1;
	}
	delete("store");
	this_object()->start_busy(1);
	tell_object(me,CYN+name()+CYN"说道：哎呀，好似出问题了，你再试一次看看。\n"NOR);
	return 0;
}
	
void init()
{
	add_action("do_list","list");
	add_action("do_qu","qu");
}

int do_list()
{
	mixed *names;
	string str,name,id,*ids;
	int i,num;
	mapping prop,temp;
	object me = this_player();
	if( check_owner(me) || this_object()->is_busy() )
		return err_msg(name()+"现在正忙。\n");
	if( me->is_busy() )
		return err_msg("你现在正忙。\n");
	me->start_busy(3);		
	set("serve_id",me->query("id"));
	restore();
	start_busy(1);
	prop = query("store");
	if( !prop || !mapp(prop) )
		return err_msg("暂时没有找到你的仓库记录。\n");
	delete("serve_id");
	delete("store");	
	names = keys(prop);
	if( !names || !arrayp(names) || sizeof(names)<1 )
		return err_msg("暂时没有找到你的仓库记录。\n");
	str = "你在此寄存的物品有：\n";
	for(i=0;i<sizeof(names);i++)
	{
		if( undefinedp(prop[names[i]]) )
			continue;
		temp = prop[names[i]];
		name = temp["name"];
		ids =  temp["ids"];
		if( !undefinedp(temp["num"]) )
			num = temp["num"];
		else	num = 1;	
		if( num<1 ) 
			num = 1;
		id = ids[0];
		str+= sprintf("%20d 号物品 ：",names[i]);
		str+= sprintf("%s(%s) 数量 %d\n",name,capitalize(id),num);
	}
	str+= "如果想取出，请用命令 qu <物品编号>\n";
	me->start_more(str);
	return 1;
}

int do_qu(string arg)
{
	int num,i,v;
	string file,str,name,id,*ids,*tmp;
	mapping prop,temp,dbase;
	object obj,me = this_player();

	if( !arg || sscanf(arg,"%d",num)!=1 )
		return err_msg("如果想取出，请用命令 qu <物品编号>\n");
	if( check_owner(me) || this_object()->is_busy() )
		return err_msg(name()+"现在正忙。\n");
	if( me->is_busy() )
		return err_msg("你现在正忙。\n");
	me->start_busy(3);		
	set("serve_id",me->query("id"));
	restore();
	start_busy(1);
	prop = query("store");
	if( !prop || !mapp(prop) )
	{
		delete("serve_id");
		delete("store");
		return err_msg("暂时没有找到你的仓库记录。\n");
	}
	if( undefinedp(prop[num]) )
	{
		delete("serve_id");
		delete("store");
		return err_msg("暂时没有找到你的仓库记录。\n");
	}
		
	temp = prop[num];
	file = temp["file"];
	name = temp["name"];
	ids = temp["ids"];
	if( !undefinedp(temp["num"]) )
		v = temp["num"];
	else	v = 1;
	dbase = temp["dbase"];
	
	obj = new(file);
	if( !obj )
	{
		delete("serve_id");
		delete("store");
		return err_msg("暂时没有找到你的物品。\n");
	}
	obj->init_weapon(1);
	obj->set_name(name,ids);
	obj->setup();
	tmp = keys(dbase);
	for(i=0;i<sizeof(tmp);i++)
	{
		if( tmp[i]=="actions" )
			continue;
		obj->set(tmp[i],dbase[tmp[i]]);
	}
	if( v>1 )
		obj->set_amount(v);		
	if( obj->move(me) )
	{
		map_delete(prop,num);
		set("store",prop);
		if( save() )
		{
			tell_object(me,name()+"将"+obj->name()+"交给了你。\n");
			delete("serve_id");
			delete("store");
			return 1;
		}
		else
		{
			if( obj )
				destruct(obj);
			delete("serve_id");
			delete("store");
			return err_msg("你的仓库保存失败。\n");		
		}
	}
	else
	{
		if( obj ) destruct(obj);
		delete("serve_id");
		delete("store");
		return err_msg("你身上的家什太多了。\n");		
	}	
}

void kill_ob(object who)
{
	message_vision("$N朝$n摇了摇头。\n",this_object(),who);
	all_inventory(environment())->remove_killer(this_object());
	this_object()->remove_all_killer();
	return;
}

void fight_ob(object who)
{
	kill_ob(who);
}

void die()
{
	powerup(0,1);
	all_inventory(environment())->remove_killer(this_object());
	this_object()->remove_all_killer();
	return;
}

void unconcious()
{
	die();
}
		