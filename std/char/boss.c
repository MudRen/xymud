#include <ansi.h>
inherit NPC;

nosave mapping Hurt;
nosave object *Rewards;
nosave object *First;
void init_reward();

void fullme()
{
	this_object()->powerup();
	this_object()->clear_condition();
	this_object()->set("mana",this_object()->query_maxmana()*2);
	this_object()->set("force",this_object()->query_maxforce()*2);
}

void setup()
{
	::setup();
	init_reward();
	set("env/no_accept_surrender",1);
	add_temp("apply/max_kee",this_object()->query_level()*50);
	add_temp("apply/max_sen",this_object()->query_level()*50);
	add_temp("apply/max_force",this_object()->query_level()*15);
	add_temp("apply/max_mana",this_object()->query_level()*15);
	Hurt = ([]);
	fullme();
}

mapping query_hurt()
{
	if( !Hurt || !mapp(Hurt) )
		return 0;
	return Hurt;
}	

object max_hurt()
{
	int i,max = 1;
	string id,*str;
	if( !environment() )
		return 0;
	if( !Hurt || !mapp(Hurt) )
		return 0;
	str = keys(Hurt);
	if( !str || !arrayp(str) || sizeof(str)<1 )
		return 0;
	i = sizeof(str);
	id = 0;
	while(i--)
	{
		if( Hurt[str[i]]>=max )
		{
			max = Hurt[str[i]];
			id = str[i];
		}	
	}
	if( !id || !stringp(id) )
		return 0;
	return present(id,environment());	
}

object select_opponent()
{
	object ob,*enemy;
	enemy = query_enemy();
	ob = max_hurt();
	if( !ob || member_array(ob,enemy)==-1 )
		return ::select_opponent();
	else	return ob;	
}

varargs int receive_damage(string type, int damage, object who,mixed attack_type)
{
	string id;
	int p;
	if( !who || who==this_object() || damage<100 || !objectp(who) )
		return ::receive_damage(type,damage,who,attack_type);
	if(objectp(who->query_temp("invoker")))
		who=who->query_temp("invoker");
	if( !userp(who) )
		return ::receive_damage(type,damage,who,attack_type);
	if( who->query_temp("pending/"+query("name")) )
		return ::receive_damage(type,damage,who,attack_type);
	id = who->query("id");
	p = damage/100;
	if( p<1 )
		p = 1;
	if( !Hurt || !mapp(Hurt) )
		Hurt = ([id : p ]);
	else if( undefinedp(Hurt[id]) )
		Hurt[id] = p;
	else	Hurt[id]+= p;
	return ::receive_damage(type,damage,who,attack_type);
}			

varargs int receive_wound(string type, int damage, object who,mixed attack_type)
{
	string id;
	int p;
	if( !who || who==this_object() || damage<80 || !objectp(who) )
		return ::receive_wound(type,damage,who,attack_type);
	if(objectp(who->query_temp("invoker")))
		who=who->query_temp("invoker");
	if( !userp(who) )
		return ::receive_wound(type,damage,who,attack_type);
	if( who->query_temp("pending/"+query("name")) )
		return ::receive_wound(type,damage,who,attack_type);
		
	id = who->query("id");
	p = damage/80;
	if( p<1 ) p = 1;
	if( !Hurt || !mapp(Hurt) )
		Hurt = ([id : p ]);
	else if( undefinedp(Hurt[id]) )
		Hurt[id] = p;
	else	Hurt[id]+= p;
	return ::receive_wound(type,damage,who,attack_type);
}

string query_hurt_msg()
{
	mixed *temp;
	int i,k,j,damage,*val;
	string id,*str,arg,msg;
	object who;
	if( !environment() )
		return 0;
	if( !Hurt || !mapp(Hurt) )
		return 0;
	str = keys(Hurt);
	if( !str || !arrayp(str) || sizeof(str)<1 )
		return 0;
	arg = "    "BBLU HIW" ╔───────────────────────────╗"NOR"\n";
	arg+= "    "BBLU HIW" ║                  "HIY"输   出   统   计"HIW"                   ║"NOR"\n";
	arg+= "    "BBLU HIW" ╟───────────────────────────╢"NOR"\n";
	
	i = sizeof(str);
	while(i--)
	{
		id = str[i];
		who = present(id,environment());
		if( !who )
			continue;
		damage = Hurt[id];
		arg+= sprintf("    "BBLU HIW" ║  "HIG"%40-s "HIR"%9d "HIW" ║"NOR"\n",who->name()+"("+who->query("id")+")",damage);
	}
	arg+= "    "BBLU HIW" ╟───────────────────────────╢"NOR"\n";
	arg+= "    "BBLU HIW" ║                  "HIY"输   出   排   名"HIW"                   ║"NOR"\n";
	arg+= "    "BBLU HIW" ╟───────────────────────────╢"NOR"\n";
	val = values(Hurt);
	val = sort_array(val,-1);
	reset_eval_cost();
	for(i=0;i<sizeof(val);i++)
	{
		temp = ({});
		for(k=0;k<sizeof(str);k++)
		{
			if( Hurt[str[k]]==val[i] )
			{
				who = present(str[k],environment());
				if( !who || who->query_temp("pending/"+query("name")) )
					continue;
				if( member_array(who,temp)==-1 )
					temp+= ({who});	
			}
		}
		if( sizeof(temp)<1 )
			continue;
		msg = "";	
		for(j=0;j<sizeof(temp);j++)
			msg+= sprintf("%s(%s) ",temp[j]->query("name"),temp[j]->query("id"));
		arg+= sprintf("    "BBLU HIW" ║ "HIY"%2d"HIG" %40-s "HIR"%8d"HIW" ║"NOR"\n",(i+1),msg,val[i]);
	}
	arg+= "    "BBLU HIW" ╟───────────────────────────╢"NOR"\n";
	who = max_hurt();
	if( who && objectp(who) )
		arg+= sprintf("    "BBLU HIW" ║ "HIR"最大伤害输出  "HIY"%38s"HIW" ║"NOR"\n",who->name()+"("+who->query("id")+")");
	arg+= "    "BBLU HIW" ╚───────────────────────────╝"NOR"\n";
	return arg;
}

void die_msg()
{
	string str;
	str = query_hurt_msg();
	if( str && stringp(str) )
		message_vision("\n"+str+"\n",this_object());
}	

void kill_ob(object who)
{
	if( !who || !present(who,environment()) )
	{
		this_object()->fullme();
		::kill_ob(who);		
		return;
	}
	if( !this_object()->is_fighting() )
	{
		this_object()->fullme();
		Hurt = ([]);
	}
	::kill_ob(who);
}			

void unconcious()
{
	die();
}

string query_maze_file(){return "maze";}

string query_log_file()
{
	if( !query("name") )
		return "NONE";
	return sprintf("/log/maze/%s_%s",query_maze_file(),query("name"));
}

string query_reward_file()
{
	if( !query("name") )
		return 0;
	return sprintf("/doc/maze/%s_%s",query_maze_file(),query("name"));
}

string obj_from(){return 0;}

string reward_ob(object who)
{
	object obj,*list,*team,leader;
	string str,log1,name,reward,t_name;
	int money,i,Te = 0;
	if( !who || !living(who) 
	|| !environment() 
	|| !present(who,environment())
	|| !userp(who) 
	|| who->query_temp("pending/"+query("name")) )
		return 0;
	log1 = query_log_file();
	if( log1=="NONE" )
		return 0;

	name = " "+who->query("name")+"("+who->query("id")+")";	
	who->set_temp("pending/"+query("name"),1);
	team = who->query_team();
	if( team && arrayp(team) && sizeof(team)>1 )
	{
		leader = who->query_leader();
		if( leader )
			Te = 1;
		else	Te = 0;	
	}
	if( Te==1 )
	{
		for(i=0;i<sizeof(team);i++)
		{
			if( team[i]==leader )
				continue;
			team[i]->set_temp("pending/"+query("name"),1);
			if( present(team[i],environment()) )
				name+= " "+team[i]->query("name")+"("+team[i]->query("id")+")";
		}
	}
	reward="";
	money = query("reward_gold");
	if( money>0 )
	{
		who->money_add(money);
		reward+= MONEY_D->money_str(money);	
	}	
	if( file_size(log1)<=0 )
	{
		if( Te==1 )
		{
			t_name = who->query_team_name();
			if( !t_name || !stringp(t_name) || t_name=="默认组队" )
				t_name = "队伍";
			message("shout",HIR"【小雨西游】"HIY+leader->name(1)+HIR"带领的"+t_name+HIR"完成了对"HIY+query("name")+HIR"的首杀！"NOR"\n",users());
		}
		else	message("shout",HIR"【小雨西游】"HIY+who->name(1)+HIR"完成了对"HIY+query("name")+HIR"的首杀！"NOR"\n",users());	
		str = NATURE_D->game_time()+name+" 完成了对"+query("name")+"的首杀。\n";
		write_file(log1,str);
		i = who->query_kar();
		i = i/40;
		i+= random(2);
		if( i>3 || wizardp(who) )
			i = 3;
		while(i--)
		{	
			list = query("first_obj");
			if( !list || !arrayp(list) || sizeof(list)<1 )
				continue;
			obj = list[random(sizeof(list))];
			if( !obj || environment(obj) )
				continue;
			if( obj->move(who) )
			{
				list-= ({obj});
				list-= ({0});
				if( sizeof(list)>0 )
					set("first_ob",list);
				else	delete("first_ob");
				if( reward!="" )
					reward+= "、";
				reward+= obj->name()+"("+obj->parse_command_id_list()[1]+")";
			}	
			else	continue;
		}
	}
	list = query("rewards_obj");
	if( list && arrayp(list) && sizeof(list)>0 )
	{
		obj = list[random(sizeof(list))];
		if( !obj || environment(obj) )
			return 0;
		if( obj->move(who) )
		{
			list-= ({obj});
			list-= ({0});
			if( sizeof(list)>0 )
				set("rewards_obj",list);
			else	delete("rewards_obj");	
			if( reward!="" )
				reward+= "、";
			reward+= obj->name()+"("+obj->parse_command_id_list()[1]+")";	
		}
	}
	if( reward!="" )
		reward = COLOR_D->clean_color(reward);
	return reward;
}

object create_reward(string file,int num)
{
	object obj;
	string *armor,*weapon,from;
	if( !file || !stringp(file) )
		return 0;
	armor = ({
		"armor","cloth","hand","kui","neck","pifeng","ring","shield","shoes","waist","wrists",
	});
	weapon = ({
		"axe","blade","fork","hammer","mace","spear","staff","stick","sword","unarmed","whip",
	});
	from = this_object()->obj_from();
	if( member_array(file,armor)!=-1 )
	{
		obj = new("/d/obj/narmor/"+file);
		this_object()->add_temp("apply/karma",10000);
		obj->init_armor(this_object());
		this_object()->add_temp("apply/karma",-10000);
		if( from && stringp(from) )
			obj->set("from",from);
		return obj;
	}
	else if( member_array(file,weapon)!=-1 )
	{
		obj = new("/d/obj/nweapon/"+file);
		this_object()->add_temp("apply/karma",10000);
		obj->init_weapon(this_object());
		this_object()->add_temp("apply/karma",-10000);
		if( from && stringp(from) )
			obj->set("from",from);
		return obj;
	}
	else if( file=="金钱" )
		;
	else
	{
		obj = new(file);
		if( !obj )
			return 0;
		if( num>1 )
			obj->set_amount(num);
		return obj;		
	}
}

void init_reward()
{
	object obj;
	string file,*tmp,rwd,*files,obj_file,log;
	int i,per,num,first=0;
	Rewards = ({});
	First = ({});
	if( !environment() )
		return;
	file = query_reward_file();
	if( !file || !stringp(file) || file_size(file)<=0 )
		return;
	file = read_file(file);	
	tmp = explode(file,"\n");
	if( !tmp || !arrayp(tmp) || sizeof(tmp)<1 )
		return;
	log = query_log_file();
	if( log!="NONE" )
	{
		if( file_size(log)<=0 )
			first = 1;
	}		
	reset_eval_cost();
	for(i=0;i<sizeof(tmp);i++)
	{
		if( sscanf(tmp[i],"1/%d %s",per,rwd)!=2 )
			continue;
		//首杀设置
		if( per==2013 && first )
		{
			if( sscanf(rwd,"%s %d",obj_file,num)==2 )
				;
			else
			{
				obj_file = rwd;
				num = 1;
			}
			set("test_file/"+i,obj_file);
			if( strsrch(obj_file,"|")==-1 )
			{
				if( obj_file=="金钱" )
					;
				else
				{
					obj = create_reward(obj_file,num);
					if( obj )
						First+= ({obj});
					obj = 0;	
				}	
			}
			else
			{
				files = explode(obj_file,"|");
				if( !files || !arrayp(files) || sizeof(files)<1 )
					continue;
				obj_file = files[random(sizeof(files))];
				if( !obj_file )
					continue;
				obj = create_reward(obj_file,num);
				if( obj )
					First+= ({obj});
				obj = 0; 		
			}
			set("first_obj",First);			
		}
		if( first )
			per = per/5;	
		if( random(per)!=0 )
			continue;
		if( sscanf(rwd,"%s %d",obj_file,num)==2 )
			;
		else
		{
			obj_file = rwd;
			num = 1;
		}
		if( strsrch(obj_file,"|")==-1 )
		{
			if( obj_file=="金钱" )
				this_object()->set("reward_gold",num);
			else
			{
				obj = create_reward(obj_file,num);
				if( obj )
					Rewards+= ({obj});
				obj = 0;	
			}	
		}
		else
		{
			files = explode(obj_file,"|");
			if( !files || !arrayp(files) || sizeof(files)<1 )
				continue;
			obj_file = files[random(sizeof(files))];
			if( !obj_file )
				continue;
			obj = create_reward(obj_file,num);
			if( obj )
				Rewards+= ({obj});
			obj = 0; 		
		}					
	}
	set("rewards_obj",Rewards);
}	 	