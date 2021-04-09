#include <ansi.h>
inherit SUPER_NPC;

void create()
{
	set_name("黑熊怪", ({ "bear monster", "bear", "monster" }));
	set_level(90);
	create_family("南海普陀山", 2, "弟子");
	set("title", "南海观音之徒");   
	set("long", @LONG
黑熊怪本是山间野兽，不知从哪里学到一身好本领。
后遇见南海观音，被南海观音收为徒弟。
LONG);
	set("gender", "男性");
	set("age", 30);
	set("attitude", "heroism");
	set("per", 19);
	set("rank_info/self", "黑熊");
	set("rank_info/rude", "熊怪");
	set("force_factor", 250);
	set("mana_factor", 320);

	set_skill("literate",900);
	set_skill("spells",900);
	set_skill("buddhism",900);
	set_skill("unarmed",900);
	set_skill("jienan-zhi",900);
	set_skill("dodge",900);
	set_skill("lotusmove",900);
	set_skill("parry",900);
	set_skill("force",900);
	set_skill("lotusforce",900);
	set_skill("blade",900);
	set_skill("cibeidao",900);

	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "cibeidao");
	map_skill("blade", "cibeidao");

   	set_skill("jingang-zhenshen",900);
	set_skill("qu-yue",900);
	set_skill("bubu-shenglian",900);
        set("no_cast",1);
	set("env/test","HIB");
	set_temp("weapon_level",80);
	set_temp("armor_level",80);
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"shield",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"blade",1)->wield();
	powerup(0,1);
}

void attempt_apprentice(object ob)
{
        if( (string)ob->query("bonze/class")!="bonze" )
        {
        	EMOTE_D->do_emote(this_object(), "shake",geteuid(ob),CYN,0,0,0);
        	tell_object(ob,CYN+name()+CYN"说道：我们普陀宝山只收佛家弟子，这位" +RANK_D->query_respect(ob) + "还是先去剃度吧。\n"NOR);
		return;
        }
        if( ob->query("class") && ob->query("class")!="bonze" 
        && !ob->query("family/putuo_class_succ") )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：阿弥陀佛，施主是啥来头啊？带艺拜师，还是去找惠岸长老吧。\n"NOR);
		return;
	}
        if( ob->query_level()<65 )
        {
        	EMOTE_D->do_emote(this_object(), "shake",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是先下去打好基础再说。\n"NOR);
           	return ;
        }
        ob->delete("family/putuo_class_guai");
        ob->delete("family/putuo_class_succ");
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们南海普陀山发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "bonze");
}

int prevent_learn(object me, string skill)
{
	int i;
	string *my_skill,*other_skill;
	my_skill = ({
		"jingang-zhenshen",
	});
	other_skill = ({
		"longxiang-li",			
	});
	
	if( member_array(skill,my_skill)==-1 )
		return 0;
	for(i=0;i<sizeof(other_skill);i++)
	{
		if( me->query_skill(other_skill[i],2)>0 )
		{
	                tell_object(me,CYN+name()+CYN"说道：你既已学了"NOR HIC"「"+to_chinese(other_skill[i])+"」"NOR CYN"，本尊者就不教你了。\n"NOR);
			return 1;
		}
	}	
	return 0;		
}
