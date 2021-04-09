// guanyin.c 惠岸行者
// By Dream Dec. 20, 1996
#include <ansi.h>
inherit SUPER_NPC;

string ask_mieyao();
string ask_cancel();
mixed ask_class();

void create()
{
        set_name("惠岸行者", ({ "huian xingzhe", "huian", "xingzhe" }));
        create_family("南海普陀山", 2, "弟子");
        set_level(120);
        set("title", "观音首徒");   
        set("long", @LONG
李天王二太子木叉，南海观音大徒弟惠岸行者。
LONG);
        set("gender", "男性");
        set("age", 25);
        set("attitude", "peaceful");
        set("rank_info/self", "贫僧");
        set("class", "bonze");
    
        set("force_factor", 175);
        set("mana_factor", 255);

        set("eff_dx", 150000);
        set("nkgain", 300);

        set_skill("literate", 1200);
        set_skill("spells", 1200);
        set_skill("buddhism", 1200);
        set_skill("unarmed", 1200);
        set_skill("jienan-zhi", 1200);
        set_skill("dodge", 1200);
        set_skill("lotusmove", 1200);
        set_skill("parry", 1200);
        set_skill("force", 1200);
        set_skill("lotusforce", 1200);
        set_skill("staff", 1200);
        set_skill("lunhui-zhang", 1200);
        set_skill("blade", 1200);
        set_skill("cibeidao", 1200);
        map_skill("spells", "buddhism");
        map_skill("unarmed", "jienan-zhi");
        map_skill("dodge", "lotusmove");
        map_skill("force", "lotusforce");
        map_skill("parry", "lunhui-zhang");
        map_skill("staff", "lunhui-zhang");
        map_skill("blade", "cibeidao");

	set_skill("tianlong-chanchang",1200);
	set_skill("jingang-sanmei",1200);
	set_skill("jingang-zhenshen",1200);
	set_skill("longxiang-li",1200);
	set_skill("qu-yue",1200);
	set_skill("bubu-shenglian",1200);

        set("inquiry", ([
           "cancel": (: ask_cancel :),
           "师门任务": (: ask_mieyao :),
           "kill": (: ask_mieyao :),
           "带艺拜师" : (: ask_class :),
                ]) );

        set("env/test","HIB");
	set_temp("armor_level",90);
	set_temp("weapon_level",90);
        setup();
        carry_object("/d/nanhai/obj/sengpao")->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"hand",1)->wear();
        carry_object(0,"wrists",1)->wear();
        carry_object(0,"waist",1)->wear();
        carry_object(0,"staff",1)->wield();
        powerup(0,1);
}

string ask_mieyao()
{
    	object who=this_player();
    	if((string)who->query("family/family_name")=="南海普陀山") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="南海普陀山" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
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
		tell_object(ob,CYN+name()+CYN"说道：阿弥陀佛，施主是啥来头啊？还是先完成贫僧的「带艺拜师」任务吧。\n"NOR);
		return;
	}
        if( ob->query_level()<95 )
        {
        	EMOTE_D->do_emote(this_object(), "shake",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是先下去打好基础再说。\n"NOR);
           	return ;
        }
        ob->delete("family/putuo_class_guai");
        ob->delete("family/putuo_class_succ");
	EMOTE_D->do_emote(this_object(), "nod",geteuid(ob),CYN,0,0,0);
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
	int i,k;
	string *skill1,*skill2;
	skill1 = ({
		"jingang-zhenshen","tianlong-chanchang",
	});
	skill2 = ({
		"longxiang-li","jingang-sanmei",
	});
	
	if( member_array(skill,skill1)==-1 
	 && member_array(skill,skill2)==-1 ) 
		return 0;
	if( member_array(skill,skill1)!=-1 )
	{
		for(i=0;i<sizeof(skill2);i++)
		{
			if( me->query_skill(skill2[i],2)>0 )
			{
				tell_object(me,CYN+name()+CYN"说道：你既已学了"NOR HIC"「"+to_chinese(skill2[i])+"」"NOR CYN"，本尊者就不教你"HIC"「"+to_chinese(skill)+"」"NOR CYN"了。\n"NOR);	
				return 1;
			}	
		}
	}	
	if( member_array(skill,skill2)!=-1 )	
	{
		for(i=0;i<sizeof(skill1);i++)
		{
			if( me->query_skill(skill1[i],2)>0 )
			{
				tell_object(me,CYN+name()+CYN"说道：你既已学了"NOR HIC"「"+to_chinese(skill1[i])+"」"NOR CYN"，本尊者就不教你"HIC"「"+to_chinese(skill)+"」"NOR CYN"了。\n"NOR);	
				return 1;
			}	
		}
	}	
	return 0;		
}

mixed ask_class()
{
	string str;
	object guai,me = this_player();
	if( (string)me->query("class")=="bonze" )
		return "阿弥陀佛，何来扰我？";
	if( me->query("family/putuo_class_succ") )
	{
		EMOTE_D->do_emote(this_object(), "smile",geteuid(me),CYN,0,0,0);
		return "不错不错。";
	}
	if( objectp(guai=me->query("family/putuo_class_guai")) )
		return "阿弥陀佛，此去开封，效果如何？";
	guai = new("/quest/family/putuo/npc/putuo_class");	
	if( guai->information(me) )
	{
		str = guai->query("name");
		str = sprintf("%s",str[0..1]);
		str = "近有开封"+str+"氏，其人性劣，你去将之度入沙门。";
		return str;
	}
	return 0;
}