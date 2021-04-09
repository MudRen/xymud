// hudian.c
// created by mes, updated 6-20-97 pickle
#include <ansi.h>
inherit SUPER_NPC;

void create()
{
  set_name("护殿妖", ({"hudian yao", "yao", "hu dian", "hudian", "monster"}));
  set_level(49);
  set("long","一个膀阔腰圆的护殿妖，看上去道行不浅。\n");
  create_family("陷空山无底洞", 1, "弟子");
  set("title","");
  set("gender", "男性");
  set("age", 20+random(15));
  set("attitude", "peaceful");
  set("shen_type", 1);

  set_skill("unarmed",490);
  set_skill("parry",490);
  set_skill("dodge",490);
  set_skill("blade",490);
  set_skill("kugu-blade",490);
  map_skill("blade", "kugu-blade");
  map_skill("parry", "kugu-blade");

  set_temp("weapon_level",40);
  set_temp("armor_level",40);
  setup();
  carry_object(0,"blade",random(2))->wield();
  carry_object(0,"cloth",random(2))->wear();
  carry_object(0,"armor",random(2))->wear();
  carry_object(0,"kui",random(2))->wear();
  carry_object(0,"shoes",random(2))->wear();
  carry_object(0,"pifeng",random(2))->wear();
  carry_object(0,"shield",random(2))->wear();
}

void init()
{
	object me;
	::init();
  	if( interactive(me = this_player()) && !is_fighting() 
	  && living(me) ) 
	{
    		call_out("greeting", 1, me);
  	}
}

void greeting(object me)
{
	int myspells, mykar, diff;
  	string npcname=this_object()->query("name");

  	if( !me || environment(me) != environment() ) 
  		return;
  	if(me->query("family/family_name") == "陷空山无底洞")
    		return;

  	myspells=me->query_skill("spells");
  	mykar=me->query_kar(); 
  	diff=80-mykar;

  	if( member_array("tian shu",me->parse_command_id_list())==-1 
  	 && member_array("yu shu",me->parse_command_id_list())==-1)
	{
      		command("say 什么东西？竟敢在无底洞出入！");
      		kill_ob(me);
      		return;
    	}
	if( random(myspells+mykar) > diff) 
		return;
  	else
    	{
      		message_vision(CYN ""+npcname+"对$N大喝道：呔！什么东西！？休想从老子眼下溜过去！\n"NOR, me);
      		message_vision(npcname+"大喊一声：现！$N顿时现出原形，原来是"+me->query("name")+"！\n", me);
      		me->delete_temp("spellslevel");
      		me->delete_temp("d_mana");
      		me->delete_temp("apply/name");
      		me->delete_temp("apply/id");
      		me->delete_temp("apply/short");
      		me->delete_temp("apply/long"); 
      		kill_ob(me);
      		return;
    	}
}