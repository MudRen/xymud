//modified by vikee for xlqy-zq station
//2000-12-2 1:34
inherit NPC;
#include <ansi.h>
 
void create()
{
 
	set_name("李靖", ({ "li jing", "jing", "li" }) );
	set_level(150);
	set("gender", "男性" );
	set("long", "托塔李天王乃是天界元帅，麾下十万天兵天将，法力无边。\n");
	set("age",40);
	set("title", "托塔天王");
	set("class", "xian");
	set("attitude", "heroism");
	set("force_factor", 500);
	set("mana_factor", 550);

	set("eff_dx", 600000);
	set("nkgain", 600);

	set_skill("spells", 1280);
        set_skill("dao", 1250);
        set_skill("unarmed", 1300);
        set_skill("yinfeng-zhua", 1250);
        set_skill("dodge", 1280);
        set_skill("blade", 1280);
        set_skill("kugu-blade", 1280);
        set_skill("yaofa", 1300);
        set_skill("lingfu-steps", 1280);
        set_skill("parry", 1280);
        set_skill("force", 1280);
        set_skill("huntian-qigong", 1280);
//        set_skill("blade", 1280);
        set_skill("sword", 1300);
        set_skill("qixiu-jian", 1280);
        map_skill("spells", "dao");
        map_skill("unarmed", "yinfeng-zhua");
        map_skill("parry", "kugu-blade");
        map_skill("sword", "qixiu-jian");
        map_skill("dodge", "lingfu-steps");
        map_skill("force", "huntian-qigong");
	
        create_family("陷空山无底洞", 1, "弟子");
	set("chat_chance",1);
	set("chat_msg", ({
                  name()+"说道：玉鼠这个小妖精跑哪里去了？\n",
		    }));
	setup();
	carry_object("/d/obj/fabao/huangjin-baota");
	carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/sky/obj/zhanyaojian")->wield();
}