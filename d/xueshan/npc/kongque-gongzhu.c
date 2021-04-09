// kongque-gongzhu.c...weiqi, 97.09.15.
inherit SUPER_NPC;
#include <ansi.h>

string get_ice(object me);

void create()
{
	set_name("孔雀公主", ({"kongque gongzhu", "kongque", "gongzhu"}));
	set_level(119);
	set("title", "明王护法");
	set("gender", "女性" );
	set("age", 23);
set("long", @LONG
这位孔雀公主是孔雀明王的女儿。孔雀明王被佛祖如来
押至灵山后，她由大鹏明王一手带大。说是侄女，与大
鹏明王实则有父女之情。
LONG );
	set("class", "yaomo");
	set("attitude", "peaceful");
	create_family2("大雪山","孔雀",2, "公主");
	set_skill("unarmed",1190);
	set_skill("cuixin-zhang",1190);
	set_skill("dodge",1190);
	set_skill("xiaoyaoyou",1190);
	set_skill("parry",1190);
       	set_skill("throwing",1190);
	set_skill("sword",1190);
       	set_skill("bainiao-jian",1190);
	set_skill("force",1190);   
	set_skill("ningxie-force",1190);
	set_skill("literate",1190);
	set_skill("spells",1190);
	set_skill("dengxian-dafa",1190);
	
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("parry", "bainiao-jian");
	map_skill("dodge", "xiaoyaoyou");
	
	set_skill("qisi-huisheng",1190);
	set_skill("qushen",1190);
	
	set("force_factor", 175);
	set("mana_factor", 176);

	set("eff_dx", -200000);
       	set("nkgain", 400);

	set("chat_chance", 15);
	set("chat_msg", ({
		"孔雀公主叹了口气。\n",	
		"孔雀公主自言自语道：也不知道父王的病什么时候能好。\n",
		"孔雀公主皱了皱眉道：按说这种草性暖，父王怎么会认为可以提炼寒毒呢？\n",
		"孔雀公主又叹了口气：做了这么久还不成，肯定还差点什么...这么多花草混来混去也没用呀？\n",
		"孔雀公主自言自语道：父王再弄不到寒毒，恐怕大事不妙了。\n",        
	}) );

	set("inquiry", ([
		"大鹏王" : (: get_ice :),
		"大鹏明王" : (: get_ice :),
		"父王" : (: get_ice :),
	]));	
	
	set("env/test","HIB");
	set_temp("weapon_level",60+random(50));
	set_temp("armor_level",60+random(50));
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"neck",random(10))->wear();
	carry_object(0,"ring",random(10))->wear();
	carry_object("/d/obj/weapon/sword/fenghuangqin")->wield();
	carry_object("/d/xueshan/obj/nihong-yuyi")->wear();
	powerup(1,1);	
}

string get_ice(object me)
{
	object env;

	me = this_player();
	env = environment(this_object());

	if( (me->query_temp("ice_given") || (int)me->query("family/generation")<=2) && (string)env->query("short")=="小木屋" && (string)me->query("family/family_name")=="大雪山")
	{
		me->delete_temp("ice_given");
		message_vision("孔雀公主在$N耳边悄声说了几句话。\n", me);
		write("孔雀公主告诉你道：既然你想见他，这就让你去。\n");
		message_vision("只见孔雀公主伸手在桌子底下按了一按。\n", me);
		env->open_down();
		return "上来时敲一敲墙即可。\n";
	}
	else
	{
		return "大鹏明王就是我父王，我父王就是大鹏明王。\n";
	}
}

int accept_object(object me, object ob)
{
	if( ((string)ob->query("id") != "lan bingkuai") 
	 && ((string)ob->query("id") != "shuangse bing") ) 
	{
		tell_object(me,CYN+name()+CYN"说道：去！去！去！别来烦你家姑奶奶我！\n");
		return 0;
	}
	else 
	{
		EMOTE_D->do_emote(this_object(), "ah",geteuid(me),CYN,0,0,0);
		EMOTE_D->do_emote(this_object(), "jump",0,CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道： 这位" + RANK_D->query_respect(me) + "真是有心人！\n");
		tell_object(me,CYN+name()+CYN"说道： 那我告诉你一个大秘密：我父王现在根本就不在冰宫里。他病得很厉害，正需要这种寒毒。\n");
		me->set_temp("ice_given", 1);
       		return 1;
	}
}

void _attempt_apprentice(object ob)
{
	if( !ob )
		return;
	if( ob->query_level()>=125 )
	{
		EMOTE_D->do_emote(this_object(), "xixi",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你都这么厉害了，还是去找父王吧。\n"NOR);
		return;
	}	
	else if( ob->query_level()>=95 )
	{
		EMOTE_D->do_emote(this_object(), "nod",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们大雪山发扬光大。\n"NOR);
        	command("recruit " + geteuid(ob) );
        	return;
	}
	else
	{
		EMOTE_D->do_emote(this_object(), "en",0,CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：嗯，有志不在年高，你先去打好基础再来吧。\n"NOR);
		return;
	}
}

void attempt_apprentice(object ob)
{
	if( ob->query("class") && ob->query("class")!="yaomo" )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你是啥来头啊？带艺拜师，还是先去找将军问问吧。\n"NOR);
		return;
	}
	return _attempt_apprentice(ob);
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}

int prevent_learn(object me, string skill)
{
	object ob = me;	
  	if( skill != "qisi-huisheng")
  		return 0;
	if( me->query_skill("jiuxi-fuqi",2)>0 )
	{
		tell_object(ob,CYN+name()+CYN"说道：你学了狮尊者的神通，本公主就不教你了。\n"NOR);
		return 1;
	} 
	if( me->query_skill("huitian-fanri",2)>0 )
	{
		tell_object(ob,CYN+name()+CYN"说道：你学了象尊者的神通，本公主就不教你了。\n"NOR);
		return 1;
	} 
	return 0;		
}