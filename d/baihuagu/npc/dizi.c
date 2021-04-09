inherit SUPER_NPC;
#include <ansi.h>
void create()
{
	int i = 30+random(9);
	set_name("不肖弟子", ({"dizi"}));
      	set_level(i);
	set("long","百花谷的弟子，不知为何跑到这儿来了。\n");
       	set("gender", "男性");
	set("attitude", "heroism");
	set("age", 30);
	set("force_factor", 150);
	set("mana_factor", 40);
	set_skill("zongheng-sword", i*10);
	set_skill("sword", i*10);
	set_skill("unarmed", i*10);
	set_skill("dodge", i*10);
	set_skill("force", i*10);
	set_skill("parry", i*10);
	set_skill("spells", i*10);
	set_skill("siji-zhang", i*10);
	set_skill("brightjade-force", i*10);
	set_skill("wuyou-steps", i*10);
	map_skill("sword", "zongheng-sword");
	map_skill("unarmed", "siji-zhang");
	map_skill("force", "brightjade-force");
	map_skill("parry", "zongheng-sword");
	map_skill("dodge", "wuyou-steps");
	setup();
}

int information(object who)
{
	mapping skill;
	string *skills;
	int i,level;
	if( !who || !living(who) )
		return 0;
	if( who->query_level()<25 )
		return 0;
	level = who->query_level();
	level = level/10*10+9;
	this_object()->set_level(level);
	skill = this_object()->query_skills();
	skills = keys(skill);
	for(i=0;i<sizeof(skills);i++)
		set_skill(skills[i],level*10);
	set("force_factor",query("skill")*5);
	set("mana_factor",query("spells")*6);
	set("env/test",({"HIM","HIB","HIY"})[random(3)]);
	set_temp("weapon_level",level*2/3);
	set_temp("armor_level",level*2/3);
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"shield",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"neck",1)->wear();
	carry_object(0,"sword",1)->wield();
	powerup(0,1);
	return 1;
}

int accept_fight (object ob)
{
        if( !query("owner_id") || query("owner_id")!=ob->query("id") )
		return 0;
	kill_ob (ob);
  	return 1;
}

void kill_ob (object ob)
{
        if( !query("owner_id") || query("owner_id")!=ob->query("id") )
	{
		this_object()->remove_killer(ob);
		ob->remove_killer(this_object());
		message_vision(HIC"不肖弟子冷冷的看着$N"HIC"。\n"NOR,ob);
		return;
	}	
	if( !this_object()->is_fighting() )
	{
		powerup(0,1);
  		set_temp("no_return",1);
  		set_temp("my_killer",ob);
  		command("say 居然胆敢来抢我秘诀？找死啊。");
  	}	
  	::kill_ob(ob);
}

void unconcious()
{
	die();
}

void die()
{
	object book;
        object ob = query_temp("my_killer");
        int succ;
        if( !ob || !present(ob,environment())
         || query("owner_id")!=ob->query("id") )
        {
        	message_vision(HIR"不肖弟子撒腿跑了。\n\n"NOR,this_object());
        	destruct(this_object());
        	return;
        }
	message_vision(HIG"不肖弟子临死前留下一本秘籍......\n"NOR,this_object());
	CHANNEL_D->do_channel(environment(),"rumor","听说"+ob->name()+HIM"为百花谷成功找回失落多年的了"HIG"纵横剑法"HIM"。"NOR);
	book=new("/d/obj/book/zongheng");   
    	book->move(ob);
    	succ = random(ob->query("mark/zongheng_re"));
    	if( wizardp(ob) )
    		tell_object(ob,"succ="+succ+"\n");
    	if( ob->is_knowing("bhg_zongheng")>0 )
    	{
    		destruct(this_object());
    		return;
	}
        if (random(6) == 4 && ob->query_level()>=25 && succ==0 )
	{
        	ob->set_knowing("bhg_zongheng",2);
            	tell_object(ob, HIR"【系统】你领悟了纵横剑法中"HIG"“纵剑”"HIR"一诀的用法。\n" NOR);        
	}
        else if (random(6) == 5 && ob->query_level()>=25 && succ==0 )
        {
        	ob->set_knowing("bhg_zongheng",1);
		tell_object(ob, HIR"【系统】你领悟了纵横剑法中"HIG"“横剑”"HIR"一诀的用法。\n" NOR);        
	}
	else
	{
        	ob->set_knowing("bhg_zongheng",3);
		tell_object(ob, HIR"【系统】你领悟了纵横剑法中“纵横四海”一招的用法。\n" NOR);        
	}
	ob->save(1);
	destruct(this_object());
}
