//挑战NPC设定
#include <ansi.h>
inherit NPC;

void setname(){return;}
void reward_ob(object who);
int is_job(){return 1;}       
int is_job2(){return 1;}       

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
	add_temp("apply/karma",30000);
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
}

void create()
{
	set_name("门派精灵",({"menpai"}));      
	set("combat_exp", 70000000);
	set("env/brief_message",4);
	set("daoxing", 7000000);
	set("fangcun/panlong_accept","done");
	set("no_sleep",1);
	set("任务",1);
	setname();
	setup();
	add_temp("apply/damage",300);
    add_temp("apply/armor",500);
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

void reward_ob(object who)
{
	object gift,weapon;    
	mapping skill;
	string *skills,temp,*ar;
	int i,pp;

	this_object()->powerup(1);	
	if( !who || !userp(who) )
		return;
	if( time()<who->query("mark/tiaozhan/last_die")+3600      	//假死时间没到
	 || who->query("combat_exp")<10000
	 || who->query("daoxing")<10000 
	 || !who->query("obstacle/reward") )	
		tell_object(who,"你条件不够，无法在此地图得到任何附加奖励。\n");
	else
	{
		pp = who->query_kar();
		pp = 100-pp;
		pp/= 10;
		if( pp<1 )
			pp = 1;
		if( random(pp)==0 )
		{
			ar = ({
				"armor","hand","cloth","kui","neck","pifeng",
				"ring","shoes","waist","wrists",
			});	
			gift = new("/d/obj/narmor/"+ar[random(sizeof(ar))]);
			i = 20000;
			i = i+who->query_kar()*10;
			set_temp("apply/karma",i);
			pp = 250+random(200);
			set_skill("force",pp);
			gift->init_armor(this_object());
			if( gift->move(who) )
			{
				CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
				who->add("combat_exp",-5000);
				who->add("daoxing",-5000);
				tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
			}
			else	destruct(gift);
		}
		else
		{
			ar = ({
				"axe","blade","fork","hammer","mace","spear","staff","stick","sword","unarmed","whip",
			});	
			gift = new("/d/obj/nweapon/"+ar[random(sizeof(ar))]);
			i = 20000;
			i = i+who->query_kar()*10;
			set_temp("apply/karma",i);
			set_skill("force",300+random(400));
			gift->init_weapon(this_object());
			if( gift->move(who) )
			{
				CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
				who->add("combat_exp",-5000);
				who->add("daoxing",-5000);
				tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");		 
			}
			else	destruct(gift);
		}	

		gift = 0;
                if( random(30)>25 )
			gift = new(sprintf("/d/obj/equip/armor_bd%d",3+random(3)));
                else if( random(100)>88 )      
			gift = new(sprintf("/d/obj/equip/weapon_bd%d",3+random(3)));
		
		if( gift )
		{	
			if( gift->move(who) )
			{
				CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->name()+HIC"。"NOR);			   
				who->add("combat_exp",-3000);
				who->add("daoxing",-3000);
				tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");		 
			}
				else	destruct(gift);
		}
		who->add("mark/tiaozhan/top1_kill",1);
		who->save();
		message_vision(HIY"\n$N"HIY"欣慰的对$n"HIY"一稽首：这位"+RANK_D->query_respect(who)+"果真是天赋异禀，少年有为。日后除魔卫道的重任就要靠你了。\n"NOR,this_object(),who);
		message_vision(HIY"$N"HIY"似乎想起来什么，变得有些心思索然，也不开口，将身一摇，化作一道金光冲天而去！\n"NOR,this_object());
		destruct(this_object());
	}
	return;
}

void heart_beat()
{
	object me = this_object();
	string str;
	int busy,hh;
	
	if( !me->is_fighting() )
		hh = 0;
	else
		hh = 3;	
	
	busy = me->query_busy();
	if( busy>hh )
	{
		me->stop_busy();
		if( hh>0 )
			me->start_busy(hh);
	}	

	if( query("force")>100 )
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
	if( me->is_fighting() && living(me) && !me->is_busy() )
	{
		if( objectp(query_temp("weapon")) )
      		str = query_temp("weapon")->query("skill_type");
		else
			str = "unarmed";
		QUEST_D->randomPfm(this_object(),str);
    }       
	::heart_beat();
}

void kill_ob(object who)
{
	int lvl,max_skill,i,wx,kee,sen,force,mana;
	mapping skill;
	string *skills;
	object ob;
	if( !environment() || !who )
		return;
	if( !userp(who) )
	{
		if( who->is_job() )
		{
			remove_killer(who);
			who->remove_killer(this_object());
			return;
		}
		::kill_ob(who);
		return;
	}
	if( this_object()->is_fighting() )
	{
		ob = query_temp("my_killer");
		if( !ob || !present(ob,environment()) )
		{
			powerup(1);
			delete_temp("my_killer");
			remove_all_killer();
			all_inventory(environment())->remove_killer(this_object());
			return;
		}
	}

	if( this_object()->is_fighting() )
	{
		if( ob==who )
			::kill_ob(who);
		else
		{
			message_vision("$N朝$n摇了摇头，说道：我的对手是"+ob->name()+"。\n",this_object(),who);
			remove_killer(who);
			who->remove_killer(this_object());
			return;
		}
	}
	
	else
	{
		lvl = who->query("mark/tiaozhan/top1_kill");
		if( lvl<1 ) lvl = 1;
		max_skill = QUEST_D->maxSkill(who,1);
		if( max_skill<700 )
			max_skill = 700;
		max_skill+= random(10)*lvl;
		skill = query_skills();
		skills = keys(skill);
		for(i=0;i<sizeof(skills);i++)
		{
			if( skill[skills[i]]<max_skill )
				skill[skills[i]] = max_skill;
		}
	
		kee = who->query("max_kee")*5/2+1000*lvl;
        sen = who->query("max_sen")*5/2+1000*lvl;
		this_object()->add("max_kee",kee);
		this_object()->add("max_sen",kee);
		this_object()->powerup();							
		force = max_skill*15+1200*lvl;
		this_object()->set("max_force",force);
		this_object()->set("max_mana",force);
		this_object()->set("force",force*2);
		this_object()->set("mana",force*2);
		wx = who->query("combat_exp");
		if( wx>query("combat_exp") )
			set("combat_exp",wx);
		wx = who->query("daoxing");
		if( wx>query("daoxing") )
			set("daoxing",wx);
		set_temp("my_killer",who);
		::kill_ob(who);
	}
}

varargs int receive_damage(string type, int damage, object who,mixed attack_type) 
{
	if( damage>query("max_kee")/8 )
		damage = query("max_kee")/16+random(query("max_kee")/16);
    return ::receive_damage(type,damage,who,attack_type); 
}

varargs int receive_wound(string type, int damage, object who,mixed attack_type) 
{
	if( damage>query("max_kee")/10 )
		damage = query("max_kee")/20+random(query("max_kee")/20);
    return ::receive_wound(type,damage,who,attack_type);
}

