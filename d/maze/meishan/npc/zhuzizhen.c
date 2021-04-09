#include <ansi.h>
#include <combat.h>
inherit BOSS;

int chat()
{ 
	mixed bz; 
	int damage;
	object weapon2,weapon3,target,weapon,me=this_object(); 
	if( !environment() 
	 || !living(this_object()) 
	 || !this_object()->is_fighting() 
	 || query("force")<100 ) 
	 	return 0; 
	if( me->is_busy() ) 
		me->stob_busy(1+random(3)); 
	if( me->is_busy() ) 
		return 0; 
	target = me->select_opponent(); 
	if( !target )
        	return 0;
        	
	if( random(3)==0 && !me->query_temp("powerup") )
		command("exert powerup");
			
        if( random(4)==0 && !me->is_busy() )
		command("exert sheqi");		
        
        if( time()>query_temp("super_attack")+15 )
        {
        	if( ( query("kee")<query("eff_kee")/10 && query("kee")>query("eff_kee")/50 )
                  ||( query("sen")<query("eff_sen")/10 && query("sen")>query("eff_sen")/50 ) 
                  ||( query("eff_kee")<me->query_maxkee()/10 && query("eff_kee")>me->query_maxkee()/50 ) 
                  ||( query("eff_sen")<me->query_maxsen()/10 && query("eff_sen")>me->query_maxsen()/50 ) )
		{
			set_temp("super_attack",time());
			message_vision(HIB"\n\n$N"HIB"摇动妖身，背后忽地冲出一头丈许的野猪，张开血盆大口朝向$n"HIB"咬去！\n"NOR,me,target);
			if( random(3)==0 )
				message_vision("结果被$N闪开了。\n\n",target);
			else
			{
				damage = target->query_maxkee()/3;
				message_vision("结果咬了个正着！\n",me);
				target->receive_damage("kee",damage,me,TYPE_CAST);	
				target->receive_wound("kee",damage,me,TYPE_CAST);
				target->set_temp("death_msg","被一头野猪咬得"HIR"死无全尸"HIM"！"NOR);
				COMBAT_D->report_status(target);
				COMBAT_D->report_status(target,1);
			}
                }
	}                           
        
	weapon = query_temp("weapon");
	if( weapon && !me->is_busy() )
	{	
		switch(weapon->query("skill_type"))
		{
			case "whip" :
				weapon2 = present("sword",me);
				weapon3 = present("stick",me);
				if( !me->query_temp("ldlh") && random(3)==0 )
					command("perform ldlh");
				if( !me->query_temp("hell_XY") && random(3)==0 )
					command("perform xingyun");
				if( random(5)==0 )
					command("perform biluo");
				else
				{ 
					if( time()-(int)me->query_temp("hell_three")>=6 && random(4)==0 )
						command("perform three");
					else if( weapon2 )
					{
						weapon->unequip();
						weapon2->wield();
						if( random(4)==0 )
							command("perform yanluo");
						if( random(3)==0 )
							command("perform three");
						weapon2->unequip();
						weapon->wield();
					}
					if( weapon3 )
					{
						weapon->unequip();
						weapon3->wield();
						if( random(3)==0 )
							command("perform suoming");
						if( random(3)==0 && time()-(int)me->query_temp("hell_three")>=6 )
							command("perform three");
						if( random(5)==0 )
							command("perform qmly");
						weapon3->unequip();
						weapon->wield();			
					}	
				}		
				break;	
			case "sword":
				weapon2 = present("whip",me);
				weapon3 = present("stick",me);
				if( random(4)==0 )
					command("perform yanluo");
				if( random(3)==0 )
					command("perform three");
				else if( weapon2 )
				{
					weapon->unequip();
					weapon2->wield();
					if( !me->query_temp("ldlh") && random(3)==0 )
						command("perform ldlh");
					if( !me->query_temp("hell_XY") && random(3)==0 )
						command("perform xingyun");
					if( random(5)==0 )
						command("perform biluo");
					weapon2->unequip();
					weapon->wield();	
				}				
				if( weapon3 )
				{
					weapon->unequip();
					weapon3->wield();
					if( random(3)==0 )
						command("perform suoming");
					if( random(3)==0 && time()-(int)me->query_temp("hell_three")>=6 )
						command("perform three");
					if( random(5)==0 )
						command("perform qmly");
					weapon3->unequip();
					weapon->wield();
				}
				break;
			case "stick":
				weapon2 = present("whip",me);
				weapon3 = present("sword",me);
				if( random(3)==0 )
					command("perform suoming");
				if( random(3)==0 && time()-(int)me->query_temp("hell_three")>=6 )
					command("perform three");
				if( random(5)==0 )
					command("perform qmly");
				else if( weapon2 )
				{
					weapon->unequip();
					weapon2->wield();
					if( !me->query_temp("ldlh") && random(3)==0 )
						command("perform ldlh");
					if( !me->query_temp("hell_XY") && random(3)==0 )
						command("perform xingyun");
					if( random(5)==0 )
						command("perform biluo");
					weapon2->unequip();
					weapon->wield();
				}
				if( weapon3 )
				{
					weapon->unequip();
					weapon3->wield();
					if( random(4)==0 )
						command("perform yanluo");
					if( random(3)==0 )
						command("perform three");
					weapon3->unequip();
					weapon->wield();
				}	
				break;
		}
	}
	else
	{
		if( query("eff_kee") < me->query_maxkee() )
			QUEST_D->addEffKee(me);
		if( query("kee") < query("eff_kee") )
                	QUEST_D->addKee(me);
		if( query("sen") < query("eff_sen") )
                	QUEST_D->addSen(me);
		if( query("eff_sen") < me->query_maxsen() )
                	QUEST_D->addEffSen(me);
		QUEST_D->randomPfm(me);
	}
	if( !me->is_busy() )
	{
		if( query("eff_kee")<me->query_maxkee() )
		 	command("eat yao");
		if( query("eff_sen")<me->query_maxsen() )
			command("eat dan");
		if( query("force")>30 )
		{
			if( query("kee")<query("eff_kee") )
				command("exert recover");
			if( query("sen")<query("eff_sen") )	
		 		command("exert refresh");
		 }		
	}			
	return 1;
}

void create()
{
        set_name("朱子真",({"zhu zizhen","zizhen","zhu"}));
        set_level(110);
        set("nickname", HIC"天地泥人"NOR);
        set("title","富贵大仙");
        set("gender", "男性" );
        set("age", 30);
        set("long", "
	面如黑漆甚蹊跷，海下髭须一剪齐。
	长唇大耳真凶恶，眼露光华扫帚眉。
	皂服绿绦飘荡荡，浑身冷气侵人肌。\n");
	set("class", "yaomo");
        set("attitude", "aggressive");
	set("force_factor", 300);
	set("mana_factor", 500);
	set("per",10);
	create_family("阎罗地府", 2, "弟子");
  	set_skill("jinghun-zhang", 1100);
 	set_skill("tonsillit",1100);
 	set_skill("gouhunshu",1100);
	set_skill("unarmed",1100);
 	set_skill("whip", 1100);
 	set_skill("stick", 1100);
 	set_skill("sword",1100);
 	set_skill("hellfire-whip",1100);
 	set_skill("zhuihun-sword",1100);
 	set_skill("kusang-bang",1100);
	set_skill("dodge",1100);
 	set_skill("ghost-steps",1100);
	set_skill("parry",1100);
 	set_skill("spells",1100);
 	set_skill("force",1100);
        map_skill("sword", "zhuihun-sword");
        map_skill("parry", "zhuihun-sword");
        map_skill("dodge", "ghost-steps");
        map_skill("unarmed", "jinghun-zhang");
        map_skill("force", "tonsillit");
        map_skill("whip", "hellfire-whip");
        map_skill("stick", "kusang-bang");
        map_skill("spells", "gouhunshu");
	set("env/test",({"HIB","HIR","HIM"})[random(3)]);
	setup();
	add_temp("apply/max_kee",10000);
	add_temp("apply/max_sen",10000);
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"hand",1)->wear();
	carry_object(0,"whip",1)->wield();
	carry_object(0,"sword",1);
	carry_object(0,"stick",1);
	carry_object("/d/obj/drug/jinchuang")->set_amount(300);
	carry_object("/d/obj/drug/hunyuandan")->set_amount(300);
	powerup(0,1);
}

string query_maze_file(){return "meishan";}

void dies()
{
	string *ids,re;
	int pp,p,i,base,damage_total;
	mapping hurt;
	object *team,corpse,who = query_temp("last_damage_from");
	message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",this_object());
	message_vision(HIB"一道黑光从尸身上窜出，直奔天际而去。\n\n"NOR,this_object());
	corpse = new("/obj/corpse");
	corpse->set_name("白猪尸体",({"baizhu's corpse","corpse"}));
	corpse->set("long","一只白猪的尸体。\n");
	if( corpse->move(environment()) )
		message_vision("\n黑雾散去，但见那遗下的尸骸却是一只白猪，原来是谁的一缕神识栖宿于此肉身作怪而已。\n",this_object());
	else	destruct(corpse);	
	if( !who || !present(who,environment()) || (who->query_level()>=120 && !wizardp(who)) 
	 || !userp(who) || who->query_temp("pending/"+query("name")) )
	{
		destruct(this_object());
		return;	
	}
	base = 200000;
	damage_total = 0;
	hurt = this_object()->query_hurt();
	if( hurt && mapp(hurt) )
	{
		ids = keys(hurt);
		if( ids && arrayp(ids) && sizeof(ids)>1 )
		{
			for(i=0;i<sizeof(ids);i++)
				damage_total+= hurt[ids[i]];	
		}
	}
	
	team = who->query_team();
	if( team && arrayp(team) && sizeof(team)>1 && damage_total>0 )
	{
		for(i=0;i<sizeof(team);i++)
		{
			if( !team[i] || !living(team[i]) || !present(team[i],environment())
			 || !userp(team[i]) || !team[i]->query_temp("maze/meishan") )
				continue;
			team[i]->set_temp("pending/"+query("name"),1);
			team[i]->add_temp("maze/meishan_kill",1);
			if( !undefinedp(hurt[team[i]->query("id")]) )
				pp = hurt[team[i]->query("id")]*100/damage_total;
			else	pp = 0;
			if( team[i]==who )
				pp+= 10;
			p = base;
			p+= p*pp/100;
			team[i]->add("combat_exp",p);
			message("vision",HIW"【梅山七圣】"+team[i]->query("name")+HIW"得到了"+p+"点武学经验，其中附加经验为"+pp+"%"NOR"\n",team);
			re = 0;
			re = reward_ob(team[i]);
			if( re && re!="" )
				message("vision",HIW"【梅山七圣】"+team[i]->query("name")+HIW"得到了"+re+HIW"。"NOR"\n",team);
			if( team[i]==who )
			{
				re = 0;
				re = reward_ob(team[i]);
				if( re && re!="" )
					message("vision",HIW"【梅山七圣】"+team[i]->query("name")+HIW"得到了"+re+HIW"。"NOR"\n",team);
			}				
		}
	}
	else	
	{
		who->set_temp("pending/"+query("name"),1);
		who->add_temp("maze/meishan_kill",1);
		p = base;
		who->add("combat_exp",p);
		tell_object(who,HIC"【梅山七圣】你得到了"+p+"点武学经验。"NOR"\n");
		re = 0;
		re = reward_ob(who);
		if( re && re!="" )
			tell_object(who,HIC"【梅山七圣】你得到了"+re+HIC"。"NOR"\n");
	}
	destruct(this_object());
	return;	
}	

int is_meishan(){ return 1;}

string obj_from(){ return "【梅山七圣副本】";}