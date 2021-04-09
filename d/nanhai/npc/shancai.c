inherit SUPER_NPC;
inherit F_MASTER;
#include <ansi.h>

void create()
{
        set_name("善财童子", ({ "shancai tongzi", "shancai", "tongzi" }));
        set_level(90);
        create_family("南海普陀山", 2, "弟子");
        set("title", "南海观音侍从");   
        set("long", @LONG
南海观音座前护法弟子善财童子。
LONG);
        set("gender", "男性");
        set("age", 15);
        set("attitude", "peaceful");
        set("rank_info/self", "贫僧");
        set("class", "bonze");
    
        set("force_factor", 175);
        set("mana_factor", 155);

        set("eff_dx", 150000);
        set("nkgain", 300);

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
        set_skill("staff",900);
        set_skill("lunhui-zhang",900);
        map_skill("spells", "buddhism");
        map_skill("unarmed", "jienan-zhi");
        map_skill("dodge", "lotusmove");
        map_skill("force", "lotusforce");
        map_skill("parry","lunhui-zhang");
        map_skill("staff", "lunhui-zhang");
        
	set("env/test","HIB");
	set_temp("weapon_level",80);
	set_temp("armor_level",80);
        setup();
        carry_object("/d/nanhai/obj/sengpao")->wear();
        carry_object(0,"armor",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"shield",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"staff",1)->wield();
	powerup(0,1);
}

void attempt_apprentice(object ob)
{
        if( (string)ob->query("bonze/class")!="bonze" )
        {
        	EMOTE_D->do_emote(this_object(), "shake",geteuid(ob),CYN,0,0,0);
        	tell_object(ob,CYN+name()+CYN"说道：阿弥陀佛，我只收佛家弟子，这位" +RANK_D->query_respect(ob) + "还是先去剃度吧。\n"NOR);
		return;
        }
        if( ob->query("class") && ob->query("class")!="bonze" 
        && !ob->query("family/putuo_class_succ") )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：阿弥陀佛，施主是啥来头啊？带艺拜师，还是去找惠岸师兄吧。\n"NOR);
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
	EMOTE_D->do_emote(this_object(), "jump",geteuid(ob),CYN,0,0,0);
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
		"longxiang-li",
	});
	other_skill = ({
		"jingang-zhenshen",			
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