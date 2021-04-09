#include <ansi.h>
#include <combat.h>
inherit NPC;

int chat()
{ 
	object target,me = this_object();	
	if( !environment() 
	 || !living(this_object()) 
	 || !this_object()->is_fighting() 
	 || query("force")<100 ) 
	 	return 0; 
	if( me->is_busy() ) 
		me->stob_busy(1+random(2)); 
	if( me->is_busy() ) 
		return 0; 
	target = me->select_opponent(); 
	if( !target )
        	return 0;
        	
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
	QUEST_D->randomPfm(me);	
	return 1;
}

void create()
{
	mapping name;
	int i = 80+random(30);
	set_level(i);
	i = i*10;
	set_name("梅山精怪",({"meishan guai","guai","jing"}));	
	set("age", 30);
	set("gender", "男性" );
	set_skill("unarmed",i);
	set_skill("dodge",i);
  	set_skill("parry",i);
  	set_skill("spells",i);
  	set_skill("force",i);
	set_skill("literate",i);
  	set("env/test",({"HIB","HIY","HIB","HIY"})[random(4)]);
  	setup();
	if( random(2) )
	{
		if( random(2) )
		{
			name = NAME_D->random_name2(0, -1, "吴", 0, 0);
			set_name(name["name"],name["id"]);
			set("title","蜈蚣精");
		}
		else
		{
			name = NAME_D->random_name2(0, -1, "常", 0, 0);	
			set_name(name["name"],name["id"]);
			set("title","长蛇精");
		}	
		create_family("陷空山无底洞", 2, "弟子");
  		if( random(2) )
  		{
  			set_skill("qixiu-jian",i);
  			set_skill("sword",i);
			map_skill("sword", "qixiu-jian");
  			map_skill("parry", "qixiu-jian");
			carry_object(0,"sword",random(3))->wield();
		}
		else
		{	
  			set_skill("blade",i);
  			set_skill("kugu-blade",i);
  			map_skill("parry", "kugu-blade");
  			map_skill("blade", "kugu-blade");
  			carry_object(0,"blade",random(3))->wield();
  		}
  		set_skill("yaofa",i);
  		set_skill("lingfu-steps",i);
  		set_skill("yinfeng-zhua",i);
  		set_skill("huntian-qigong",i);
  		map_skill("force", "huntian-qigong");
  		map_skill("spells", "yaofa");
  		map_skill("unarmed", "yinfeng-zhua");
		map_skill("dodge", "lingfu-steps");
	}	
	else if( random(2) )
	{
		name = NAME_D->random_name2(0, 1, "朱", 0, 0);	
		set_name(name["name"],name["id"]);
		set("title","野猪精");
		create_family("阎罗地府", 2, "弟子");
	  	set_skill("jinghun-zhang",i);
 		set_skill("tonsillit",i);
 		set_skill("gouhunshu",i);
 		set_skill("ghost-steps",i);
 		switch(random(3))
 		{
 			case 0 :
 				set_skill("whip",i);
 				set_skill("hellfire-whip",i);
 				map_skill("whip", "hellfire-whip");
 				map_skill("parry", "hellfire-whip");
 				carry_object(0,"whip",random(3))->wield();
 				break;
 			case 1 :
 				set_skill("kusang-bang",i);
 				set_skill("stick",i);
 				map_skill("stick", "kusang-bang");
 				map_skill("parry", "kusang-bang");
 				carry_object(0,"stick",random(3))->wield();
 				break;
 			default:
 				set_skill("sword",i);
 				set_skill("zhuihun-sword",i);
 				map_skill("sword", "zhuihun-sword");
 				map_skill("parry", "zhuihun-sword");
 				carry_object(0,"sword",random(3))->wield();
 				break;
 		}		
		map_skill("dodge", "ghost-steps");
        	map_skill("unarmed", "jinghun-zhang");
        	map_skill("force", "tonsillit");
		map_skill("spells", "gouhunshu");
	}
	else
	{
		name = NAME_D->random_name2(0, 1, "杨", 0, 0);	
		set_name(name["name"],name["id"]);
		set("title","山羊精");
		create_family("东海龙宫", 2, "弟子");
		set_skill("literate",i);
		set_skill("unarmed",i);
		set_skill("dodge",i);
		set_skill("force",i);
		set_skill("parry",i);
		set_skill("fork",i);
		set_skill("spells",i);
		set_skill("seashentong",i);
		set_skill("dragonfight",i);
		set_skill("dragonforce",i);
		set_skill("fengbo-cha",i);
		set_skill("dragonstep",i);
		map_skill("spells", "seashentong");
		map_skill("unarmed", "dragonfight");
		map_skill("force", "dragonforce");
		map_skill("fork", "fengbo-cha");
		map_skill("parry", "fengbo-cha");
		map_skill("dodge", "dragonstep");
		carry_object(0,"unarmed",random(3))->wield();
	}
	setup();
	add_temp("apply/max_kee",10000);
	add_temp("apply/max_sen",30000);
	carry_object(0,"cloth",random(3))->wear();
	carry_object(0,"shoes",random(3))->wear();
	carry_object(0,"pifeng",random(3))->wear();
	carry_object(0,"kui",random(3))->wear();
	carry_object(0,"hand",random(3))->wear();
	carry_object("/d/obj/drug/jinchuang")->set_amount(50);
	carry_object("/d/obj/drug/hunyuandan")->set_amount(50);
	carry_object("/d/obj/drug/yundan")->set_amount(1+random(5));
	powerup(0,1);
}

string query_maze_file(){return "meishan";}

void dies()
{
	int i,p,base;
	object *team,corpse,who = query_temp("last_damage_from");

	message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",this_object());
	lose_inventory();
	corpse = new("/obj/corpse");
	corpse->set_name(query("title")+"的尸体",({"shi ti","corpse"}));
	corpse->set("long",query("title")+"的尸体。\n");
	if( corpse->move(environment()) )
		;
	else	destruct(corpse);	
	if( !who || !present(who,environment()) 
	 || !userp(who) )
	{
		destruct(this_object());
		return;	
	}
	base = 10000;
	if( pointerp(team = who->query_team())
	 && sizeof(team)>1 )
	{
		for(i=0;i<sizeof(team);i++)
		{
			if( !team[i] || !living(team[i]) || !present(team[i],environment())
			 || !userp(team[i]) || !team[i]->query_temp("maze/meishan") )
				continue;
			p = base;
			p = p/2+random(p*3/2);
			team[i]->add("combat_exp",p);
			message("vision",HIW"【梅山七圣】"+team[i]->query("name")+HIW"得到了"+p+"点武学经验。"NOR"\n",team);
		}
	}
	else	
	{
		p = base;
		who->add("combat_exp",p);
		p = p/2+random(p);
		tell_object(who,HIC"【梅山七圣】你得到了"+p+"点武学经验。"NOR"\n");
	}
	who->add_temp("maze/meishan_killed",1);
	tell_object(who,HIY"【梅山七圣】你已杀死了"HIR+chinese_number(who->query_temp("maze/meishan_killed"))+HIY"个精怪。"NOR"\n");
	if( random(who->query_temp("maze/meishan_killed"))>10 )
	{
		who->delete_temp("maze/meishan_killed");
		if( who->query_temp("apply/meishan_buff")<10 )
		{
			who->add_temp("apply/meishan_buff",1);
			who->add_temp("apply/combat_damage",50+random(50));
			who->add_temp("apply/spells_damage",50+random(50));
			tell_object(who,HIY"【梅山七圣】恭喜！你获得了"HIR+chinese_number(who->query_temp("apply/meishan_buff"))+"级"HIG"「杨戬的青睐」"HIY"增益状态，攻击力得到了提升！"NOR"\n");
		}	
	}
	destruct(this_object());
	return;	
}
int is_meishan(){ return 1;}

string obj_from(){ return "【梅山七圣副本】";}