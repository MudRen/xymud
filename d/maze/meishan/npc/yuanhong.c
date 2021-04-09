#include <ansi.h>
inherit BOSS;

string query_maze_file(){return "meishan";}

int chat()
{ 
	mixed bz; 
	object target,weapon,me=this_object(); 
	if( !environment() 
	 || !living(this_object()) 
	 || !this_object()->is_fighting() 
	 || query("force")<100 ) 
	 	return 0; 
	if( me->is_busy() ) 
		me->stob_busy(1+random(5)); 
	if( me->is_busy() ) 
		return 0; 
	target = me->select_opponent(); 
	if( !target )
        	return 0;
	weapon = query_temp("weapon");
	if( random(4)==0 && !target->is_busy() ) 
	{
		if( weapon )
		{
			weapon->unequip();
			reset_action();
		}	
		command("perform jinghun");
		if( weapon )
			weapon->wield();	
	}
	if( random(3)==0 && !me->query_temp("powerup") )
		command("exert shenjia");
	if( random(3)==0 && !me->query_temp("jldl") )
		command("exert jldl");
		
	if( query("kee")*100/me->query_maxkee()<30
         && query("kee")*100/me->query_maxkee()>5
         && !query_temp("xuangong") )
	{
		message_vision(HIW"\n$N"HIW"运起八九玄功，顿时身形暴涨，化作一只百丈巨猿！"NOR"\n\n",me);
		me->set_temp("xuangong",1);
		me->add_temp("apply/max_kee",10000);
		me->add_temp("apply/max_sen",10000);
		me->add_temp("apply/max_force",5000);
		me->add_temp("apply/max_mana",5000);
		me->add("eff_kee",10000);
		me->add("kee",10000);
		me->add("eff_sen",10000);
		me->add("sen",10000);
		me->add("force",8000);
		me->add("mana",8000);
	}         
		
	weapon = query_temp("weapon");
	if( weapon )
	{	
		if( random(5)==0 && !me->is_busy() )
			command("perform qiankun");
		if( random(2)==0 && time()-(int)me->query_temp("puti_pili")>=7
		 && !me->is_busy() )
			command("perform pili");
		if( random(4)==0 && time()-(int)me->query_temp("puti_wu")>=5
		 && !me->is_busy() )
			command("perform wu");
		if( random(6)==0 && !me->is_busy() )
			command("perform leiting");
		if( query("kee")*100/me->query_maxkee()<50
		 && query("kee")*100/me->query_maxkee()>10
		 && !me->is_busy() 
		 && random(2)==0 )
		 {
		 	command("eat yao");
		 	command("exert recover");
		 	command("perform panlong");
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
	if( query("sen")*100/this_object()->query_maxsen()<50
	 && query("sen")*100/this_object()->query_maxsen()>10
	&& !this_object()->is_busy() )
	{
		command("eat dan");
		command("exert refresh");
	}		
	return 1;
}

void create()
{
        set_name("袁洪",({"yuan hong","yuan","hong"}));
        set_level(110);
        set("title", HIC"天生神通"NOR);
        set("gender", "男性" );
        set("age", 33);
        set("long", "
	银盔素铠甲，缨络大红凝；
	左插狼牙箭，右悬宝剑锋。
	横担铁棍。坐下神行白马。\n");
	set("class", "toaist");
        set("attitude", "aggressive");
	set("force_factor", 500);
	set("mana_factor", 600);

	set_skill("unarmed",1100);
        set_skill("dodge",1100);
        set_skill("parry",1100);
        set_skill("spells",1100);  
        set_skill("dao",1100);
        set_skill("literate",1100);
        set_skill("stick",1100);  
        set_skill("qianjun-bang",1100);
        set_skill("puti-zhi",1100);  
        set_skill("jindouyun",1100);
        set_skill("dodge",1100);
        set_skill("force",1100);   
        set_skill("wuxiangforce",1100);
	set_skill("bajiu-xuangong",1100);
        map_skill("spells", "dao");
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        map_skill("stick", "qianjun-bang");
        map_skill("parry", "qianjun-bang");
        map_skill("dodge", "jindouyun");
        create_family("方寸山三星洞", 2, "弟子");
	set("env/test",({"HIB","HIR","HIM"})[random(3)]);
	setup();
	add_temp("apply/max_kee",15000);
	add_temp("apply/max_sen",15000);
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"hand",1)->wear();
	carry_object(0,"stick",1)->wield();
	carry_object("/d/obj/drug/jinchuang")->set_amount(300);
	carry_object("/d/obj/drug/hunyuandan")->set_amount(300);
	powerup(0,1);
}

void dies()
{
	string *ids,re;
	int pp,p,i,base,damage_total;
	mapping hurt;
	object *team,corpse,who = query_temp("last_damage_from");
	message_vision(HIW"\n$N"HIW"恨恨说道：此乃我等与那杨戬旧隙，偏偏遇到多管闲事的主！\n"NOR,this_object());
	message_vision(HIW"$N"HIW"将身一摇，顿见一道白光从$P顶梁泥丸宫窜出，直奔天际而去。\n\n"NOR,this_object());
	corpse = new("/obj/corpse");
	corpse->set_name("白猿尸体",({"baiyuan's corpse","corpse"}));
	corpse->set("long","一只普通的白猿的尸体。\n");
	if( corpse->move(environment()) )
		message_vision("\n白光一闪，但见那遗下的尸骸却是一只普通的白猿，原来是谁的一缕神识栖宿于此肉身作怪而已。\n",this_object());
	else	destruct(corpse);	
	if( !who || !present(who,environment()) || (who->query_level()>=120 && !wizardp(who))
	 || !userp(who) || who->query_temp("pending/"+query("name")) )
	{
		destruct(this_object());
		return;	
	}
	base = 500000;
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