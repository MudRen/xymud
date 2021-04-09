// worker.c
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("老道士", ({"laodao"}));
        set_level(16);
        set("gender", "男性" );
        set("age", 73);
        set("long", "一位老道士，眉毛和胡子都白了．\n");
	create_family("方寸山三星洞", 4, "弟子");
	set("attitude", "peaceful");
        set_skill("unarmed", 130);
        set_skill("dodge", 160);
        set_skill("parry", 130);
        set_skill("literate", 140);
        set_skill("puti-zhi", 120);  
        set_skill("force", 160);   
        set_skill("wuxiangforce", 160);
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        set("per", 30);
        set("force_factor", 2);
        setup();
        carry_object("/d/lingtai/obj/cloth")->wear();
	delete("title");
}

int accept_object(object me,object ob)
{	
	object who;
        who=this_player();

        if( ob->query("id")=="songguo" && who->query("family/family_name")=="方寸山三星洞"
         && !userp(ob) ) 
        {
        	if( time()<query("gived")+1800 )
        	{
        		write(CYN"老道士说道：刚刚给过人了，你待会再来。\n"NOR);
        		return 0;
        	}
		write("老道士高兴的胡子都翘起来了，说：这可是好东西呀！\n");
		set("gived",time());
		carry_object("/d/obj/book/stickbook");
                command("give piece to " + who->query("id"));
		return 1;
	}
	return 0;
}
