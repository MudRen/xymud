//挑战NPC设定
#include <ansi.h>
inherit NPC;

void setname(){return;}
void reward_ob(object who);
int is_job(){return 1;}       

int is_pass(object who)
{
	if( !who )
		return 0;
	return who->query("mark/tiaozhan/"+query("name"));
}

void setup()
{
	mapping my;
	int qi,shen,i;
	string myforce,myspells,*gifts;
	int myforce_lvl,myspells_lvl;
	object ob = this_object();

	my = query_entire_dbase();
	my["max_force"] = query_skill("force")/2*50;
	my["max_mana"] = query_skill("spells")/2*30;
	my["mana"] = my["max_mana"]*2;
	my["force"] = my["max_force"]*2;
	if( undefinedp(my["age"]) ) my["age"] = random(30) + 15;
	gifts = ({
		"str","cor","int","cps","per","con","kar"
	});
	for(i=0;i<sizeof(gifts);i++)
		if( undefinedp(my[gifts[i]]) ) 
			my[gifts[i]] = random(21) + 10;
	qi= (my["con"]+my["str"])/2;
	shen= (my["spi"]+my["int"])/2;

	if( undefinedp(my["max_kee"]) ) 
	{
		if( my["age"]<=30 ) 
			my["max_kee"] = (my["age"]-4)*qi;
		else    my["max_kee"] = 26*qi;
		myforce=ob->query_skill_mapped("force");
		myforce_lvl=ob->query_skill("force");
		my["max_kee"]+= myforce_lvl*3;
		if( my["max_force"]>0 ) 
			my["max_kee"] += my["max_force"]*2/5;
		if( my["max_kee"]<1 ) 
			my["max_kee"]=1;
	}
	if( undefinedp(my["max_sen"]) ) 
	{
		if( my["age"] <= 14 ) my["max_sen"] = 10*shen;
		else if( my["age"] <= 30 ) my["max_sen"] = (my["age"] - 4) *shen;
		else if( my["age"] <= 40 ) my["max_sen"] = 26 * shen;
		else    
		{
			if( my["fake_age"] <= 40 )
				my["max_sen"] = 26 * shen;
			else    my["max_sen"] = 26 * shen - (my["fake_age"]- 40) * 5;
		}
		myspells=ob->query_skill_mapped("spells");
		myspells_lvl=ob->query_skill("spells");
		my["max_sen"]+=myspells_lvl*3;
		if( my["max_mana"]>0 ) 
			my["max_sen"] += my["max_mana"]*2/5;
		if( my["max_sen"]<1 ) 
			my["max_sen"]=1;
	}
	if( undefinedp(my["unit"])) my["unit"]="位";
	if( undefinedp(my["gender"])) my["gender"]="男性";
	if( undefinedp(my["can_speak"])) my["can_speak"]=1;
	if( undefinedp(my["attitude"])) my["attitude"]="peaceful";
	if( undefinedp(my["limbs"])) 
		my["limbs"]= ({
			"头部", "颈部", "胸口", "后心", "左肩", "右肩", "左臂",
			"右臂", "左手", "右手", "腰间", "小腹", "左腿", "右腿",
			"左脚", "右脚"
		});
	set_heart_beat(1);
	enable_player();
	set_max_items(30);
	this_object()->update_age(); // mon 7/3/99
	if( !query("race") )
		set("race", "人类");
	if( !query_max_encumbrance() )
		set_max_encumbrance( my["str"]*5000 +query_skill("unarmed",1)*200);
	reset_action();
	set("force_factor",query_skill("force")/4);
	set("mana_factor",query_skill("spells")/4);
	set("food",1000);
	set("water",1000);
	::setup();
	powerup(1);     
	set("env/no_teach",1);			
        set("任务",1);                  
	i = 5000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"armor",1)->wear();
	carry_object(0,"hand",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"neck",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"waist",1)->wear();
	carry_object(0,"wrists",1)->wear();
	add_temp("apply/karma",-i);
}

void create()
{
	set_name("门派精灵",({"menpai"}));      
	set("combat_exp", 70000000);
	set("env/brief_message",3);
	set("daoxing", 7000000);
	set("fangcun/panlong_accept","done");
	set("no_sleep",1);
	set("任务",1);
	setname();
	setup();
	add_temp("apply/damage",50);
	add_temp("apply/armor",100);
}

int accept_fight(object who){return 0;}

int prevent_learn(object me,string skill)
{
	command("say 我久不授徒，已尽数忘光了，你还是去 开来 找合适你的师傅吧。");
	return 1;
}

void tell_object(object who,string arg)
{
	arg = HIG"【星月挑战】"+arg+NOR;
	return efun::tell_object(who,arg);
}


void heart_beat()
{
object me = this_object();
if( me->query("force")>50 )
{
        if( me->is_boss() )
	{
        	if( query("eff_kee") < query("max_kee") )
        		QUEST_D->addEffKee(me);
        	if( query("kee") < query("eff_kee") )
        		QUEST_D->addKee(me);
        	if( query("sen") < query("eff_sen") )
        		QUEST_D->addSen(me);
        	if( query("eff_sen") < query("max_sen") )
        		QUEST_D->addEffSen(me);
       }
       else if( random(3)==0 )
	{
        	if( query("eff_kee") < query("max_kee") )
        		QUEST_D->addEffKee(me);
        	if( query("kee") < query("eff_kee") )
        		QUEST_D->addKee(me);
        	if( query("sen") < query("eff_sen") )
        		QUEST_D->addSen(me);
        	if( query("eff_sen") < query("max_sen") )
        		QUEST_D->addEffSen(me);
       }        		
}
::heart_beat();
}

void reward_ob(object who)
{
	object gift,weapon;    
	mapping skill;
	string *skills,temp,*ar;
	int i,pp;
	
	remove_call_out("tiaozhan_hit");
	if( !who )
		return;
	if( time()<who->query("mark/tiaozhan/last_die")+3600      	//假死时间没到
	 || who->query("combat_exp")<10000
	 || who->query("daoxing")<10000 
	 || !who->query("obstacle/reward") )	
	{	 	
		tell_object(who,"你条件不够，无法在此地图得到任何附加奖励。\n");
		return;
	}
	if( query("id")!=environment()->query("master") )
	{
		who->add("mark/tiaozhan/"+environment()->query("master")+"_dizi_killed",1);
		pp = who->query("mark/tiaozhan/"+environment()->query("master")+"_dizi_killed");
		if( pp<1 )
			pp = 1;
		if( random(pp)==0 )
		{	       
			who->add("obstacle/rebirth",-1); 
			tell_object(who,"佛祖奖励你一根救命毫毛。\n");  
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了一根救命毫毛。"NOR);
			who->add("combat_exp",-3000);
			who->add("daoxing",-3000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了2000点的武学和道行。\n");
		}
/*		
		pp = who->query_temp("tiaozhan_weapon_get");
		if( pp<5 )
			pp = 5;
		if( wizardp(who) )
			pp = 2; 
		if( random(pp)==0 && who->query("新任务/镖_pot")>=10 )
		{
			gift = new("/obj/weapon");
			if( gift && gift->move(who) )
			{
				CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->name()+HIC"。"NOR);
				who->add("新任务/镖_pot",-3);
				who->save();
				tell_object(who,"因为获得追加奖励，你的灵力减少了三点。\n"); 
				who->add_temp("tiaozhan_weapon_get",1);
			}
		}
*/		
	}
	else
	{
                if( !is_pass(who) && query("id")==environment()->query("master") )
		{
			who->set("mark/tiaozhan/"+query("name"),1);
			who->add("mark/tiaozhan/num",1);
		}
		
		if( random(30)>25 )
		{
			who->add("potential",30000);	
			tell_object(who,"你获得了30000点潜能。\n");
			who->add("combat_exp",-3000);
			who->add("daoxing",-3000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");
		}			
		pp = who->query_temp("tiaozhan_armor_get");
		if( pp<5 )
			pp = 5;
		pp+= 5;			
		if( wizardp(who) )
			pp = 2; 
		if( random(pp)==0 )
		{
			ar = ({
				"armor","hand","cloth","kui","neck","pifeng",
				"ring","shoes","waist","wrists",
			});	
			gift = new("/d/obj/narmor/"+ar[random(sizeof(ar))]);
			i = environment()->query("number");
			i = 1000+i*300;
			i = i+who->query_temp("apply/karma")*10;
			i = i-pp*100;
			add_temp("apply/karma",i);
			gift->init_armor(this_object());
			add_temp("apply/karma",-i);
			if( gift->move(who) )
			{
				CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
				who->add_temp("tiaozhan_armor_get",1);
				who->add("combat_exp",-3000);
				who->add("daoxing",-3000);
				who->save();
				tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");		 
			}
			else	destruct(gift);
		}
		else
		{
			pp = who->query_temp("tiaozhan_weapon_get");
			if( pp<5 )
				pp = 5;
			pp+= 10;	
			if( wizardp(who) )
				pp = 2; 
			if( random(pp)==0 )
			{
				weapon = who->query_temp("weapon");
				if( !weapon )
					temp = "unarmed";
				else
					temp = weapon->query("skill_type");
				temp = "/d/obj/nweapon"+temp;
				if( file_size(temp+".c")>0 )
				{									
					gift = new("/d/obj/nweapon"+temp);
					i = environment()->query("number");
                                        i = 3000+i*500;
					i = i+who->query_temp("apply/karma")*10;
					i = i-pp*150;
					add_temp("apply/karma",i);
					gift->init_weapon(this_object());
					add_temp("apply/karma",-i);
					if( gift->move(who) )
					{
						CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
						who->add_temp("tiaozhan_weapon_get",1);
						who->add("combat_exp",-3000);
						who->add("daoxing",-3000);
						who->save();
						tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");		 
					}
					else	destruct(gift);
				}	
				i = 0;
			}
			else if( random(30)==25 )
			{
				gift = new(sprintf("/d/obj/equip/armor_bd%d",1+random(4)));
				if( gift->move(who) )
				{
					CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
					who->add_temp("tiaozhan_armor_get",1);
					who->add("combat_exp",-2000);
					who->add("daoxing",-2000);
					who->save();
					tell_object(who,"因为获得追加奖励，你失去了2000点的武学和道行。\n");		 
				}
				else	destruct(gift);
			}
		}
	}
	return;
}

varargs int receive_damage(string type, int damage, object who,mixed attack_type) 
{
	QUEST_D->addKee(this_object());
	QUEST_D->addSen(this_object());
	return ::receive_damage(type,damage,who,attack_type); 
}

varargs int receive_wound(string type, int damage, object who,mixed attack_type) 

{
	QUEST_D->addEffKee(this_object());
	QUEST_D->addEffSen(this_object());		
	return ::receive_wound(type,damage,who,attack_type);
}

void help_kill(object who)
{
	int i,f=0;
	object *inv,npc;
	if( !who )      return;
	inv = all_inventory(environment());
	for(i=0;i<sizeof(inv);i++)
	{
		npc = inv[random(sizeof(inv))]; 
		if( npc && living(npc) && !userp(npc) //玩家或昏迷的
		 && !npc->is_fighting(who)		     //在战斗的
		 && npc!=this_object()			  //..
		 && f< 2
		 && npc->query("my_master")==query("id") )		  //非挑战NPC
		{
			say( sprintf("%s在旁说道：%s道友，休要惊慌，我来助你一臂之力。\n",npc->name(),this_object()->name(1)[0..1]));
			npc->set_temp("help_kill",1);
			npc->kill_ob(who);
			f++;
		}
	}
	return;       
}

void tiaozhan_hit(object who)
{
	return;
}
	
void kill_ob(object who)
{
	if( !who || !present(who,environment()) )  
	{	
		powerup(1);
		remove_all_killer();
		all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( this_object()->is_boss() )
		help_kill(who);
        if( !this_object()->is_fighting() && userp(who) )
		call_out("tiaozhan_hit",1+random(3),who);
	::kill_ob(who);
}
