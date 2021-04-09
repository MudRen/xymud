#include <ansi.h>
#include <combat.h>
#include "/cmds/std/valid_move.h"
inherit BOSS;

int chat()
{ 
	mixed bz; 
	int damage;
	object weapon2,target,weapon,me=this_object(); 
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
        
        if( random(5)==0 && !target->is_busy() )
        {
        	message_vision("\n\n"YEL"$N"HIR"后退几步，口内吐出一块牛黄。有碗口大小，喷出来如火雷一般，砸向$n"YEL"！"NOR"\n",me,target);
        	if( random(3)==0 )
        		message_vision("结果被$N闪开了。\n",target);
        	else
        	{
        		target->start_busy(5);
        		message_vision(HIY"结果$N"HIY"被打了正着，顿时肉身溃败，口吐鲜血！"NOR"\n",target);
        		damage = target->query_maxkee()/3;
        		target->receive_wound("kee",damage,me,TYPE_CAST);
        		COMBAT_D->report_status(target),1;
        	}	
        }
        if( random(4)==0 && !me->is_busy() )
        	command("exert budong");
	if( !me->query_temp("powerup") && random(4)==0 && !me->is_busy() )
		command("exert fire");
	if( random(7)==0 && !me->is_busy() )
		command("cast zhuang");
	if( random(7)==0 && !me->is_busy() )
		command("cast sanmei");
        if( !objectp(me->query_temp("invocation")) && random(6)==0 )
        	command("cast niushi");	
        	
        weapon = query_temp("weapon");
        if( !me->is_busy() )
        {
        	if( random(5)==0 && !target->is_blind() )
        	{
        		if( weapon )
        			weapon->unequip();
        		command("perform yin");
        		if( weapon && present(weapon,me) )
        			weapon->wield();
        	}
        	weapon = query_temp("weapon");
        	if( weapon && !me->is_busy() )
        	{
        		if( !me->query_temp("powerup") && random(2)==0 )
        			command("perform shenli");
        		if( random(4)==0 )
        			command("perform wujin");
        		if( random(3)==0 )
        			command("perform back");			
        	}
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
	set_name("金大升",({"jin dasheng","jin","dasheng"}));
  	set_level(110);
  	set("nickname", HIC"踏破山河"NOR);
  	set("title","青水大仙");
  	set("gender", "男性" );
  	set("age", 30);
  	set("long", "身高一丈六尺，顶上双角，卷嘴尖耳，金甲红袍，全身甲胄，十分轩昂。\n");
	set("class", "yaomo");
  	set("attitude", "aggressive");
	set("force_factor", 300);
	set("mana_factor", 500);
	set("per",10);
	create_family("火云洞", 2, "弟子");
	set_skill("spells", 1100);
  	set_skill("stick", 1100);
  	set_skill("dali-bang", 1100);
  	set_skill("unarmed", 1100);
  	set_skill("moyun-shou", 1100);
  	set_skill("dodge", 1100);
  	set_skill("moshenbu", 1100);
  	set_skill("parry", 1100);
  	set_skill("force", 1100);
  	set_skill("huomoforce", 1100);
  	set_skill("pingtian-dafa", 1100);
  	map_skill("force", "huomoforce");
  	map_skill("spells", "pingtian-dafa");
  	map_skill("stick", "dali-bang");
  	map_skill("parry", "dali-bang");
  	map_skill("unarmed", "moyun-shou");
  	map_skill("dodge", "moshenbu");
	set("env/test",({"HIB","HIR","HIM"})[random(3)]);
	setup();
	add_temp("apply/max_kee",10000);
	add_temp("apply/max_sen",10000);
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

string query_maze_file(){return "meishan";}

void dies()
{
	string *ids,re;
	int pp,p,i,base,damage_total;
	mapping hurt;
	object *team,corpse,who = query_temp("last_damage_from");
	message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",this_object());
	message_vision(HIY"一道黄光从尸身上窜出，直奔天际而去。\n\n"NOR,this_object());
	corpse = new("/obj/corpse");
	corpse->set_name("野牛尸体",({"yeniu's corpse","corpse"}));
	corpse->set("long","一只野牛的尸体。\n");
	if( corpse->move(environment()) )
		message_vision("\n黄光散去，但见那遗下的尸骸却是一只野牛，原来是谁的一缕神识栖宿于此肉身作怪而已。\n",this_object());
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