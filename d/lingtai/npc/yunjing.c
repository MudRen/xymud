  // worker.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
void create()
{
        set_name("云静", ({"yun jing", "yun"}));
        set_level(44);
        set("gender", "男性" );
        set("age", 33);
        set("long", "方寸山三星洞第三代弟子中的杰出人物．\n");
        set("attitude", "peaceful");
	set("class", "taoist");
        create_family("方寸山三星洞", 3, "弟子");
        set("eff_dx", 30000);
        set("nkgain", 200);
        set_skill("unarmed",440);
        set_skill("dodge",440);
        set_skill("parry",440);
        set_skill("spells",440);  
        set_skill("dao",440);
        set_skill("literate",440);
        set_skill("stick",440);  
        set_skill("qianjun-bang",440);
        set_skill("puti-zhi",440);  
        set_skill("jindouyun",440);
        set_skill("dodge",440);  
        set_skill("force",440);   
        set_skill("wuxiangforce",440);
        map_skill("spells", "dao");
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        map_skill("stick", "qianjun-bang");
        map_skill("parry", "qianjun-bang");
        map_skill("dodge", "jindouyun");
        set("force_factor",200);
        set("mana_factor",200);
        setup();
        carry_object(0,"stick",random(5))->wield();
        carry_object(0,"shoes",random(5))->wear();
        carry_object(0,"cloth",random(5))->wear();
        carry_object(0,"pifeng",random(5))->wear();
        carry_object(0,"ring",random(5))->wear();
	powerup(0,1);
}

void attempt_apprentice(object ob)
{
        if( ob->query("class")=="bonze" )
        {
		EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：我们方寸山虽是有教无类，但是偏偏不收秃驴！哼！\n"NOR);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们方寸山发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","三星洞方寸山又多了一个弟子  "+ob->name(1)+HIW"\n                                 方寸山的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "taoist");
}