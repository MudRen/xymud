// worker.c
#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;
void create()
{
        set_name("云霄", ({"yun xiao", "yun"}));
        set_level(43);
        set("gender", "男性" );
        set("age", 33);
        set("long",
"方寸山三星洞第三代弟子中的杰出人物。
在场边转来转去发些牢骚。\n");
	set("class", "taoist");

        set("attitude", "peaceful");
        create_family("方寸山三星洞", 3, "弟子");
        set_skill("unarmed", 430);
        set_skill("dodge", 430);
        set_skill("parry", 430);
        set_skill("spells", 430);  
        set_skill("dao", 430);
        set_skill("literate", 430);
        set_skill("stick", 430);  
        set_skill("puti-zhi", 430);  
        set_skill("jindouyun", 430);
        set_skill("dodge", 430);  
        set_skill("force", 430);   
        set_skill("wuxiangforce", 430);
        map_skill("spells", "dao");
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        map_skill("dodge", "jindouyun");
	map_skill("stick","qianjun-bang");
        set("force_factor", 220);
        set("mana_factor", 150);
        setup();
        carry_object(0,"cloth",random(2))->wear();
        carry_object(0,"stick",random(2))->wield();
        carry_object(0,"shoes",random(2))->wear();
        carry_object(0,"hand",random(2))->wear();
        carry_object(0,"pifeng",random(2))->wear();        
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