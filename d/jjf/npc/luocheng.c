//created 8-5-97 pickle
//罗成 luocheng.c
inherit SUPER_NPC;
inherit F_MASTER;
#include <ansi.h>

int handle_kill(object me);
int accept_fight(object me);
int attempt_apprentice(object me);
int recruit_apprentice(object me);
void check_fight (object npc, object me);
void player_win(object me);
void player_lose(object me);
void move_down(object ob);

void create()
{
  set_name("罗成", ({"luo cheng", "luo", "cheng", "luocheng", "master", "shifu"}));
  set_level(39);
  set ("long", @LONG
罗成是秦琼的表弟，乃是隋唐第七条好汉。传说他早已
在保长安时被乱箭射死战死，但不知为何还在这里。听
说罗成年幼时曾受过异人传授，学得一身奇异的内功，
因此比武极少败过。
LONG);
  create_family("将军府", 2, "蓝");
  set("title", "开国元勋");
  set("gender", "男性");
  set("age", 34);
  set("per", 30);
  set_skill("literate",390);
  set_skill("force",390);
  set_skill("lengquan-force",390);
  set_skill("parry",390);
  set_skill("dodge", 390);
  set_skill("yanxing-steps",390);
  set_skill("unarmed", 390);
  set_skill("changquan",390);
  set_skill("mace",290);
  set_skill("wusi-mace",290);
  set_skill("spear",390);
  set_skill("bawang-qiang", 390);
  map_skill("mace", "wusi-mace");
  map_skill("force", "lengquan-force");
  map_skill("unarmed", "changquan");
  map_skill("spear", "bawang-qiang");
  map_skill("parry", "bawang-qiang");
  map_skill("dodge", "yanxing-steps");
  set("force_factor", 100);
  set("env/test","HIY");
  setup();
  carry_object(0,"spear",1)->wield();
  carry_object(0,"armor",1)->wear();
  carry_object(0,"kui",1)->wear();
  carry_object(0,"pifeng",1)->wear();
  carry_object(0,"ring",1)->wear();
  carry_object(0,"cloth",1)->wear();
  carry_object(0,"shoes",1)->wear();
  carry_object(0,"wrists",1)->wear();
  carry_object(0,"waist",1)->wear();
  carry_object(0,"hand",1)->wear();
  powerup(0,1);
}

void init()
{
	object ob;
	::init();
	if( interactive(ob = this_player()) && member_array(ob, query_enemy()) != -1)
	{
		if (is_fighting())
	    	{
			message_vision(CYN"罗成对$N喝道：“又是你！滚出去！”"NOR, ob);
			move_down(ob);
	    	}
	}
	add_action("do_kill", "kill");
        add_action("do_surrender", "surrender");
}

int do_surrender()
{
    this_player()->delete_temp("pending/jjf_apprentice_luocheng");
    return 0;
}

int do_kill(string arg)
{
	if(!arg || !id(arg)) 
		return 0;
    	handle_kill(this_player());
    	return 1;
}

int handle_kill(object me)
{
    if(is_fighting() || !accept_fight(me) )
    {
        message_vision(CYN"罗成抱拳道：众位，既然$N想要拼命，还请稍候片刻。\n"NOR, me);
        this_object()->remove_all_enemy();
        return 1;
    }
    message_vision(CYN"罗成说道：好，我们便切磋一下！\n"NOR,me);
    fight_ob(me);
    return 1;
}

int accept_fight(object me)
{
	if(me->query_temp("pending/jjf_apprentice_luocheng"))
    	{
    		powerup(0,1);
		remove_call_out("check_fight");
      		call_out("check_fight", 1, this_object(), me);
      		return 1;
    	}
  	command("say 难道你来这里就是想打架？我看还是算了吧。\n");
  	call_out("move_down", 1, me);
  	return 0;
}

void kill_ob(object me)
{
	accept_fight(me);
}

int attempt_apprentice(object me)
{
  	string myname=RANK_D->query_respect(me);

  	if( me->query("class")=="yaomo" || me->query("class")=="ghost" )
        {
		EMOTE_D->do_emote(this_object(), "pei",geteuid(me),CYN,0,0,0);
           	tell_object(me,CYN+name()+CYN"说道：妖魔鬼怪休要猖狂！\n"NOR);
           	return 0;
        }
        if( me->query("class")!="fighter" || me->query("family/family_name")!="将军府" )
        {
        	EMOTE_D->do_emote(this_object(), "?",geteuid(me),CYN,0,0,0);
           	tell_object(me,CYN+name()+CYN"说道：你不是本府弟子，前来何事？\n"NOR);
           	return 0;
        }
	if(me->is_knowing("jjf_luocheng") ) 
  	{
    		command("say 不错，不错。"+myname+"果然是可教之才！");
    		command("say "+myname+"武艺过人。你我不妨切磋一番。");
    		command("recruit "+me->query("id"));
    		return 1;
  	}
	if (is_fighting())
  	{
    		command("say 现在在下正忙，"+myname+"请稍候。");
    		return 1;
  	}
  	command("consider");
  	command("say 在下从不收徒。");
  	command("say 但阁下若能胜过我手中枪，你我不妨互相切磋功夫。");
  	me->set_temp("pending/jjf_apprentice_luocheng", 1);
  	return 1;
}

void combat_lose(object me)
{
	powerup(0,1);
	remove_killer(me);
	me->remove_killer(this_object());
    	this_object()->delete_temp("last_opponent");
	if (me->query_temp("pending/jjf_apprentice_luocheng"))
      	{
		me->set_knowing("jjf_luocheng",1);
        	me->delete_temp("pending/jjf_apprentice_luocheng");
		command("recruit "+me->query("id"));
      	}
    	return;
}

void combat_win(object me)
{
	powerup(0,1);
	remove_killer(me);
	me->remove_killer(this_object());
	this_object()->delete_temp("last_opponent");
    	command("say "+RANK_D->query_respect(me) +"不必气馁，再接再厉！");
    	return;
}

void move_down(object me)
{
	if( !me || environment(this_object())!=find_object("/d/jjf/guest_cabinet2"))
      		return;
    	me->move("/d/jjf/guest_cabinet");
    	return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class","fighter");
}