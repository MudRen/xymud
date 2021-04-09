// bishu.c 碧鼠精
#include <ansi.h>
inherit SUPER_NPC;

void create()
{
	set_name("碧鼠精", ({"bi shu", "bi", "shu", "bishu", "monster"}));
	set_level(120);
	set("gender", "女性");
	set("age", 19);
	set("long",
"虽然她看起来弱不禁风，但听说她天赋及佳，是块修仙的好料子。\n"
"自从入无底洞以来，她的武功进步及快，颇有赶过玉鼠的架式。\n");
	create_family("陷空山无底洞", 2, "弟子");
	set("title", "无底洞大弟子");
	set("nickname", HIR"九死一生"NOR);
	set("attitude", "heroic");
  
	set_skill("unarmed",1200);
	set_skill("dodge",1200);
	set_skill("parry",1200);
	set_skill("stealing",1200);
	set_skill("spells",1200);
	set_skill("sword",1200);
	set_skill("qixiu-jian",1200);
	set_skill("yinfeng-zhua",1200);
	set_skill("lingfu-steps",1200);
	set_skill("force",1200);
	set_skill("blade",1200);
	set_skill("kugu-blade",1200);
	set_skill("yaofa",1200);
	set_skill("huntian-qigong",1200);
  	map_skill("force", "huntian-qigong");
  	map_skill("blade", "kugu-blade");
  	map_skill("unarmed", "yinfeng-zhua");
  	map_skill("spells", "yaofa");
  	map_skill("sword", "qixiu-jian");
  	map_skill("parry", "qixiu-jian");
  	map_skill("dodge", "lingfu-steps");
  
  	set_skill("tuxing",1200);
  	set_skill("zhihua",1200);
  	
	set("force_factor", 120);
	set("mana_factor", 125);
	set("inquiry", ([
		"name": "本姑娘就是地涌夫人的开山大弟子！",
                "here": "你瞎了眼啦？这里就是鼎鼎大名的陷空山无底洞！",
		"rumors": "不知道！找别人问去。",
		"人肉包子": "你瞎了眼啦？本姑娘又不是厨子！",
	]) );  
	set_temp("weapon_level",60);
	set_temp("armor_level",60);
	set("env/test","HIR");
	setup();
	carry_object(0,"sword",1)->wield();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"neck",1)->wear();
	powerup(0,1);
}

void attempt_apprentice(object ob)
{
        if( ob->query("class")=="xian" || ob->query("class")=="dragon"
         || ob->query("class")=="bonze" || ob->query("class")=="taoist" )
        {
		EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你是哪路神仙派来的？！\n"NOR);
           	return ;
        }
        if( ob->query("class") && ob->query("class")!="yaomo" )
        {
        	if( !ob->query("family/wdd_class") )
        	{
        		EMOTE_D->do_emote(this_object(), "zeze",geteuid(ob),CYN,0,0,0);
           		tell_object(ob,CYN+name()+CYN"说道：想弃暗投明？还是去问过总管吧。\n"NOR);
           		return ;
        	}
        }
        if( ob->query_level()>125 )
        {
		EMOTE_D->do_emote(this_object(), "zeze",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你这么厉害了，还是找我师傅吧。\n"NOR);
           	return ;
        }
        if( ob->query_level()<75 )
        {
		EMOTE_D->do_emote(this_object(), "pei",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你功夫这么渣，你家里人知道吗？\n"NOR);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们妖族发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        return;
}

void recruit_apprentice(object ob)
{
  	if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}

void init(){}

int prevent_learn(object me, string skill)
{
	int mykugu = me->query_skill("kugu-blade",2);
  	if( wizardp(me) && me->query("env/immortal"))
    		return 0;
  	if( skill == "kugu-blade")
  	{
      		if( mykugu<180)
      		{
   			tell_object(me,CYN+name()+CYN"说道：你难道是来消遣姑奶奶的吗？！\n"NOR);
   			return 1;
      		}
	}
  	return 0;
}

void bishu_leave(object me)
{
        if( !me || !present(me,environment()) 
         || !living(me) )
                return;
        tell_object(me,CYN+name()+CYN"说道：这、这、这，这可怎么办是好？\n"NOR);
        EMOTE_D->do_emote(this_object(), "sigh",0,CYN,0,0,0); 
                tell_object(me,CYN+name()+CYN"说道：既然夫人有令在此，我还是赶紧回去一趟吧！\n"NOR);
        message_vision(YEL"碧鼠精抓了一把土，向空中一抛，喝声：走！借土遁去了。\n"NOR, me);
        destruct(this_object());
        return;
}

int accept_object(object me, object ob)
{
    if( ob->query("name_recognized") != "白骨令" )
    {
        tell_object(me,CYN+name()+CYN"怒道：混帐，我又不是收破烂的！\n"NOR);
        return 0;
    }
    remove_call_out("bishu_leave");
    call_out("bishu_leave", 1, me);
    return 1;
}
